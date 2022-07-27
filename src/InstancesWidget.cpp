#include "InstancesWidget.h"

namespace Netlist {

  InstancesWidget::InstancesWidget(QWidget* parent)
    :QWidget(parent), cellViewer_(NULL), baseModel_(new InstancesModel(this)),
     view_(new QTableView(this)), load_(new QPushButton(this))
  {
    setAttribute(Qt::WA_QuitOnClose, false);
    setAttribute(Qt::WA_DeleteOnClose, false);
    setContextMenuPolicy(Qt::ActionsContextMenu);

    view_->setShowGrid(false);
    view_->setAlternatingRowColors(true);
    view_->setSelectionBehavior(QAbstractItemView::SelectRows);
    view_->setSelectionMode(QAbstractItemView::SingleSelection);
    view_->setSortingEnabled(true);
    view_->setModel(baseModel_);

    QHeaderView* hHeader = view_->horizontalHeader();
    hHeader->setDefaultAlignment(Qt::AlignHCenter);
    hHeader->setMinimumSectionSize(150);
    hHeader->setStretchLastSection(true);
      
    QHeaderView* vHeader = view_->verticalHeader();
    vHeader->setVisible(true);

    QHBoxLayout* hlayout = new QHBoxLayout();
    hlayout->addStretch();
    hlayout->addWidget(load_);
    hlayout->addStretch();

    QFrame* separator = new QFrame();
    separator->setFrameShape(QFrame::HLine);
    separator->setFrameShadow(QFrame::Sunken);
    
    QVBoxLayout* vlayout = new QVBoxLayout();
    vlayout->setSizeConstraint(QLayout::SetFixedSize);
    vlayout->addWidget(view_);
    vlayout->addLayout(hlayout);

    setLayout(vlayout);
    
    load_->setText("Load");
    connect(    load_, SIGNAL(clicked()), this, SLOT(load()));
  }
  int InstancesWidget::getSelectedRow() const
  {
    QModelIndexList selecteds = view_->selectionModel()->selection().indexes();

    if(selecteds.empty())
      return -1;

    return selecteds.first().row();
  }
  void InstancesWidget::load()
  {
    int selectedRow = getSelectedRow();

    if(selectedRow < 0)
      return;

    cellViewer_->setCell(baseModel_->getModel(selectedRow));
  }
}
