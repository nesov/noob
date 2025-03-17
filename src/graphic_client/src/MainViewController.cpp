
#include "MainViewController.h"
#include "AppConsts.h"

inline void MainViewController::addMenuOptionsArray(std::vector<std::string>& m_dropdownOptions) {
	for (auto &option : m_dropdownOptions)
		m_selectTaskDropDown -> add(option.c_str());
}

inline void MainViewController::onConnectButtonClicked(Fl_Widget *widget, void *user_data) {
	std::string input_val = m_inputField->value();
	int type = getSelectedTaskType();
	if (!input_val.empty()) {
		m_buff -> append(("\nMe: " + input_val + '\n').c_str());
		clearInput();
		m_buff -> append(("Server: " + composeMessageAndSend(type, input_val) + '\n').c_str());
		scrollFeed();
	}
}

inline void MainViewController::clearInput() { m_inputField->value(""); }

inline void MainViewController::scrollFeed() {
	int totalLines = m_messagesFeed -> count_lines(0, m_buff -> length(), true);
	m_messagesFeed -> scroll(totalLines, 0);
	m_messagesFeed -> redraw();
}

inline int MainViewController::getSelectedTaskType() {
	std::string selected = m_selectTaskDropDown->value();
	for (int i = 0; i < m_dropdownOptions.size(); i++) {
		if (selected == m_dropdownOptions[i]) {
			return i;
		}
		else if (selected == m_dropdownOptions[3]) {
			return 4;
		}
	}
	return 99;
}

std::string MainViewController::composeMessageAndSend(int task, std::string &text) {
	if (task < 0){
		return "Task number can't be negative.";
	}
	Message message;
	message.setType(static_cast<MessageType>(task));
	message.setData(text.c_str());
	Message fromServ;

	if (m_network->start()) {
		if (m_network -> isConnected()) {
			m_network -> sendMessage(message);
			fromServ = m_network->receiveMessage();
			m_network -> stop();
		}
		else {
			m_network -> stop();
			return "Message is not send due to connecting issues.";
		}
	} else {
		return "Message is not sent due to connecting issues, Make sure the server is running.";
	}
	return fromServ.getData();
}

inline void MainViewController::onExitButtonClicked(Fl_Widget *widget, void *user_data) {
	auto *input = static_cast<MainViewController*>(user_data);
	Fl::delete_widget(input -> m_mainWindow);
	exit(0);
}

MainViewController::MainViewController(INetworkService *service) {
	if (service) {
		m_network = service;
	}
	Draw();
}

MainViewController::~MainViewController() {
	delete m_mainWindow;
	delete m_connectButton;
	delete m_exitButton;
	delete m_messagesFeed;
	delete m_inputField;
	delete m_selectTaskDropDown;
}

void MainViewController::Draw() {
	m_mainWindow = new Fl_Double_Window(200, 200, 548, 508, kAppName.c_str());
	m_mainWindow -> user_data(static_cast<void *>(this));

	{
		m_connectButton = new Fl_Button(355, 455, 80, 30, "Send");
		m_connectButton -> tooltip("Click to send");
		m_connectButton -> down_box(FL_DOWN_BOX);
		m_connectButton -> color(FL_LIGHT1);
		m_connectButton -> selection_color(FL_LIGHT1);
		m_connectButton -> callback([](Fl_Widget *widget, void *data) {
            auto *instance = static_cast<MainViewController*>(data);
            instance -> onConnectButtonClicked(widget, data); }, this);
	}

	{
		m_exitButton = new Fl_Button(445, 455, 80, 30, "Exit");
		m_exitButton -> down_box(FL_DOWN_BOX);
		m_exitButton -> callback([](Fl_Widget *widget, void *data) {
            auto *instance = static_cast<MainViewController*>(data);
            instance -> onExitButtonClicked(widget, data); }, this);
	}

	{
		m_buff = new Fl_Text_Buffer();
		m_messagesFeed = new Fl_Text_Display(10, 35, 525, 310);
		m_messagesFeed -> wrap_mode(1, 0);
		m_messagesFeed -> buffer(m_buff);
	}

	{
		m_inputField = new Fl_Multiline_Input(10, 372, 525, 68);
		m_inputField -> align(Fl_Align(292));
	}

	{
		m_selectTaskDropDown = new Fl_Input_Choice(125, 456, 220, 27, "Select task: ");
		m_selectTaskDropDown -> add("Select Items");
		addMenuOptionsArray(m_dropdownOptions);
		m_selectTaskDropDown -> value(0);
	}

	m_mainWindow->end();
	m_mainWindow->show();
}
