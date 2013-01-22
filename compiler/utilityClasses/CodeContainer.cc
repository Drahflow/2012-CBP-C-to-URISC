#include <string>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <assert.h>
#include <iomanip>
#include "CodeContainer.h"

int& CodeContainer::operator[](int const& index)
{
	return codeContainer[index].code;
}

void CodeContainer::addComment(const std::string &comment) {
        if(codeContainer.empty()) {
                initialComments.push_back(comment);
        } else {
                codeContainer.back().comments.push_back(comment);
        }
}

void CodeContainer::setInstruction(int position, int code)
{
		Instruction instr;
		instr.code = code;
		codeContainer[position] = instr;
}

void CodeContainer::push_back(int code)
{
        Instruction instr;
        instr.code = code;

	codeContainer.push_back(instr);
}

void CodeContainer::addClearAkk()
{
	addClear(clearAddr);
}

void CodeContainer::addClear(int addr)
{
	push_back(addr);
	push_back(addr);
	push_back(addr);
}

void CodeContainer::addNOP()
{
	push_back(clearAddr);
	push_back(clearAddr);
	push_back(clearAddr);
	push_back(clearAddr);
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

void CodeContainer::addStackPush( int addr )
{
	addClearAkk();
	// change stack pointer value by -1
	addClearAkk();
	int pos = size();
	push_back(0); // put 1 to akk
	push_back(stackPointerAddr); // stackPointer = stackPointer - 1
	addClearAkk();
	int localAddr = address();
	push_back(localAddr + 15);
	push_back(localAddr + 15);
	push_back(localAddr + 15);
	push_back(stackPointerAddr);
	push_back(localAddr + 15);
	push_back(localAddr + 16);
	push_back(localAddr + 16);
	push_back(localAddr + 16);
	push_back(stackPointerAddr);
	push_back(localAddr + 16);
	push_back(localAddr + 17);
	push_back(localAddr + 17);
	push_back(localAddr + 17);
	push_back(stackPointerAddr);
	push_back(localAddr + 17);
	push_back(0); // get overwritten to clear stackaddress
	push_back(0);
	push_back(0);
	localAddr = address();
	push_back(localAddr + 8);
	push_back(localAddr + 8);
	push_back(localAddr + 8);
	push_back(stackPointerAddr);
	push_back(localAddr + 8);
	push_back(addr); // load address
	push_back(clearAddr); // store -(*addr) in akk and borrow
	push_back(1); // skip, use the 1 later
	int oneAddr = localAddr + 7;
	push_back(0); // store *addr at the stack pointer position

	Instruction instr;
	instr.code = oneAddr;
	//code[pos] = instr; //write address of the 1 to the codeContainer
	codeContainer[pos] = instr; //write address of the 1 to the codeContainer
	
}

void CodeContainer::addStackPop( int addr )
{
	// change stack pointer by +1
	push_back(clearAddr);
	push_back(clearAddr);
	push_back(clearAddr);
	int oneAddr = address()+2;
	push_back(oneAddr); // load one to akk
	push_back(clearAddr); // (0-1)
	push_back(1); // skip
	push_back(stackPointerAddr); // (*stackPointerAddr) + 1
	// pop:
	addClear(addr);
	addClear(clearAddr);
	push_back(clearAddr); //store -(*stackPointerAddr)
	push_back(clearAddr); // skip
	int localAddr = address();
	push_back(localAddr + 7);
    push_back(localAddr + 7);
	push_back(localAddr + 7);
	push_back(stackPointerAddr);
	push_back(localAddr + 7); //load stack pointer to specified position
	push_back(clearAddr);
	push_back(clearAddr);
	push_back(clearAddr);
	push_back(0); // load value from stack to akk
	push_back(clearAddr); // store -value to clearAddr
	push_back(1); //skip
	push_back(addr); // store stack value to addr

}

int CodeContainer::size()
{
	return codeContainer.size();
}

using namespace std;

string CodeContainer::getCodeString(void) {
	stringstream returnValue;

        for(vector<string>::const_iterator i = initialComments.begin(); i != initialComments.end(); ++i) {
          returnValue << "; " << *i << "\n";
        }

	for (vector<Instruction>::iterator it = codeContainer.begin() ; it != codeContainer.end(); ++it) {
		// returnValue << *it;
		int instr = it->code;
		if(instr >= 0)
		{
			returnValue << setbase(16) << instr;
		}
		else
		{
			 // check if we've actually allocated the address
			size_t offset = -instr - 1;
			if(!(staticValues.size() > offset)) {
                          returnValue << "; ERROR: static value for " << offset << " not allocated";
                        } else {
                          returnValue << setbase(16) << codeContainer.size() + offset + PROGRAM_OFFSET;
                        }
		}
		returnValue << "\n";

                for(vector<string>::const_iterator i = it->comments.begin(); i != it->comments.end(); ++i) {
                  returnValue << "; " << *i << "\n";
                }
		//returnValue += itoa(*it);
		//returnValue += "\n";
	}
        returnValue << "; ===== const table =====\n";
	// write default values
	for(vector<unsigned short>::iterator it = staticValues.begin(); it != staticValues.end(); ++it)
	{
		returnValue << setbase(16) << *it;
		returnValue << "\n";
	}
	return returnValue.str();
}

