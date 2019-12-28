#include <windows.h>
#include <stdio.h>
#include <commdlg.h>
#include <ole2.h>

#include "SaveAsDialog.h"


/******************** COM ERROR DESCRIPTION STRING ******************************/

static void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
	TCHAR *szErrorMessage = NULL;
	TCHAR str[255];
	
	if(FACILITY_WINDOWS == HRESULT_FACILITY(hr))
		hr = HRESULT_CODE(hr);
	
	if(FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &szErrorMessage, 0, NULL) != 0)
	{
		wsprintf(str, TEXT("%s ==> %d"), szErrorMessage, __LINE__);
		LocalFree(szErrorMessage);
	}
	else
		wsprintf(str, TEXT("[Could not find a description for error # %#x.]\n\n%d"), hr,__LINE__);
	
	MessageBox(hwnd, str, TEXT("COM ERROR"), MB_OK);
}

/******************** AUTOMATION HELPER FUNCTION ******************************/
HRESULT AutoWrap(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, int cArgs...)
{
	//Begin variable-argument list...
	va_list marker;
	va_start(marker, cArgs);
	
	if(!pDisp)
	{
		MessageBox(NULL, "NULL IDispatch passed to AutoWrap()", "ERROR", MB_OK);
		return(E_FAIL);
	}
	
	//variables used
	DISPPARAMS dp          = { NULL, NULL, 0, 0 };
	DISPID     dispidNamed = DISPID_PROPERTYPUT;
	DISPID     dispID;
	HRESULT    hr;
	char       buf[200];
	char       szName[200];
	
	//convert down to ANSI
	WideCharToMultiByte(CP_ACP, 0, ptName, -1, szName, 256, NULL, NULL);
	
	//Get DISPID for name passed...
	hr = pDisp->GetIDsOfNames(IID_NULL, &ptName, 1, GetUserDefaultLCID(), &dispID);
	if(FAILED(hr))
	{
		sprintf(buf, "IDispatch::GetIDsOfNames(\"%s\") failed w/err 0x08lx", szName, hr);
		MessageBox(NULL, buf, "AutoWrap()", MB_ICONERROR);
		//ComErrorDescriptionString(NULL, hr);
		return(hr);
	}
	
	//Allocate memory for arguments...
	VARIANT *pArgs = new VARIANT[cArgs + 1];
	//Extract arguments...
	for(int i = 0; i < cArgs; i++)
	{
		pArgs[i] = va_arg(marker, VARIANT);
	}
	
	//Build DISPPARAMS
	dp.cArgs = cArgs;
	dp.rgvarg = pArgs;
	
	//Handle special-case for property-puts
	if(autoType & DISPATCH_PROPERTYPUT)
	{
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
	}
	
	//Make the call
	hr = pDisp->Invoke(dispID, IID_NULL, GetUserDefaultLCID(), autoType, &dp, pvResult, NULL, NULL);
	if(FAILED(hr))
	{
		sprintf(buf, "IDispatch::Invoke(\"%s\"=%08lx) failed w/err 0x%08lx", szName, dispID, hr);
		MessageBox(NULL, buf, "AutoWrap()", MB_ICONERROR);
		//ComErrorDescriptionString(NULL, hr);
		return(hr);
	}
	
	//End variable-argument section...
	va_end(marker);
	
	delete []pArgs;
	
	return(hr);
}


