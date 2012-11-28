#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "XMLWriter.h"
#include "Preferences.h"

/* STD */
#include <iostream>

/* XML */
#include <libxml++/libxml++.h>

void XMLWriter::write(const std::string &file)
{
  Preferences &preferences = Preferences::instance ();
  
  try
  {
    xmlpp::Document document;
    document.set_internal_subset("example_xml_doc", "", "example_xml_doc.dtd");

    //foo is the default namespace prefix.
    xmlpp::Element* nodeRoot = document.create_root_node("dbg_launcher", "http://foo", "foo"); //Declares the namespace and uses its prefix for this node
    nodeRoot->set_namespace_declaration("http://foobar", "foobar"); //Also associate this prefix with this namespace: 

    xmlpp::Element* nodeChildApplications = nodeRoot->add_child("applications");

    for (std::vector<DbgApplication>::iterator app_it = preferences.dbg_applications.begin(); app_it != preferences.dbg_applications.end(); ++app_it)
    {
      DbgApplication &dbg_app = *app_it;

      xmlpp::Element* nodeChildApplication = nodeChildApplications->add_child("application");
      
      //Associate prefix with namespace:
      nodeChildApplication->set_namespace_declaration("http://bar", "bar");
       
      nodeChildApplication->set_namespace("bar"); //So it will be bar::examplechild.
      
      //foo is the namespace prefix. You could also just use a name of foo:id".
      nodeChildApplication->set_attribute("name", dbg_app.name, "foo");
      nodeChildApplication->set_attribute("command", dbg_app.command, "foo");
      nodeChildApplication->set_attribute("parameter", dbg_app.parameter, "foo");
      nodeChildApplication->set_attribute("terminal", dbg_app.terminal ? "yes" : "no", "foo");
      nodeChildApplication->set_attribute("debugger", dbg_app.debugger ? "yes" : "no", "foo");

      //nodeChildApplication->set_child_text("Some content");
      //nodeChildApplication->add_child_comment("Some comments");
    }

    document.write_to_file(file);
    
  }
  catch(const std::exception& ex)
  {
    std::cout << "Exception caught: " << ex.what() << std::endl;
  }
}

