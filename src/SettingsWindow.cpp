#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "SettingsWindow.h"

using namespace std;
using namespace Eflxx;
using namespace Elmxx;

Settings::Settings(const std::string &name, Elm_Win_Type type, int i) :
  Window(name, type),
  mNumber (i)
{
  newWindow();
}

Settings::Settings(Evasxx::Object &parent, const std::string &name, Elm_Win_Type type, int i) :
  Window(parent, name, type),
  mNumber (i)
{
  newWindow();
}

Settings::~Settings()
{

}

Settings* Settings::factory(int i)
{
  return new Settings("settings", ELM_WIN_BASIC, i);
}

Settings* Settings::factory(Evasxx::Object &parent, int i)
{
  return new Settings(parent, "settings", ELM_WIN_BASIC, i);
}

void Settings::newWindow()
{
  Preferences &preferences = Preferences::instance ();
  
  DbgApplication &dbg_app = preferences.dbg_applications[mNumber];
  
  Window *win = this;
  win->setTitle(dbg_app.name + " Settings");
  win->setAutoDel(true);

  Label *lb = NULL;
  mEtName = NULL;
  mEtCommand = NULL;
  mEtParameter = NULL;
  mCkTerminal = NULL;
  mCkDebugger = NULL;

  Background *bg = Background::factory(*win);
  win->addResizeObject(*bg);
  bg->setSizeHintWeight(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bg->setSizeHintMin(Eflxx::Size(400, 50));
  bg->show();

  Box *bx = Box::factory(*win);
  win->addResizeObject(*bx);
  bx->setSizeHintWeight(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bx->setSizeHintAlign(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bx->setOrientation(Box::Vertical);
  bx->show();

  Table *tb = Table::factory(*win);
  bx->packEnd(*tb);
  tb->setSizeHintWeight(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  tb->setSizeHintAlign(EVAS_HINT_FILL, EVAS_HINT_FILL);
  tb->show();

  lb = Label::factory(*win);
  lb->setSizeHintWeight(0.1, EVAS_HINT_EXPAND);
  lb->setSizeHintAlign(0, 0);
  lb->setSizeHintPadding(Eflxx::Padding(10, 10, 10, 10));
  lb->setText("Name:");
  tb->pack(*lb, Rect(0, 0, 1, 1));
  lb->show();

  mEtName = Entry::factory(*win);
  mEtName->setSizeHintWeight(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  mEtName->setSizeHintAlign(EVAS_HINT_FILL, EVAS_HINT_FILL);
  mEtName->setSizeHintPadding(Eflxx::Padding(10, 10, 10, 10));
  mEtName->setScrollable(true);
  mEtName->setSingleLine(true);
  mEtName->setText(dbg_app.name);
  tb->pack(*mEtName, Rect(1, 0, 1, 1));
  mEtName->show();

  lb = Label::factory(*win);
  lb->setSizeHintWeight(0.1, EVAS_HINT_EXPAND);
  lb->setSizeHintAlign(EVAS_HINT_FILL, EVAS_HINT_FILL);
  lb->setSizeHintPadding(Eflxx::Padding(10, 10, 10, 10));
  lb->setText("Command:");
  tb->pack(*lb, Rect(0, 1, 1, 1));
  lb->show();

  mEtCommand = Entry::factory(*win);
  mEtCommand->setSizeHintWeight(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  mEtCommand->setSizeHintAlign(EVAS_HINT_FILL, EVAS_HINT_FILL);
  mEtCommand->setSizeHintPadding(Eflxx::Padding(10, 10, 10, 10));
  mEtCommand->setSizeHintMin(Eflxx::Size(50, 0));
  mEtCommand->setScrollable(true);
  mEtCommand->setSingleLine(true);
  mEtCommand->setText(dbg_app.command);
  tb->pack(*mEtCommand, Rect(1, 1, 1, 1));
  mEtCommand->show();

  lb = Label::factory(*win);
  lb->setSizeHintWeight(0.1, EVAS_HINT_EXPAND);
  lb->setSizeHintAlign(EVAS_HINT_FILL, EVAS_HINT_FILL);
  lb->setSizeHintPadding(Eflxx::Padding(10, 10, 10, 10));
  lb->setText("Parameter:");
  tb->pack(*lb, Rect(0, 2, 1, 1));
  lb->show();

  mEtParameter = Entry::factory(*win);
  mEtParameter->setSizeHintWeight(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  mEtParameter->setSizeHintAlign(EVAS_HINT_FILL, EVAS_HINT_FILL);
  mEtParameter->setSizeHintPadding(Eflxx::Padding(10, 10, 10, 10));
  mEtParameter->setSizeHintMin(Eflxx::Size(50, 0));
  mEtParameter->setScrollable(true);
  mEtParameter->setSingleLine(true);
  mEtParameter->setText(dbg_app.parameter);
  tb->pack(*mEtParameter, Rect(1, 2, 1, 1));
  mEtParameter->show();

  mCkTerminal = Check::factory(*win);
  mCkTerminal->setSizeHintWeight(0.1, EVAS_HINT_EXPAND);
  mCkTerminal->setSizeHintAlign(EVAS_HINT_FILL, EVAS_HINT_FILL);
  mCkTerminal->setSizeHintPadding(Eflxx::Padding(10, 10, 10, 10));
  mCkTerminal->setText("Start with terminal");
  mCkTerminal->setState(dbg_app.terminal);
  tb->pack(*mCkTerminal, Rect(0, 3, 2, 1));
  mCkTerminal->show();

  mCkDebugger = Check::factory(*win);
  mCkDebugger->setSizeHintWeight(0.1, EVAS_HINT_EXPAND);
  mCkDebugger->setSizeHintAlign(EVAS_HINT_FILL, EVAS_HINT_FILL);
  mCkDebugger->setSizeHintPadding(Eflxx::Padding(10, 10, 10, 10));
  mCkDebugger->setText("Start with debugger");
  mCkDebugger->setState(dbg_app.debugger);
  tb->pack(*mCkDebugger, Rect(0, 4, 2, 1));
  mCkDebugger->show();

  Box *bx2 = Box::factory(*win);
  bx2->setSizeHintWeight(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bx2->setSizeHintAlign(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bx2->setOrientation(Box::Horizontal);
  bx->packEnd(*bx2);
  bx2->show();

  Button *bt = Button::factory(*win);
  bt->setText("OK");
  bt->setSizeHintWeight(EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
  bt->setSizeHintAlign(EVAS_HINT_FILL, EVAS_HINT_FILL);
  bx2->packEnd(*bt);
  bt->show();
  bt->getEventSignal("clicked")->connect(sigc::mem_fun(this, &Settings::ok_bt));

  win->show();
}

void Settings::ok_bt(Evasxx::Object &obj, void *event_info)
{
  Preferences &preferences = Preferences::instance ();
  
  DbgApplication &dbg_app = preferences.dbg_applications[mNumber];
  
  dbg_app.name = mEtName->getText();
  dbg_app.command = mEtCommand->getText();
  dbg_app.parameter = mEtParameter->getText();
  dbg_app.terminal = mCkTerminal->getState();
  dbg_app.debugger = mCkDebugger->getState();

  destroy();
}
