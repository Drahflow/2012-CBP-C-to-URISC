#ifndef FUNCTIONDEF_H
#define FUNCTIONDEF_H

#include <string>
#include "Type.h"
#include "Node.h"

class FunctionDef : public Node
{
  Type type;
  std::string name;
  //Block block;
  public:
    FunctionDef(int line, Type type, char* name) : Node(line) { }
    std::string getName() { return name; }
    Type getType() { return type; }
    std::string explain(int ind);
};


#endif
