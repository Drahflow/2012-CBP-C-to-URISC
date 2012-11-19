#ifndef VARIABLEDEF_H
#define VARIABLEDEF_H

#include <string>
#include "Type.h"
#include "Node.h"

class VariableDef : public Node
{
  Type type;
  std::string name;
  public:
    VariableDef(int line, Type type, char* name) : Node(line), type(type), name(std::string(name)) { }
    std::string getName() { return name; }
    Type getType() { return type; }
    std::string explain(int ind);
};


#endif
