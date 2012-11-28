#ifndef MAIN_H
#define MAIN_H

#include <evasxx/Evasxx.h>
#include <elementaryxx/Elementaryxx.h>

#include "SettingsWindow.h"
#include "XMLLoader.h"
#include "XMLWriter.h"

class Main
{
public:
  Main(int argc, char **argv);

  int run();
  void quit();

private:
  void click_settings_bt(Evasxx::Object &obj, void *event_info, int i);
  void run_process(Evasxx::Object &obj, void *event_info, Elmxx::Check *ck, int i);
  void my_win_del(Evasxx::Object &obj, void *event_info);

  int mArgc;
  char **mArgv;

  Elmxx::Application *elmApp;
  Settings *mSettings;
  XMLLoader xmlLoader;
  XMLWriter xmlWriter;
};

#endif // MAIN_H
