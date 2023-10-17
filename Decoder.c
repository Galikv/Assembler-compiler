#include "Decoder.h"

bool Decode(const StringP assemblyLine, ProgramTables* pogramTables, bool bHandleCommandStep)
{
	bool bFlag = true;
	List* origList = NULL;
	List list;
	String temp = "";
	String labelName = "";
	String instructionName = "";
	Node* p = NULL;

	if(strlen(assemblyLine) >= 1 && assemblyLine[strlen(assemblyLine)-1] == 10 || assemblyLine[strlen(assemblyLine) - 1] == 13)
	{
		assemblyLine[strlen(assemblyLine) - 1] = '\0';
	}

	origList = parseLine(assemblyLine);
	p = origList->head;
	CreateNewList(&list, sizeof(String));

	while(p != NULL && IsEqual(p->value, ";") == false)
	{
		String temp1 = "";
		strcpy(temp1, p->value);
		RemoveSpaces(temp1, temp);
		AddTail(&list, (void*) temp);

		p = p->next;
	}

	/* Delete origList */
	DeleteListNodes(origList);
	DeleteListPtr(origList);

	do
	{
		p = list.head;
		if(p == NULL)
		{
			break;
		}

		/* check if label */
		if(p->next != NULL && IsEqual((StringP)(p->next->value), ":"))
		{
			/* copy label */
			strcpy(labelName, p->value);
			/* skip label */
			p = p->next;
			/* skip ': */
			p = p->next;
		}
		else if(IsEqual(p->value, ":"))
		{
			fprintf(stderr, "Error: label name not exist before ':'.\n");
			bFlag = false;
			break;
		}
		
		/* instrcution */
		if(p == NULL)
		{
			fprintf(stderr, "Error: instruction not defined on '%s'.\n", assemblyLine);
			bFlag = false;
			break;
		}

		strcpy(instructionName, p->value);

	} while(0);

	if(bFlag && (IsEqual(labelName, "") == false || IsEqual(instructionName, "") == false))
	{
		if(IsEqual(labelName, "") == false && IsValidSymbol(labelName) == false)
		{
			fprintf(stderr, "Error: label '%s' invalid.\n", labelName);
			bFlag = false;
		}

		if(strlen(instructionName) == 0)
		{
			fprintf(stderr, "Error: No Instruction defined on '%s'.\n", assemblyLine);
			bFlag = false;
		}
		else
		{
			bool bInstruction = true;
			Instruction oInstruction;
			bInstruction = GetInstruction(instructionName, &oInstruction);
			if(bInstruction == false)
			{
				fprintf(stderr, "Error: Undefined command '%s'\n", instructionName);
			}

			bFlag &= bInstruction;

			if(bInstruction)
			{
				/* parse command */
				bFlag &= ParseCommand(oInstruction, labelName, &list, pogramTables, bHandleCommandStep);
			}
		}
	}

	DeleteListNodes(&list);
	
	return bFlag;
}

void RemoveSpaces(const StringP str, StringP newStr)
{
	int length = strlen(str);
	int start=0;
	int end=length;
	int i=0;

	if(end == -1)
	{
		return ;
	}

	/* Remove Left */
	for(i=0; i<length; i++)
	{
		if(str[i] != ' ')
		{
			break;
		}

		++start;
	}

	/* Remove Right */
	for(i=length - 1; i>=0; i--)
	{
		if(str[i] != ' ')
		{
			break;
		}

		--end;
	}

	if(start >= end)
	{
		strcpy(newStr, "");
	}
	else
	{
		strncpy(newStr, str + start, end - start);
		newStr[end - start] = '\0';
	}
}
List* parseLine(const StringP strp) 
{
	List* list = (List*) malloc(sizeof(List)); 
	String str = "";
	String sTemp = "";
	bool bInString = false;
	
	/* Delimeters */
	char TokenArr[] = {',', ':', '\t', '\"', ' '};
	int i=0;
	int count = 0;

	/* Create new list and return it back with all arguments */
	CreateNewList(list, sizeof(str));
	for(i=0; i<strlen(strp); i++)
	{
		bool bIsToken = false;
		int j;
		for(j=0; j<sizeof(TokenArr); j++)
		{
			if(strp[i] == TokenArr[j])
			{
				bIsToken = true;
				break;
			}
		}

		if(bIsToken)
		{
			 if(bInString && strp[i] != '\"')
			 {
				 continue;
			 }

			/* skip backspace */
			if(i - count > 0)
			{
				strncpy(str, strp + count, i-count);
				str[i-count] = '\0';
				AddTail(list, str);
			}

			if(strp[i] == '\"')
			{
				bInString = !bInString;
			}

			if(strp[i] != ' ')
			{
				str[0] = strp[i];
				str[1] = '\0';
				AddTail(list, str);
			}
			
			count = i + 1;
		}
	}

	strcpy(str, strp + count);
	RemoveSpaces(str, sTemp);
	if(IsEqual(sTemp, "") == false)
	{
		AddTail(list, sTemp);
	}

	return list;
}


