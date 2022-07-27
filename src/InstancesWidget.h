#ifndef NETLIST_INSTANCE_WIDGET_H 
#define NETLIST_INSTANCE_WIDGET_H 

#include <QTableView>
#include <QPushButton>
#include <QHeaderView>
#include "Cell.h"
#include "InstancesModel.h"
#include "CellViewer.h"

namespace Netlist
{  
  class InstancesWidget : public QWidget {
    Q_OBJECT;
  public:
    InstancesWidget(QWidget* parent=NULL );
    int getSelectedRow() const;
    
    inline void setCell(Cell*);
    inline void setCellViewer(CellViewer*);
    public slots:
      void load();
  private:
      CellViewer*     cellViewer_;
      InstancesModel* baseModel_;
      QTableView*     view_;
      QPushButton*    load_;
  };
  
  inline void InstancesWidget::setCell(Cell* c)
  {
    baseModel_->setCell(c);
  }
  inline void InstancesWidget::setCellViewer(CellViewer* cv)
  {
    cellViewer_ = cv;
  }
}
#endif
