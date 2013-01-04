#include <string>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <assert.h>
#include "CodeContainer.h"

int& CodeContainer::operator[](int const& index)
{
	return codeContainer[index];
}

void CodeContainer::push_back(int code)
{
	codeContainer.push_back(code);
}

void CodeContainer::addClearAkk()
{
	addClear(clearAddr);
}

void CodeContainer::addClear(int addr)
{
	codeContainer.push_back(addr);
	codeContainer.push_back(addr);
	codeContainer.push_back(addr);
}

void CodeContainer::addNOP()
{
	codeContainer.push_back(clearAddr);
	codeContainer.push_back(clearAddr);
	codeContainer.push_back(clearAddr);
	codeContainer.push_back(clearAddr);
}

int CodeContainer::allocate(unsigned short value)
{
	staticValues.push_back(value);
	return -staticValues.size();
}

void CodeContainer::initStatic(int addr, unsigned short value)
{
	size_t index = -addr - 1;
	assert(staticValues.size() > index);
	staticValues[index] = value;
}

void CodeContainer::addLoad(int addr)
{
	addClearAkk();
	push_back(addr);
}

int CodeContainer::size()
{
	return codeContainer.size();
}

using namespace std;

string CodeContainer::getCodeString(void) {
	stringstream returnValue;
	for (vector<int>::iterator it = codeContainer.begin() ; it != codeContainer.end(); ++it) {
		// returnValue << *it;
		int instr = *it;
		if(instr >= 0)
		{
			returnValue << instr;
		}
		else
		{
			 // check if we've actually allocated the address
			size_t offset = -instr - 1;
			assert(staticValues.size() > offset);
			returnValue << codeContainer.size() + offset + PROGRAM_OFFSET;
		}
		returnValue << "\n";
		//returnValue += itoa(*it);
		//returnValue += "\n";
	}
	// write default values
	for(vector<unsigned short>::iterator it = staticValues.begin(); it != staticValues.end(); ++it)
	{
		returnValue << *it;
		returnValue << "\n";
	}
	return returnValue.str();
}

