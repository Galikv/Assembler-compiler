#ifndef _MACRO_H_
#define _MACRO_H_


#include "List.h"
#include <string.h>
#include <stdio.h> 
#include "Utilities.h"
#include "MemoryTables.h"

/* macro structure */
typedef struct Macro
{
    char* mName;
    List mValue;
} Macro;

/* -- macro table-- */
typedef struct MacroTable
{
    List list;
} MacroTable;


bool addMacroToTable(const FILE* filep, MacroTable* MacroList);

bool SwitchMacro(const StringP assemblyLine, MacroTable* MacroList ,const char* pi_sFileName);

#endif
