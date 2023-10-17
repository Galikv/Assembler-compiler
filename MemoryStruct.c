#include "MemoryStruct.h"

void AddMemoryWord(MemoryCell* newCell , const MemoryCell srcAdressMode, const MemoryCell destAdressMode, const unsigned int opcode , const unsigned int ARE) 
{
	/*bits 0-1 will be A\R\E , bits 2-3 will be the source-register , bits 4-5 will be the destination-register and bits 6-9 will be the opcode */

	*(newCell) += (opcode * pow(2,6));
	*(newCell) += (srcAdressMode* pow(2,4));
	*(newCell) += (destAdressMode * pow(2,2));
	*(newCell) += (ARE);	
}

void SetARE(MemoryCell* cell , const unsigned int ARE)
{
	*cell *= (pow(2,2));
	*cell += ARE;
}
void SetAddress(MemoryCell* cell, const MemoryCell address)
{
	*cell |= address;
}
void SetRegisterAddress(MemoryCell* codeValue, const int srcRegisterNum , const int destRegisterNum)
{
	*codeValue = (srcRegisterNum * pow(2,6));
	*codeValue += (destRegisterNum * pow(2,2));
}

