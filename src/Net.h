#ifndef NETLIST_NET_H
#define NETLIST_NET_H

#include <vector>
#include <string>
#include "XmlUtil.h"
#include "Term.h"
#include "Cell.h"
#include "Node.h"
#include "Line.h"

namespace Netlist
{
  class Net
  {
  private:
    Cell* owner_;
    std::string name_;
    unsigned int id_;
    Term::Type type_;
    std::vector<Node*> nodes_;
    std::vector<Line*> lines_;
    
  public:
    Net  (Cell*, const std::string&, Term::Type);
    ~Net ();


     //accesseurs
     Cell* getCell () const;
     const std::string& getName () const;
     unsigned int getId () const;
     Term::Type getType () const;
     Node* getNode(size_t);
     const std::vector<Node*>& getNodes () const;
     size_t getFreeNodeId () const;

     //modificateurs
     void add(Node*);
     void add(Line*);
     
     bool remove(Node*);
     bool remove(Line*);
     
     void  toXml   (std::ostream&);
     static Net* fromXml (Cell*, xmlTextReaderPtr);

     inline const std::vector<Line*>& getLines () const;
  };

  inline const std::vector<Line*>& Net::getLines () const { return lines_; }
}

#endif
