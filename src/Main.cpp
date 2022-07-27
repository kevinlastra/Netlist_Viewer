#include <QApplication>
#include <QtGui>
#include "CellViewer.h"
#include "Cell.h"

using namespace std;
using namespace Netlist;

int main ( int argc, char* argv[] )
{
  QApplication* qa = new QApplication(argc, argv);

  Cell::load( "vdd" );
  Cell::load( "gnd" );
  Cell::load( "TransistorN" );
  Cell::load( "TransistorP" );
  Cell::load( "and2" );
  Cell::load( "or2" );
  Cell::load( "xor2" );
  Cell::load("halfadder");
  
  CellViewer* viewer = new CellViewer();
  //viewer->setCell(halfadder);
  viewer->show();

  int rvalue = qa->exec();
  delete qa;
  return rvalue;
}
