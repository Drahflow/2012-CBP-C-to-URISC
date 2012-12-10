#ifndef FUNCTIONDEF_H
#define FUNCTIONDEF_H

#include <string>
#include "Type.h"
#include "Node.h"
#include "Block.h"

class FunctionDef : public Node
{
  Type type;
  std::string name;
  Block *block;
  public:
    FunctionDef(int line, Type type, char* name, Block *block) : Node(line), block(block), name(name), type(type) { }
    std::string getName() { return name; }
    Type getType() { return type; }
    std::string explain(int ind);
};


#endif
