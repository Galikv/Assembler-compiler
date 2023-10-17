#include "macro.h"
#include "Decoder.h"


void InitMacroTable(List* MacroList)
{
	CreateNewList(MacroList, sizeof(Macro));
}
bool addMacroToTable(const FILE* filep, MacroTable* MacroList)
{
	bool bStatus = true;
	List* pOrigList = NULL;
	List list;
	String sTemp = "";
	/*String sLabel = "";*/
	Node* p = NULL;
	char buffLine[MAX_ROW_LENGTH] = "";
	char buffLine2[MAX_ROW_LENGTH] = "";

	CreateNewList(&MacroList->list, sizeof(Macro));

	while(fgets(buffLine, MAX_ROW_LENGTH, filep))	
	{

	/*if(strlen(assemblyLine) >= 1 && assemblyLine[strlen(assemblyLine)-1] == 10 || assemblyLine[strlen(assemblyLine) - 1] == 13)
	{
		assemblyLine[strlen(assemblyLine) - 1] = '\0';
	}*/

	
		pOrigList = parseLine(buffLine);
		p = pOrigList->head;
		CreateNewList(&list, sizeof(String));
		
		while(p != NULL)
		{
			String sTemp1 = "";
			strcpy(sTemp1, p->value);
			AddTail(&list, (void*) sTemp1);
			p = p->next;
		}


		p = list.head;
			
		/*--CHECK IF STARTS WITH MACRO--*/
		if(IsEqual((StringP)(p->value), "macro"))
		{
			Macro * macroTemp = ( Macro*) malloc(sizeof(Macro));
			macroTemp->mName = ( char*) malloc(sizeof(String));
		
		
			p = p->next;
			/*-- Is valid name--*/
			if(IsEqual(p->value, ".struct") || IsEqual(p->value, ".entry") || IsEqual(p->value, ".extern") || IsEqual(p->value, ".data") || 				IsEqual(p->value,".string") || IsEqual(p->value, "mov") || IsEqual(p->value, "add") || IsEqual(p->value, "cmp") || 				IsEqual(p->value,"sub") || IsEqual(p->value, "lea")|| IsEqual(p->value, "clr") || IsEqual(p->value, "not") || 				IsEqual(p->value,"inc") || IsEqual(p->value, "dec") || IsEqual(p->value, ".jmp") || IsEqual(p->value, "bne")|| 				IsEqual(p->value,"jsr") || IsEqual(p->value, "get") || IsEqual(p->value, "prn") || IsEqual(p->value, "rts") || 				IsEqual(p->value, "hlt")) 
			{
				bStatus = false;
				return bStatus;
			}
			strcpy(macroTemp->mName , p->value);
			p = p->next;

			CreateNewList(&macroTemp->mValue, sizeof(String));
			
			while(fgets(buffLine2, MAX_ROW_LENGTH, filep))
			{
				pOrigList = parseLine(buffLine2);
				p = pOrigList->head;
				/*--CHECK IF ENDS WITH "ENDMACRO"*/
				if(IsEqual((StringP)(p->value), "endmacro\n"))
				{
					break;
				}
				AddTail(&macroTemp->mValue, buffLine2);
				memset(buffLine2, 0, sizeof buffLine2);
				
			}
			AddTail(&MacroList->list, (void*) macroTemp);
		}
	
		DeleteListNodes(&list);
	}
	return bStatus;
}


/*bool SwitchMacro(const StringP assemblyLine, MacroTable* MacroList ,const char* pi_sFileName)
{
		
}*/

