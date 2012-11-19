#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <vector>
#include "Node.h"

class Program : public Node
{
  std::vector<Node*> definitions;
  public:
    Program(int line) : Node(line) { };
    void add(Node* node) { definitions.push_back(node); }
    std::string explain(int ind = 0);
};

#endif
