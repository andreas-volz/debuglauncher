#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

/* local */
#include "XMLLoader.h"
#include "searchFile.h"
#include "Preferences.h"

/* STD */
#include <cassert>

using namespace std;

XMLLoader::XMLLoader() :
  mLogger("dbg_launcher")
{
}

XMLLoader::~XMLLoader()
{
}

bool XMLLoader::load(const std::string &file)
{
  try
  {
    xmlpp::DomParser parser;
    parser.set_validate(false); // TODO enable again after writing DTD
    parser.set_substitute_entities();	// We just want the text to be resolved/unescaped automatically.
    parser.parse_file(file);
    if (parser)
    {
      // Walk the tree:
      const xmlpp::Node *pNode = parser.get_document()->get_root_node();	// deleted by DomParser.
      parseRootNode(pNode);


      return true;
    }
  }
  catch (const exception &ex)
  {
    LOG4CXX_FATAL(mLogger, "Exception caught: " << ex.what());
  }

  return false;
}

void XMLLoader::parseRootNode(const xmlpp::Node *node)
{
  const xmlpp::ContentNode *nodeContent = dynamic_cast < const xmlpp::ContentNode * >(node);
  const xmlpp::TextNode *nodeText = dynamic_cast < const xmlpp::TextNode * >(node);
  const xmlpp::CommentNode *nodeComment = dynamic_cast < const xmlpp::CommentNode * >(node);

  if (nodeText && nodeText->is_white_space())	//Let's ignore the indenting
    return;

  Glib::ustring nodename = node->get_name();

  if (!nodeText && !nodeComment && !nodename.empty())	//Let's not say "name: text".
  {
    if (nodename == "dbg_launcher")
    {
      // Recurse through child nodes
      xmlpp::Node::NodeList list = node->get_children();
      for (xmlpp::Node::NodeList::iterator iter = list.begin();
           iter != list.end(); ++iter)
      {
        parseApplicationsNode(*iter);
      }
    }
  }
}

void XMLLoader::parseApplicationsNode(const xmlpp::Node *node)
{
  const xmlpp::ContentNode *nodeContent = dynamic_cast < const xmlpp::ContentNode * >(node);
  const xmlpp::TextNode *nodeText = dynamic_cast < const xmlpp::TextNode * >(node);
  const xmlpp::CommentNode *nodeComment = dynamic_cast < const xmlpp::CommentNode * >(node);

  if (nodeText && nodeText->is_white_space())	//Let's ignore the indenting
    return;

  Glib::ustring nodename = node->get_name();

  if (!nodeText && !nodeComment && !nodename.empty())	//Let's not say "name: text".
  {
    if (nodename == "applications")
    {
      //Recurse through child nodes:
      xmlpp::Node::NodeList list = node->get_children();
      for (xmlpp::Node::NodeList::iterator iter = list.begin();
           iter != list.end(); ++iter)
      {
        parseApplicationNode(*iter);
      }
    }
  }
}

void XMLLoader::parseApplicationNode(const xmlpp::Node *node)
{
  const xmlpp::TextNode *nodeText = dynamic_cast < const xmlpp::TextNode * >(node);
  const xmlpp::Element *nodeElement = dynamic_cast < const xmlpp::Element * >(node);

  Preferences &preferences = Preferences::instance ();
  
  if (nodeText && nodeText->is_white_space())	//Let's ignore the indenting
    return;

  Glib::ustring nodename = node->get_name();

  if (nodename == "application")
  {
    LOG4CXX_DEBUG(mLogger, "Node = " << node->get_name());

    const xmlpp::Attribute *name_attribute = nodeElement->get_attribute("name");
    const xmlpp::Attribute *command_attribute = nodeElement->get_attribute("command");
    const xmlpp::Attribute *parameter_attribute = nodeElement->get_attribute("parameter");
    const xmlpp::Attribute *terminal_attribute = nodeElement->get_attribute("terminal");
    const xmlpp::Attribute *debugger_attribute = nodeElement->get_attribute("debugger");

    if (name_attribute)
    {
      LOG4CXX_DEBUG(mLogger, "Attribute name = " << name_attribute->get_value());

      DbgApplication dbg_app;
      if (name_attribute)
      {
        dbg_app.name = name_attribute->get_value();
      

        if (command_attribute)
        {
          dbg_app.command = command_attribute->get_value();
        }

        if (parameter_attribute)
        {
          dbg_app.parameter = parameter_attribute->get_value();
        }

        if (terminal_attribute)
        {
          if ((terminal_attribute->get_value() == "yes") ||
              (terminal_attribute->get_value() == "true"))
          {
            dbg_app.terminal = true;
          }
        }

        if (debugger_attribute)
        {
          if ((debugger_attribute->get_value() == "yes") ||
              (debugger_attribute->get_value() == "true"))
          {
            dbg_app.debugger = true;
          }
        }
      }
      
      preferences.dbg_applications.push_back(dbg_app);
    }  
  }
}

