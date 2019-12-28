#include <windows.h>
#include <commdlg.h>
#include "AstroMediComp_Project.h"

#define EXCEL_SPREADSHEET_FILTER 800
#define CSV_FILTER               801

void SaveAsDialogInitialize(HWND hwnd, int filter);
BOOL PopFileSaveDlg(HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName);
