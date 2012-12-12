#include <string>
#include <sstream>
#include <stdio.h>
#include <vector>
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
	codeContainer.push_back(0x7fff);
	codeContainer.push_back(0x7fff);
	codeContainer.push_back(0x7fff);
}

void CodeContainer::addNOP()
{
	codeContainer.push_back(0x7fff);
	codeContainer.push_back(0x7fff);
	codeContainer.push_back(0x7fff);
	codeContainer.push_back(0x7fff);
}

int CodeContainer::size()
{
	return codeContainer.size();
}

using std::ostringstream;

std::string CodeContainer::getCodeString(void) {
	std::stringstream returnValue;
	for (std::vector<int>::iterator it = codeContainer.begin() ; it != codeContainer.end(); ++it) {
		returnValue << *it;
		returnValue << "\n";
		//returnValue += itoa(*it);
		//returnValue += "\n";
	}
	return returnValue.str();
}

