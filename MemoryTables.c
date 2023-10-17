#include "MemoryTables.h"
#include <stdio.h>
#include <string.h>

/* -- Create Tables -- */
void CreateProgramTables(ProgramTables* programTables)  
{
    CreateNewList(&programTables->memoryTable,sizeof(Memory));
	CreateNewList(&programTables->symbolTable,sizeof(Symbol));
	programTables->sizeOfInstructions = 0;
}


/* -- Delete Tables -- */
void DeleteProgramTables(ProgramTables* programTables) 
{
    DeleteListNodes(&programTables->memoryTable);
	DeleteListNodes(&programTables->symbolTable);
}

/* -- Finds a symbol in symbol table -- */
bool FindSymbol(const List* symbolList, const StringP Symbolname , Symbol** Foundsymbol)
{
	Node* p = symbolList->head;
	Symbol* pCurrSymbol = NULL;

	while(p != NULL)
	{
		
		pCurrSymbol = (Symbol*) p->value;
		if(IsEqual(Symbolname, pCurrSymbol->name))
		{
			*Foundsymbol = pCurrSymbol;
			return true;
		}

		p = p->next;
	}

	return false;
}

bool AddNewSymbol(List* symbolList, const StringP name, const MemoryCell address, const StringP attribute) 
{
	Symbol tempSymbol;
	Symbol* pSymbol = NULL;
	bool bFound = FindSymbol(symbolList, name, &pSymbol);
	if(IsEqual(attribute, "external"))
	{
		/* symbol not found on symbol table */
	 	if(bFound == false)
		{
			pSymbol = &tempSymbol;
			strcpy(pSymbol->name, name);
			pSymbol->value = 0;
			strcpy(pSymbol->attributes, attribute);
			AddTail(symbolList, (void*) pSymbol);
		}
		

		if(bFound == true)
		{
			fprintf(stderr, "Failed: Symbol '%s' is defined as external and can't be declared twice\n", pSymbol->name);
			return false;
		}
	}
 	else if (IsEqual(attribute, "data") || IsEqual(attribute, "string") || IsEqual(attribute, "code") || IsEqual(attribute, "entry") || 															IsEqual(attribute, "struct")) 
	{ 
	
		/* Symbol not found. Insert as new symbol to symbol table */
	 	if(bFound == false)
		{
			/* -- Set symbol -- */
			pSymbol = &tempSymbol;
			strcpy(pSymbol->name, name);
			strcpy(pSymbol->attributes, attribute);
			pSymbol->value = address;
			
			/* -- Add to symbol table -- */
			AddTail(symbolList, (void*) pSymbol);
			
		}
		else
		{
			/* Check if symbol doesn't declared before */
			if(IsEqual(pSymbol->attributes, attribute))
			{
				fprintf(stderr, "Failed: Symbol '%s' has already been declared.\n", pSymbol->name);
				return false;
			}

			strcat(pSymbol->attributes, ", ");
			strcat(pSymbol->attributes, attribute);

			
			/* If it is a symbol (relocatable), set the address */
			if(IsEqual(attribute, "data") || IsEqual(attribute,"string") || IsEqual(attribute,"code") || IsEqual(attribute,"struct") || 					IsEqual(attribute,"entry"))
			{
				pSymbol->value = address;
			} 
			else
			{
				fprintf(stderr, "Failed: Symbol '%s' has already been declared.\n", pSymbol->name);
				return false;		
			}

		}

	}
	
	return true;
}

void SetInstrutionSize(ProgramTables* programTables)
{
	programTables->sizeOfInstructions = programTables->memoryTable.size;
}

bool AddInstruction(List* memoryTable, const MemoryCell codeValue, const StringP name, MemoryCell* address,  const unsigned int ARE)
{
    Memory entry;
    if(memoryTable->size == MEMORY_SPACE)
	{
		fprintf(stderr, "Failed: The program used all memory it has.\n");
		return false;
	}
	entry.codeValue = codeValue;
    	strcpy(entry.Symbolname, name); 
	entry.AREvalue = ARE;
    	AddTail(memoryTable, &entry);
   	*address = PROGRAM_ADDRESS + memoryTable->size -1;
    return true;
}


bool SetAddressToLabels(ProgramTables* programTables)
{
	bool bFlag = true;
	Node* p = programTables->memoryTable.head;
	MemoryCell jumpCounter = 100;
	MemoryCell jumpDistnace;
	String structName="";
	while(p)
	{
		Memory* pMemoryEntry = (Memory*) p->value;
		if(IsEqual(pMemoryEntry->Symbolname, "") == false)
		{
			Symbol* pSymbol;
			strncat(structName ,pMemoryEntry->Symbolname, strlen(pMemoryEntry->Symbolname) -2);
			if(FindSymbol(&(programTables->symbolTable), pMemoryEntry->Symbolname, &pSymbol) == false && FindSymbol(&(programTables->symbolTable), structName, &pSymbol) == 														false)									
			{
				bFlag = false;
				fprintf(stderr, "Error: Symbol\struct %s not found in Symbol Table\n", pMemoryEntry->Symbolname);
			}                                           
			else
			{
				if(pMemoryEntry->AREvalue == 'J')
				{
					if(IsEqual(pSymbol->attributes, "external"))
					{
						SetAddress(&(pMemoryEntry->codeValue), pSymbol->value);
						SetARE(&(pMemoryEntry->codeValue),1);/*E*/
						pMemoryEntry->AREvalue = 'E';
					} 
					else
					{
						SetAddress(&(pMemoryEntry->codeValue), pSymbol->value);
						SetARE(&(pMemoryEntry->codeValue),2);/*R*/
						pMemoryEntry->AREvalue = 'R';
					}
				} 
				else
				{
					jumpDistnace = jumpCounter - pSymbol->value;
					SetARE(&(pMemoryEntry->codeValue),0);
					pMemoryEntry->AREvalue = 'A';
				}
			}
			
		}
		jumpCounter++;
		p = p->next;
		strcpy(structName, "");
	}

	return bFlag;
}

