#ifndef CODECONTAINER_H
#define CODECONTAINER_H

#include <string>
#include <vector>
#include <iostream>

class CodeContainer
{
	std::vector<int> codeContainer;
	public:
	void push_back(int code);
	int size();
	int& operator[](int const& index);
	void addNOP();
	void addClearAkk();
    std::string getCodeString(void); 
};

#endif //CODECONTAINER_H
