#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include "searchFile.h"
#include "Exceptions.h"

/* to get home dir */
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

/// some system specific defines
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#  define PATH_SEPARATOR string("\\")
#else
#  define PATH_SEPARATOR string("/")
#endif

#define DATA_THEME_DIR "themes/"

using namespace std;

const std::string searchEdjeFile(const std::string &theme)
{
  vector <string> name_vector;
  
#ifdef HAVE_CONFIG_H 
  name_vector.push_back(string(PACKAGE_DATA_DIR "/" DATA_THEME_DIR) + theme);
  name_vector.push_back(string(PACKAGE_SOURCE_DIR) + "/data/" DATA_THEME_DIR + theme);
#endif

  name_vector.push_back(DATA_THEME_DIR + theme);
  
  const string &file = searchFile(name_vector);

  if (file.empty())
  {
    throw FileNotFoundException(theme);
  }

  return file;
}

const std::string searchPixmapFile(const std::string &pixmap)
{
  vector <string> name_vector;

#ifdef HAVE_CONFIG_H  
  name_vector.push_back(string(PACKAGE_PIXMAPS_DIR) + "/" + pixmap);
  name_vector.push_back(string(PACKAGE_SOURCE_DIR) + "/pixmaps/" + pixmap);
#endif

  name_vector.push_back("pixmaps/" + pixmap);

  const string &file = searchFile(name_vector);
  
  if (file.empty())
  {
    throw FileNotFoundException(pixmap);
  }
  
  return file;
}

const std::string searchDataFile(const std::string &data)
{
  vector <string> name_vector;

#ifdef HAVE_CONFIG_H  
  name_vector.push_back(string(PACKAGE_DATA_DIR) + "/" + data);
  name_vector.push_back(string(PACKAGE_SOURCE_DIR) + "/data/" + data);
#endif

  name_vector.push_back("data/" + data);

  const string &file = searchFile(name_vector);
  
  if (file.empty())
  {
    throw FileNotFoundException(data);
  }
  
  return file;
}

const std::string searchFile(std::vector <std::string> &name_vector)
{
  struct stat buf;

  for (unsigned int i = 0; i < name_vector.size(); i++)
  {
    string &try_name = name_vector[i];

    bool found = !(stat(try_name.c_str(), &buf));
    //cout << "try_name: " << try_name << endl;

    if (found)
    {
      return try_name;
    }
  }

  return "";
}

const std::string getHomeDir()
{
#if defined(__APPLE__) && defined(__MACH__)
    return getCurrentUserHomeFolderPath() + "/"; // call of MACFileUtils
#endif

#ifndef _WIN32
  uid_t uid;
  struct passwd *pass;

  uid = getuid();
  pass = getpwuid (uid);

  return string(pass->pw_dir) + PATH_SEPARATOR;
#else // _WIN32

  HINSTANCE hinstLib;
  MYPROC ProcAdd;
  BOOL fFreeResult, fRunTimeLinkSuccess = FALSE;
  TCHAR szPath[MAX_PATH];

  /* Get a handle to the DLL module. */
  hinstLib = LoadLibrary("shfolder");

  /* If the handle is valid, try to get the function address. */
  if (hinstLib != NULL)
  {
    ProcAdd = (MYPROC) GetProcAddress(hinstLib, "SHGetFolderPathA");


    /* If the function address is valid, call the function. */
    if (NULL != ProcAdd)
    {
      fRunTimeLinkSuccess = TRUE;
      ProcAdd (NULL,
               CSIDL_PERSONAL, /* Test CSIDL_FLAG_CREATE !! */
               NULL,
               0,
               szPath);
    }

    /* Free the DLL module. */
    fFreeResult = FreeLibrary(hinstLib);
  }

  /* If unable to call the DLL function, use an alternative. */
  if (! fRunTimeLinkSuccess)
  {
    /* later use getWindir?? or something else as fallback */
    return string ("c:\\");
  }

  return string (string(szPath) + "\\");
#endif // _WIN32
}

/* Return the Users Working directory where the load and save dialog should be
   point to. On Linux and Window this will be the same as getHomeDir() but
   on a OS X Box this will point to the Users Desktop because it is not common
   to store files which are supposed for further processing on the users home
   dir. */
const string getUserWorkDir()
{
#if defined(__APPLE__) && defined(__MACH__)
    return getUsersDocumentsFolderPath() + "/";
#else
    return getHomeDir();
#endif
}
