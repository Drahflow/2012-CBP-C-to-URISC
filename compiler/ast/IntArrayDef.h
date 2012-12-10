#ifndef INTARRAYDEF_H
#define INTARRAYDEF_H

#include <vector>
#include <string>
#include "Type.h"
#include "VariableDef.h"

class IntArrayDef : public VariableDef
{
  int size;
  std::vector<int> data;
 
  public:
    void initialize(const std::vector<int>& data)
    {
      this->data = data;
      if(size < 0)
        size = data.size();
      // else
    }
    
    IntArrayDef(int line, char* name, int size = -1) : VariableDef(line, TYPE_INT, name), size(size) { }
    std::string explain(int ind);
};

#endif
