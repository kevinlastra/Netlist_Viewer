#include "Shape.h"

namespace Netlist
{
  BoxShape::BoxShape (Symbol* owner, const Box& b)
    : Shape(owner), box_(b) {}
  BoxShape::BoxShape (Symbol* owner, int x1, int y1, int x2, int y2)
    : Shape(owner), box_(x1,y1,x2,y2) {}
  BoxShape::~BoxShape(){}
  Box BoxShape::getBoundingBox () const {return box_;}
  
  void  BoxShape::toXml(std::ostream& os) const
  {
    os << ++indent     << "<box x1=\"" << box_.getX1()
       << "\" y1=\""   << box_.getY1() << "\" x2=\""
       << box_.getX2() << "\" y2=\""   << box_.getY2()
       << "\"/>\n";
    --indent;
  }
  
  BoxShape* BoxShape::fromXml (Symbol* s, xmlTextReaderPtr reader)
  {
    std::string x1_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"x1" ) );
    std::string y1_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y1" ) );
    std::string x2_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"x2" ) );
    std::string y2_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y2" ) );

    if(x1_str.empty() || y1_str.empty() ||  x2_str.empty() || y2_str.empty())
      return NULL;
    
    int x1 = atoi(x1_str.c_str());
    int y1 = atoi(y1_str.c_str());
    int x2 = atoi(x2_str.c_str());
    int y2 = atoi(y2_str.c_str());
    
    BoxShape* b = new BoxShape(s, x1, y1, x2, y2);

    return b;
  }
}
