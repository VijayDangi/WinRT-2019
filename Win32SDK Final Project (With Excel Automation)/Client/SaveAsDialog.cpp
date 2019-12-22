#include "SaveAsDialog.h"
/******************** INITIALIZE SAVE AS DIALOG BOX ******************************/
OPENFILENAME ofn;

TCHAR szCSVFilter[] = TEXT("Comma-Seperator Values (*CSV)\0*.csv\0") \
											TEXT("All Files (*.*)\0*.*\0\0");
			
TCHAR szExcelFilter[] =  TEXT("eXceL Spreadsheet (*.XLS)\0*.xls\0") \
												 TEXT("eXceL Spreadsheet eXtended (*.XLSX)\0*.xlsx\0") \
												 TEXT("All Files (*.*)\0*.*\0\0");
			
void SaveAsDialogInitialize(HWND hwnd, int filter)
{
	// static TCHAR szFilter[] = TEXT("Comma-Seperator Values (*CSV)\0*.csv\0") \
														// TEXT("eXceL Spreadsheet (*.XLS)\0*.xls\0") \
														// TEXT("eXceL Spreadsheet eXtended (*.XLSX)\0*.xlsx\0");
											
	ofn.lStructSize       = sizeof(OPENFILENAME);
	ofn.hwndOwner         = hwnd;
	ofn.hInstance         = NULL;
	
	if(filter == CSV_FILTER)
		ofn.lpstrFilter       = szCSVFilter;
	else
		ofn.lpstrFilter       = szExcelFilter;
	
	ofn.lpstrCustomFilter = NULL;
	ofn.nMaxCustFilter    = 0;
	ofn.nFilterIndex      = 0;
	ofn.lpstrFile         = NULL;
	ofn.nMaxFile          = MAX_PATH;
	ofn.lpstrFileTitle    = NULL;
	ofn.nMaxFileTitle     = MAX_PATH;
	ofn.lpstrInitialDir   = NULL;
	ofn.lpstrTitle        = NULL;
	ofn.Flags             = 0;
	ofn.nFileOffset       = 0;
	ofn.nFileExtension    = 0;
	ofn.lpstrDefExt       = TEXT("csv");
	ofn.lCustData         = 0L;
	ofn.lpfnHook          = NULL;
	ofn.lpTemplateName    = NULL;
}

/******************** OPEN SAVE AS DIALOG BOX ******************************/
BOOL PopFileSaveDlg(HWND hwnd, PTSTR pstrFileName, PTSTR pstrTitleName)
{
	ofn.hwndOwner      = hwnd;
	ofn.lpstrFile      = pstrFileName;
	ofn.lpstrFileTitle = pstrTitleName;
	ofn.Flags          = OFN_OVERWRITEPROMPT;
	
	return(GetSaveFileName(&ofn));
}


