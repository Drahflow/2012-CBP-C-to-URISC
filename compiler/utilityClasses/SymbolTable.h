#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <map>
#include <string>

class SymbolTable {
  public:
    struct Variable {
      std::string name;
      bool global;
      int addr;
    };

  private:
    std::map<std::string, Variable> entries;
    const SymbolTable *parent;

  public:
    SymbolTable(): parent(0) { }
    SymbolTable *createSubscope() const;

    void addVariable(const std::string &name, int addr, bool global);
    const Variable &resolveVariable(const std::string &name) const;
};

#endif //SYMBOLTABLE_H
