#include "Utilities.h"

void Build32baseTable(Base bTable)
{
	int i , j=97;
	char c;
	for(i=10;i<32;i++)
	{	
		c=(char)j;
		bTable[i] =c;
		j++;

	}
	bTable[0]='!';
	bTable[1]='@';
	bTable[2]='#';
	bTable[3]='$';
	bTable[4]='%';
	bTable[5]='^';
	bTable[6]='&';
	bTable[7]='*';
	bTable[8]='<';
	bTable[9]='>';

}
void DecimalTo32Base(int dec , Result_t res)
{	
	int i=0;	
	Base bTable;
	Build32baseTable(bTable);
	while(dec-32 >= 0)
	{
		dec = dec-32;
		i++;
	}
	res[0]=bTable[i];
	res[1]=bTable[dec];
	
}

bool changeStrToInt(const StringP str, int* num)
{
	int i=0;
	int len = strlen(str);
	bool bNegative = false;
	bool bPositive = false;

	*num = 0;

	if(len == 0)
	{
		return false;
	}
	
	for(i=0; i<len; i++)
	{
		/* get digits */
		int nDigit = str[i] - '0';

		if(i == 0 && str[i] == '-')
		{
			bNegative = true;
			continue;
		}
		if(i == 0 && str[i] == '+')
		{
			bPositive = true;
			continue;
		}

		if(0 > nDigit || 9 < nDigit)
		{
			return false;
		}

		if(i == 0 || (bNegative && i == 1))
		{
			*num = nDigit;
		}
		else if(i == 0 || (bPositive && i == 1))
		{
			*num *= 10;
			*num += nDigit;
		}
		else
		{
			*num *= 10;
			*num += nDigit;
		}
	}

	/* return as negative */
	if(bNegative)
	{
		*num *= -1;
	}
	return true;
}

bool IsEqual(const char* str1, const char* str2)
{
    int equal = strcmp(str1, str2);
    if (equal == 0)
        return true;
    return false;
}

MemoryCell FixNegativeNum(MemoryCell pi_nNumber) 
{
    	if(pi_nNumber >= 0)
	{
		return pi_nNumber;
	}
	pi_nNumber *= -1;
	pi_nNumber = ~pi_nNumber;
	pi_nNumber += 1;
	pi_nNumber &= 0x3FF;

	return pi_nNumber;
}

bool GetRegisterNumber(StringP regName, MemoryCell* regNum)
{
    int nNumber = 0;
	if(strlen(regName) != 2 || regName[0] != 'r' || changeStrToInt(regName + 1, &nNumber) == false)
	{
		return false;
	}
	if(nNumber >= 0 && nNumber <= 7)
	{
		*regNum = nNumber;
		return true;
	}
	return false;
}
