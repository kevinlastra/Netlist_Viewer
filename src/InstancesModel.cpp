#include "InstancesModel.h"

namespace Netlist {

  InstancesModel::InstancesModel(QObject* parent)
    :QAbstractTableModel(parent), cell(NULL)
  {}
  InstancesModel::~InstancesModel(){}

  void InstancesModel::setCell(Cell* c)
  {
    emit layoutAboutToBeChanged();
    cell = c;
    emit layoutChanged();
  }
  Cell* InstancesModel::getModel(int row)
  {
    if(!cell || row >= (int)cell->getInstances().size())
      return NULL;

    return cell->getInstances()[row]->getMasterCell();
  }
  int InstancesModel::rowCount(const QModelIndex& parent) const
  {
    return (cell)?cell->getInstances().size() : 0;
  }
  int InstancesModel::columnCount(const QModelIndex& parent) const
  {
    return 2;
  }
  QVariant InstancesModel::data(const QModelIndex& index, int role) const
  {
    if(!cell || !index.isValid())
      return QVariant();
    if(role == Qt::DisplayRole)
    {
      int row = index.row();
      switch(index.column())
      {
      case 0:
	return cell->getInstances()[row]->getName().c_str();
      case 1:
	return cell->getInstances()[row]->getMasterCell()->getName().c_str();
      }
    }
    return QVariant();
  }
  QVariant InstancesModel::headerData(int section, Qt::Orientation orientation, int role) const
  {
    if(orientation == Qt::Vertical || role != Qt::DisplayRole)
      return QVariant();

    switch(section)
    {
    case 0:
      return "Instance";
    case 1:
      return "MasterCell";
    }
    return QVariant();
  }
}
