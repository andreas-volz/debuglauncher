#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <string>
#include <vector>

/* EFL */
#include <ecorexx/Ecorexx.h>

class DbgApplication
{
public:
  DbgApplication()
  {
    terminal = false;
    debugger = false;
    mExePtr = NULL;
  }

  std::string name;
  std::string command;
  std::string parameter;
  bool terminal;
  bool debugger;
  Ecorexx::Exe *mExePtr;
};

class Preferences
{
public: // Singleton
  static Preferences& instance();

private: // Singleton
  Preferences() {}
  Preferences(const Preferences&);
  Preferences(Preferences&);
  virtual ~Preferences() {}
  void operator = (Preferences&);
  
public:
  void init();

  std::vector<DbgApplication> dbg_applications;
  
private:
  
};

#endif // PREFERENCES_H
