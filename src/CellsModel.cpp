#include "CellsModel.h"

namespace Netlist
{
  CellsModel::CellsModel(QObject* parent)
    :QAbstractTableModel(parent)
  {}
  CellsModel::~CellsModel(){}

  Cell* CellsModel::getModel(int row)
  {
    if(((size_t)row) >= Cell::getAllCells().size())
      return NULL;

    return Cell::getAllCells()[row];
  }
  int CellsModel::rowCount(const QModelIndex& parent) const
  {
    return Cell::getAllCells().size();
  }
  int CellsModel::columnCount(const QModelIndex& parent) const
  {
    return 1;
  }
  QVariant CellsModel::data(const QModelIndex& index, int role) const
  {
    if(!index.isValid())
      return QVariant();
    if(role == Qt::DisplayRole)
    {
      int row = index.row();
      if(index.column() == 0)
      {
	return Cell::getAllCells()[row]->getName().c_str();
      }
    }
    return QVariant();
  }
  QVariant CellsModel::headerData(int section, Qt::Orientation orientation, int role) const
  {
    if(orientation == Qt::Vertical || role != Qt::DisplayRole)
      return QVariant();

    if(section == 0)
    {
      return "Cell";
    }
    return QVariant();
  }
  void CellsModel::updateDatas()
  {
    emit layoutChanged();
  }
}
