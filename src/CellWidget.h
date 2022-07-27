#ifndef NETLIST_CELL_WIDGET_H
#define NETLIST_CELL_WIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include <QRect>
#include <QPoint>
#include <QResizeEvent>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QApplication>
#include <QSize>

class QPainter;

#include "Box.h"
#include "Term.h"
#include "Instance.h"
#include "Symbol.h"
#include "Shape.h"
#include "Cell.h"
#include "Line.h"
#include "Node.h"
#include "Net.h"

namespace Netlist {

  class Cell;
  class NodeTerm;


  class CellWidget : public QWidget {
      Q_OBJECT;
    public:
                      CellWidget         (QWidget* parent=NULL);
      virtual        ~CellWidget         ();
              void    setCell            (Cell*);
      inline  Cell*   getCell            ()              const;
      inline  int     xToScreenX         (int)           const;
      inline  int     yToScreenY         (int)           const;
      inline  QRect   boxToScreenRect    (const Box&)    const;
      inline  QPoint  pointToScreenPoint (const Point&)  const;
      inline  int     ScreenXTox         (int)           const;
      inline  int     ScreenYToy         (int)           const;
      inline  Box     screenRectToBox    (const QRect&)  const;
      inline  Point   screenPointToPoint (const QPoint&) const;
      virtual QSize   minimumSizeHint    ()              const;
      virtual void    resizeEvent        (QResizeEvent*);
      
    protected:
      virtual void    paintEvent         (QPaintEvent*);
      virtual void    keyPressEvent      (QKeyEvent*);
              void    mouseMoveEvent     (QMouseEvent*);
      
      public slots:
	
	void goLeft();
	void goRight();
	void goUp();
	void goDown();
      
    private:
      Cell* cell_;
      Box* viewport;
      int width_screen_size, height_screen_size;
      
      void query(QPainter&);
  };


  inline Cell* CellWidget::getCell () const { return cell_; }
  inline int CellWidget::xToScreenX(int x) const
  {
    return x - viewport->getX1();
  }
  inline int CellWidget::yToScreenY(int y) const
  {
    return viewport->getY1() - y;
  }
  inline int CellWidget::ScreenXTox(int x) const
  {
    return x + viewport->getX1();
  }
  inline int CellWidget::ScreenYToy(int y) const
  {
    return viewport->getY1() - y;
  }
  inline QRect CellWidget::boxToScreenRect(const Box& b) const
  {
    return QRect(xToScreenX(b.getX1()),
		 yToScreenY(b.getY1()),
		 b.getX2()-b.getX1(), b.getY1()-b.getY2());
  }
  inline QPoint CellWidget::pointToScreenPoint(const Point& p) const
  {
    return QPoint(xToScreenX(p.getX()), yToScreenY(p.getY()));
  }
  inline Box CellWidget::screenRectToBox(const QRect& qr) const
  {
    return Box(ScreenXTox(qr.x()), ScreenYToy(qr.y()), ScreenXTox(qr.x() + qr.width()), ScreenYToy(qr.x() - qr.height()));
  }
  inline Point CellWidget::screenPointToPoint(const QPoint& qp) const
  {
    return Point(ScreenXTox(qp.x()), ScreenYToy(qp.y()));
  }
}  // Netlist namespace.

#endif  // NETLIST_CELL_WIDGET_H
