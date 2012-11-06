#ifndef NODE_H
#define NODE_H

// abstract base class for all AST nodes
class Node
{
  int line;
  public:
    Node(int line = 0) : line(line) { }
    
    // line number, for error messages
    int getLine() { return line; }
    
    // returns a human-readable description of this node and its subnodes
    virtual std::string explain() = 0;
    
    virtual ~Node() { }
};

#endif
