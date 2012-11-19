#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include "Node.h"

class Command : public Node
{
  public:
    std::string explain(int ind) { return indent(ind) + "TODO in subclasses\n"; }
    Command(int line) : Node(line) { }
};

#endif
