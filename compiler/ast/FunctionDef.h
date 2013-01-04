#ifndef FUNCTIONDEF_H
#define FUNCTIONDEF_H

#include <string>
#include "Type.h"
#include "Node.h"
#include "Block.h"

class FunctionDef : public Node {
  private:
    Type type;
    std::string name;
    std::vector<VariableDef *> *parameters;
    Block *block;

  public:
    FunctionDef(int line, Type type, char* name, std::vector<VariableDef *> *parameters, Block *block)
      : Node(line), type(type), name(name), parameters(parameters), block(block) { }

    std::string getName() { return name; }
    Type getType() { return type; }

    std::string explain(int ind);

    void generate(CodeContainer *, SymbolTable *);
};


#endif
