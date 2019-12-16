#include <stdio.h>
#include "AstroMediComp_Project_String.h"

int stringLength(char *str)
{
	if(str == NULL)
		return(-1);
	
	int i = 0;
	while(str[i] != '\0')  i++;
	
	return(i);
}

// 1 => both same
// 0 => not same
short stringsAreEqual(char *str1, char* str2)
{
	int a;
	if( (a = stringLength(str1)) == stringLength(str2))
	{
		if(a != -1)
		{
			short flag = 0;
			for(short i = 0; i < a; i++)
			{
				if(str1[i] == str2[i])
					flag = 1;
				else
				{
					flag = 0;
					break;
				}
			}
			if(flag == 1)
				return(1);
			else
				return(0);
		}
		else
		{
			return(-1);
		}
	}
	
	return(0);
}


// 1 => both same
// 0 => not same
short stringsAreEqualIgnoreCase(char *str1, char* str2)
{
	int a;
	if( (a = stringLength(str1)) == stringLength(str2))
	{
		if(a != -1)
		{
			short flag = 0;
			for(short i = 0; i < a; i++)
			{
				if(str1[i] >= 'a' && str1[i] <= 'z')
				{
					if( (str1[i] == str2[i]) || ((str1[i] - 32) == str2[i]) )
						flag = 1;
					else
					{
						flag = 0;
						break;
					}
				}
				else if(str1[i] >= 'A' && str1[i] <= 'Z')
				{
					if( (str1[i] == str2[i]) || ((str1[i] + 32) == str2[i]) )
						flag = 1;
					else
					{
						flag = 0;
						break;
					}
				}
				else if(str1[i] == str2[i])
					flag = 1;
				else
				{
					flag = 0;
					break;
				}
			}
			if(flag == 1)
				return(1);
			else
				return(0);
		}
		else
		{
			return(-1);
		}
	}
	
	return(0);
}


//1=>same
//0=>not
short compareStringWithInteger(char *str, int val)
{
	int length = stringLength(str);
	int num = 0;
	for(short i = 0; i < length; i++)
	{
		switch(str[i])
		{
			case '0': num = num * 10 + 0; break;
			case '1': num = num * 10 + 1; break;
			case '2': num = num * 10 + 2; break;
			case '3': num = num * 10 + 3; break;
			case '4': num = num * 10 + 4; break;
			case '5': num = num * 10 + 5; break;
			case '6': num = num * 10 + 6; break;
			case '7': num = num * 10 + 7; break;
			case '8': num = num * 10 + 8; break;
			case '9': num = num * 10 + 9; break;
		}
	}
	
	if(val == num)
		return(1);
	
	return(0);
}


