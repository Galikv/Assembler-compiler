#ifndef _MEMORY_TABLES_H_
#define _MEMORY_TABLES_H_

#include "List.h"
#include "Utilities.h"
#include "Instructions.h"
#include "MemoryStruct.h"

/* Symbol data structure */
typedef struct Symbol
{
    SymbolString name;
    MemoryCell value;
    char attributes[12];
} Symbol;

/* Memory data structure that will be stored as an entry in the memory table */
typedef struct Memory
{
    MemoryCell codeValue; /* code value after processing  */
    String Symbolname; /* if there is a symbol in this row, symbol name will be saved here */
    char AREvalue;
} Memory;

typedef struct ProgramTables
{
    List memoryTable;
    List symbolTable;
    int sizeOfInstructions;
} ProgramTables;



/* ---Handles tables--- */
/* Initialize the Perogram table */
void CreateProgramTables(ProgramTables* programTables);
/* Delete Perogram table */
void DeleteProgramTables(ProgramTables* programTables);
/* --Finds Symbol in Symbol table-- */
bool FindSymbol(const List* symbolList, const StringP Symbolname , Symbol** Foundsymbol);
/*-- Adds new symbol to symbol table-- */
bool AddNewSymbol(List* symbolList, const StringP name, const MemoryCell address, const StringP attribute);


/*--Sets instrution size --*/
void SetInstrutionSize(ProgramTables* programTables);

/*-- Add instruction to memory table-- */
bool AddInstruction(List* memoryTable, const MemoryCell codeValue, const StringP name, MemoryCell* address,  const unsigned int ARE);

/*-- Second transition over the assembly code , setting labels addresses  --*/
bool SetAddressToLabels(ProgramTables* programTables);


/*--- Handles out put files ---*/
void CreateOutPutFiles(const ProgramTables* programTable, const char* fName);
/* Create object File */
void CreateObFile(const char* fName , const ProgramTables* programTable);
/* Create External File */
bool CreateExternFile(const char* const fName, const ProgramTables* programTable) ;
/* Create Entry File */
bool CreateEntryFile(const char* const fName, const ProgramTables* programTable);



















void SetCurrentSizeAsInstrutionSize(ProgramTables* programTables);

/* Delete Perogram table. */
void DeleteProgramTables(ProgramTables* programTables);


/* Print symbol table. */
void PrintSymbolTable(List* symbolList);

/* Search symbol in symbol table. */
bool FindSymbol(const List* symbolList, const StringP symbolName, Symbol** Foundsymbol);

/* add or Update symbol entry in symbol table. */
bool AddNewSymbol(List* symbolList, const StringP symbolName, const MemoryCell symbolAddress, const StringP symbolAttribute);

/* Set all places in code that used symbols in opcode with the address of the symbols */
bool SetAddressToLabels(ProgramTables* pProgramTables);

/* Delete symbol table. */
void DeleteSymbolTable(List* symbolList);


/* Memory table Functions. */

/* Print memory table to file.----------------------------------------צריך לשנות --------------------------------*/ 
void PrintMemoryTable(const ProgramTables* programTable, const char* pi_sFileName);

/* Delete memory table. */
void DeleteMemoryTable(List* memoryList);

#endif
