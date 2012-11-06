#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include "Node.h"

class Command : public Node
{
  public:
    std::string explain() { return "TODO in subclasses"; }
    Command(int line) : Node(line) { }
};

#endif
