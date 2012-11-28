#include "Preferences.h"

#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif

using namespace std;

Preferences& Preferences::instance()
{
  static Preferences g;
  return g;
}

void Preferences::init ()
{
}

