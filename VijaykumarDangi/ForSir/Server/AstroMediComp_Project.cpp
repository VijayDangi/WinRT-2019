#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "AstroMediComp_Project.h"
#include "AstroMediComp_Project_String.h"

#define DATA_DIRECTORY "C:\\AMC\\"


//CRecordFile
class CRecordFile : public IReadRecordFile, IWriteRecordFile
{
	private:
		long m_cRef;
		
	public:
		//constructor
		CRecordFile(void);
		//destructor
		~CRecordFile(void);
		
		//IUnknown specific method declarations (inherited)
		HRESULT __stdcall QueryInterface(REFIID, void**);
		ULONG   __stdcall AddRef(void);
		ULONG   __stdcall Release(void);
		
		//IReadRecordFile specific method declarations (inherited)
		HRESULT __stdcall ReadRecord(const char*, short, char*, struct EmployeeDetails**, int*);
		
		//IWriteRecordFile specific method declarations (inherited)
		HRESULT __stdcall WriteRecord(const char*, struct EmployeeDetails*, int*);
		
		//CRecordFile custom methods
		HRESULT __stdcall SearchRecordInFile    (const char*, short , char*, struct EmployeeDetails**, int*);
		HRESULT __stdcall SearchRecordInAllFile (short , char*, struct EmployeeDetails**, int*);
		HRESULT __stdcall ReadRecordFromFile    (const char *, struct EmployeeDetails**, int *);
		HRESULT __stdcall ReadRecordFromAllFile (struct EmployeeDetails**, int *);
};

//class CRecordFileClassFactory
class CRecordFileClassFactory : public IClassFactory
{
	private:
		long m_cRef;
	
	public:
		//constructor
		CRecordFileClassFactory(void);
		//destructor
		~CRecordFileClassFactory(void);
		
		//IUnknown specific method declarations (inherited)
		HRESULT __stdcall QueryInterface(REFIID, void**);
		ULONG   __stdcall AddRef(void);
		ULONG   __stdcall Release(void);
		
		//IClassFactory specific method declarations (inherited)
		HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
		HRESULT __stdcall LockServer(BOOL);
};

//global variable declarations
long glNumberOfActiveComponents = 0;
long glNumberOfServerLocks = 0;

//DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	switch(dwReason)
	{
		case DLL_PROCESS_ATTACH:  break;
		case DLL_THREAD_ATTACH:   break;
		case DLL_THREAD_DETACH:   break;
		case DLL_PROCESS_DETACH:  break;
	}
	
	return(TRUE);
}

//Implementation of CRecordFile's constructor method
CRecordFile::CRecordFile(void)
{
	m_cRef = 1;
	InterlockedIncrement(&glNumberOfActiveComponents);
}

//Implementation of CRecordFile's destructor method
CRecordFile::~CRecordFile(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
}

//Implementation of CRecordFile's IUnknown's method
HRESULT CRecordFile::QueryInterface(REFIID riid, void **ppv)
{	
	if(riid == IID_IUnknown)
		*ppv = static_cast<IReadRecordFile *>(this);
	else if(riid == IID_IReadRecordFile)
		*ppv = static_cast<IReadRecordFile *>(this);
	else if(riid == IID_IWriteRecordFile)
		*ppv = static_cast<IWriteRecordFile *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	
	reinterpret_cast<IUnknown *>(* ppv)->AddRef();
		
	return(S_OK);
}
//////////////////////////////////////////////
ULONG CRecordFile::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	
	return(m_cRef);
}
///////////////////////////////////////////////
ULONG CRecordFile::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if(m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}


