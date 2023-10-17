#ifndef _INSTRUCTIONS_H
#define _INSTRUCTIONS_H

#include "Utilities.h"
#include "MemoryStruct.h"
#include <string.h>


/* --Addressing Modes-- */
#define ADDRESSING_MODE_IMMEDIATE				0
#define ADDRESSING_MODE_DIRECT					1
#define ADDRESSING_MODE_STRUCT       			 	2
#define ADDRESSING_MODE_REGISTER_DIRECT				3
#define ADDRESSING_MODE_UNKNOWN					4
#define MIN_VALID_NUMBER					-1024
#define MAX_VALID_NUMBER					1023

/* --instuction data structure-- */
typedef struct Instruction
{
    char name[12];                 /* instuction name */
    unsigned int opcode;            /* Opcode value */
    bool srcAdressMode[4];     /* Valid source addressing mode this instruction can use */
    bool destAdressMode[4];    /* Valid Destination addressing mode this instruction can use */
} Instruction;

/* --check if given Instruction exists, if so return true else return false-- */
bool GetInstruction(char* InstructionName, Instruction* givenInstruction);

#endif
