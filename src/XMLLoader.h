#ifndef XML_LOADER_H
#define XML_LOADER_H

/* STD */
#include <iostream>
#include <string>
#include <map>

/* XML */
#include <libxml++/libxml++.h>

/* local */
#include "Logger.h"

class XMLLoader
{
public:
  XMLLoader();
  ~XMLLoader();

  bool load(const std::string &file);

protected:
  void parseRootNode(const xmlpp::Node *node);

  void parseApplicationsNode(const xmlpp::Node *node);
  void parseApplicationNode(const xmlpp::Node *node);

private:
  Logger mLogger;

};

#endif // XML_LOADER_H