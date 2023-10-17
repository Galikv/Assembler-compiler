#ifndef _DECODER_H_
#define _DECODER_H_

#include "Utilities.h"
#include "List.h"
#include "MemoryTables.h"
#include <string.h>
#include <stdio.h> 
#include "Instructions.h"
#include "MemoryStruct.h"

/*-- First transition over the assembly code --*/
bool Decode(const StringP assemblyLine, ProgramTables* pogramTables, bool bHandleCommandStep);

/*-- Removes white spaces --*/
void RemoveSpaces(const StringP str, StringP newStr);

/*-- Checks that line is valid and needs to be decoded --*/
List* parseLine(const StringP str);

/*-- validation checks --*/
bool IsValidNumber(const int pi_nNumber);
bool IsValidStruct(const StringP labelName);
bool IsValidSymbol(const StringP symbolName);

/*-- Handle register dierect --*/
MemoryCell GetAddressingModeCode(const MemoryCell addressingMode);

bool GetAddressingMode(const StringP sArg, MemoryCell* addressingMode) ;


/*-- Parses the current line --*/
bool ParseCommand(const Instruction instruct, const StringP label, const List* list, ProgramTables* pogramTables, bool bHandleCommandStep);

/*-- Handle adding args to tables --*/
/*-- case1: the assembly line has 2 args (meaning: has destenation and source) --*/
bool Add2Args(const Instruction instruct, const StringP label, const List* args, ProgramTables* pogramTables, bool bHandleCommandStep);

/*case2: the assembly line has 1 arg (meaning: has only destenation)*/
bool Add1Args(const Instruction instruct, const StringP label, const List* args, ProgramTables* pogramTables, bool bHandleCommandStep);

/*case3: the assembly line has 0 args (meaning: has no destenation nor source)*/
bool Add0Args(const Instruction instruct, const StringP label, const List* args, ProgramTables* pogramTables, bool bHandleCommandStep);

/*-- Adds source and destenation according to the amount of args --*/
bool AddSrcDest(const Instruction instruct, const StringP src, const StringP dest, ProgramTables* pogramTables, int count);


/*-- Adding data to tables --*/
bool addExternalOrEntry(const List* args, ProgramTables* pogramTables, bool bHandleCommandStep, const char name[12]);

bool AddDataToTables(const StringP label, const List* args, ProgramTables* pogramTables, bool bHandleCommandStep);

bool AddStructToTables(const StringP label, const List* args, ProgramTables* pogramTables, bool bHandleCommandStep);

bool AddStringToTables(const StringP label, const List* args, ProgramTables* pogramTables, bool bHandleCommandStep);

#endif
