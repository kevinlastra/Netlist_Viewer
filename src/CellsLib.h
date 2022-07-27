#ifndef NETLIST_CELL_LIB_H
#define NETLIST_CELL_LIB_H

#include <QTableView>
#include <QPushButton>
#include <QHeaderView>
#include "InstancesModel.h"
#include "CellViewer.h"
#include "CellsModel.h"

namespace Netlist
{

  class CellsLib : public QWidget
  {
    Q_OBJECT;
  public:
    CellsLib(QWidget* parent=NULL);
    int getSelectedRow() const;

    inline void setCellViewer(CellViewer*);
    inline CellsModel* getBaseModel();
    public slots:
      void load();
  private:
      CellViewer* cellViewer_;
      CellsModel* baseModel_;
      QTableView* view_;
      QPushButton* load_;
  };

  inline CellsModel* CellsLib::getBaseModel()
  {
    return baseModel_;
  }
  inline void CellsLib::setCellViewer(CellViewer* cv)
  {
    cellViewer_ = cv;
  }
}
#endif
