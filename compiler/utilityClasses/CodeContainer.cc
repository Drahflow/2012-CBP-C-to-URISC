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
	int index = -addr - 1;
	assert(index >= 0);
	assert(staticValues.size() > index);
	staticValues[index] = value;
}

void CodeContainer::initSigned(int addr, int value)
{
	int index = -addr - 1;
	assert(index >= 0);
	assert(staticValues.size() > index);
	// when using a reference to another static address, check bounds
	assert(value >= 0 || staticValues.size() > -value - 1);
	staticValues[index] = value;
}


void CodeContainer::addLoad(int addr)
{
	addNOP();
	push_back(addr);
}

void CodeContainer::addStackPush( int addr )
{
	addComment( "StackPush" );
	// change stack pointer value by -1
	addClearAkk();
	int pos = size();
	int oneAddr = allocate();
	initStatic(oneAddr, 1);
	push_back(oneAddr); // put 1 to akk
	push_back(stackPointerAddr); // stackPointer = stackPointer - 1
	addClearAkk();
	int localAddr = address();
	push_back(localAddr + 30);
	push_back(localAddr + 30);
	push_back(localAddr + 30);
	push_back(stackPointerAddr);
	push_back(clearAddr);  // 0 - *stackPointerAddr
	push_back( 0 );  // skipped
	push_back(localAddr + 30); // 0 - (0 - *stackPointerAddr)
	push_back( clearAddr ); // clear *clearAddr
	push_back( clearAddr );
	push_back( clearAddr );
	push_back(localAddr + 31);
	push_back(localAddr + 31);
	push_back(localAddr + 31);
	push_back(stackPointerAddr);
	push_back(clearAddr);  // 0 - *stackPointerAddr
	push_back( 0 );  // skipped
	push_back(localAddr + 31);
	push_back( clearAddr ); // clear *clearAddr
	push_back( clearAddr ); // clear *clearAddr
	push_back( clearAddr ); // clear *clearAddr
	push_back(localAddr + 32);
	push_back(localAddr + 32);
	push_back(localAddr + 32);
	push_back(stackPointerAddr);
	push_back(clearAddr);  // 0 - *stackPointerAddr
	push_back( 0 );  // skipped
	push_back(localAddr + 32);
	push_back( clearAddr ); // clear *clearAddr
	push_back( clearAddr ); // clear *clearAddr
	push_back( clearAddr ); // clear *clearAddr
	push_back( 0xeeee ); // get overwritten to clear stackaddress
	push_back( 0xeeee );
	push_back( 0xeeee );
	localAddr = address();
	push_back(localAddr + 14);
	push_back(localAddr + 14);
	push_back(localAddr + 14);
	push_back(stackPointerAddr);
	push_back( localAddr + 5);  // 0 - *stackPointerAddr
	push_back( 0xEEEE );  // skipped address is localAddr+5
	push_back(localAddr + 14);
	push_back( clearAddr ); // clear *cleaAddr and akk
	push_back( clearAddr ); // clear *cleaAddr and akk
	push_back( clearAddr ); // clear *cleaAddr and akk
	push_back( clearAddr ); // clear *cleaAddr and akk
	push_back(addr); // load address
	push_back(clearAddr); // store -(*addr) in akk and borrow
	push_back(clearAddr); // skipped or zero
	//int oneAddr = localAddr + 13;
	push_back( 0xeeee ); // store *addr at the stack pointer position
	push_back(localAddr + 5); // clear *(localAddr + 5)
	push_back(localAddr + 5); // clear *(localAddr + 5)
	push_back(localAddr + 5); // clear *(localAddr + 5)
	push_back(localAddr + 5); // clear *(localAddr + 5)
	//Instruction instr;
	//instr.code = oneAddr;
	//code[pos] = instr; //write address of the 1 to the codeContainer
	//codeContainer[pos] = instr; //write address of the 1 to the codeContainer
	
}

void CodeContainer::addStackPop( int addr )
{
	addComment( "StackPop" );
	// pop:
	addClear(addr);
	addClear(clearAddr);
	push_back(clearAddr); //store -(*stackPointerAddr)
	push_back(clearAddr); // skip
	int localAddr = address();
	push_back(localAddr + 10);
    push_back(localAddr + 10);
	push_back(localAddr + 10);
	push_back(stackPointerAddr);
	push_back(clearAddr);  // 0 - *stackPointerAddr
	push_back( 0 ); // skipped
	push_back(localAddr + 10); //load stack pointer to specified position 0 - (0- *stackPointerAddr)
	push_back(clearAddr);
	push_back(clearAddr);
	push_back(clearAddr);
	push_back( 0xeeee ); // load value from stack to akk
	push_back(clearAddr); // store -value to clearAddr
	push_back(clearAddr); //skip
	push_back(addr); // store stack value to addr
	// change stack pointer by +1
	addComment( "StackPointer + 1" );
	push_back(clearAddr);
	push_back(clearAddr);
	push_back(clearAddr);
	push_back(clearAddr);
	int oneAddr = allocate();
	initStatic(oneAddr, 1);

	push_back(oneAddr); // load one to akk
	push_back(clearAddr); // (0-1)
	push_back(clearAddr); // skipped or zero
	push_back(stackPointerAddr); // (*stackPointerAddr) + 1

}

int CodeContainer::size()
{
	return codeContainer.size();
}

using namespace std;

string CodeContainer::getCodeString(void) {
	stringstream returnValue;
        int loadAddr = PROGRAM_OFFSET;

        for(vector<string>::const_iterator i = initialComments.begin(); i != initialComments.end(); ++i) {
          returnValue << "; " << *i << "\n";
        }

	for (vector<Instruction>::iterator it = codeContainer.begin() ; it != codeContainer.end(); ++it) {
		// returnValue << *it;
		int instr = it->code;
		if(instr >= 0)
		{
			returnValue << setbase(16) << instr << " ; " << setbase(16) << loadAddr++;
		}
		else
		{
			 // check if we've actually allocated the address
			size_t offset = -instr - 1;
			if(!(staticValues.size() > offset)) {
                          returnValue << "; ERROR: static value for " << offset << " not allocated";
                        } else {
                          returnValue << setbase(16) << codeContainer.size() + offset + PROGRAM_OFFSET << " ; " << setbase(16) << loadAddr++;
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
	for(vector<int>::iterator it = staticValues.begin(); it != staticValues.end(); ++it)
	{
		if(*it >= 0)
		{
			returnValue << setbase(16) << (unsigned short) *it << " ; " << setbase(16) << loadAddr++;
		}
		else
		{
			size_t offset = -*it - 1;
			assert(staticValues.size() > offset);
			returnValue << setbase(16) << codeContainer.size() + offset + PROGRAM_OFFSET << " ; " << setbase(16) << loadAddr++;
		}	
		returnValue << "\n";
	}
	return returnValue.str();
}

