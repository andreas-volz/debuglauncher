#ifndef MAIN_H
#define MAIN_H

/* EFL */
#include <evasxx/Evasxx.h>
#include <elementaryxx/Elementaryxx.h>
#include <eflxx/CountedPtr.h>

#include "SettingsWindow.h"
#include "XMLLoader.h"
#include "XMLWriter.h"

class Main
{
public:
  Main(int argc, char **argv);
  ~Main();

  int run();
  void quit();

  void updateGUI();

private:
  void click_settings_bt(Evasxx::Object &obj, void *event_info, int i);
  void run_process(Evasxx::Object &obj, void *event_info, Elmxx::Check *ck, int i);
  void my_win_del(Evasxx::Object &obj, void *event_info);
  bool delSignalHandler(int type, void *event);

  Logger mLogger;
  
  int mArgc;
  char **mArgv;

  Eflxx::CountedPtr<Elmxx::Application> elmApp;
  Settings *mSettings;
  XMLLoader xmlLoader;
  XMLWriter xmlWriter;
  Eflxx::CountedPtr<Ecorexx::Event> mEcoreExeDelEvent;
  sigc::slot<bool, int, void*> delSlot;
  std::vector<Elmxx::Check*> mCheckList;
  std::vector<Elmxx::Button*> mButtonList;
};

#endif // MAIN_H
