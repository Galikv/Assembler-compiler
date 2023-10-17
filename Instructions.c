#include "Instructions.h"
#include <stdio.h>

bool GetInstruction(char* InstructionName, Instruction* givenInstruction)
{
    if(IsEqual(InstructionName, "mov"))
    {
        givenInstruction->opcode = 0;
        strcpy(givenInstruction->name, "mov");

        givenInstruction->srcAdressMode[ADDRESSING_MODE_IMMEDIATE] =           true;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_DIRECT] =              true;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_STRUCT] =              true;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =     true;

        givenInstruction->destAdressMode[ADDRESSING_MODE_IMMEDIATE] =          false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_DIRECT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_STRUCT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =    true;

        return true;

    } else if(IsEqual(InstructionName, "cmp")){
        givenInstruction->opcode = 1;
        strcpy(givenInstruction->name, "cmp");

        givenInstruction->srcAdressMode[ADDRESSING_MODE_IMMEDIATE] =           true;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_DIRECT] =              true;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_STRUCT] =              true;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =     true;

        givenInstruction->destAdressMode[ADDRESSING_MODE_IMMEDIATE] =          true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_DIRECT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_STRUCT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =    true;

        return true;

    } else if(IsEqual(InstructionName, "add")){

        givenInstruction->opcode = 2;
        strcpy(givenInstruction->name, "add");

        givenInstruction->srcAdressMode[ADDRESSING_MODE_IMMEDIATE] =           true;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_DIRECT] =              true;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_STRUCT] =              true;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =     true;

        givenInstruction->destAdressMode[ADDRESSING_MODE_IMMEDIATE] =          false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_DIRECT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_STRUCT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =    true;

        return true;

    } else if(IsEqual(InstructionName, "sub")){
        givenInstruction->opcode = 3; 
        strcpy(givenInstruction->name, "sub");


        givenInstruction->srcAdressMode[ADDRESSING_MODE_IMMEDIATE] =           true;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_DIRECT] =              true;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_STRUCT] =              true;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =     true;

        givenInstruction->destAdressMode[ADDRESSING_MODE_IMMEDIATE] =          false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_DIRECT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_STRUCT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =    true;

        return true;

    } else if(IsEqual(InstructionName, "lea")){

        givenInstruction->opcode = 6;
        strcpy(givenInstruction->name, "lea");

        givenInstruction->srcAdressMode[ADDRESSING_MODE_IMMEDIATE] =           false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_DIRECT] =              true;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_STRUCT] =              true;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =     false;

        givenInstruction->destAdressMode[ADDRESSING_MODE_IMMEDIATE] =          false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_DIRECT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_STRUCT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =    true;

        return true;
        
    } else if(IsEqual(InstructionName, "clr")){

        givenInstruction->opcode = 5;
        strcpy(givenInstruction->name, "clr");

        givenInstruction->srcAdressMode[ADDRESSING_MODE_IMMEDIATE] =           false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_DIRECT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_STRUCT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =     false;

        givenInstruction->destAdressMode[ADDRESSING_MODE_IMMEDIATE] =          false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_DIRECT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_STRUCT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =    true;

        return true;

    } else if(IsEqual(InstructionName, "not")){

        givenInstruction->opcode = 4;
        strcpy(givenInstruction->name, "not");

        givenInstruction->srcAdressMode[ADDRESSING_MODE_IMMEDIATE] =           false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_DIRECT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_STRUCT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =     false;

        givenInstruction->destAdressMode[ADDRESSING_MODE_IMMEDIATE] =          false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_DIRECT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_STRUCT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =    true;

        return true;

    } else if(IsEqual(InstructionName, "inc")){

        givenInstruction->opcode = 7;

        givenInstruction->srcAdressMode[ADDRESSING_MODE_IMMEDIATE] =           false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_DIRECT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_STRUCT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =     false;

        givenInstruction->destAdressMode[ADDRESSING_MODE_IMMEDIATE] =          false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_DIRECT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_STRUCT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =    true;

        return true;

    } else if(IsEqual(InstructionName, "dec")){

        givenInstruction->opcode = 8;
        strcpy(givenInstruction->name, "dec");

        givenInstruction->srcAdressMode[ADDRESSING_MODE_IMMEDIATE] =           false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_DIRECT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_STRUCT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =     false;

        givenInstruction->destAdressMode[ADDRESSING_MODE_IMMEDIATE] =          false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_DIRECT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_STRUCT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =    true;

        return true;

    } else if(IsEqual(InstructionName, "jmp")){
        givenInstruction->opcode = 9;
        strcpy(givenInstruction->name, "jmp");

        givenInstruction->srcAdressMode[ADDRESSING_MODE_IMMEDIATE] =           false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_DIRECT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_STRUCT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =     false;

        givenInstruction->destAdressMode[ADDRESSING_MODE_IMMEDIATE] =          false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_DIRECT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_STRUCT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =    true;

        return true;

    } else if(IsEqual(InstructionName, "bne")){

        givenInstruction->opcode = 10;
        strcpy(givenInstruction->name, "bne");

        givenInstruction->srcAdressMode[ADDRESSING_MODE_IMMEDIATE] =           false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_DIRECT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_STRUCT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =     false;

        givenInstruction->destAdressMode[ADDRESSING_MODE_IMMEDIATE] =          false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_DIRECT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_STRUCT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =    true;

        return true;

    } else if(IsEqual(InstructionName, "jsr")){
        givenInstruction->opcode = 13;
        strcpy(givenInstruction->name, "jsr");

        givenInstruction->srcAdressMode[ADDRESSING_MODE_IMMEDIATE] =           false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_DIRECT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_STRUCT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =     false;

        givenInstruction->destAdressMode[ADDRESSING_MODE_IMMEDIATE] =          false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_DIRECT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_STRUCT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =    true;

        return true;

    } else if(IsEqual(InstructionName, "get")){
        
        givenInstruction->opcode = 11;
        strcpy(givenInstruction->name, "get");

        givenInstruction->srcAdressMode[ADDRESSING_MODE_IMMEDIATE] =           false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_DIRECT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_STRUCT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =     false;

        givenInstruction->destAdressMode[ADDRESSING_MODE_IMMEDIATE] =          false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_DIRECT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_STRUCT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =    true;

        return true;

    } else if(IsEqual(InstructionName, "prn")){

        givenInstruction->opcode = 12;
        strcpy(givenInstruction->name, "prn");

        givenInstruction->srcAdressMode[ADDRESSING_MODE_IMMEDIATE] =           false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_DIRECT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_STRUCT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =     false;

        givenInstruction->destAdressMode[ADDRESSING_MODE_IMMEDIATE] =          true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_DIRECT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_STRUCT] =             true;
        givenInstruction->destAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =    true;

        return true;

    } else if(IsEqual(InstructionName, "rts")){

        givenInstruction->opcode = 14;
        strcpy(givenInstruction->name, "rts");
        
        givenInstruction->srcAdressMode[ADDRESSING_MODE_IMMEDIATE] =           false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_DIRECT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_STRUCT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =     false;

        givenInstruction->destAdressMode[ADDRESSING_MODE_IMMEDIATE] =          false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_DIRECT] =             false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_STRUCT] =             false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =    false;

        return true;

    } else if(IsEqual(InstructionName, "hlt")){

        givenInstruction->opcode = 15;
        strcpy(givenInstruction->name, "hlt");
        
        givenInstruction->srcAdressMode[ADDRESSING_MODE_IMMEDIATE] =           false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_DIRECT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_STRUCT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =     false;

        givenInstruction->destAdressMode[ADDRESSING_MODE_IMMEDIATE] =          false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_DIRECT] =             false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_STRUCT] =             false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =    false;

        return true;

    } else if(IsEqual(InstructionName, ".data")){
        
        givenInstruction->opcode = 20;
        strcpy(givenInstruction->name, ".data");
        
        givenInstruction->srcAdressMode[ADDRESSING_MODE_IMMEDIATE] =           false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_DIRECT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_STRUCT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =     false;

        givenInstruction->destAdressMode[ADDRESSING_MODE_IMMEDIATE] =          false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_DIRECT] =             false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_STRUCT] =             false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =    false;

        return true;

    } else if(IsEqual(InstructionName, ".string")){
        
        givenInstruction->opcode = 30;
        strcpy(givenInstruction->name, ".string");
        
        givenInstruction->srcAdressMode[ADDRESSING_MODE_IMMEDIATE] =           false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_DIRECT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_STRUCT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =     false;

        givenInstruction->destAdressMode[ADDRESSING_MODE_IMMEDIATE] =          false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_DIRECT] =             false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_STRUCT] =             false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =    false;

        return true;

    } else if(IsEqual(InstructionName, ".entry")){
        givenInstruction->opcode = 40;
        strcpy(givenInstruction->name, ".entry");
        
        givenInstruction->srcAdressMode[ADDRESSING_MODE_IMMEDIATE] =           false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_DIRECT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_STRUCT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =     false;

        givenInstruction->destAdressMode[ADDRESSING_MODE_IMMEDIATE] =          false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_DIRECT] =             false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_STRUCT] =             false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =    false;

        return true;

    } else if(IsEqual(InstructionName, ".extern")){

        givenInstruction->opcode = 50;
        strcpy(givenInstruction->name, ".extern");
        
        givenInstruction->srcAdressMode[ADDRESSING_MODE_IMMEDIATE] =           false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_DIRECT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_STRUCT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =     false;

        givenInstruction->destAdressMode[ADDRESSING_MODE_IMMEDIATE] =          false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_DIRECT] =             false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_STRUCT] =             false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =    false;

        return true;

    } else if(IsEqual(InstructionName, ".struct")){
        
        givenInstruction->opcode = 60;
        strcpy(givenInstruction->name, ".struct");
        
        givenInstruction->srcAdressMode[ADDRESSING_MODE_IMMEDIATE] =           false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_DIRECT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_STRUCT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =     false;

        givenInstruction->destAdressMode[ADDRESSING_MODE_IMMEDIATE] =          false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_DIRECT] =             false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_STRUCT] =             false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =    false;

        return true;

    } else {
        /* invalid instruction name */
        givenInstruction->opcode = 99;
        strcpy(givenInstruction->name, "");

        givenInstruction->srcAdressMode[ADDRESSING_MODE_IMMEDIATE] =           false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_DIRECT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_STRUCT] =              false;
        givenInstruction->srcAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =     false;

        givenInstruction->destAdressMode[ADDRESSING_MODE_IMMEDIATE] =          false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_DIRECT] =             false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_STRUCT] =             false;
        givenInstruction->destAdressMode[ADDRESSING_MODE_REGISTER_DIRECT] =    false;

        return false;
    }
}

