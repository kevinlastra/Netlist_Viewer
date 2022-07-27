#ifndef NETLIST_OPEN_CELL_DIALOG_H
#define NETLIST_OPEN_CELL_DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

namespace Netlist
{
  class OpenCellDialog : public QDialog
  {
    Q_OBJECT;
  public:
    OpenCellDialog(QWidget* parent=NULL);
    const QString getCellName() const;
    void setCellName(const QString&);
    static bool run(QString&);
  protected:
    QLineEdit* lineEdit_;
  };
}

#endif
