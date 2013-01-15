#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include "Node.h"

class Command : public Node
{
  public:
    Command(int line) : Node(line) { }

    virtual int getLocalVariableCount() const { return 0; }
};

#endif
