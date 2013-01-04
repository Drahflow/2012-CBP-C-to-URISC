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

