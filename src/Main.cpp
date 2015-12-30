#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* log4cxx */
#ifdef HAVE_LOG4CXX
#include "log4cxx/logger.h"
#include "log4cxx/basicconfigurator.h"
#include "log4cxx/propertyconfigurator.h"
#include "log4cxx/helpers/exception.h"
#endif // HAVE_LOG4CXX

/* EFL */
#include <ecorexx/Ecorexx.h>

#include "Main.h"
#include "searchFile.h"
#include "Preferences.h"
#include "Logger.h"

using namespace std;
using namespace Eflxx;
using namespace Elmxx;

#ifdef HAVE_LOG4CXX
using namespace log4cxx;
using namespace log4cxx::helpers;
#endif // HAVE_LOG4CXX

// main function only to run Main class
int main(int argc, char **argv)
{
  Main mainloop(argc, argv);
  return mainloop.run();
}

Main::Main(int argc, char **argv) :
  mLogger("DebugLauncher.Main"),
  mArgc(argc),
  mArgv(argv),
  elmApp(NULL)
{
#ifdef HAVE_LOG4CXX
  //BasicConfigurator::configure ();
  PropertyConfigurator::configure(searchDataFile("logging.prop"));
#endif // HAVE_LOG4CXX

  Preferences &preferences = Preferences::instance ();
  preferences.init ();
}

Main::~Main()
{
}

int Main::run()
{ 
  elmApp = CountedPtr<Elmxx::Application>(new Application(mArgc, mArgv));
  Theme mytheme;
  Icon *icSettings = NULL;
  Button *btSettings = NULL;
  Button *bt = NULL;
  Check *ck = NULL; 

  delSlot = sigc::mem_fun(*this, &Main::delSignalHandler);
  
  mEcoreExeDelEvent = CountedPtr<Ecorexx::Event>(new Ecorexx::Event(ECORE_EXE_EVENT_DEL, delSlot));

  Preferences &preferences = Preferences::instance ();

  xmlLoader.load(getUserWorkDir() + ".debuglauncher/applications.xml");

  Window *win = Window::factory("table", ELM_WIN_BASIC);
  win->setTitle("DebugLauncher");
  win->setAutoDel(true);
  win->getEventSignal("delete,request")->connect(sigc::mem_fun(this, &Main::my_win_del));

  mytheme.addExtension(searchEdjeFile("debuglauncher_check.edj"));

  Background *bg = Background::factory(*win);
  win->addResizeObject(*bg);
  bg->setSizeHintWeight(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bg->show();

  Table *tb = Table::factory(*win);
  win->addResizeObject(*tb);
  tb->setSizeHintWeight(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  tb->show();

  unsigned int i = 0;
  for (std::vector<DbgApplication>::iterator app_it = preferences.dbg_applications.begin(); app_it != preferences.dbg_applications.end(); ++app_it)
  {
    DbgApplication &dbg_app = *app_it;

    icSettings = Icon::factory(*win);
    icSettings->setStandard("preferences-system");
    icSettings->setSizeHintWeight(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    icSettings->setSizeHintAlign(EVAS_HINT_FILL, EVAS_HINT_FILL);
    icSettings->setSizeHintMin(Eflxx::Size(35, 35));
    icSettings->show();

    btSettings = Button::factory(*win);
    btSettings->setSizeHintWeight(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    btSettings->setSizeHintAlign(EVAS_HINT_FILL, EVAS_HINT_FILL);
    btSettings->setContent (*icSettings);
    tb->pack(*btSettings, Rect(0, i, 1, 1));
    btSettings->show();  
    btSettings->getEventSignal("clicked")->connect(sigc::bind(sigc::mem_fun(this, &Main::click_settings_bt), i));

    bt = Button::factory(*win);
    bt->setText(dbg_app.name);
    bt->setSizeHintWeight(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
    bt->setSizeHintAlign(EVAS_HINT_FILL, EVAS_HINT_FILL);
    tb->pack(*bt, Rect(1, i, 1, 1));
    mButtonList.push_back(bt);
    bt->show();

    ck = Check::factory(*win);
    tb->pack(*ck, Rect(2, i, 1, 1));
    ck->setStyle("lamp");
    ck->setState(false);
    ck->setDisabled(true);
    ck->show();
    mCheckList.push_back(ck);
    bt->getEventSignal("clicked")->connect(sigc::bind(sigc::mem_fun(this, &Main::run_process), ck, i));

    ++i;
  }
  
  win->show();

  elmApp->run();

  return 0;
}

void Main::updateGUI()
{
  Preferences &preferences = Preferences::instance ();

  unsigned int i = 0;
  for (std::vector<DbgApplication>::iterator app_it = preferences.dbg_applications.begin(); app_it != preferences.dbg_applications.end(); ++app_it)
  {
    DbgApplication &dbg_app = *app_it;

    mCheckList[i]->setState((dbg_app.mPid == -1)? false : true);
    mButtonList[i]->setText(dbg_app.name);
    
    ++i;
  }
}

void Main::quit()
{
  //BUG: disabled, because defect
  //xmlWriter.write(getUserWorkDir() + ".debuglauncher/applications.xml");
  
  Elmxx::Application::exit();
}

bool Main::delSignalHandler(int type, void *event)
{
  Preferences &preferences = Preferences::instance ();
  Ecore_Exe_Event_Del *delEvent = static_cast<Ecore_Exe_Event_Del*>(event);
  
  for (std::vector<DbgApplication>::iterator app_it = preferences.dbg_applications.begin(); app_it != preferences.dbg_applications.end(); ++app_it)
  {
    DbgApplication &dbg_app = *app_it;

    if(dbg_app.mPid == delEvent->pid)
    {
      dbg_app.mPid = -1;
      delete dbg_app.mExePtr;
      dbg_app.mExePtr = NULL;
    }
  }

  updateGUI();
  
  cout << "process exit" << endl;
  return true;
}

void Main::my_win_del(Evasxx::Object &obj, void *event_info)
{
  quit();
}

void Main::click_settings_bt(Evasxx::Object &obj, void *event_info, int i)
{
  mSettings = Settings::factory(i, this);
}

void Main::run_process(Evasxx::Object &obj, void *event_info, Check *ck, int i)
{
  Preferences &preferences = Preferences::instance ();
  
  DbgApplication &dbg_app = preferences.dbg_applications[i];
  
  if (ck->getState())
  {
    if (dbg_app.mExePtr)
    {
      LOG4CXX_TRACE(mLogger, "Try to kill process: " << dbg_app.command);
      
      dbg_app.mExePtr->kill();  
    }
  }
  else
  {
    string exe_command;

    if (dbg_app.terminal)
    {
      exe_command += "xterm -hold -e "; 
    }
    
    if (dbg_app.debugger)
    {
      exe_command = "nemiver "; 
    }

    exe_command += dbg_app.command + " " + dbg_app.parameter;
    
    
    dbg_app.mExePtr = new Ecorexx::Exe(exe_command, NULL);    
    dbg_app.mPid = dbg_app.mExePtr->getPid();
  }

  updateGUI();
}

