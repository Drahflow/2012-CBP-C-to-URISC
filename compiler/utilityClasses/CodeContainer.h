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
        std::vector<int> staticValues;

        public:
        // address of clear dummy
        const int clearAddr;

        // address of expression result
        const int exprResultAddr;

        // address of temp value
        const int tempAddr;

        // address of expression result
        const int stackPointerAddr;
        const int functionStackPointerAddr; //the functionStackPointerAddr tracks functionCalls and is neede for local Variables

        void push_back(int code);
        void addComment(const std::string &);
        int size();
        int& operator[](int const& index);
        void addNOP();
        void addClearAkk();

		void setInstruction(int position, int code);
        
        // returns the address of the last inserted instruction + 1, program offset already considered
        unsigned short address() { return codeContainer.size() + PROGRAM_OFFSET; }
        
        // loads *addr into acc
        void addLoad(int addr);

        // pushes and pops *addr to the stack
        void addStackPush( int addr);
        void addStackPop( int addr);
		void setFunctionStackPointer( int addr );
        /* 
         * allocates a new static address after the program code,
         * initializes it to value and returns the temporary address (< 0)
        */
        int allocate(unsigned short value = 0);
        
        // (re)sets default value of statically allocated memory
        void initStatic(int addr, unsigned short value);
        void initSigned(int addr, int value);
        
        // clears memory and acc at addr
        void addClear(int addr);
        std::string getCodeString(void); 

        CodeContainer()
          : clearAddr(0x7FFF), exprResultAddr(0x7FFE), tempAddr(0x7FFD), stackPointerAddr(allocate(0x7FFB)), functionStackPointerAddr(0x7FFC) { }
};

#endif //CODECONTAINER_H