void CreateOutPutFiles(const ProgramTables* programTable, const char* fName)
{
	CreateObFile(fName , programTable);
	CreateExternFile(fName, programTable);
	CreateEntryFile(fName, programTable);
}

void CreateObFile(const char* fName , const ProgramTables* programTable)
{
	Node* p = programTable->memoryTable.head;
	int address = PROGRAM_ADDRESS; 
	Result_t res1 ,res2 , res3 , res4;
	int length = strlen(fName);
	FILE* fOb = NULL;

	char* obfName = (char*) malloc(length + 4);

	if(obfName == NULL)
	{
		fprintf(stderr, "Error: malloc failed.");
		return ;
	}

	strcpy(obfName, fName);
	sprintf(obfName, "%s.ob", fName);

	fOb = fopen(obfName, "w");
	if(fOb == NULL)
	{
		fprintf(stderr, "Error: can't create file %s\n", obfName);
		return ;
	}

	DecimalTo32Base(programTable->sizeOfInstructions , res1);
	DecimalTo32Base(programTable->memoryTable.size - programTable->sizeOfInstructions , res2);

	fprintf(fOb, "   %c%c", res1[0] , res1[1]);
	fprintf(fOb, "   %c%c\n", res2[0] , res2[1]);

	while(p != NULL)
	{
		Memory* pInstructionCode = (Memory*) p->value;

		DecimalTo32Base(address,res3);
		DecimalTo32Base(pInstructionCode->codeValue, res4);

		fprintf(fOb, "   %c%c ", res3[0] , res3[1]);
		fprintf(fOb, "   %c%c \n", res4[0] , res4[1]);
		
		p = p->next;
		address++;

	}
	/* free string */
	free(obfName);
	
	/* close file */
	fclose(fOb);

}

bool CreateExternFile(const char* const fName, const ProgramTables* programTable) 
{
	FILE* fExtern = NULL;
	Node* pMemory = NULL;
	Node* p = programTable->symbolTable.head;
	MemoryCell nAddress = 0;
	Result_t res;

	while(p)
	{
		Symbol* pSymbol = (Symbol*) p->value;
		if(IsEqual(pSymbol->attributes, "external"))
		{
			pMemory = programTable->memoryTable.head;

			if(fExtern == NULL)
			{
				char* extName = (char*) malloc(strlen(fName) + 5);
				if(extName == NULL)
				{
					fprintf(stderr, "Error: allocation failed. Your computer has not enough memory.\n");
					return false;
				}
				
				sprintf(extName, "%s.ext", fName);
				fExtern = fopen(extName, "w");

				if(fExtern == NULL)
				{
					fprintf(stderr, "Error: Failed to create file %s\n", extName);
					return false;
				}

				free(extName);
			}

			nAddress = PROGRAM_ADDRESS;
			while(pMemory)
			{
				Memory* pMemoryEntry = (Memory*) pMemory->value;
				if(IsEqual(pSymbol->name, pMemoryEntry->Symbolname))
				{
					DecimalTo32Base(nAddress , res);
					fprintf(fExtern, "%s\t%s\n", pSymbol->name,res);
				}

				nAddress++;
				pMemory = pMemory->next;
			}
		}

		p = p->next;
	}

	if(fExtern)
	{
		fclose(fExtern);
	}

	return true;
} 
 
bool CreateEntryFile(const char* const fName, const ProgramTables* programTable)
{
	FILE* fEntry = NULL;
	Node* p = programTable->symbolTable.head;
	Result_t res;

	while(p)
	{
		Symbol* pSymbol = (Symbol*) p->value;
		if(strstr(pSymbol->attributes, "entry") != NULL)
		{
			if(fEntry == NULL)
			{
				char* entName = (char*) malloc(strlen(fName) + 5);
				if(entName == NULL)
				{
					fprintf(stderr, "Error: allocation failed. Your computer has not enough memory.\n");
					return false;
				}
				sprintf(entName, "%s.ent", fName);
				fEntry = fopen(entName, "w");

				if(fEntry == NULL)
				{
					fprintf(stderr, "Error: Failed to create file %s\n", entName);
					return false;
				}

				free(entName);
			}
			DecimalTo32Base(pSymbol->value , res);
			fprintf(fEntry, "%s\t%s\n", pSymbol->name, res);
		}

		p = p->next;
	}

	if(fEntry)
	{
		fclose(fEntry);
	}

	return true;
} 

