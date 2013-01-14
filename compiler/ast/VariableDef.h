#ifndef VARIABLEDEF_H
#define VARIABLEDEF_H

#include <string>
#include "Type.h"
#include "Node.h"

class VariableDef : public Node
{
  protected:
    Type type;
    std::string name;
    bool global;
    int addr;

  public:
    VariableDef(int line, Type type, char* name) : Node(line), type(type), name(std::string(name)), global(false), addr(0xFFFF) { }
    std::string getName() { return name; }
    Type getType() { return type; }
    std::string explain(int ind);
    // call if definition is global/static
    void setGlobal() { global = true; }
    void setLocalAddr(int addr);
    void generate(CodeContainer *, SymbolTable *);
};


#endif
