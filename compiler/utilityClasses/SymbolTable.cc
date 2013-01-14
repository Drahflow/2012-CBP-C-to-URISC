#include "SymbolTable.h"

#include <stdexcept>

SymbolTable *SymbolTable::createSubscope() const {
  SymbolTable *child = new SymbolTable();
  child->parent = this;

  return child;
}

void SymbolTable::addVariable(const std::string &name, int addr, bool global) {
  if(entries.find(name) != entries.end()) {
    throw std::runtime_error("Duplicate symbol table entry: " + name);
  }

  entries[name].name = name;
  entries[name].global = global;
  entries[name].addr = addr;
}

const SymbolTable::Variable &SymbolTable::resolveVariable(const std::string &name) const {
  std::map<std::string, Variable>::const_iterator i = entries.find(name);
  if(i != entries.end()) return i->second;
  if(parent) return parent->resolveVariable(name);
  throw std::runtime_error("Could not resolve: " + name);
}
