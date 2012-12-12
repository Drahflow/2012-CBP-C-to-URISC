#include <string>
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



int CodeContainer::size()
{
	return codeContainer.size();
}

using std::string;

string CodeContainer::getCodeString(void) {
	string returnValue;
	for (std::vector<int>::iterator it = codeContainer.begin() ; it != codeContainer.end(); ++it) {
		returnValue += *it;
		returnValue += "\n";
	}
	return returnValue;
}

