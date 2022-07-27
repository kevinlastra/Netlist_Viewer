#include "Shape.h"

namespace Netlist
{
  LineShape::LineShape (Symbol* owner, int x1, int y1, int x2, int y2)
    : Shape(owner), x1_(x1), y1_(y1), x2_(x2), y2_(y2)
  {}
  LineShape::~LineShape(){}

  Box LineShape::getBoundingBox () const
  {
    return Box(x1_,y1_,x2_,y2_);
  }
  
  Point LineShape::getP1() const
  {
    return Point(x1_, y1_);
  }
  Point LineShape::getP2() const
  {
    return Point(x2_, y2_);
  }
  void  LineShape::toXml   (std::ostream& os) const
  {
    os << ++indent   << "<line x1=\"" << x1_ << "\" y1=\""
       << y1_        << "\" x2=\""    << x2_ << "\" y2=\""
       << y2_        << "\"/>\n";
    --indent;
  }
  LineShape* LineShape::fromXml (Symbol* s, xmlTextReaderPtr reader)
  {
    std::string x1_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"x1" ) );
    std::string y1_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y1" ) );
    std::string x2_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"x2" ) );
    std::string y2_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y2" ) );

    if(x1_str.empty() || y1_str.empty() ||
       x2_str.empty() || y2_str.empty())
      return NULL;
    
    int x1 = atoi(x1_str.c_str());
    int y1 = atoi(y1_str.c_str());
    int x2 = atoi(x2_str.c_str());
    int y2 = atoi(y2_str.c_str());
    
    LineShape* l = new LineShape(s, x1, y1, x2, y2);

    return l;
  }
}