////////////////////////////////////////////
HRESULT CRecordFile::SearchRecordInFile(
													const char *departmentName,
													short searchCategory,
													char *searchString,
													struct EmployeeDetails **employeeRecordArray,
													int *recordLength
									)
{
	(*recordLength) = 0;
	////printf("+++++++++++++++++ SEARCH ==> %s ++++++++++++++++++++++++\n", departmentName);
	struct EmployeeDetails *tempraryPointer = NULL;
	
	if(*employeeRecordArray != NULL)
		tempraryPointer = *employeeRecordArray;
	
	FILE *fSearch      = NULL;
	FILE *fSearchIndex = NULL;
	
	char *readString;
	int size = 0;
	
	//char FileName[40] = "AstroMediComp_";
	char FileName[40];
	char IndexFileName[50];
	
	strcpy(FileName, DATA_DIRECTORY);
	strcat(FileName, departmentName);
	strcpy(IndexFileName, FileName);
	
	strcat(IndexFileName, "_INDEX.dat");
	strcat(FileName, ".dat");
	
	fSearch = fopen(FileName, "r");
	if(fSearch == NULL)
	{
		char str[255];
		wsprintf(str, TEXT("Error File open LINE NO : %d"), __LINE__);
		MessageBox(NULL, str, TEXT("Error"), MB_OK);
		return(S_FALSE);
	}
	
	fSearchIndex = fopen(IndexFileName, "r");
	if(fSearchIndex == NULL)
	{
		fclose(fSearch);
		char str[255];
		wsprintf(str, TEXT("Error File Open LINE NO : %d"), __LINE__);
		MessageBox(NULL, str, TEXT("Error"), MB_OK);
		return(S_FALSE);
	}
	
	while(fscanf(fSearchIndex, "%d", &size) != EOF)
	{
		readString = (char *) malloc(sizeof(char) * size);
		fscanf(fSearch, "%[^\n]%*c", readString); //reaad line from file
		readString[size] = '\0';
		
		char arr[10][255];
		int in = 0;
		char temp[255];
		short length = 0;
		
		for(short i = 0; i < size; i++)
		{
			if(readString[i] == '@')
			{
				short flag = 0;
				for(short k = 0; k <= 4; k++)
				{
					if(readString[i + k] == '@')
						flag = 1;
					else
					{
						flag = 0;
						temp[length++] = readString[i];
						break;
					}
				}
				if(flag == 1)
				{
					temp[length] = '\0';
					strcpy(arr[in], temp);
					in++;
					i += 4;
					length = 0;
				}
			}
			else
			{
				temp[length++] = readString[i];
			}
		}
		temp[length] = '\0';
		strcpy(arr[in], temp);
		
		short flag = 0;
		//search by firstName
		if(searchCategory      == SEARCH_BY_FIRST_NAME)
		{
			flag = stringsAreEqualIgnoreCase(arr[0], searchString);
		}
		//search by lastName
		else if(searchCategory == SEARCH_BY_LAST_NAME)
		{
			flag = stringsAreEqualIgnoreCase(arr[1], searchString);			
		}
		//search by email
		else if(searchCategory == SEARCH_BY_EMAIL_ID)
		{
			flag = stringsAreEqual(arr[2], searchString);
		}
		//search by mobile
		else if(searchCategory == SEARCH_BY_MOBILE_NUMBER)
		{
			flag = stringsAreEqual(arr[3], searchString);
		}
		//search by dateOfBirth
		else if(searchCategory == SEARCH_BY_DATE_OF_BIRTH)
		{
			flag = stringsAreEqual(arr[6], searchString);
		}
		//search by dateOfJoining
		else if(searchCategory == SEARCH_BY_DATE_OF_JOINING)
		{
			flag = stringsAreEqual(arr[7], searchString);
		}
		//search by employeeId
		// else if(searchCategory == SEARCH_BY_EMPLOYEE_ID)
		// {
			
		// }
		
		if(flag == 1) //matched
		{
			if(tempraryPointer == NULL)
			{
				tempraryPointer = (struct EmployeeDetails*) malloc( sizeof(struct EmployeeDetails) );
				*employeeRecordArray = tempraryPointer;
			}
			else
			{
				tempraryPointer->nextDetails = (struct EmployeeDetails*) malloc( sizeof(struct EmployeeDetails) );
				tempraryPointer = tempraryPointer->nextDetails;
			}
			// tempraryPointer->firstName     = (char *) malloc( sizeof(char) * strlen(arr[0]));
			// tempraryPointer->lastName      = (char *) malloc( sizeof(char) * strlen(arr[1]));
			// tempraryPointer->email_id         = (char *) malloc( sizeof(char) * strlen(arr[2]));
			// tempraryPointer->mobile_no        = (char *) malloc( sizeof(char) * strlen(arr[3]));
			// tempraryPointer->gender        = (char *) malloc( sizeof(char) * strlen(arr[4]));
			// tempraryPointer->dateOfBirth   = (char *) malloc( sizeof(char) * strlen(arr[5]));
			// tempraryPointer->dateOfJoining = (char *) malloc( sizeof(char) * strlen(arr[6]));
			// tempraryPointer->department_name    = (char *) malloc( sizeof(char) * strlen(arr[7]));
			
			tempraryPointer->nextDetails = NULL;
			
			//copy in struct
			strcpy( tempraryPointer->firstName     , arr[0]);
			strcpy( tempraryPointer->lastName      , arr[1]);
			strcpy( tempraryPointer->email_id         , arr[2]);
			strcpy( tempraryPointer->mobile_no        , arr[3]);
			strcpy( tempraryPointer->gender        , arr[4]);
			strcpy( tempraryPointer->address       , arr[5]);
			strcpy( tempraryPointer->dateOfBirth   , arr[6]);
			strcpy( tempraryPointer->dateOfJoining , arr[7]);
			strcpy( tempraryPointer->department_name    , arr[8]);
			strcpy( tempraryPointer->employeeId    , arr[9]);
			
			// //string to integer employeeId conversion
			// tempraryPointer->employeeId = 0;
			// for(short i = 0; i < length; i++)
			// {
				// switch(temp[i])
				// {
					// case '0': tempraryPointer->employeeId = tempraryPointer->employeeId * 10 + 0; break;
					// case '1': tempraryPointer->employeeId = tempraryPointer->employeeId * 10 + 1; break;
					// case '2': tempraryPointer->employeeId = tempraryPointer->employeeId * 10 + 2; break;
					// case '3': tempraryPointer->employeeId = tempraryPointer->employeeId * 10 + 3; break;
					// case '4': tempraryPointer->employeeId = tempraryPointer->employeeId * 10 + 4; break;
					// case '5': tempraryPointer->employeeId = tempraryPointer->employeeId * 10 + 5; break;
					// case '6': tempraryPointer->employeeId = tempraryPointer->employeeId * 10 + 6; break;
					// case '7': tempraryPointer->employeeId = tempraryPointer->employeeId * 10 + 7; break;
					// case '8': tempraryPointer->employeeId = tempraryPointer->employeeId * 10 + 8; break;
					// case '9': tempraryPointer->employeeId = tempraryPointer->employeeId * 10 + 9; break;
				// }
			// }
			(*recordLength)++;
		}
		free(readString);
	}
	
	fclose(fSearch);
	fclose(fSearchIndex);

	return(S_OK);
}

