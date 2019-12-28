#include <windows.h>
#include <stdio.h>
#include <commdlg.h>
#include <ole2.h>

#include "SaveAsDialog.h"


/******************** EXPORT DATA IN CSV FILE ******************************/
int AMC_ExportInCSVFileFormate(HWND hwnd, struct EmployeeDetails *employee)
{
	if(employee == NULL)
		return(-1);
	
	TCHAR szFileName[MAX_PATH];
	TCHAR szTitleName[MAX_PATH];
	
	szFileName[0] = '\0';
	szTitleName[0] = '\0';
	
	SaveAsDialogInitialize(hwnd, CSV_FILTER);
	if(! PopFileSaveDlg(hwnd, szFileName, szTitleName) )
	{
		return(1);
	}
	
	FILE *fp = fopen(szFileName, "w");
	fprintf(fp,
					"%s, %s, %s, %s, %s, %s, %s, %s, %s, %s\n\n",
					"Employee ID",
					"FirstName",
					"LastName",
					"Email Id",
					"Mobile No.",
					"Gender",
					"Address",
					"Date Of Birth",
					"Date Of Joining",
					"Department"
				);
				
	while(employee)
	{
		fprintf(fp,
					"\"%s\", %s, %s, %s, %s, %s, \"%s\", %s, %s, %s\n",
					employee->employeeId,
					employee->firstName,
					employee->lastName,
					employee->email_id,
					employee->mobile_no,
					employee->gender,
					employee->address,
					employee->dateOfBirth,
					employee->dateOfJoining,
					employee->department_name
				);
				
		employee = employee->nextDetails;
	}
	
	MessageBox(NULL, TEXT("DONE"), TEXT("DONE"), MB_OK);
	
	fclose(fp);
	
	return(0);
}

