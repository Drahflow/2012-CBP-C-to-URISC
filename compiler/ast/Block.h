#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <string>
#include "Command.h"
#include "VariableDef.h"

class Block : public Command
{ 
  std::vector<VariableDef*> *variables;
  std::vector<Command*> *commands;

  public:
    Block(int line, std::vector<Command*> *commands, std::vector<VariableDef*> *vars) 
      : Command(line), variables(vars), commands(commands) { }
    Block(int line, std::vector<Command*> *commands) 
      : Command(line), variables(0), commands(commands) { }
    Block(int line)
      : Command(line), variables(0), commands(0) { }

    std::string explain(int);

    void generate(CodeContainer *, SymbolTable *);
    int getLocalVariableCount() const;
};

#endif
