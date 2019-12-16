#include <string.h>
#include "AMC_Functions.h"


/******************** FREE MEMORY OF EMPLOYEE STRUCT ******************************/
void AMC_FreeEmployeeStructMemory(struct EmployeeDetails *employee)
{
	if(employee == NULL)
		return;
	
	struct EmployeeDetails *temp = NULL;
	
	while(employee->nextDetails != NULL)
	{
		temp     = employee;
		employee = employee->nextDetails;
		free(temp);
	}
	free(employee);
	employee = NULL;
}

/******************** AMC_GetText ******************************************/
//getText
int AMC_GetText(HWND hwndEditClass, char **returnText)
{
	// int numberOfLine = SendMessage(hwndEditClass, EM_GETLINECOUNT, (WPARAM) 0, (LPARAM) 0);
	//return string length without null terminating character
	int stringLength = SendMessage(hwndEditClass, WM_GETTEXTLENGTH, (WPARAM)0, (LPARAM)0);
  if(*returnText != NULL)
		free(*returnText);
	*returnText = NULL;
	if(stringLength == 0)
		return(0);
	*returnText = (char*) malloc( (stringLength + 1) * sizeof(char));
	
	//WM_GETTEXT
	int numberOfCharacter = SendMessage(hwndEditClass, WM_GETTEXT, (WPARAM) (stringLength + 1), (LPARAM)(*returnText));
	
	return(numberOfCharacter);
}

///******************** AMC_SetText ******************************************/
//setText
int AMC_SetText(HWND hwndEditClass, char *str)
{
	SendMessage(hwndEditClass , WM_SETTEXT, (WPARAM)0, (LPARAM) str);
	return(strlen(str));
}


/******************** AMC_SetSelectedText ******************************************/
//setSelected text
int AMC_SetSelectedText(HWND listBoxClassHWND, HWND staticClassHWND)
{
	int index = SendMessage(listBoxClassHWND, LB_GETCURSEL, 0, 0);
	TCHAR str[127] = "\0";
	SendMessage(listBoxClassHWND, LB_GETTEXT, index, (LPARAM) str);
	//SetWindowText(staticClassHWND, string);
	SendMessage(staticClassHWND , WM_SETTEXT, (WPARAM)0, (LPARAM) str);
	ShowWindow (listBoxClassHWND, SW_HIDE);
	return(index);
}

/******************** AMC_SetIndex ******************************************/
void AMC_SetIndex(HWND listBoxClassHWND, HWND staticClassHWND, int index)
{
	SendMessage(listBoxClassHWND, LB_SETCURSEL, (WPARAM) index, (LPARAM) 0);
	
	TCHAR str[127] = "\0";
	SendMessage(listBoxClassHWND, LB_GETTEXT, (WPARAM) index, (LPARAM) str);
	SendMessage(staticClassHWND , WM_SETTEXT, (WPARAM)0     , (LPARAM) str);
}

