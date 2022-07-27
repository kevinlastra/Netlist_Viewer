#include "Instance.h"
#include "Shape.h"
namespace Netlist
{
  Instance::Instance(Cell* owner, Cell* model, const std::string& s)
    :owner_(owner),masterCell_(model),name_(s)
  {
    owner_->add(this);
    std::vector<Term*> Cterms_ = model->getTerms();
    for(unsigned int i = 0; i < Cterms_.size(); ++i)
    {
      new Term(this, Cterms_[i]);
    }
  }
  Instance::~Instance()
  {
    for(unsigned int i = 0; i < terms_.size(); ++i)
    {
      delete terms_[i];
    }
  }

  //accesseurs
  const std::string& Instance::getName() const{return name_;}
  Cell* Instance::getMasterCell() const{return masterCell_;}
  Cell* Instance::getCell() const{return owner_;}
  const std::vector<Term*>& Instance::getTerms() const
  {
    return terms_;
  }
  Term* Instance::getTerm(const std::string& s) const
  {
    for(unsigned int i = 0; i < terms_.size(); i++)
    {
      if(terms_[i]->getName() == s)
      {
	return terms_[i];
      }
    }
    return NULL;
  }
  Point Instance::getPosition() const{return position_;}

  //modificateurs
  bool Instance::connect(const std::string& name, Net* n)
  {
    Term* t = getTerm(name);
    if(t != NULL)
    {
      t->setNet(n);
      return true;
    }
    return false;
  }
  void Instance::add(Term* t)
  {
    terms_.push_back(t);
  }
  void Instance::remove(Term* t)
  {
    for(unsigned int i = 0; i < terms_.size(); i++)
    {
      if(terms_[i] == t)
	terms_.erase(terms_.begin()+i);
    }
  }
  void Instance::setPosition(const Point& p)
  {
    position_ = p;

    std::vector<Shape*> s = getMasterCell()->getSymbol()->getShapes();
    for(size_t i = 0; i < s.size(); ++i)
    {
      TermShape* ts = dynamic_cast<TermShape*>(s[i]);
      if(ts != NULL)
      {
	Term* t = getTerm(ts->getTerm()->getName());
	t->setPosition(getPosition().translate(ts->getX(), ts->getY()));
      }	
    }    
  }
  void Instance::setPosition(int x, int y)
  {
    setPosition(Point(x,y));
  }
  void Instance::toXml(std::ostream& stream)
  {
    stream << indent << "<instance name=\""<<name_<<"\" mastercell=\""
	   << masterCell_->getName() <<"\" x=\""<<position_.getX()
	   << "\" y=\"" << position_.getY() << "\"/>" << std::endl;
  }
  Instance* Instance::fromXml (Cell* c, xmlTextReaderPtr reader)
  {
    std::string name = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
    std::string mastercell = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"mastercell" ) );
    std::string x_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"x" ) );
    std::string y_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y" ) );

    if(name.empty() || mastercell.empty() ||
       x_str.empty() || y_str.empty())
      return NULL;
    Instance* i = new Instance(c, Cell::find(mastercell), name);
    i->setPosition(atoi(x_str.c_str()), atoi(y_str.c_str()));
    return i;
  }
}
