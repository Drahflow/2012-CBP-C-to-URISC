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
  	
  	int headAddr = 0xFFFF;
  	if(size > 0)
  	{
	  	// allocate first element
		headAddr = code->allocate();
		
		// allocate remaining elements
		int prevAddr = headAddr;
		for(int i = 1; i < size; i++)
		{
			int nextAddr = code->allocate();
			// ensure this is contiguous
			assert(prevAddr + 1 == nextAddr);
			prevAddr = nextAddr;
		}
	}
	
	// initialize values
	if(data.size() > 0)
	{
		int currentAddr = headAddr;
		for(vector<int>::iterator it = data.begin(); it != data.end(); ++it)
			code->initStatic(currentAddr++, *it);
	}
	
	// allocate pointer
	int pointerAddr = code->allocate(headAddr);
	
	// add pointer to symbol table
	symbols->addVariable(name, pointerAddr, global);
}
