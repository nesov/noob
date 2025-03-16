
#include "MainViewController.h"
#include "AppConsts.h"


inline void MainViewController::printMessageHistory(vector* m_messages ) {
  std::string result;
  for (auto& message : *m_messages)
    result += message +"\n";
  m_messagesFeed -> value(result.c_str());
}

inline void MainViewController::addMenuOptionsArray(vector* m_dropdownOptions) {
  for(auto& option: *m_dropdownOptions)
    m_selectTaskDropDown -> add(option.c_str());
}

inline void MainViewController::onConnectButtonClicked(Fl_Widget* widget,void* user_data) {
  std::string input_val = m_inputField -> value();
  int type = getSelectedTaskType();
  if (!input_val.empty()) {
    m_messages.push_back(input_val);
    m_inputField -> value("");
    m_messages.push_back(composeMessageAndSend(type, input_val));
    printMessageHistory(&m_messages);
  }
}

int MainViewController::getSelectedTaskType(){
  std::string selected = m_selectTaskDropDown -> value();

  if (selected == m_dropdownOptions[0]) 
    return 0;
  if (selected == m_dropdownOptions[1])
    return 1; 
  if (selected == m_dropdownOptions[2]) 
    return 2;
  if (selected== m_dropdownOptions[3])
    return 4; 

  return 0;
}

std::string MainViewController::composeMessageAndSend(int task, std::string& text) {
  if (task < 0){
      return "Task number can't be negative.";
  }
  Message message;
  message.setType(static_cast<MessageType>(task));
  message.setData(text.c_str()); 
  Message fromServ;

  if (m_network -> start()){
    if (m_network -> isConnected()){
        m_network -> sendMessage(message);
        fromServ = m_network -> receiveMessage();
        m_network -> stop();
    } else {  
      return "Message is not send due to connecting issues.";
    }
  } else {
      return "Message is not sent due to connecting issues, Make sure the server is running.";
  }
  return fromServ.getData();
}


// inline void MainViewController::onSelectOptionClicked(Fl_Widget* widget, void* user_data){
//     auto* field = static_cast<Fl_Input_Choice*> (widget);
//     if ( strcmp((field -> value()), "Select Items")) {
//       m_inputField -> value((field -> value()));
//     }
// }

inline void MainViewController::onExitButtonClicked(Fl_Widget* widget, void* user_data) {
    auto* input = static_cast<MainViewController*>(user_data);
    Fl::delete_widget(input -> m_mainWindow);
    exit(0);
}

// MainViewController::MainViewController(){
//   Draw();
// }

MainViewController::MainViewController(INetworkService* service) {
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
    m_mainWindow = new Fl_Double_Window(100,100 ,548, 508, kAppName.c_str());
    m_mainWindow -> user_data(static_cast<void*>(this));

    { 
        Fl_Group* group1 = new Fl_Group(350, 450, 180, 40);
        { 
          m_connectButton = new Fl_Button(355, 455, 80, 30, "Send");
          m_connectButton -> tooltip("Click to send");
          m_connectButton -> down_box(FL_DOWN_BOX);
          m_connectButton -> color(FL_LIGHT1);
          m_connectButton -> selection_color(FL_LIGHT1);
          m_connectButton -> callback([](Fl_Widget* widget, void* data) {
            auto *instance = static_cast<MainViewController*>(data);
            instance -> onConnectButtonClicked(widget, data);
          },this);
        }
    
        { 
          m_exitButton = new Fl_Button(445, 455, 80, 30, "Exit");
          m_exitButton -> down_box(FL_DOWN_BOX);
          m_exitButton -> callback([](Fl_Widget* widget, void* data){
            auto *instance = static_cast<MainViewController*>(data);
            instance -> onExitButtonClicked(widget, data);
          },this);
        }
        group1 -> end();
    }

    { 
      Fl_Group* group2 = new Fl_Group(5, 25, 535, 415);
      { 
        m_messagesFeed = new Fl_Multiline_Output (10, 35, 525, 310);
      }
      
      { 
        m_inputField = new Fl_Multiline_Input(10, 372, 525, 68);
        m_inputField -> align(Fl_Align(292));
      } 
      group2 -> end();
    }

    { 
      Fl_Group* group3 = new Fl_Group(25, 455, 325, 60);
      { 
        m_selectTaskDropDown = new Fl_Input_Choice(125, 456, 220, 27, "Select task: ");
        m_selectTaskDropDown -> add("Select Items");
        addMenuOptionsArray(&m_dropdownOptions);
        // m_selectTaskDropDown -> callback([](Fl_Widget* widget, void* user_data){
        //   auto* instance = static_cast<MainViewController*>(user_data);
        //   instance -> onSelectOptionClicked(widget, user_data);
        // },this);
        m_selectTaskDropDown -> value(0);
      } 
      group3 -> end();
    }
    m_mainWindow -> end();
    m_mainWindow -> show();
}
