#ifndef _MEMOPERATIONS_H_
#define _MEMOPERATIONS_H_
	
#include <math.h>
#include "Utilities.h"
#include "Instructions.h"

/* --Bit to turn on for the Addressing Mode chosed-- */
#define ADDRESSING_MODE_IMMEDIATE_VALUE			0
#define ADDRESSING_MODE_DIRECT_VALUE			1
#define ADDRESSING_MODE_STRUCT_VALUE		        2
#define ADDRESSING_MODE_REGISTER_DIRECT_VALUE		3


/*--Create new memory word--*/
void AddMemoryWord(MemoryCell* newCell , const MemoryCell srcAdressMode, const MemoryCell destAdressMode, const unsigned int opcode , const unsigned int ARE);

/*--Set ARE value--*/
void SetARE(MemoryCell* cell , const unsigned int ARE);

/*--Set address--*/
void SetAddress(MemoryCell* cell, const MemoryCell address);

/*--Set register address (src:bits 5-2 , dest:bits 6-9)--*/
void SetRegisterAddress(MemoryCell* codeValue, const int srcRegisterNum , const int destRegisterNum);

#endif
