#include "CellViewer.h"
#include "InstancesWidget.h"
#include "CellsLib.h"

namespace Netlist
{
  CellViewer::CellViewer(QWidget* parent)
    : QMainWindow(parent), cellWidget_(new CellWidget()), saveCellDialog_(new SaveCellDialog(this)),
      instancesWidget_(new InstancesWidget()),
      cellsLib_(new CellsLib())
  {

    instancesWidget_->setCellViewer(this);
    cellsLib_->setCellViewer(this);
    
    setCentralWidget(cellWidget_);

    QMenu* fileMenu = menuBar()->addMenu("&File");

    QAction* open_action = new QAction("&Open Cell", this);
    open_action->setStatusTip("Open Cell");
    open_action->setShortcut(QKeySequence("CTRL+O"));
    open_action->setVisible(true);

    QAction* save_action = new QAction("&Save As", this);
    save_action->setStatusTip("Save tp disk (rename) the Cell");
    save_action->setShortcut(QKeySequence("CTRL+S"));
    save_action->setVisible(true);

    QAction* quit_action = new QAction("&Quit", this);
    quit_action->setStatusTip("Quit");
    quit_action->setShortcut(QKeySequence("CTRL+Q"));
    quit_action->setVisible(true);

    
    fileMenu->addAction(open_action);
    fileMenu->addAction(save_action);
    fileMenu->addAction(quit_action);
    
    connect(open_action, SIGNAL(triggered()), this, SLOT(openCell()));
    connect(save_action, SIGNAL(triggered()), this, SLOT(saveCell()));
    connect(quit_action, SIGNAL(triggered()), this, SLOT(close()));

    connect(this, SIGNAL(cellLoaded()), cellsLib_->getBaseModel(), SLOT(updateDatas()));
    
    showCellsLib();
    showInstanceWidget();
  }
  void CellViewer::saveCell()
  {
    Cell* cell = getCell();
    if(cell == NULL)
      return;

    QString cellName = cell->getName().c_str();

    if(saveCellDialog_->run(cellName))
      {
	cell->setName(cellName.toStdString());
	cell->save(cellName.toStdString());
      }
  }
  void CellViewer::openCell()
  {
    Cell* c = getCell();
    QString cellName;
    if(c)
      cellName = c->getName().c_str();
    if(OpenCellDialog::run(cellName))
    {
      if((c = Cell::find(cellName.toStdString())) == NULL)
      {
	c = Cell::load(cellName.toStdString());
      }
      emit cellLoaded();
      setCell(c);
    }
  }
  void CellViewer::setCell(Cell* c)
  {
    cellWidget_->setCell(c);
    instancesWidget_->setCell(c);
  }
  Cell* CellViewer::getCell() const
  {
    return cellWidget_->getCell();
  }
  void CellViewer::showCellsLib()
  {
    cellsLib_->show();
  }
  void CellViewer::showInstanceWidget()
  {
    instancesWidget_->show();
  }
}