bool IsValidNumber(const int pi_nNumber)
{
	return MIN_VALID_NUMBER <= pi_nNumber && pi_nNumber <= MAX_VALID_NUMBER;
}

/* Check if label has valid name */
bool IsValidSymbol(const StringP symbolName)
{
	int i;
	if(IsEqual(symbolName, "") || strlen(symbolName) > MAX_VALID_SYMBOL || (symbolName[0] >= '0' && symbolName[0] <= '9'))
	{
		return false;
	}

	for(i=0; i<strlen(symbolName); i++)
	{
		if((symbolName[i] >= '0' && symbolName[i] <= '9') == false && 
			(symbolName[i] >= 'A' && symbolName[i] <= 'z') == false)
		{
			return false;
		}
	}

	return true;
}

bool IsValidStruct(const StringP labelName)
{
	
	int i ;
	bool bDot = false;
	if(IsEqual(labelName, "") || strlen(labelName) > MAX_VALID_SYMBOL || ((labelName[0] >= '0' && labelName[0] <= '9')))
	{
		return false;
	}
	
	for(i=0; i<=strlen(labelName); i++)
	{
		if(bDot)
		{
			if(labelName[i] == '1' || labelName[i] == '2')
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		
		if(labelName[i] == '.')
		{
			bDot=true;
		}
		else
		{
			 if((labelName[i] >= '0' && labelName[i] <= '9') == false && 
			(labelName[i] >= 'A' && labelName[i] <= 'z') == false )
			{
				return false;
			}
		}
	}
	return false;
}
MemoryCell GetAddressingModeCode(const MemoryCell addressingMode) 
{
	switch(addressingMode)
	{
		case ADDRESSING_MODE_IMMEDIATE: 			return ADDRESSING_MODE_IMMEDIATE_VALUE;
		case ADDRESSING_MODE_DIRECT:				return ADDRESSING_MODE_DIRECT_VALUE;
		case ADDRESSING_MODE_STRUCT:		        return ADDRESSING_MODE_STRUCT_VALUE;
		case ADDRESSING_MODE_REGISTER_DIRECT:		return ADDRESSING_MODE_REGISTER_DIRECT_VALUE;
		default: return 0x0F;
	}
}

bool GetAddressingMode(const StringP sArg, MemoryCell* addressingMode) 
{
	int temp1 = 0;
	MemoryCell temp2 = 0;

	/* 00 - IMMEDIATE*/
	if(sArg[0] == '#')
	{
		if(changeStrToInt(sArg+1, &temp1) == false)
		{
			fprintf(stderr, "Error: Immediate addressing mode must get only number after '#'. The value %s is invalid.\n", sArg+1);
			*addressingMode = ADDRESSING_MODE_UNKNOWN; 
			return false;
		}

		if(IsValidNumber(temp1) == false)
		{
			fprintf(stderr, "Error: The value %d in immediate addressing mode is an out-of-range number.", temp1);
			*addressingMode = ADDRESSING_MODE_UNKNOWN; 
			return false;
		}
		*addressingMode = ADDRESSING_MODE_IMMEDIATE; 
		return true;
	}
	
	/* 11 - REGISTER_DIRECT */
	else if(GetRegisterNumber(sArg, &temp2))
	{	
		*addressingMode = ADDRESSING_MODE_REGISTER_DIRECT;		
		return true;
	}
	
	else
	{
		/* 10 - STRUCT */
		if(IsValidStruct(sArg) == true && IsValidSymbol(sArg) == false)
		{
			*addressingMode = ADDRESSING_MODE_STRUCT_VALUE;
			return true;
		}
		/* should be a symbol name */
		if(IsValidSymbol(sArg) == false && (IsValidStruct(sArg) == false))
		{
			fprintf(stderr, "Error: Invalid symbol\struct name '%s'\n", sArg);
			*addressingMode = ADDRESSING_MODE_UNKNOWN;
			return false;
		}
		/* 01 - DIRECT */
		*addressingMode = ADDRESSING_MODE_DIRECT;
		return true;
	}

}

bool ParseCommand(const Instruction instruct, const StringP label, const List* list, ProgramTables* pogramTables, bool bHandleCommandStep) 
{
	bool bFlag = true;
	List listArgs;
	CreateNewList(&listArgs, list->nodeSize);

	/* Check command found */
	if(instruct.opcode != 99)
	{
		Node* copyNode = list->head;
		if(IsEqual(label, "") == false)
		{
			/* Skip: '<lablel>' ':' */
			copyNode = copyNode->next->next;
		}

		/* skip command */
		copyNode = copyNode->next;

		/* Copy from 'copyNode' to tail */
		CopyListNodes(copyNode, list->tail, &listArgs);
	}
	/* Handle Entry and External */
	if(IsEqual(instruct.name, ".entry") || IsEqual(instruct.name, ".extern"))
	{
		bFlag &= addExternalOrEntry( &listArgs, pogramTables, bHandleCommandStep, instruct.name); 
	} 
	/* Handle Data */
	else if(IsEqual(instruct.name, ".data"))
	{
		bFlag = AddDataToTables(label, &listArgs, pogramTables, bHandleCommandStep);
	} 
	/* Handle String */
	else if(IsEqual(instruct.name, ".string"))
	{
		bFlag = AddStringToTables(label, &listArgs, pogramTables, bHandleCommandStep);
	}
	/* Handle Struct */
	else if(IsEqual(instruct.name, ".struct"))
	{
		bFlag = AddStructToTables(label, &listArgs, pogramTables, bHandleCommandStep);
	}
	else
	{
		bool bIstcructionWithSrc =  instruct.srcAdressMode[0] || 
					    instruct.srcAdressMode[1] || 
		       			    instruct.srcAdressMode[2] || 
		 			    instruct.srcAdressMode[3];

		bool bIstcructionWithDest = instruct.destAdressMode[0] || 
					    instruct.destAdressMode[1] || 
					    instruct.destAdressMode[2] || 
					    instruct.destAdressMode[3];
		
		if(bIstcructionWithSrc && bIstcructionWithDest)
		{
			/* command with 2 args */

			bFlag = Add2Args(instruct, label, &listArgs, pogramTables, bHandleCommandStep);
			
		}
		else if(!bIstcructionWithSrc && bIstcructionWithDest)
		{
			/* command with 1 arg */
			
			bFlag = Add1Args(instruct, label, &listArgs, pogramTables, bHandleCommandStep);
			
		}
		else if(!bIstcructionWithSrc && !bIstcructionWithDest)
		{
			/* command with 0 args */
			
			bFlag = Add0Args(instruct, label, &listArgs, pogramTables, bHandleCommandStep);
			
		}
		else
		{
			fprintf(stderr, "Error: command defined with src without target in Parser %d\n", __LINE__);
			bFlag = false;
		}
	}

	DeleteListNodes(&listArgs);
	return bFlag;
}

bool Add2Args(const Instruction instruct, const StringP label, const List* args, ProgramTables* pogramTables, bool bHandleCommandStep)
{
	/* memory code for src and destination */
	MemoryCell nSrcAddressingMode = 0;
	MemoryCell nDestAddressingMode = 0;

	bool bFlag = true;
	String src = "";
	String dest = "";
	MemoryCell codeValue = 0;
	MemoryCell address = 0;
	Node* p = args->head;
	char* pArg = src;

	if(bHandleCommandStep == false)
	{
		return bFlag;
	}

	/*-- Creating new list without whiteSpaces --*/
	while(p)
	{
		if(IsEqual((char*) p->value, " ") || IsEqual((char*) p->value, "\t"))
		{
			/*-- skip --*/
		}
		else if(IsEqual((char*) p->value, ","))
		{
			if(pArg == src)
			{
				pArg = dest;
			}
			else
			{
				fprintf(stderr, "Error: Can't have more than 1 ',' in instruction '%s'.\n", instruct.name);
				return false;
			}
		}
		else
		{
			if(IsEqual(pArg, "") == false)
			{
				fprintf(stderr, "Between 2 args must be ',' that seperate them.\n");
				pArg = NULL;
				break;
			}

			strcpy(pArg, p->value);
		}

		p = p->next;
	}
	

	if(pArg != dest)
	{
		fprintf(stderr, "Error: Instruction %s must get %d args.\n", instruct.name, 2);
		return false;
	}

	if(!IsEqual(args->head->next->value, ","))
	{
		fprintf(stderr, "Error: undefined using '%s' between args.\n", (char*) args->head->next->value);
		bFlag = false;
	}

	if(GetAddressingMode(src, &nSrcAddressingMode))
	{
		if(instruct.srcAdressMode[nSrcAddressingMode] == false)
		{
			fprintf(stderr, "Error: Source used an invalid addressing mode for opcode '%s'\n", instruct.name);
			bFlag = false;
		}
	}
	else
	{
		bFlag = false;
	}

	if(GetAddressingMode(dest, &nDestAddressingMode))
	{
		if(instruct.destAdressMode[nDestAddressingMode] == false)
		{
			fprintf(stderr, "Error: Destination used an invalid addressing mode for opcode '%s'\n", instruct.name);
			bFlag = false;
		}
	}
	else
	{
		bFlag = false;
	}

    	AddMemoryWord(&codeValue, GetAddressingModeCode(nSrcAddressingMode), GetAddressingModeCode(nDestAddressingMode), instruct.opcode,0);
	bFlag &= AddInstruction(&pogramTables->memoryTable, codeValue, "", &address, 'A');
	
	if(IsEqual(label, "") == false)
	{
		bFlag &= AddNewSymbol(&pogramTables->symbolTable, label, address, "code"); 
	}
	bFlag &= AddSrcDest(instruct, src, dest, pogramTables, 0);
	return bFlag;
}

bool Add1Args(const Instruction instruct, const StringP label, const List* args, ProgramTables* pogramTables, bool bHandleCommandStep)
{
	MemoryCell nDestAddressingMode = 0;
	bool bFlag = true;
	MemoryCell codeValue = 0;
	MemoryCell address = 0;
	String dest="";
	Node* p = args->head;
	char* pArg = dest;

	if(bHandleCommandStep == false)
	{
		return bFlag;
	}

	/*-- Creating new list without whiteSpaces --*/
	while(p)
	{
		if(IsEqual((char*) p->value, " ") || IsEqual((char*) p->value, "\t"))
		{
			/*-- skip --*/
		}
		else if(IsEqual((char*) p->value, ","))
		{
			fprintf(stderr, "Error: Can't have ',' in instruction '%s'.\n", instruct.name);
			return false;
		}
		else
		{
			if(IsEqual(pArg, "") == false)
			{
				fprintf(stderr, "Error: Invalid argument '%s' in instruction '%s'\n", (char*) p->value, instruct.name);
				pArg = NULL;
				break;
			}

			strcpy(pArg, p->value);
		}

		p = p->next;
	}

	if(pArg == NULL)
	{
		fprintf(stderr, "Error: Instruction %s must get %d args.\n", instruct.name, 1);
		return false;
	}
	if(GetAddressingMode(args->head->value, &nDestAddressingMode))
	{
		if(instruct.destAdressMode[nDestAddressingMode] == false)
		{
			fprintf(stderr, "Error: Destination used an invalid addressing mode for instruction '%s'\n", instruct.name);
			bFlag = false;
		}
	}
	else
	{
		bFlag = false;
	}

	/* Set Instruction for memory*/
    	AddMemoryWord(&codeValue, 0, GetAddressingModeCode(nDestAddressingMode), instruct.opcode , 0);

	/* Insert to memory */
	bFlag &= AddInstruction(&pogramTables->memoryTable, codeValue, "", &address, 'A');

	if(IsEqual(label, "") == false)
	{
		/* Insert to symbol table */
		bFlag &= AddNewSymbol(&pogramTables->symbolTable, label, address, "code");
	}
	/* Add src and target instructions */
	bFlag &= AddSrcDest(instruct, "", args->head->value, pogramTables, 0);
	return bFlag;
}

bool Add0Args(const Instruction instruct, const StringP label, const List* args, ProgramTables* pogramTables, bool bHandleCommandStep)
{
	bool bFlag = true;
	MemoryCell codeValue = 0;
	MemoryCell address = 0;
	Node* p = args->head;

	if(bHandleCommandStep == false)
	{
		return bFlag;
	}
	
	while(p)
	{
		if(IsEqual((char*) p->value, " ") == false && IsEqual((char*) p->value, "\t") == false)
		{
			fprintf(stderr, "Error: Invalid argument '%s' in opcode '%s'\n", (char*) p->value, instruct.name);
			fprintf(stderr, "Error: Instruction %s must get %d args.\n", instruct.name, 0);
			return false;
		}

		p = p->next;
	}

	/* Set instruction code */
   	AddMemoryWord(&codeValue, 0, 0, instruct.opcode , 0);

	/* Add instruction to memory */
	bFlag &= AddInstruction(&pogramTables->memoryTable, codeValue, "", &address, 'A');

	if(IsEqual(label, "") == false)
	{
		/* Add symbol to Symbol Table */
		bFlag &= AddNewSymbol(&pogramTables->symbolTable, label, address, "code");
	}

	return bFlag;
}

bool addExternalOrEntry( const List* args, ProgramTables* pogramTables, bool bHandleCommandStep, const char name[12])
{
    char attribute[12] = "external";
	if(bHandleCommandStep)
	{
		return true;
	}

	if(args->head == NULL)
	{
		fprintf(stderr, "Error: %s must have one argument.\n", name);
		return false;
	}

	if(args->head->next != NULL)
	{
		fprintf(stderr, "Error: %s can't have more than 1 argument.\n", name);
		return false;
	}
    if(IsEqual(name, ".entry"))
    {
        strcpy(attribute, "entry");
    }
	return AddNewSymbol(&(pogramTables->symbolTable), (char*) args->head->value, 0, (StringP) attribute);
}

bool AddSrcDest(const Instruction instruct, const StringP src, const StringP dest, ProgramTables* pogramTables, int count/*=0*/)
{
	bool bFlag = true;
	MemoryCell codeValue = 0;
	bool bHasSrcAndDest = !IsEqual(src, "") && !IsEqual(dest, "");
	MemoryCell address = 0;
	const bool bHasSrc = (count == 0 && bHasSrcAndDest);
	const StringP sArg = (bHasSrc ? src : dest);
	MemoryCell nSrcRegisterNumber , nDstRegisterNumber; 

	if(count > 1 || (count == 1 && !bHasSrcAndDest))
	{
		return bFlag;
	}
	/* 00 - IMMEDIATE*/
	if(sArg[0] == '#')
	{
		int num = 0;
		changeStrToInt(sArg + 1, &num);
		codeValue = FixNegativeNum(num);
		bFlag &= AddInstruction(&pogramTables->memoryTable, codeValue, "", &address, 'A');
	}
	/* 11 - REGISTER_DIRECT */
	else if(GetRegisterNumber(src, &nSrcRegisterNumber) && GetRegisterNumber(dest, &nDstRegisterNumber))
	{
		if(bHasSrc && (GetRegisterNumber(dest, &nDstRegisterNumber)))
		{
			SetRegisterAddress(&codeValue, nSrcRegisterNumber ,nDstRegisterNumber);
		}
		else
		{
			nDstRegisterNumber = 0;
			SetRegisterAddress(&codeValue, nSrcRegisterNumber ,nDstRegisterNumber);
		}
		bFlag &= AddInstruction(&pogramTables->memoryTable, codeValue, "", &address, 'A');
		count++;
	}
	/* 11 - REGISTER_DIRECT WITH ONLY 1 REGISTER */
	else if(GetRegisterNumber(sArg, &nSrcRegisterNumber))
	{
		if(bHasSrcAndDest && (GetRegisterNumber(dest, &nDstRegisterNumber)))
		{
			nSrcRegisterNumber = 0;
			SetRegisterAddress(&codeValue, nSrcRegisterNumber ,nDstRegisterNumber);
		}
		else
		{
			nDstRegisterNumber = 0;
			SetRegisterAddress(&codeValue, nSrcRegisterNumber ,nDstRegisterNumber);
		}
		bFlag &= AddInstruction(&pogramTables->memoryTable, codeValue, "", &address, 'A');
	}
	/* 01 - DIRECT */
	else if((IsValidSymbol(sArg) == true) && (IsValidStruct(sArg) == false )) 
	{
		/* value will be set later: value and ARE (still don't know if symbol or extern) */
		bFlag &= AddInstruction(&pogramTables->memoryTable, codeValue, sArg, &address, 'J');
	}
	/* 10 - STRUCT */
	else if(IsValidStruct(sArg)) 
	{		
		/* value will be set later: value and ARE (still don't know if symbol or extern) */
		/*add strcut address to table*/
		bFlag &= AddInstruction(&pogramTables->memoryTable, codeValue, sArg, &address, 'J');
		changeStrToInt(sArg + ((strlen(sArg) - 1)) , &codeValue);
		/*add the wanted field*/
		bFlag &= AddInstruction(&pogramTables->memoryTable, codeValue, sArg, &address, 'A');
		
	}
	else
	{
		fprintf(stderr, "Error: Undefined Error\n");
		bFlag = false;
	}

	return bFlag &&  AddSrcDest(instruct, src, dest, pogramTables, ++count);
}



bool AddDataToTables(const StringP label, const List* args, ProgramTables* pogramTables, bool bHandleCommandStep)
{
	bool bFlag = true;
	MemoryCell address =0;
	MemoryCell Temp1 = 0;
	Node* p = args->head;
	MemoryCell Temp2 = 0;
	int count = 0;


	if(bHandleCommandStep)
	{
		return bFlag;
	}

	while(p)
	{
		int nTemp = 0;
		String sValue;

		RemoveSpaces((char*) p->value, sValue);

		if(count % 2 == 1)
		{
			/* should receive ',' */
			if(sValue[0] != ',')
			{
				fprintf(stderr, "Error: invalid value '%s' in data.\n", sValue);
				bFlag = false;
			}
		}
		else
		{
			if(changeStrToInt(sValue, &nTemp) == false)
			{
				fprintf(stderr, "Error: Invalid value '%s' in data arguments. Only numbers are allowed.\n", sValue);
				bFlag = false;
			}
			else if(IsValidNumber(nTemp) == false)
			{
				fprintf(stderr, "Error: Used an out of range number '%d' in data.\n", nTemp);
				bFlag = false;
			}
			Temp2 = nTemp;
			bFlag &= AddInstruction(&pogramTables->memoryTable, FixNegativeNum(Temp2), "", &Temp1, 'A');
			if(address == 0 && IsEqual(label, "") == false)
			{
				address = Temp1;
			}
		}

		p = p->next;
		count++;
	}

	if(IsEqual(label, "") == false)
	{
		/* Insert to symbol table */
		bFlag &= AddNewSymbol(&pogramTables->symbolTable, label, address, "data");
	}

	return bFlag;
}
bool AddStructToTables(const StringP label, const List* args, ProgramTables* pogramTables, bool bHandleCommandStep)
{
	bool bFlag = true;
	MemoryCell adress =0;
	MemoryCell temp1 = 0;
	Node* p = args->head;
	MemoryCell temp2 = 0; 
	int count = 0;
	StringP str = "";
	int length = 0;
	int i;


	if(bHandleCommandStep)
	{
		return bFlag;
	}

	if(p)
	{
		int nTemp = 0;
		String sValue;


		RemoveSpaces((char*) p->value, sValue);

		if(count % 2 == 1)
		{
			/* should receive ',' */
			if(sValue[0] != ',')
			{
				fprintf(stderr, "Error: invalid value '%s' in data.\n", sValue);
				bFlag = false;
			}
		}
		else
		{
			if(changeStrToInt(sValue, &nTemp) == false)
			{
				fprintf(stderr, "Error: Invalid value '%s' in data arguments. Only numbers are allowed.\n", sValue);
				bFlag = false;
			}
			else if(IsValidNumber(nTemp) == false)
			{
				fprintf(stderr, "Error: Used an out of range number '%d' in data.\n", nTemp);
				bFlag = false;
			}
			temp2 = nTemp;
			bFlag &= AddInstruction(&pogramTables->memoryTable, FixNegativeNum(temp2), "", &temp1, 'A');
			if(adress == 0 && IsEqual(label, "") == false)
			{ 
				adress = temp1;
			}
		}

	}

	p = p->next->next;

	if(((char*) p->value)[0] != '\"')
	{
		fprintf(stderr, "Error: stirng must start with '\"'\n");
		bFlag = false;
	}

	if(((char*) args->tail->value)[0] != '\"')
	{
		fprintf(stderr, "Error: stirng must end with 1 '\"'\n");
		bFlag = false;
	}

	if(p == args->tail)
	{
		fprintf(stderr, "Error: string must end with 2 '\"'\n");
		bFlag = false;
	}

	if(bFlag == false)
	{
		return bFlag;
	}

	
	p = p->next;
	str = p->value;
	length = strlen(str);

	/* not empty string */
	if(p != args->tail)
	{
		for(i=0; i<length; i++)
		{
			bFlag &= AddInstruction(&pogramTables->memoryTable, str[i], "", &temp1, 'A'); 
			if(adress == 0 && IsEqual(label, "") == false)
			{
				adress = temp1;
			}
		}

		p = p->next;
	}
	bFlag &= AddInstruction(&pogramTables->memoryTable, 0, "", &temp1, 'A');
	if(adress == 0 && IsEqual(label, "") == false)
	{
		adress = temp1;
	}


	if(p != args->tail)
	{
		fprintf(stderr, "Error: string must end with 3 '\"\n");
		bFlag = false;
	}
	
	if(IsEqual(label, "") == false)
	{
		/* Insert to symbol table */
		bFlag &= AddNewSymbol(&pogramTables->symbolTable, label, adress, "struct");
	}

	return bFlag;
}
bool AddStringToTables(const StringP label, const List* args, ProgramTables* pogramTables, bool bHandleCommandStep)
{
	bool bFlag = true;
	MemoryCell address = 0;
	MemoryCell temp1 = 0;
	Node* p = args->head;
	StringP str = "";
	int length = 0;
	int i;

	if(bHandleCommandStep)
	{
		return bFlag;
	}

	if(((char*) p->value)[0] != '\"')/*-- not sure about it --*/
	{
		fprintf(stderr, "Error: stirng must start with '\"'\n");
		bFlag = false;
	}

	if(((char*) args->tail->value)[0] != '\"')
	{
		fprintf(stderr, "Error: stirng must end with '\"'\n");
		bFlag = false;
	}

	if(p == args->tail)
	{
		fprintf(stderr, "Error: string must end with '\"'\n");
		bFlag = false;
	}

	if(bFlag == false)
	{
		return bFlag;
	}

	p = p->next;
	str = p->value;
	length = strlen(str);

	/* not empty string */
	if(p != args->tail)
	{
		for(i=0; i<length; i++)
		{
			bFlag &= AddInstruction(&pogramTables->memoryTable, str[i], "", &temp1, 'A'); 
			if(address == 0 && IsEqual(label, "") == false)
			{
				address = temp1;
			}
		}

		p = p->next;
	}

	bFlag &= AddInstruction(&pogramTables->memoryTable, 0, "", &temp1, 'A');

	if(address == 0 && IsEqual(label, "") == false)
	{
		address = temp1;
	}

	if(p != args->tail)
	{
		fprintf(stderr, "Error: string must end with '\"\n");
		bFlag = false;
	}
	
	if(IsEqual(label, "") == false)
	{
		/* Insert to symbol table */
		bFlag &= AddNewSymbol(&pogramTables->symbolTable, label, address, "string");
	}


	return bFlag;
}
