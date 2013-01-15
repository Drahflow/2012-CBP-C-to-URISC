#ifndef CODECONTAINER_H
#define CODECONTAINER_H

#include <string>
#include <vector>
#include <iostream>

// address the program is loaded at
#define PROGRAM_OFFSET 0x2

class CodeContainer
{
        private:
        struct Instruction {
                int code;
                std::vector<std::string> comments;
        };

        std::vector<std::string> initialComments;
        std::vector<Instruction> codeContainer;
        std::vector<unsigned short> staticValues;

        public:
        // address of clear dummy
        const int clearAddr;

        // address of expression result
        const int exprResultAddr;

        // address of expression result
        const int stackPointerAddr;

        void push_back(int code);
        void addComment(const std::string &);
        int size();
        int& operator[](int const& index);
        void addNOP();
        void addClearAkk();
        
        // returns the address of the last inserted instruction + 1, program offset already considered
        unsigned short address() { return codeContainer.size() + PROGRAM_OFFSET; }
        
        // loads *addr into acc
        void addLoad(int addr);
        
        /* 
         * allocates a new static address after the program code,
         * initializes it to value and returns the temporary address (< 0)
        */
        int allocate(unsigned short value = 0);
        
        // (re)sets default value of statically allocated memory
        void initStatic(int addr, unsigned short value);
        
        // clears memory and acc at addr
        void addClear(int addr);
        std::string getCodeString(void); 

        CodeContainer()
          : clearAddr(0x7FFF), exprResultAddr(0x7FFE), stackPointerAddr(allocate(0x7FFD)) { }
};

#endif //CODECONTAINER_H
