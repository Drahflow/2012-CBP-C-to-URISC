#include <assert.h>
#include <string>
#include <sstream>
#include <vector>
#include "IntArrayDef.h"

using namespace std;

string IntArrayDef::explain(int ind)
{
  stringstream expl;
  expl << indent(ind) << "int_array_def:" << getLine() << " " << getName();
  expl << " size=" << size << " " << "#data=" << data.size() << endl;
  return expl.str();
}

void IntArrayDef::generate(CodeContainer *code, SymbolTable *symbols)
{
	assert(global);
	assert(size >= (int) data.size());
  	
        // allocate first element
        int headAddr = code->allocate();
        int addr = headAddr;
        int i = 0;
        while(1) {
          code->initStatic(addr, data[i]);
          if(++i >= size) break;

          int prevAddr = addr;
          addr = code->allocate();
          // ensure this is contiguous
          assert(prevAddr - 1 == addr);
        }

	// allocate pointer
	int pointerAddr = code->allocate(headAddr);
	
	// add pointer to symbol table
	symbols->addVariable(name, pointerAddr, global);
}
