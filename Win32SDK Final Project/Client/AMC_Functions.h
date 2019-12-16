#ifndef __AMC_FUNCTIONS_H__
#define __AMC_FUNCTIONS_H__

#include "Main.h"

void AMC_FreeEmployeeStructMemory(struct EmployeeDetails *);
int  AMC_GetText (HWND, char **);
int  AMC_SetText(HWND, char*);
void AMC_SetIndex(HWND , HWND , int);
int  AMC_SetSelectedText(HWND, HWND);

#endif
