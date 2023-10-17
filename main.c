#include <stdio.h>
#include "Utilities.h"
#include "Instructions.h"
#include "MemoryTables.h"
#include "Decoder.h"
#include "macro.h"

int main(int argc, char** argv)
{
	ProgramTables oProgramTables;
	MacroTable oMacrolist;
	String sFileName = "";
	int i;
	FILE* pFileAssembly = NULL;
	/*FILE* pFileMacro= NULL;*/
	char currLine[MAX_ROW_LENGTH] = "";

	/* check contain any file */
	if(argc == 1)
	{
		fprintf(stderr, "Please add a file as argument.\n");
		return 0;
	}

	/*--add macro to tables--*/
	/*for(i=1; i<argc; i++)
	{
		bool bFlag = true;
		sprintf(sFileName, "%s.as", argv[i]);
		pFileMacro = fopen(sFileName, "r");

		if(pFileMacro == NULL)
		{
			fprintf(stderr, "Failed: The file %s does not exists.\n", sFileName);
			continue;
		}

		fprintf(stdout, "Open file %s and start creating macro files..\n", sFileName);		
		
		InitMacroTable(&oMacrolist);

		bFlag &= addMacroToTable(pFileMacro, &oMacrolist);

		/* put cursor at start of file */
		/*fseek(pFileMacro, 0 , SEEK_SET);

	}*/
	for(i=1; i<argc; i++)
	{
		int k;
		bool bFlag = true;
		sprintf(sFileName, "%s.as", argv[i]);
		pFileAssembly = fopen(sFileName, "r");

		if(pFileAssembly == NULL)
		{
			fprintf(stderr, "Error: The file %s does not exists.\n", sFileName);
			continue;
		}

		fprintf(stdout, "Open file %s and start creating output files..\n", sFileName);
		
		CreateProgramTables(&oProgramTables);

		for(k=0; k<=1; k++)
		{
			while (fgets(currLine, MAX_ROW_LENGTH, pFileAssembly))
			{
				bFlag &= Decode(currLine, &oProgramTables, k==0);
			}

			if(k == 0)	

			{
				SetInstrutionSize(&oProgramTables);
			}

			/* put cursor at start of file */
			fseek(pFileAssembly, 0 , SEEK_SET);
		}

		 if(bFlag)
		{
			bFlag &= SetAddressToLabels(&oProgramTables);
		}

		if(bFlag)
		{
			fprintf(stdout, "Assembly file %s.as successfuly parsed and decoded.\n", argv[i]);
		}
		else
		{
			fprintf(stdout, "Assembly file %s.as failed on parsing/decoding.\n", argv[i]);
		}

		if(bFlag)
		{
			 CreateOutPutFiles(&oProgramTables, argv[i]);
		}
		
		DeleteProgramTables(&oProgramTables);
	}

	return 0;
}