void createFilesIfNotExist()
{
	FILE *fp = NULL;
		
	fp = fopen(".\\data\\WM_CREATE.dat"            , "w");
	fclose(fp);
	fp = fopen(".\\data\\WM_CREATE_INDEX.dat"      , "w");
	fclose(fp);
	
	fp = fopen(".\\data\\WM_LBUTTONDOWN.dat"       , "w");
	fclose(fp);
	fp = fopen(".\\data\\WM_LBUTTONDOWN_INDEX.dat" , "w");
	fclose(fp);
	
	fp = fopen(".\\data\\WM_SIZE.dat"              , "w");
	fclose(fp);
	fp = fopen(".\\data\\WM_SIZE_INDEX.dat"        , "w");
	fclose(fp);
	
	fp = fopen(".\\data\\WM_KEYUP.dat"             , "w");
	fclose(fp);
	fp = fopen(".\\data\\WM_KEYUP_INDEX.dat"       , "w");
	fclose(fp);
	
	fp = fopen(".\\data\\WM_KEYDOWN.dat"           , "w");
	fclose(fp);
	fp = fopen(".\\data\\WM_KEYDOWN_INDEX.dat"     , "w");
	fclose(fp);
	
	fp = fopen(".\\data\\WM_COMMAND.dat"           , "w");
	fclose(fp);
	fp = fopen(".\\data\\WM_COMMAND_INDEX.dat"     , "w");
	fclose(fp);
	
	fp = fopen(".\\data\\WM_DRAWITEM.dat"          , "w");
	fclose(fp);
	fp = fopen(".\\data\\WM_DRAWITEM_INDEX.dat"    , "w");
	fclose(fp);
	
	fp = fopen(".\\data\\WM_PAINT.dat"             , "w");
	fclose(fp);
	fp = fopen(".\\data\\WM_PAINT_INDEX.dat"       , "w");
	fclose(fp);
	
	fp = fopen(".\\data\\WM_CHAR.dat"              , "w");
	fclose(fp);
	fp = fopen(".\\data\\WM_CHAR_INDEX.dat"        , "w");
	fclose(fp);
	
	fp = fopen(".\\data\\WM_DESTROY.dat"           , "w");
	fclose(fp);
	fp = fopen(".\\data\\WM_DESTROY_INDEX.dat"     , "w");
	fclose(fp);
	
	fp = fopen(".\\data\\WM_SETFOCUS.dat"          , "w");
	fclose(fp);
	fp = fopen(".\\data\\WM_SETFOCUS_INDEX.dat"    , "w");
	fclose(fp);
	
	fp = fopen(".\\data\\WM_ENABLE.dat"            , "w");
	fclose(fp);
	fp = fopen(".\\data\\WM_ENABLE_INDEX.dat"      , "w");
	fclose(fp);
	
	fp = fopen(".\\data\\WM_MOUSEMOVE.dat"         , "w");
	fclose(fp);
	fp = fopen(".\\data\\WM_MOUSEMOVE_INDEX.dat"   , "w");
	fclose(fp);
	
	fp = fopen(".\\data\\WM_RBUTTONDOWN.dat"       , "w");
	fclose(fp);
	fp = fopen(".\\data\\WM_RBUTTONDOWN_INDEX.dat" , "w");
	fclose(fp);
	
	fp = fopen(".\\data\\EmployeeFile.dat", "w");
	fprintf(fp, "%4d", 0);
	fclose(fp);
	
	fp = fopen(".\\data\\AstroMediComp_Index.dat"                , "w");
	
	fprintf(
					fp,
					"%s %s %s\n",
					"WM_CREATE",
					".\\data\\WM_CREATE.dat",
					".\\data\\WM_CREATE_INDEX.dat"
					);
					
	fprintf(
					fp,
					"%s %s %s\n",
					"WM_LBUTTONDOWN",
					".\\data\\WM_LBUTTONDOWN.dat",
					".\\data\\WM_LBUTTONDOWN_INDEX.dat"
					);
					
	fprintf(
					fp,
					"%s %s %s\n",
					"WM_SIZE",
					".\\data\\WM_SIZE.dat",
					".\\data\\WM_SIZE_INDEX.dat"
					);
					
	fprintf(
					fp,
					"%s %s %s\n",
					"WM_KEYUP",
					".\\data\\WM_KEYUP.dat",
					".\\data\\WM_KEYUP_INDEX.dat"
					);
	
	fprintf(
					fp,
					"%s %s %s\n",
					"WM_KEYDOWN",
					".\\data\\WM_KEYDOWN.dat",
					".\\data\\WM_KEYDOWN_INDEX.dat"
					);
	
	fprintf(
					fp,
					"%s %s %s\n",
					"WM_COMMAND",
					".\\data\\WM_COMMAND.dat",
					".\\data\\WM_COMMAND_INDEX.dat"
					);
	
	fprintf(
					fp,
					"%s %s %s\n",
					"WM_DRAWITEM",
					".\\data\\WM_DRAWITEM.dat",
					".\\data\\WM_DRAWITEM_INDEX.dat"
					);
	
	fprintf(
					fp,
					"%s %s %s\n",
					"WM_PAINT",
					".\\data\\WM_PAINT.dat",
					".\\data\\WM_PAINT_INDEX.dat"
					);
	
	fprintf(
					fp,
					"%s %s %s\n",
					"WM_CHAR",
					".\\data\\WM_CHAR.dat",
					".\\data\\WM_CHAR_INDEX.dat"
					);
	
	fprintf(
					fp,
					"%s %s %s\n",
					"WM_DESTROY",
					".\\data\\WM_DESTROY.dat",
					".\\data\\WM_DESTROY_INDEX.dat"
					);
	
	fprintf(
					fp,
					"%s %s %s\n",
					"WM_SETFOCUS",
					".\\data\\WM_SETFOCUS.dat",
					".\\data\\WM_SETFOCUS_INDEX.dat"
					);
	
	fprintf(
					fp,
					"%s %s %s\n",
					"WM_ENABLE",
					".\\data\\WM_ENABLE.dat",
					".\\data\\WM_ENABLE_INDEX.dat"
					);
	
	fprintf(
					fp,
					"%s %s %s\n",
					"WM_MOUSEMOVE",
					".\\data\\WM_MOUSEMOVE.dat",
					".\\data\\WM_MOUSEMOVE_INDEX.dat"
					);
	
	fprintf(
					fp,
					"%s %s %s\n",
					"WM_RBUTTONDOWN",
					".\\data\\WM_RBUTTONDOWN.dat",
					".\\data\\WM_RBUTTONDOWN_INDEX.dat"
					);
	
	
	fclose(fp);
}


