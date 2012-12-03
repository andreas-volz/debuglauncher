#ifndef SETTINGS_H
#define SETTINGS_H

#include <elementaryxx/Elementaryxx.h>

#include "Preferences.h"

/* forward declarations */
class Main;

class Settings : public Elmxx::Window
{
public:

  static Settings* factory(int i, Main *mainApp);
  static Settings* factory(Evasxx::Object &parent, int i, Main *mainApp);

  void newWindow();
  
  void ok_bt(Evasxx::Object &obj, void *event_info);

protected:
  Settings(const std::string &name, Elm_Win_Type type, int i, Main *mainApp);
  Settings(Evasxx::Object &parent, const std::string &name, Elm_Win_Type type, int i, Main *mainApp);
  
private:
  Settings (); // forbid standard constructor
  virtual ~Settings (); // forbid direct delete -> use Object::destroy()
  Settings (const Settings&); // forbid copy constructor

  int mNumber;
  Elmxx::Entry *mEtName;
  Elmxx::Entry *mEtCommand;
  Elmxx::Entry *mEtParameter;
  Elmxx::Check *mCkTerminal;
  Elmxx::Check *mCkDebugger;
  Main *mMainApp;
};

#endif // SETTINGS_H
