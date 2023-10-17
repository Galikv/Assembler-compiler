#ifndef _UTILITIES_H_
#define _UTILITIES_H_
#include <stdint.h>
#include <string.h>

/* Defines */
#define MEMORY_SPACE 			256
#define MAX_VALID_SYMBOL		30
#define PROGRAM_ADDRESS			100
#define MAX_ROW_LENGTH			81
#define MEMORY_SIZE                     10
#define MIN_VALID_NUMBER		-1024
#define MAX_VALID_NUMBER		1023


/* Types */
typedef int8_t bool;
#define true 1
#define false 0
typedef char String[MAX_ROW_LENGTH];
typedef char* StringP;
typedef char SymbolString[MAX_VALID_SYMBOL + 1];
typedef char Result_t[2];
typedef int16_t MemoryCell;
typedef char Base[32];

/*-- Bulid 32 bade table --*/
void Build32baseTable(Base bTable);

/*-- convert decimal to 32 base --*/
void DecimalTo32Base(int dec , Result_t res);

/*-- Get number from string --*/
bool changeStrToInt(const StringP str, int* num);

/*-- Checks if 2 string are equal --*/
bool IsEqual(const char* str1, const char* str2);

/*-- fix negative number before insert to memory (two complement system)--*/
MemoryCell FixNegativeNum(MemoryCell pi_nNumber) ;

/*-- Gets register num from register name (if isnt register return false)--*/
bool GetRegisterNumber(StringP regName, MemoryCell* regNum);


#endif
