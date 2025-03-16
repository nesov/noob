#pragma once 

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
// #include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input_Choice.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Multiline_Output.H>

#include <string>
#include <vector>

#include "IViewController.h"
#include <FL/Fl_Text_Display.H>

#include "ssapi/INetworkService.h"


class MainViewController : public IViewController {
  using vector =  std::vector<std::string>;

  public:
    MainViewController() = delete;

    MainViewController(INetworkService* service);

    ~MainViewController() override;

  private:
    INetworkService* m_network; 

    Fl_Double_Window            *m_mainWindow;
    Fl_Button                   *m_connectButton;
    Fl_Button                   *m_exitButton;
    Fl_Multiline_Output         *m_messagesFeed;
    Fl_Multiline_Input          *m_inputField;
    Fl_Input_Choice             *m_selectTaskDropDown;

    std::vector<std::string>    m_messages;
    std::vector<std::string>    m_dropdownOptions = {
      "Echo 0", 
      "Task 1",
      "Task 2",
      "Task 4"
    };
  
    void Draw() override;

    void printMessageHistory          (vector* m_messages);
    void addMenuOptionsArray          (vector* m_dropdownOptions);
    std::string composeMessageAndSend (int task, std::string &text);
    int getSelectedTaskType();
    
    // void onSelectOptionClicked  (Fl_Widget* widget, void* user_data);
    void onConnectButtonClicked (Fl_Widget* widget, void* user_data);
    void onExitButtonClicked(Fl_Widget *widget, void *user_data);
};
