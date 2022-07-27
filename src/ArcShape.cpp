#include "Shape.h"

namespace Netlist
{
  ArcShape::ArcShape (Symbol* s, int start_, int span_, const Box& b)
    :Shape(s), box_(b), start_(start_), span_(span_)
  {}
  ArcShape::ArcShape (Symbol* s, int start_, int span_, int x1, int y1, int x2, int y2)
    :Shape(s), box_(x1,y1,x2,y2), start_(start_), span_(span_)
  {}
  ArcShape::~ArcShape (){}
  Box ArcShape::getBoundingBox () const
  {
    return box_;
  }
  
  void  ArcShape::toXml   (std::ostream& os) const
  {
    os << ++indent     << "<Arc x1=\""  << box_.getX1()  << "\" y1=\""
       << box_.getY1() << "\" x2=\""    << box_.getX2() << "\" y2=\""
       << box_.getY2() << "\" start=\"" << start_       << "\" span=\""
       << span_        << "\">\n";
    --indent;
  }
  ArcShape* ArcShape::fromXml (Symbol* s, xmlTextReaderPtr reader)
  {
    std::string x1_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"x1" ) );
    std::string y1_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y1" ) );
    std::string x2_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"x2" ) );
    std::string y2_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y2" ) );
    std::string start_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"start" ) );
    std::string span_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"span" ) );

    if(x1_str.empty() || y1_str.empty() ||
       x2_str.empty() || y2_str.empty() ||
       start_str.empty() || span_str.empty())
      return NULL;
    
    int x1 = atoi(x1_str.c_str());
    int y1 = atoi(y1_str.c_str());
    int x2 = atoi(x2_str.c_str());
    int y2 = atoi(y2_str.c_str());
    int start = atoi(start_str.c_str());
    int span = atoi(span_str.c_str());
    
    ArcShape* e = new ArcShape(s, start, span, x1, y1, x2, y2);

    return e;
  }
}
