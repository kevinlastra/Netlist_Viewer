#include "Shape.h"
#include "Cell.h"

namespace Netlist
{
  TermShape::TermShape(Symbol* owner, std::string name, int x1, int y1, TermShape::NameAlign na)
    : Shape(owner), term_(NULL), x1_(x1), y1_(y1), align_(na)
  {
    term_ = owner->getCell()->getTerm(name);
  }
  TermShape::~TermShape(){}
  Box TermShape::getBoundingBox () const
  {
    return Box(x1_,y1_,x1_,y1_);
  }
  void  TermShape::toXml(std::ostream& os) const
  {
    os << ++indent << "<term name=\"" << term_->getName() << "\" x1=\""
       << x1_      << "\" y1=\""      << y1_              << "\" align=\""
       << AligntoString(align_)       << "\"/>\n";
    --indent;
  }
  Shape* TermShape::fromXml (Symbol* s, xmlTextReaderPtr reader)
  {
    std::string name = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"name" ) );
    std::string x_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"x1" ) );
    std::string y_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"y1" ) );
    std::string align_str = xmlCharToString( xmlTextReaderGetAttribute( reader, (const xmlChar*)"align" ) );

    if(name.empty() || align_str.empty() ||
       x_str.empty() || y_str.empty())
      return NULL;

    NameAlign align = toAlign( align_str );
    if(align == Unknown)
      return NULL;
    
    int x = atoi(x_str.c_str());
    int y = atoi(y_str.c_str());
    
    TermShape* t = new TermShape(s, name, x, y, align);

    return t;
  }

  TermShape::NameAlign TermShape::toAlign(std::string s)
  {
    if(!s.compare("top_left"))
      return TopLeft;
    if(!s.compare("top_right"))
      return TopRight;
    if(!s.compare("bottom_left"))
      return BottomLeft;
    if(!s.compare("bottom_right"))
      return BottomRight;
    return Unknown;
  }
  std::string TermShape::AligntoString(TermShape::NameAlign na)
  {
    switch(na)
    {
    case TopLeft:
      return "top_left";
    case TopRight:
      return "top_right";
    case BottomLeft:
      return "bottom_left";
    case BottomRight:
      return "bottom_right";
    default:
      return "unknown";
    }
  }
}
