#include "Term.h"
#include "Shape.h"
#include "Symbol.h"

namespace Netlist
{
  Symbol::Symbol(Cell* cell):owner_(cell){}
  Symbol::~Symbol(){}

  Cell* Symbol::getCell () const {return owner_;}
  Box Symbol::getBoundingBox () const
  {
    Box b = Box();
    for(size_t i = 0; i < shapes_.size(); ++i)
    {
      b = b.merge(shapes_[i]->getBoundingBox());
    }
    return b;
  }
  Point Symbol::getTermPosition (Term* t) const
  {
    TermShape* ts = getTermShape(t);
    if(ts)
      return Point(ts->getX(), ts->getY());
    return Point();
  }
  TermShape* Symbol::getTermShape (Term* t) const
  {
    TermShape* ts = NULL;
    for(size_t i = 0; i < shapes_.size(); ++i)
    {
      ts = dynamic_cast<TermShape*>(shapes_[i]);
      if(ts != NULL && ts->getTerm() == t)
	return ts;
    }
    return NULL;
  }
  

  void Symbol::add (Shape* s)
  {
    shapes_.push_back(s);
  }
  void Symbol::remove (Shape* s)
  {
    for(size_t i = 0; i < shapes_.size(); ++i)
    {
      if(shapes_[i] == s)
      {
	shapes_.erase(shapes_.begin() + i);
	break;
      }
    }
  }
  void Symbol::toXml (std::ostream& os) const
  {
    os << indent << "<symbol>\n";
    for(size_t i = 0; i < shapes_.size(); ++i)
    {
      shapes_[i]->toXml(os);
    }
    os << indent << "</symbol>\n";
  }
  Symbol* Symbol::fromXml (Cell* c, xmlTextReaderPtr reader)
  {
    Symbol* s = c->getSymbol();
    if(s == NULL)
      return NULL;

    const xmlChar* SymbolTag = xmlTextReaderConstString( reader, (const xmlChar*)"symbol" );
    
    while(1)
    {
      int status = xmlTextReaderRead(reader);
      if (status != 1) {
	if (status != 0) {
	  std::cerr << "[ERROR] Symbol::fromXml(): Unexpected termination of the XML parser." << std::endl;
	}
	break;
      }
      
      switch ( xmlTextReaderNodeType(reader) ) {
      case XML_READER_TYPE_COMMENT:
      case XML_READER_TYPE_WHITESPACE:
      case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
	continue;
      }
      
      const xmlChar* nodeName = xmlTextReaderConstLocalName( reader );
      if((nodeName == SymbolTag) && (xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT))
	break;
      else
	if(Shape::fromXml(s, reader))
	  continue;

      std::cerr << "[ERROR] Symbol::fromXml(): Unknown or misplaced tag <" << nodeName
		<< "> (line: " << xmlTextReaderGetParserLineNumber(reader) << ")." << std::endl;
      break;
    }
        
    return s;
  }
}
