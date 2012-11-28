#ifndef SETTINGS_H
#define SETTINGS_H

#include <elementaryxx/Elementaryxx.h>

#include "Preferences.h"

class Settings : public Elmxx::Window
{
public:

  static Settings* factory(int i);
  static Settings* factory(Evasxx::Object &parent, int i);

  void newWindow();
  
  void ok_bt(Evasxx::Object &obj, void *event_info);

protected:
  Settings(const std::string &name, Elm_Win_Type type, int i);
  Settings(Evasxx::Object &parent, const std::string &name, Elm_Win_Type type, int i);
  
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
};

#endif // SETTINGS_H
