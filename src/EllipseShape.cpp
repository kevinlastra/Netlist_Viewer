#include "Shape.h"

namespace Netlist
{
  EllipseShape::EllipseShape (Symbol* s, const Box& b)
    :Shape(s), box_(b)
  {}
  EllipseShape::EllipseShape (Symbol* s, int x1, int y1, int x2, int y2)
    :Shape(s), box_(x1,y1,x2,y2)
  {}
  EllipseShape::~EllipseShape (){}
  Box EllipseShape::getBoundingBox () const
  {
    return box_;
  }
  
  void  EllipseShape::toXml   (std::ostream& os) const{}
  EllipseShape* EllipseShape::fromXml (Symbol* s, xmlTextReaderPtr reader)
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
    
    EllipseShape* e = new EllipseShape(s, x1, y1, x2, y2);

    return e;
  }
}