/******************** AMC_ExportInExcelFileFormate_Automation ******************************/
int AMC_ExportInExcelFileFormate_Automation(HWND hwnd, struct EmployeeDetails *employee, int lengthOfRecord)
{
	if(employee == NULL || lengthOfRecord < 1)
		return(-1);
	
	TCHAR szFileName[MAX_PATH];
	TCHAR szTitleName[MAX_PATH];
	
	szFileName[0]  = '\0';
	szTitleName[0] = '\0';
		
	//Initialize COM for this thread
	//CoInitialize(NULL);
	
	//Get CLSID
	CLSID clsid;
	HRESULT hr = CLSIDFromProgID(L"Excel.Application", &clsid);
	
	if(FAILED(hr))
	{
		MessageBox(hwnd, "CLSIDFromProgID() failed", "Error", MB_ICONERROR);
		return(-1);
	}
	
	//start server and get IDispatch...
	IDispatch* pXlApp;
	hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void**) &pXlApp);
	if(FAILED(hr))
	{
		MessageBox(hwnd, "Excel not registered properly", "Error", MB_ICONERROR);
		return(-1);
	}
	
	//Make it visible (i.e. app.visible = 0)
	{
		VARIANT x;
		x.vt = VT_I4;
		x.lVal = FALSE;
		hr = AutoWrap(DISPATCH_PROPERTYPUT, NULL, pXlApp, L"Visible", 1, x);
		if(FAILED(hr))
		{
			pXlApp->Release();
			return(-1);
		}
	}
	
	//Get Workbooks collection
	IDispatch *pXlBooks;
	{
		VARIANT result;
		VariantInit(&result);
		hr = AutoWrap(DISPATCH_PROPERTYGET, &result, pXlApp, L"Workbooks", 0);
		if(FAILED(hr))
		{
			pXlApp->Release();
			return(-1);
		}
		pXlBooks = result.pdispVal;
	}
	
	//call Workbooks.Add() to get a new workbook...
	IDispatch *pXlBook;
	{
		VARIANT result;
		VariantInit(&result);
		hr = AutoWrap(DISPATCH_PROPERTYGET, &result, pXlBooks, L"Add", 0);
		if(FAILED(hr))
		{
			pXlBooks->Release();
			pXlApp->Release();
			return(-1);
		}
		pXlBook = result.pdispVal;
	}
	
	/**
	 * Create VARINAT ARRAY To Store data for sheet
	 **/
	//create a ( lengthOfRecord X 10 ) safearray of variant...
	VARIANT arr;
	arr.vt = VT_ARRAY | VT_VARIANT;
	{
		SAFEARRAYBOUND sab[2];
		//lLbound  ==> The lower bound of the dimension.
		//cElements ==> The number of elements in the dimension.
		sab[0].lLbound = 1;    //
		sab[0].cElements = lengthOfRecord + 2; // 2 for header and one gap
		
		sab[1].lLbound = 1;    //The lower bound of the dimension.
		sab[1].cElements = 10; //The number of elements in the dimension.
		
		arr.parray = SafeArrayCreate(VT_VARIANT, 2, sab);
	}

	//enter COLUMN_HEADER (title) first in array
	{
		OLECHAR* sOleText;
		//create entry value for (1, 1)
			//employee ID
				int len = strlen("Employee ID") + 1;
				sOleText = (OLECHAR*)malloc(sizeof(OLECHAR) * len);
				mbstowcs(sOleText, "Employee ID", len);
				
				long indices[] = {1, 1};
				VARIANT tmp;
				tmp.vt = VT_BSTR;
				tmp.bstrVal = SysAllocString(sOleText);
				//Add to safearray...
				SafeArrayPutElement(arr.parray, indices, (void*) &tmp);
				
				free(sOleText);

		//create entry value for (1, 2)
			//FirstName
				len = strlen("FirstName") + 1;
				sOleText = (OLECHAR*)malloc(sizeof(OLECHAR) * len);
				mbstowcs(sOleText, "FirstName", len);
				
				indices[0] = 1;
				indices[1] = 2;
				tmp.vt = VT_BSTR;
				tmp.bstrVal = SysAllocString(sOleText);
				//Add to safearray...
				SafeArrayPutElement(arr.parray, indices, (void*) &tmp);
				
				free(sOleText);
				
		//create entry value for (1, 3)
			//Last Name
				len = strlen("LastName") + 1;
				sOleText = (OLECHAR*)malloc(sizeof(OLECHAR) * len);
				mbstowcs(sOleText, "LastName", len);
				
				indices[0] = 1;
				indices[1] = 3;
				tmp.vt = VT_BSTR;
				tmp.bstrVal = SysAllocString(sOleText);
				//Add to safearray...
				SafeArrayPutElement(arr.parray, indices, (void*) &tmp);
				
				free(sOleText);
				
		//create entry value for (1, 4)
			//Email ID
				len = strlen("Email Id") + 1;
				sOleText = (OLECHAR*)malloc(sizeof(OLECHAR) * len);
				mbstowcs(sOleText, "Email Id", len);
				
				indices[0] = 1;
				indices[1] = 4;
				tmp.vt = VT_BSTR;
				tmp.bstrVal = SysAllocString(sOleText);
				//Add to safearray...
				SafeArrayPutElement(arr.parray, indices, (void*) &tmp);
				
				free(sOleText);
				
		//create entry value for (1, 5)
			//Mobile NO.
				len = strlen("Mobile No.") + 1;
				sOleText = (OLECHAR*)malloc(sizeof(OLECHAR) * len);
				mbstowcs(sOleText, "Mobile No.", len);
				
				indices[0] = 1;
				indices[1] = 5;
				tmp.vt = VT_BSTR;
				tmp.bstrVal = SysAllocString(sOleText);
				//Add to safearray...
				SafeArrayPutElement(arr.parray, indices, (void*) &tmp);
				
				free(sOleText);
				
		//create entry value for (1, 6)
			//Gender
				len = strlen("Gender") + 1;
				sOleText = (OLECHAR*)malloc(sizeof(OLECHAR) * len);
				mbstowcs(sOleText, "Gender", len);
				
				indices[0] = 1;
				indices[1] = 6;
				tmp.vt = VT_BSTR;
				tmp.bstrVal = SysAllocString(sOleText);
				//Add to safearray...
				SafeArrayPutElement(arr.parray, indices, (void*) &tmp);
				
				free(sOleText);
				
		//create entry value for (1, 7)
			//Address
				len = strlen("Address") + 1;
				sOleText = (OLECHAR*)malloc(sizeof(OLECHAR) * len);
				mbstowcs(sOleText, "Address", len);
				
				indices[0] = 1;
				indices[1] = 7;
				tmp.vt = VT_BSTR;
				tmp.bstrVal = SysAllocString(sOleText);
				//Add to safearray...
				SafeArrayPutElement(arr.parray, indices, (void*) &tmp);
				
				free(sOleText);
				
		//create entry value for (1, 8)
			//Date of Birth
				len = strlen("Date Of Birth") + 1;
				sOleText = (OLECHAR*)malloc(sizeof(OLECHAR) * len);
				mbstowcs(sOleText, "Date Of Birth", len);
				
				indices[0] = 1;
				indices[1] = 8;
				tmp.vt = VT_BSTR;
				tmp.bstrVal = SysAllocString(sOleText);
				//Add to safearray...
				SafeArrayPutElement(arr.parray, indices, (void*) &tmp);
				
				free(sOleText);
				
		//create entry value for (1, 9)
			//Date of Joining
				len = strlen("Date Of Joining") + 1;
				sOleText = (OLECHAR*)malloc(sizeof(OLECHAR) * len);
				mbstowcs(sOleText, "Date Of Joining", len);
				
				indices[0] = 1;
				indices[1] = 9;
				tmp.vt = VT_BSTR;
				tmp.bstrVal = SysAllocString(sOleText);
				//Add to safearray...
				SafeArrayPutElement(arr.parray, indices, (void*) &tmp);
				
				free(sOleText);
				
		//create entry value for (1, 10)
			//Department
				len = strlen("Department") + 1;
				sOleText = (OLECHAR*)malloc(sizeof(OLECHAR) * len);
				mbstowcs(sOleText, "Department", len);
				
				indices[0] = 1;
				indices[1] = 10;
				tmp.vt = VT_BSTR;
				tmp.bstrVal = SysAllocString(sOleText);
				//Add to safearray...
				SafeArrayPutElement(arr.parray, indices, (void*) &tmp);
				
				free(sOleText);
	}

	for(int i = 1; i<=10;i++)
	{
	//create entry value for (2, i)
		VARIANT tmp;
		tmp.vt = VT_BSTR;
		tmp.bstrVal = SysAllocString(L"");
		//Add to safearray...
		long indices[] = {2,i};
		SafeArrayPutElement(arr.parray, indices, (void*) &tmp);
	}

	OLECHAR* sOleText = NULL;
	//Fill safearray with some values...
	for(int i = 3; i <= lengthOfRecord + 2; i++)
	{
	
	//create entry value for (i, 1)
		//employee ID
		int len = strlen(employee->employeeId) + 1;
		sOleText = (OLECHAR*)malloc(sizeof(OLECHAR) * len);   //create space for OLESTR
		mbstowcs(sOleText, employee->employeeId, len);  // convert string to OLE string
		
		long indices[] = {i, 1};
		VARIANT tmp;
		tmp.vt = VT_BSTR;
		tmp.bstrVal = SysAllocString(sOleText);    //Allocate space for string
		//Add to safearray...
		SafeArrayPutElement(arr.parray, indices, (void*) &tmp);   //add data in array at specified index
		
		free(sOleText);
		
	//create entry value for (i, 2)
		//First Name
		len = strlen(employee->firstName) + 1;
		sOleText = (OLECHAR*)malloc(sizeof(OLECHAR) * len);
		mbstowcs(sOleText, employee->firstName, len);
		
		indices[0] = i;
		indices[1] = 2;
		tmp.vt = VT_BSTR;
		tmp.bstrVal = SysAllocString(sOleText);
		//Add to safearray...
		SafeArrayPutElement(arr.parray, indices, (void*) &tmp);
		
		free(sOleText);
		
	//create entry value for (i, 3)
		//Last Name
		len = strlen(employee->lastName) + 1;
		sOleText = (OLECHAR*)malloc(sizeof(OLECHAR) * len);
		mbstowcs(sOleText, employee->lastName, len);
		
		indices[0] = i;
		indices[1] = 3;
		tmp.vt = VT_BSTR;
		tmp.bstrVal = SysAllocString(sOleText);
		//Add to safearray...
		SafeArrayPutElement(arr.parray, indices, (void*) &tmp);
		
		free(sOleText);
		
	//create entry value for (i, 4)
		//Email ID
		len = strlen(employee->email_id) + 1;
		sOleText = (OLECHAR*)malloc(sizeof(OLECHAR) * len);
		mbstowcs(sOleText, employee->email_id, len);
		
		indices[0] = i;
		indices[1] = 4;
		tmp.vt = VT_BSTR;
		tmp.bstrVal = SysAllocString(sOleText);
		//Add to safearray...
		SafeArrayPutElement(arr.parray, indices, (void*) &tmp);
		
		free(sOleText);
		
	//create entry value for (i, 5)
		//Mobile No.
		len = strlen(employee->mobile_no) + 1;
		sOleText = (OLECHAR*)malloc(sizeof(OLECHAR) * len);
		mbstowcs(sOleText, employee->mobile_no, len);
		
		indices[0] = i;
		indices[1] = 5;
		tmp.vt = VT_BSTR;
		tmp.bstrVal = SysAllocString(sOleText);
		//Add to safearray...
		SafeArrayPutElement(arr.parray, indices, (void*) &tmp);
		
		free(sOleText);
		
	//create entry value for (i, 6)
		//Gender
		len = strlen(employee->gender) + 1;
		sOleText = (OLECHAR*)malloc(sizeof(OLECHAR) * len);
		mbstowcs(sOleText, employee->gender, len);
		
		indices[0] = i;
		indices[1] = 6;
		tmp.vt = VT_BSTR;
		tmp.bstrVal = SysAllocString(sOleText);
		//Add to safearray...
		SafeArrayPutElement(arr.parray, indices, (void*) &tmp);
		
		free(sOleText);
		
	//create entry value for (i, 7)
		//Address
		len = strlen(employee->address) + 1;
		sOleText = (OLECHAR*)malloc(sizeof(OLECHAR) * len);
		mbstowcs(sOleText, employee->address, len);
		
		indices[0] = i;
		indices[1] = 7;
		tmp.vt = VT_BSTR;
		tmp.bstrVal = SysAllocString(sOleText);
		//Add to safearray...
		SafeArrayPutElement(arr.parray, indices, (void*) &tmp);
		
		free(sOleText);
		
	//create entry value for (i, 8)
		//Date of Birth
		len = strlen(employee->dateOfBirth) + 1;
		sOleText = (OLECHAR*)malloc(sizeof(OLECHAR) * len);
		mbstowcs(sOleText, employee->dateOfBirth, len);
		
		indices[0] = i;
		indices[1] = 8;
		tmp.vt = VT_BSTR;
		tmp.bstrVal = SysAllocString(sOleText);
		//Add to safearray...
		SafeArrayPutElement(arr.parray, indices, (void*) &tmp);
		
		free(sOleText);
		
	//create entry value for (i, 9)
		//Date of Joining
		len = strlen(employee->dateOfJoining) + 1;
		sOleText = (OLECHAR*)malloc(sizeof(OLECHAR) * len);
		mbstowcs(sOleText, employee->dateOfJoining, len);
		
		indices[0] = i;
		indices[1] = 9;
		tmp.vt = VT_BSTR;
		tmp.bstrVal = SysAllocString(sOleText);
		//Add to safearray...
		SafeArrayPutElement(arr.parray, indices, (void*) &tmp);
		
		free(sOleText);
		
	//create entry value for (i, 10)
		//Department
		len = strlen(employee->department_name) + 1;
		sOleText = (OLECHAR*)malloc(sizeof(OLECHAR) * len);
		mbstowcs(sOleText, employee->department_name, len);
		
		indices[0] = i;
		indices[1] = 10;
		tmp.vt = VT_BSTR;
		tmp.bstrVal = SysAllocString(sOleText);
		//Add to safearray...
		SafeArrayPutElement(arr.parray, indices, (void*) &tmp);
		
		free(sOleText);
	}
	
	//Get ActiveSheet object;
	IDispatch* pXlSheet;
	{
		VARIANT result;
 	  VariantInit(&result);
	  hr = AutoWrap(DISPATCH_PROPERTYGET, &result, pXlBook, L"ActiveSheet", 0);
		if(FAILED(hr))
		{
			pXlBook->Release();
			pXlBooks->Release();
			pXlApp->Release();
			VariantClear(&arr);
			return(-1);
		}
	  pXlSheet = result.pdispVal;
	}
	
	//Get range object
	IDispatch* pXlRange;
	{
		VARIANT initialRange;
		initialRange.vt = VT_BSTR;
		initialRange.bstrVal = SysAllocString(L"A1");
		
;	
		char str[] = "J";
		char numChar[5];
		//char *  itoa ( int value, char * str, int base );
		itoa((lengthOfRecord+2), numChar, 10);
	
		strcat(str, numChar);
		
		int len = strlen(str) + 1;
		sOleText = (OLECHAR*)malloc(sizeof(OLECHAR) * len);
		mbstowcs(sOleText, str, len);
		
		VARIANT finalRange;
		finalRange.vt = VT_BSTR;
		
		finalRange.bstrVal = SysAllocString(sOleText);
		
		VARIANT result;
		VariantInit(&result);
		hr = AutoWrap(DISPATCH_PROPERTYGET, &result, pXlSheet, L"Range", 2, finalRange, initialRange);
		if(FAILED(hr))
		{
			pXlSheet->Release();
			pXlBook->Release();
			pXlBooks->Release();
			pXlApp->Release();
			VariantClear(&arr);
			return(-1);
		}
		// VariantClear(&finalRange);
		// VariantClear(&initialRange);
		
		pXlRange = result.pdispVal;
	}
	
	//Set range with our safearray...
	hr = AutoWrap(DISPATCH_PROPERTYPUT, NULL, pXlRange, L"Value", 1, arr);
	if(FAILED(hr))
	{
		pXlRange->Release();
		pXlSheet->Release();
		pXlBook->Release();
		pXlBooks->Release();
		pXlApp->Release();
		VariantClear(&arr);
		return(-1);
	}
		
	{
	 TCHAR szFileName[MAX_PATH];
	 TCHAR szTitleName[MAX_PATH];

	 szFileName[0] = '\0';
	 szTitleName[0] = '\0'; 
	 
	//Initialize Save As Dialog Box
   SaveAsDialogInitialize(hwnd, EXCEL_SPREADSHEET_FILTER);
	 if(! PopFileSaveDlg(hwnd, szFileName, szTitleName) )
	 {
		 return(-1);
	 }
	 
	 OLECHAR *sOleText= (OLECHAR*)malloc( sizeof(OLECHAR) * (strlen(szFileName)+1));
	 mbstowcs(sOleText,szFileName,strlen(szFileName)+1); 
	 
	 VARIANT name;
	 name.vt = VT_BSTR;
	 name.bstrVal = SysAllocString(sOleText);
		
		VARIANT fformat;
		fformat.vt = VT_I4;
		fformat.lVal = 43;
		
		hr = AutoWrap(DISPATCH_PROPERTYPUT, NULL, pXlBook, L"SaveAs", 2, fformat, name);
		if(FAILED(hr))
		{
			AutoWrap(DISPATCH_METHOD, NULL, pXlApp, L"Quit", 0);
			pXlRange->Release();
			pXlSheet->Release();
			pXlBook->Release();
			pXlBooks->Release();
			pXlApp->Release();
			VariantClear(&arr);
			//return(-1);
			return(0);  //As SaveAs will show error message.
		}
	}

	// Tell Excel to quit (i.e. App.Quit)
  hr = AutoWrap(DISPATCH_METHOD, NULL, pXlApp, L"Quit", 0);
	if(FAILED(hr))
	{
		pXlRange->Release();
		pXlSheet->Release();
		pXlBook->Release();
		pXlBooks->Release();
		pXlApp->Release();
		VariantClear(&arr);
		return(-1);
	}
	
	 // Release references...
   pXlRange->Release();
   pXlSheet->Release();
   pXlBook->Release();
	 pXlBooks->Release(); 
   pXlApp->Release();
   VariantClear(&arr);

   // Uninitialize COM for this thread...
   //CoUninitialize();
	 printf("%d\n", __LINE__);
	 
	 return(0);
}
