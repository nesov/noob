#pragma once 

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input_Choice.H>

#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Multiline_Output.H>

#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Text_Buffer.H>

#include <string>
#include <vector>

#include "IViewController.h"
#include "ssapi/INetworkService.h"


class MainViewController : public IViewController {
  // using vector =  std::vector<std::string>;

  public:
    MainViewController() = delete;
    MainViewController(INetworkService* service);

    ~MainViewController() override;
    void Draw() override;

  private:
    INetworkService* m_network; 

    Fl_Double_Window            *m_mainWindow;
    Fl_Button                   *m_connectButton;
    Fl_Button                   *m_exitButton;
    Fl_Text_Display             *m_messagesFeed;
    Fl_Text_Buffer              *m_buff; 


    Fl_Multiline_Input          *m_inputField;
    Fl_Input_Choice             *m_selectTaskDropDown;
    std::vector<std::string>    m_dropdownOptions = {
      "Echo 0", 
      "Task 1",
      "Task 2",
      "Task 4"
    };
  
    void addMenuOptionsArray(std::vector<std::string>& m_dropdownOptions);
    void scrollFeed();
    void clearInput();
    
    int getSelectedTaskType();
    std::string composeMessageAndSend (int task, std::string &text);
    
   
    void onConnectButtonClicked (Fl_Widget* widget, void* user_data);
  
    void onExitButtonClicked(Fl_Widget *widget, void *user_data);
};
