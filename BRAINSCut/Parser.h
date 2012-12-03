#ifndef Parser_h
#define Parser_h

#include <ProcessDescription.h>
#include "XMLParser.h"
#include <list>
#include <vector>
#include <iostream>

class StringMap :
  public std::map<std::string, std::string>
{
public:
  typedef std::map<std::string, std::string> Superclass;
  typedef Superclass::const_iterator         const_iterator;
  std::string Get(const char *eleType,
                  const char *key)
  {
    StringMap::const_iterator it = this->find( std::string(key) );

    if( it == this->end() )
      {
      std::string msg("Missing Name attribute ");
      msg +=  key;
      msg += " in ";
      msg += eleType;
      throw ProcessObjectException(msg);
      }
    return it->second;
  }

  std::string GetIfExist(const char *eleType,
                         const char *key)
  {
    StringMap::const_iterator it = this->find( std::string(key) );

    if( it == this->end() )
      {
      std::cout << " *** Note ***" << std::endl
                << " *** Note ***" << std::endl
                << " Missing Name of attribute, mark as NA "
                << eleType << " " << key
                << std::endl << std::endl;
      return "NA";
      }
    return it->second;
  }

};

class Parser : public XMLParserBase
{
public:
  Parser(const std::string & filename) : XMLParserBase(filename)
  {
  }

  virtual void StartElement(void *userData, const XML_Char *name, const XML_Char * *atts);

  virtual void EndElement(void *userData, const XML_Char *name);

};

extern bool ReadXML(const char *filename, ProcessDescription & prob);

#endif // Parser_h