HRESULT CRecordFile::SearchRecordInAllFile(
													short searchCategory,
													char *searchString,
													struct EmployeeDetails **employeeRecordArray,
													int *recordLength
											)
{
	struct EmployeeDetails* tempraryPointer = NULL;
	int tempraryRecordLength = 0;
	*employeeRecordArray = NULL;
	*recordLength = 0;
	HRESULT hr;
	
	//WM_CREATE
	hr = SearchRecordInFile(Department_WM_CREATE       , searchCategory,       searchString,       &tempraryPointer,       &tempraryRecordLength);
	if(*employeeRecordArray == NULL && tempraryPointer != NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
		tempraryPointer = tempraryPointer->nextDetails;
	*recordLength += tempraryRecordLength;
	
	
	//WM_LBUTTONDOWN
	tempraryRecordLength = 0;
	hr = SearchRecordInFile(Department_WM_LBUTTONDOWN  , searchCategory,       searchString,       &tempraryPointer,       &tempraryRecordLength);
	if(*employeeRecordArray == NULL && tempraryPointer != NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
		tempraryPointer = tempraryPointer->nextDetails;
	*recordLength += tempraryRecordLength;
	
	
	//WM_SIZE
	tempraryRecordLength = 0;
	hr = SearchRecordInFile(Department_WM_SIZE         , searchCategory,       searchString,       &tempraryPointer,       &tempraryRecordLength);
	if(*employeeRecordArray == NULL && tempraryPointer != NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
		tempraryPointer = tempraryPointer->nextDetails;
	*recordLength += tempraryRecordLength;
	
	
	//WM_KEYUP
	tempraryRecordLength = 0;
	hr = SearchRecordInFile(Department_WM_KEYUP        , searchCategory,       searchString,       &tempraryPointer,       &tempraryRecordLength);
	if(*employeeRecordArray == NULL && tempraryPointer != NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
		tempraryPointer = tempraryPointer->nextDetails;
	*recordLength += tempraryRecordLength;
	
	
	//WM_KEYDOWN
	tempraryRecordLength = 0;
	hr = SearchRecordInFile(Department_WM_KEYDOWN      , searchCategory,       searchString,       &tempraryPointer,       &tempraryRecordLength);
	if(*employeeRecordArray == NULL && tempraryPointer != NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
		tempraryPointer = tempraryPointer->nextDetails;
	*recordLength += tempraryRecordLength;
	
	
	//WM_COMMAND
	tempraryRecordLength = 0;
	hr = SearchRecordInFile(Department_WM_COMMAND      , searchCategory,       searchString,       &tempraryPointer,       &tempraryRecordLength);
	if(*employeeRecordArray == NULL && tempraryPointer != NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
		tempraryPointer = tempraryPointer->nextDetails;
	*recordLength += tempraryRecordLength;
	
	
	//WM_DRAWITEM
	tempraryRecordLength = 0;
	hr = SearchRecordInFile(Department_WM_DRAWITEM     , searchCategory,       searchString,       &tempraryPointer,       &tempraryRecordLength);
	if(*employeeRecordArray == NULL && tempraryPointer != NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
		tempraryPointer = tempraryPointer->nextDetails;
	*recordLength += tempraryRecordLength;
	
	
	//WM_PAINT
	tempraryRecordLength = 0;
	hr = SearchRecordInFile(Department_WM_PAINT        , searchCategory,       searchString,       &tempraryPointer,       &tempraryRecordLength);
	if(*employeeRecordArray == NULL && tempraryPointer != NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
		tempraryPointer = tempraryPointer->nextDetails;
	*recordLength += tempraryRecordLength;
	
	
	//WM_CHAR
	tempraryRecordLength = 0;
	hr = SearchRecordInFile(Department_WM_CHAR         , searchCategory,       searchString,       &tempraryPointer,       &tempraryRecordLength);
	if(*employeeRecordArray == NULL && tempraryPointer != NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
		tempraryPointer = tempraryPointer->nextDetails;
	*recordLength += tempraryRecordLength;
	
	
	//WM_DESTROY
	tempraryRecordLength = 0;
	hr = SearchRecordInFile(Department_WM_DESTROY      , searchCategory,       searchString,       &tempraryPointer,       &tempraryRecordLength);
	if(*employeeRecordArray == NULL && tempraryPointer != NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
		tempraryPointer = tempraryPointer->nextDetails;
	*recordLength += tempraryRecordLength;
	
	
	//WM_SETFOCUS
	tempraryRecordLength = 0;
	hr = SearchRecordInFile(Department_WM_SETFOCUS     , searchCategory,       searchString,       &tempraryPointer,       &tempraryRecordLength);
	if(*employeeRecordArray == NULL && tempraryPointer != NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
		tempraryPointer = tempraryPointer->nextDetails;
	*recordLength += tempraryRecordLength;
	
	
	//WM_ENABLE
	tempraryRecordLength = 0;
	hr = SearchRecordInFile(Department_WM_ENABLE       , searchCategory,       searchString,       &tempraryPointer,       &tempraryRecordLength);
	if(*employeeRecordArray == NULL && tempraryPointer != NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
		tempraryPointer = tempraryPointer->nextDetails;
	*recordLength += tempraryRecordLength;
	
	
	//WM_MOUSEMOVE
	tempraryRecordLength = 0;
	hr = SearchRecordInFile(Department_WM_MOUSEMOVE    , searchCategory,       searchString,       &tempraryPointer,       &tempraryRecordLength);
	if(*employeeRecordArray == NULL && tempraryPointer != NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
		tempraryPointer = tempraryPointer->nextDetails;
	*recordLength += tempraryRecordLength;
	
	
	//WM_RBUTTONDOWN
	tempraryRecordLength = 0;
	hr = SearchRecordInFile(Department_WM_RBUTTONDOWN  , searchCategory,       searchString,       &tempraryPointer,       &tempraryRecordLength);
	if(*employeeRecordArray == NULL && tempraryPointer != NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
		tempraryPointer = tempraryPointer->nextDetails;
	*recordLength += tempraryRecordLength;

	return(hr);
}

HRESULT CRecordFile::ReadRecordFromFile(
													const char *departmentName,
													struct EmployeeDetails **employeeRecordArray,
													int *recordLength
											)
{
	(*recordLength) = 0;
	////printf("+++++++++++++++++ %s ++++++++++++++++++++++++\n", departmentName);
	struct EmployeeDetails *tempraryPointer = NULL;
	if(*employeeRecordArray != NULL)
		tempraryPointer = *employeeRecordArray;
	
	FILE *fRead      =  NULL;
	FILE *fReadIndex =  NULL;
	char *readString;
	int size = 0;
	//char FileName[30] = "AstroMediComp_";
	char FileName[40];
	char IndexFileName[50];
	
	
	//createding file names
	strcpy(FileName, DATA_DIRECTORY);
	strcat(FileName, departmentName);
	strcpy(IndexFileName, FileName);
	strcat(IndexFileName, "_INDEX.dat");
	strcat(FileName, ".dat");
	
	fRead = fopen(FileName, "r");
	if(fRead == NULL)
	{
		char str[255];
		wsprintf(str, TEXT("Error File Open LINE NO : %d"), __LINE__);
		MessageBox(NULL, str, TEXT("Error"), MB_OK);
		return(S_FALSE);
	}
	////printf("LINE : %d\n", __LINE__);
	fReadIndex = fopen(IndexFileName, "r");
	if(fReadIndex == NULL)
	{
		fclose(fRead);
		char str[255];
		wsprintf(str, TEXT("Error File Open LINE NO : %d"), __LINE__);
		MessageBox(NULL, str, TEXT("Error"), MB_OK);
		return(S_FALSE);
	}
	////printf("LINE : %d\n", __LINE__);
	struct EmployeeDetails *tempPtr = NULL;
	while(fscanf(fReadIndex, "%d", &size) != EOF)
	{
		////printf("LINE : %d\n", __LINE__);
		readString = (char *) malloc(sizeof(char) * size);
		fscanf(fRead, "%[^\n]%*c", readString); //reaad line from file
		readString[size] = '\0';
		////printf("LINE : %d\n", __LINE__);
		char arr[10][255];
		int in = 0;
		char temp[255];
		short length = 0;
		//printf("LINE : %d\n", __LINE__);
		for(short i = 0; i < size; i++)
		{
			if(readString[i] == '@')
			{
				short flag = 0;
				for(short k = 0; k <= 4; k++)
				{
					if(readString[i + k] == '@')
						flag = 1;
					else
					{
						flag = 0;
						temp[length++] = readString[i];
						break;
					}
				}
				if(flag == 1)
				{
					temp[length] = '\0';
					strcpy(arr[in], temp);
					in++;
					i += 4;
					length = 0;
				}
			}
			else
			{
				temp[length++] = readString[i];
			}
		}
		//printf("LINE : %d\n", __LINE__);
		temp[length] = '\0';
		strcpy(arr[in], temp);
		//printf("LINE : %d\n", __LINE__);
		tempPtr = (struct EmployeeDetails *) malloc( sizeof(struct EmployeeDetails) );
		if(tempPtr == NULL)
		{
			// char str[255];
			// wsprintf(str, TEXT("Error File Open LINE NO : %d"), __LINE__);
			// // MessageBox(NULL, str, TEXT("Error"), MB_OK);
			
			return(E_OUTOFMEMORY);
		}
		else
		{
			// tempPtr->firstName     = (char *) malloc( sizeof(char) * strlen(arr[0]));
			// tempPtr->lastName      = (char *) malloc( sizeof(char) * strlen(arr[1]));
			// tempPtr->email_id         = (char *) malloc( sizeof(char) * strlen(arr[2]));
			// tempPtr->mobile_no        = (char *) malloc( sizeof(char) * strlen(arr[3]));
			// tempPtr->gender        = (char *) malloc( sizeof(char) * strlen(arr[4]));
			// tempPtr->dateOfBirth   = (char *) malloc( sizeof(char) * strlen(arr[5]));
			// tempPtr->dateOfJoining = (char *) malloc( sizeof(char) * strlen(arr[6]));
			// tempPtr->department_name    = (char *) malloc( sizeof(char) * strlen(arr[7]));
			
			tempPtr->nextDetails = NULL;
			//printf("LINE : %d\n", __LINE__);
			//copy in struct
			strcpy( tempPtr->firstName     , arr[0]);
			strcpy( tempPtr->lastName      , arr[1]);
			strcpy( tempPtr->email_id         , arr[2]);
			strcpy( tempPtr->mobile_no        , arr[3]);
			strcpy( tempPtr->gender        , arr[4]);
			strcpy( tempPtr->address       , arr[5]);
			strcpy( tempPtr->dateOfBirth   , arr[6]);
			strcpy( tempPtr->dateOfJoining , arr[7]);
			strcpy( tempPtr->department_name    , arr[8]);
			strcpy( tempPtr->employeeId    , arr[9]);
			
			//printf("LINE : %d\n", __LINE__);
			//string to integer employeeId conversion
			// tempPtr->employeeId = 0;
			// for(short i = 0; i < length; i++)
			// {
				// switch(temp[i])
				// {
					// case '0': tempPtr->employeeId = tempPtr->employeeId * 10 + 0; break;
					// case '1': tempPtr->employeeId = tempPtr->employeeId * 10 + 1; break;
					// case '2': tempPtr->employeeId = tempPtr->employeeId * 10 + 2; break;
					// case '3': tempPtr->employeeId = tempPtr->employeeId * 10 + 3; break;
					// case '4': tempPtr->employeeId = tempPtr->employeeId * 10 + 4; break;
					// case '5': tempPtr->employeeId = tempPtr->employeeId * 10 + 5; break;
					// case '6': tempPtr->employeeId = tempPtr->employeeId * 10 + 6; break;
					// case '7': tempPtr->employeeId = tempPtr->employeeId * 10 + 7; break;
					// case '8': tempPtr->employeeId = tempPtr->employeeId * 10 + 8; break;
					// case '9': tempPtr->employeeId = tempPtr->employeeId * 10 + 9; break;
				// }
			// }
		}
			//printf("LINE : %d\n", __LINE__);
		if(*employeeRecordArray == NULL)
		{
			tempraryPointer = tempPtr;
			*employeeRecordArray = tempraryPointer;
		}
		else
		{
			tempraryPointer->nextDetails = tempPtr;
			tempraryPointer = tempraryPointer->nextDetails;
			
		}
		//printf("LINE : %d\n", __LINE__);
		(*recordLength)++;
		free(readString);
		//printf("LINE : %d\n", __LINE__);
	}
	//printf("LINE : %d\n", __LINE__);
	fclose(fRead);
	fclose(fReadIndex);

	return(S_OK);
}


HRESULT CRecordFile::ReadRecordFromAllFile(
													struct EmployeeDetails **employeeRecordArray,
													int *recordLength
											)
{
	struct EmployeeDetails *tempraryPointer = NULL;
	int tempraryRecordLength = 0;
	*employeeRecordArray = NULL;
	*recordLength = 0;
	HRESULT hr;
	
	//WM_CREATE
	hr = ReadRecordFromFile(Department_WM_CREATE      , &tempraryPointer, &tempraryRecordLength);
	if(*employeeRecordArray == NULL && tempraryPointer != NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
	{
		tempraryPointer = tempraryPointer->nextDetails;
	}
	*recordLength += tempraryRecordLength;
	
	
	//WM_LBUTTONDOWN
	tempraryRecordLength = 0;
	hr = ReadRecordFromFile(Department_WM_LBUTTONDOWN , &tempraryPointer, &tempraryRecordLength);
	if(*employeeRecordArray == NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
	{
		tempraryPointer = tempraryPointer->nextDetails;
	}
	*recordLength += tempraryRecordLength;
	
	
	//WM_SIZE
	tempraryRecordLength = 0;
	hr = ReadRecordFromFile(Department_WM_SIZE        , &tempraryPointer, &tempraryRecordLength);
	if(*employeeRecordArray == NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
	{
		tempraryPointer = tempraryPointer->nextDetails;
	}
	*recordLength += tempraryRecordLength;
	
	
	
	//WM_KEYUP
	tempraryRecordLength = 0;
	hr = ReadRecordFromFile(Department_WM_KEYUP       , &tempraryPointer, &tempraryRecordLength);
	if(*employeeRecordArray == NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
	{
		tempraryPointer = tempraryPointer->nextDetails;
	}
	*recordLength += tempraryRecordLength;
	
	
	
	//WM_KEYDOWN
	tempraryRecordLength = 0;
	hr = ReadRecordFromFile(Department_WM_KEYDOWN     , &tempraryPointer, &tempraryRecordLength);
	if(*employeeRecordArray == NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
	{
		tempraryPointer = tempraryPointer->nextDetails;
	}
	*recordLength += tempraryRecordLength;
	
	
	
	//WM_COMMAND
	tempraryRecordLength = 0;
	hr = ReadRecordFromFile(Department_WM_COMMAND     , &tempraryPointer, &tempraryRecordLength);
	if(*employeeRecordArray == NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
	{
		tempraryPointer = tempraryPointer->nextDetails;
	}
	*recordLength += tempraryRecordLength;
	
	
	
	//WM_DRAWITEM
	tempraryRecordLength = 0;
	hr = ReadRecordFromFile(Department_WM_DRAWITEM    , &tempraryPointer, &tempraryRecordLength);
	if(*employeeRecordArray == NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
	{
		tempraryPointer = tempraryPointer->nextDetails;
	}
	*recordLength += tempraryRecordLength;
	
	
	
	//WM_PAINT
	tempraryRecordLength = 0;
	hr = ReadRecordFromFile(Department_WM_PAINT       , &tempraryPointer, &tempraryRecordLength);
	if(*employeeRecordArray == NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
	{
		tempraryPointer = tempraryPointer->nextDetails;
	}
	*recordLength += tempraryRecordLength;
	
	
	//WM_CHAR
	tempraryRecordLength = 0;
	hr = ReadRecordFromFile(Department_WM_CHAR        , &tempraryPointer, &tempraryRecordLength);
	if(*employeeRecordArray == NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
	{
		tempraryPointer = tempraryPointer->nextDetails;
	}
	*recordLength += tempraryRecordLength;
	
	
	
	//WM_DESTROY
	tempraryRecordLength = 0;
	hr = ReadRecordFromFile(Department_WM_DESTROY     , &tempraryPointer, &tempraryRecordLength);
	if(*employeeRecordArray == NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
	{
		tempraryPointer = tempraryPointer->nextDetails;
	}
	*recordLength += tempraryRecordLength;
	
	
	
	//WM_SETFOCUS
	tempraryRecordLength = 0;
	hr = ReadRecordFromFile(Department_WM_SETFOCUS    , &tempraryPointer, &tempraryRecordLength);
	if(*employeeRecordArray == NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
	{
		tempraryPointer = tempraryPointer->nextDetails;
	}
	*recordLength += tempraryRecordLength;
	
	
	
	
	//WM_ENABLE
	tempraryRecordLength = 0;
	hr = ReadRecordFromFile(Department_WM_ENABLE      , &tempraryPointer, &tempraryRecordLength);
	if(*employeeRecordArray == NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
	{
		tempraryPointer = tempraryPointer->nextDetails;
	}
	*recordLength += tempraryRecordLength;
	
	
	//WM_RBUTTONDOWN
	tempraryRecordLength = 0;
	hr = ReadRecordFromFile(Department_WM_RBUTTONDOWN , &tempraryPointer, &tempraryRecordLength);
	if(*employeeRecordArray == NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
	{
		tempraryPointer = tempraryPointer->nextDetails;
	}
	*recordLength += tempraryRecordLength;
	
	
	
	//WM_MOUSEMOVE
	tempraryRecordLength = 0;
	hr = ReadRecordFromFile(Department_WM_MOUSEMOVE   , &tempraryPointer, &tempraryRecordLength);
	if(*employeeRecordArray == NULL)
		*employeeRecordArray = tempraryPointer;
	while(tempraryPointer != NULL && tempraryPointer->nextDetails != NULL)
	{
		tempraryPointer = tempraryPointer->nextDetails;
	}
	*recordLength += tempraryRecordLength;
	
	return(hr);
}


//ReadRecord
HRESULT CRecordFile::ReadRecord(
													const char *departmentName,
													short searchCategory,
													char *searchString,
													struct EmployeeDetails **employeeRecordArray,
													int *recordLength
											)
{
	HRESULT hr;
	if(searchString != NULL && searchCategory != SEARCH_NONE)		//search string
	{
		if(departmentName != NULL)
		{
			//search in specific file
			hr = SearchRecordInFile(departmentName, searchCategory, searchString, employeeRecordArray, recordLength);
		}
		else
		{
			//search in all file
			hr = SearchRecordInAllFile(searchCategory, searchString, employeeRecordArray, recordLength);
		}
	}
	else
	{
		if(departmentName != NULL)
		{
			//read from specific file
			hr = ReadRecordFromFile(departmentName, employeeRecordArray, recordLength);
		}
		else
		{
			//read from all file
			hr = ReadRecordFromAllFile(employeeRecordArray, recordLength);
		}
	}

	return(hr);
}


//WriteRecord
HRESULT CRecordFile::WriteRecord(
													const char *departmentName,
													struct EmployeeDetails *employeeRecordArray,
													int *recordLength
											)
{		
	if(employeeRecordArray == NULL)
	{
		return(S_FALSE);
	}
				
	FILE *fWrite      =  NULL;
	FILE *fWriteIndex =  NULL;
	FILE *eif = NULL;
	
	short size = 0;
	int iEmployeeID;
	//char FileName[40] = "AstroMediComp_";
	char FileName[40] = "";
	char IndexFileName[60];
	char EmployeeIDFile[] = "C:\\AMC\\EmployeeFile.dat";
	
	//generate employee id
	eif = fopen(EmployeeIDFile, "r");
	fscanf(eif, "%4d", &iEmployeeID);
	fclose(eif);
	eif = NULL;

	char str[12];

	sprintf(str, "AMC-%d", iEmployeeID);
		
	strcpy(employeeRecordArray->employeeId, str);
	
	//creating file names
  strcpy(FileName, DATA_DIRECTORY);
	strcat(FileName, departmentName);
	strcpy(IndexFileName, FileName);
	
	strcat(IndexFileName, "_INDEX.dat");
	strcat(FileName, ".dat");
	

	fWrite = fopen(FileName, "a");
	if(fWrite == NULL)
	{
		char str[255];
		wsprintf(str, TEXT("Error File Open LINE NO : %d"), __LINE__);
		MessageBox(NULL, str, TEXT("Error"), MB_OK);
		return(S_FALSE);
	}
	
	fWriteIndex = fopen(IndexFileName, "a");
	if(fWriteIndex == NULL)
	{
		fclose(fWrite);
		char str[255];
		//printf("%s",fWriteIndex);
		wsprintf(str, TEXT("Error File Open LINE NO : %d"), __LINE__);
		MessageBox(NULL, str, TEXT("Error"), MB_OK);
		return(S_FALSE);
	}

	while(employeeRecordArray != NULL)
	{
		size = fprintf(fWrite,
							"%s@@@@@%s@@@@@%s@@@@@%s@@@@@%s@@@@@%s@@@@@%s@@@@@%s@@@@@%s@@@@@%s\n",
							employeeRecordArray->firstName,
							employeeRecordArray->lastName,
							employeeRecordArray->email_id,
							employeeRecordArray->mobile_no,
							employeeRecordArray->gender,
							employeeRecordArray->address,
							employeeRecordArray->dateOfBirth,
							employeeRecordArray->dateOfJoining,
							employeeRecordArray->department_name,
							employeeRecordArray->employeeId
						);
		
		fprintf(fWriteIndex, "%4d", size);
		
		//update employee id
		eif = fopen(EmployeeIDFile, "w");
		fprintf(eif, "%4d", ++iEmployeeID);
		fclose(eif);
		
		////printf("Employee Id : %s\n", employeeRecordArray->employeeId);
		employeeRecordArray = employeeRecordArray->nextDetails;
	}
	fclose(fWrite);
	fclose(fWriteIndex);

	return(S_OK);
}

/********************************************/
//Implementation of CRecordFileClassFactory's constructor
CRecordFileClassFactory::CRecordFileClassFactory(void)
{
	m_cRef = 1;
}

//Implementation of CRecordFileClassFactory's destructor
CRecordFileClassFactory::~CRecordFileClassFactory(void)
{	
}

//Implementation of CRecordFileClassFactory's IUnknown's method
HRESULT CRecordFileClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	if(riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if(riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CRecordFileClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CRecordFileClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if(m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

HRESULT CRecordFileClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	///************************///
	FILE *fp = fopen("C:\\AMC\\AstroMediComp_Index.dat","r");
	if(fp)
	{
		fclose(fp);  //data files are present
	}
	else
	{
		createFilesIfNotExist(); //files are not present and create the files first
	}
	
	CRecordFile *pCRecordFile = NULL;
	HRESULT hr;
	
	if(pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);
	
	//create instance
	pCRecordFile = new CRecordFile;
	
	if(pCRecordFile == NULL)
		return(E_OUTOFMEMORY);
	
	hr = pCRecordFile->QueryInterface(riid, ppv);
	pCRecordFile->Release();
	
	// MessageBox(NULL, TEXT("OUT => CRecordFileClassFactory::CreateInstance"), TEXT("INFO"), MB_OK);
	return(hr);
}

HRESULT CRecordFileClassFactory::LockServer(BOOL fLock)
{
	// MessageBox(NULL, TEXT("IN => CRecordFileClassFactory::LockServer"), TEXT("INFO"), MB_OK);
	if(fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	
	// MessageBox(NULL, TEXT("OUT => CRecordFileClassFactory::LockServer"), TEXT("INFO"), MB_OK);
	return(S_OK);
}






extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	// MessageBox(NULL, TEXT("IN => DllGetClassObject"), TEXT("INFO"), MB_OK);
	CRecordFileClassFactory *pCRecordFileClassFactory = NULL;
	HRESULT hr;
	
	if(rclsid != CLSID_RecordFile)
		return(CLASS_E_CLASSNOTAVAILABLE);
	
	//create class factory
	pCRecordFileClassFactory = new CRecordFileClassFactory;
	if(pCRecordFileClassFactory == NULL)
		return(E_OUTOFMEMORY);
	
	hr = pCRecordFileClassFactory->QueryInterface(riid, ppv);
	pCRecordFileClassFactory->Release();

	// MessageBox(NULL, TEXT("OUT => DllGetClassObject"), TEXT("INFO"), MB_OK);	
	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	// MessageBox(NULL, TEXT("IN => DllCanUnloadNow"), TEXT("INFO"), MB_OK);
	
	if((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
	{
		// MessageBox(NULL, TEXT("IN => DllCanUnloadNow OK"), TEXT("INFO"), MB_OK);
		return(S_OK);
	}
	else
	{
		// MessageBox(NULL, TEXT("IN => DllCanUnloadNow FALSE"), TEXT("INFO"), MB_OK);
		return(S_FALSE);
	}
}


