#ifndef NETLIST_SHAPE_H
#define NETLIST_SHAPE_H

#include "string.h"
#include "Symbol.h"
#include "Box.h"
#include "Point.h"
#include "Term.h"

namespace Netlist {

  class BoxShape;
  class EllipseShape;
  class ArcShape;
  class LineShape;
  
  class Shape
  {
  public:
    Shape (Symbol*);
    virtual ~Shape ();
    inline Symbol* getSymbol () const;
    virtual Box getBoundingBox () const = 0;

    virtual void  toXml   (std::ostream&) const = 0;
    static Shape* fromXml (Symbol*, xmlTextReaderPtr);
  private:
    Symbol* owner_;
  };

  inline Symbol* Shape::getSymbol () const { return owner_; }


  
  class BoxShape : public Shape
  {
  public:
    BoxShape (Symbol*, const Box&);
    BoxShape (Symbol*, int x1, int y1, int x2, int y2);
    ~BoxShape ();
    Box getBoundingBox () const;
    
    void  toXml   (std::ostream&) const;
    static BoxShape* fromXml (Symbol*, xmlTextReaderPtr);
    
  private:
    Box box_;
  };
  

  class LineShape : public Shape
  {
  public:

    LineShape (Symbol*, int x1, int y1, int x2, int y2);
    ~LineShape ();
    Box getBoundingBox () const;

    Point getP1() const;
    Point getP2() const;

    void  toXml   (std::ostream&) const;
    static LineShape* fromXml (Symbol*, xmlTextReaderPtr);
  private:
    int x1_, y1_, x2_, y2_;
  };
  
  class TermShape : public Shape
  {
  public:
    enum NameAlign {TopLeft = 1, TopRight, BottomLeft, BottomRight, Unknown};
    
    TermShape (Symbol*, std::string name, int x1, int y1, NameAlign na);
    ~TermShape ();
    
    Box getBoundingBox () const;
    inline Term* getTerm () const;
    inline Cell* getCell () const;
    inline int getX () const;
    inline int getY () const;
    inline NameAlign getAlign() const;
    
    void  toXml   (std::ostream&) const;
    static Shape* fromXml (Symbol*, xmlTextReaderPtr);

    static NameAlign toAlign(std::string);
    static std::string AligntoString(NameAlign);
  private:
    Term* term_;
    int x1_, y1_;
    NameAlign align_;
  };

  inline Term* TermShape::getTerm () const{return term_;}
  inline Cell* TermShape::getCell () const{return term_->getCell();}
  inline int TermShape::getX () const{return x1_;}
  inline int TermShape::getY () const{return y1_;}
  inline TermShape::NameAlign TermShape::getAlign() const{return align_;}
  
  class EllipseShape : public Shape
  {    
  public:
    EllipseShape (Symbol*, const Box&);
    EllipseShape (Symbol*, int x1, int y1, int x2, int y2);
    ~EllipseShape ();
    Box getBoundingBox () const;
    
    void  toXml   (std::ostream&) const;
    static EllipseShape* fromXml (Symbol*, xmlTextReaderPtr);
    
  private:
    Box box_;
  };

  class ArcShape : public Shape
  {    
  public:
    ArcShape (Symbol*, int start_, int span_, const Box&);
    ArcShape (Symbol*, int start_, int span_, int x1, int y1, int x2, int y2);
    ~ArcShape ();
    Box getBoundingBox () const;

    inline int getStart();
    inline int getSpan();
    void  toXml   (std::ostream&) const;
    static ArcShape* fromXml (Symbol*, xmlTextReaderPtr);
    
  private:
    Box box_;
    int start_, span_;
  };

  inline int ArcShape::getStart(){return start_;}
  inline int ArcShape::getSpan(){return span_;}
}

#endif
