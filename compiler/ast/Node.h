#ifndef NODE_H
#define NODE_H

#include <string>
#include "../utilityClasses/CodeContainer.h"
#include "../utilityClasses/SymbolTable.h"

#define NODE_INDENT_CHAR ' '
#define NODE_INDENT_REPEAT 4

// abstract base class for all AST nodes
class Node
{
  int line;
  public:
    Node(int line) : line(line) { }
    
    // line number, for error messages
    int getLine() { return line; }
    
    // returns a human-readable description of this node and its subnodes
    virtual std::string explain(int indent_level = 0) = 0;
    // TODO make abstract
    // method for code generation, override in subclasses
    virtual void generate(CodeContainer* code, SymbolTable* table) { }
    virtual ~Node() { }

  protected:
    // helper function to generate indent padding before each explain() line
    std::string indent(int level) 
    {
      return std::string(NODE_INDENT_REPEAT * level, NODE_INDENT_CHAR);
    }
};

#endif
