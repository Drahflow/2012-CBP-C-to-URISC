#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <vector>
#include "Node.h"
#include "FunctionDef.h"

class Program : public Node
{
  std::vector<Node*> definitions;
  public:
    Program(int line) : Node(line) { };
    void add(VariableDef* def) { definitions.push_back(def); }
    void add(FunctionDef* def) { definitions.push_back(def); }
    std::string explain(int ind = 0);
};

#endif
