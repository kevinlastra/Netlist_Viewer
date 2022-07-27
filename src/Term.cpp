#include "Term.h"
#include "Net.h"

namespace Netlist
{
  Term::Term(Cell* c, const std::string& name, Direction d)
    :owner_(c),name_(name),direction_(d),type_(External),net_(NULL),node_(this)
  {
    ((Cell*)owner_)->add(this);
  }
  Term::Term(Instance* i, const Term* modelTerm)
    :owner_(i),name_(modelTerm->getName()),direction_(modelTerm->getDirection()),type_(Internal),net_(NULL),node_(this)
  {
    ((Instance*)owner_)->add(this);
  }
  Term::~Term()
  {
    if(isInternal())
      ((Instance*)owner_)->remove(this);
    else
      ((Cell*)owner_)->remove(this);

    if(net_ != NULL)
    {
      net_->remove(&node_);
    }
  }
  
  //accesseurs
  Cell* Term::getOwnerCell() const
  {
    if(isExternal())
      return (Cell*)owner_;
    return ((Instance*)owner_)->getCell();
  }

    
  //modificateurs
  void Term::setNet(Net* n)
  {
    if(n == NULL)
    {
      net_->remove(&node_);
      net_ = NULL;
    }
    else if(net_ == NULL)
    {
      n->add(&node_);
      net_ = n;
    }
    else
    {
      if(net_->remove(&node_))
      {
	n->add(&node_);
	net_ = n;
      }
    }
  }
  void Term::setNet(const std::string& s)
  {
    setNet(getOwnerCell()->getNet(s));
  }
  inline void Term::setDirection (Direction d)
  {
    direction_ = d;
  }
  void Term::setPosition  (const Point& p)
  {
    node_.setPosition(p);
  }
  void Term::setPosition  (int x, int y)
  {
    node_.setPosition(x,y);
  }
    

  std::string Term::toString(Type t)
  {
    switch(t)
      {
      case Internal:
	return "Internal";
      case External:
	return "External";
      }
    return "";
  }
  std::string Term::toString(Direction d)
  {
    switch(d)
      {
      case In:
	return "In";
      case Out:
	return "Out";
      case Inout:
	return "Inout";
      case Tristate:
	return "Tristate";
      case Transcv:
	return "Transcv";
      case Unknown:
	return "Unknown";
      }
    return "";
  }
  Term::Direction Term::toDirection(std::string s)
  {
    if(!s.compare("In"))
      return In;
    if(!s.compare("Out"))
      return Out;
    if(!s.compare("Inout"))
      return Inout;
    if(!s.compare("Tristate"))
      return Tristate;
    if(!s.compare("Transcv"))
      return Transcv;
    return Unknown;
  }
  void Term::toXml(std::ostream& stream)
  {
    stream << indent << "<term name=\"" << name_
	   << "\" direction=\"" << toString(direction_)
	   << "\" x=\""<<getPosition().getX()
	   << "\" y=\""<<getPosition().getY()
	   << "\"/>" << std::endl;
  }
  Term* Term::fromXml(Cell* c, xmlTextReaderPtr reader)
  {    
    std::string name = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
    std::string dir_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"direction" ) );
    std::string x_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"x" ) );
    std::string y_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y" ) );

    if(name.empty() || dir_str.empty() ||
       x_str.empty() || y_str.empty())
      return NULL;

    Direction dir = toDirection( dir_str );
    if(dir == Unknown)
      return NULL;

    Term* t = new Term(c, name, dir);
    int x = atoi(x_str.c_str());
    int y = atoi(y_str.c_str());

    t->setPosition(x, y);
    return t;
  }
}
