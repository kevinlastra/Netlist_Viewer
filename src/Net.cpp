#include "Net.h"

namespace Netlist
{
  Net::Net(Cell* c, const std::string& s, Term::Type t)
    :owner_(c),name_(s),id_(0),type_(t)
  {
    owner_->add(this);
  }
  Net::~Net()
  {
    NodeTerm* n;
    for(unsigned int i = 0; i < nodes_.size(); ++i)
    {
      n = (NodeTerm*)nodes_[i];
      if(n)
        n->getTerm()->setNet(NULL);
    }
  }


  //accesseurs
  Cell* Net::getCell() const{return owner_;}
  const std::string& Net::getName() const{return name_;}
  unsigned int Net::getId() const{return id_;}
  Term::Type Net::getType() const{return type_;}
  Node* Net::getNode(size_t id)
  {
    if(id < nodes_.size())
      return nodes_[id];
    return NULL;
  }
  const std::vector<Node*>& Net::getNodes() const
  {
    return nodes_;
  }
  size_t Net::getFreeNodeId() const
  {
    for(unsigned int i = 0; i < nodes_.size(); i++)
    {
      if(nodes_[i]==NULL)
        return i;
    }
    return nodes_.size();
  }
  
//modificateurs
  void Net::add(Node* n)
  {
    size_t id = n->getId();
    if(id == Node::noid)
    {
      id = getFreeNodeId();
      n->setId(id);
    }
    
    if(id < nodes_.size())
      nodes_[id] = n;
    else
    {
      nodes_.resize(id+1);
      nodes_[id] = n;
    }
  }
  void Net::add(Line* line)
  {
    if(line)
      lines_.push_back(line);
  }
  bool Net::remove(Node* n)
  {
    if(n)
    {
      for(std::vector<Node*>::iterator il = nodes_.begin(); il != nodes_.end(); ++il)
      {
        if(*il == n)
        {
          nodes_.erase(il);
          return true;
        }
      }
    }
    return false;
  }
  bool Net::remove(Line* line)
  {
    if(line)
    {
      for(std::vector<Line*>::iterator il = lines_.begin(); il != lines_.end(); ++il)
      {
        if(*il == line)
        {
          lines_.erase(il);
          return true;
        }
      }
    }
    return false;
  }
  void Net::toXml(std::ostream& stream)
  {
    stream << indent++ << "<net name=\"" << name_ << "\" type=\""
           << Term::toString(type_) << "\">"
           << std::endl;
    
    for(unsigned int i = 0; i < nodes_.size(); ++i)
    {
      if(nodes_[i] != NULL)
        nodes_[i]->toXml(stream);
    }
    for(unsigned int i = 0; i < lines_.size(); ++i)
    {
      if(lines_[i] != NULL)
        lines_[i]->toXml(stream);
    }
    stream << --indent << "</net>" << std::endl;
  }
  Net* Net::fromXml (Cell* c, xmlTextReaderPtr reader)
  {
    std::string name = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
    std::string type = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"type" ) );
    
    if(name.empty() || type.empty())
      return NULL;
    
    Term::Type t;
    if(!type.compare("Internal"))
      t = Term::Internal;
    else if(!type.compare("External"))
      t = Term::External;
    else
      return NULL;
    Net* n = new Net(c, name, t);
    
    const xmlChar* nodeTag      = xmlTextReaderConstString( reader, (const xmlChar*)"node" );
    const xmlChar* lineTag      = xmlTextReaderConstString( reader, (const xmlChar*)"line" );
    const xmlChar* nodeName;
    
    while(true)
    {
      int status = xmlTextReaderRead(reader);
      if (status != 1) {
        if (status != 0) {
          std::cerr << "[ERROR] Cell::fromXml(): Unexpected termination of the XML parser." << std::endl;
        }
        break;
      }
      
      switch ( xmlTextReaderNodeType(reader) )
      {
        case XML_READER_TYPE_COMMENT:
        case XML_READER_TYPE_WHITESPACE:
        case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
        continue;
      }
      
      nodeName = xmlTextReaderConstLocalName( reader );
      
      if(nodeName == nodeTag)
      {
        if(xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT)
        {
          if(!Node::fromXml(n, reader))
	    return NULL;
        }
        else if(xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT)
          break;
        else
          return NULL;
      }
      else if(nodeName == lineTag)
      {
	if(xmlTextReaderNodeType(reader) == XML_READER_TYPE_ELEMENT)
	{
	  if(!Line::fromXml(n, reader))
	    return NULL;
	}
	else if(xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT)
	  break;
	else
	  return NULL;
      }
      else
	break;
    }
    return n;
  }
}
