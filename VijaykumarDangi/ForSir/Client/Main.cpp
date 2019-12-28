
/*************** HEADER FILES ***********************************/
#include "Main.h"

//define
IReadRecordFile *pIReadRecord = NULL;
IWriteRecordFile *pIWriteRecord = NULL;

BOOL sortFlag = SORT_ASCENDING;


/**
 WinMain START 
 **/
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE prevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("AstroMediComp");
  HWND         hwnd;
  MSG          msg;
  WNDCLASSEX   wndclass;
	
	/**************** COM INITIALIZE AND GET INSTANCE OF CO-CLASS ***********/
	//COM Initialization
	HRESULT hr = CoInitialize(NULL);
	if(FAILED(hr))
	{
		TCHAR str[] = TEXT("COM Library Can Not Be Initialized.\nProgram Will Now Exit.\n\n");
		MessageBox(NULL, str, TEXT("ERROR"), MB_ICONERROR);
		exit(0);
	}
	
	/**
	 * CoCreateInstance() : get Interface IReadRecordFile
	 **/
	hr = CoCreateInstance(CLSID_RecordFile, NULL, CLSCTX_INPROC_SERVER, IID_IReadRecordFile, (void**)&pIReadRecord);
	if(FAILED(hr))
	{
		TCHAR str[125];
		wsprintf( str, TEXT("Interface Can Not Be Obtained.\nLine No: %d"), __LINE__);
		MessageBox(NULL, str, TEXT("ERROR"), MB_ICONERROR);
		exit(0);
	}
	
	//Get Interface IWriteRecordFile
	hr = pIReadRecord->QueryInterface(IID_IWriteRecordFile, (void**)&pIWriteRecord);
	if(FAILED(hr))
	{
		TCHAR str[125];
		wsprintf( str, TEXT("Interface Can Not Be Obtained.\nLine No: %d"), __LINE__);
		MessageBox(NULL, str, TEXT("ERROR"), MB_ICONERROR);
		exit(0);
	}
	
	
	wndclass.cbSize        = sizeof(wndclass);
	wndclass.style         = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc   = WndProc;
	wndclass.cbClsExtra    = 0;
	wndclass.cbWndExtra    = 0;
	wndclass.hInstance     = hInstance;
	wndclass.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hIconSm       = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH) GetStockObject(BLACK_BRUSH);//(HBRUSH) (COLOR_BTNFACE + 1);
	wndclass.lpszMenuName  = TEXT("SHOWMENU");
	wndclass.lpszClassName = szAppName;
	
	if(!RegisterClassEx(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT or above!!"), szAppName, MB_ICONERROR);
		return(0);
	}
	
	//Create Main Window
	hwnd = CreateWindow(
						szAppName,
						TEXT("AstroMediComp"),
						(WS_OVERLAPPEDWINDOW &~ WS_MAXIMIZEBOX) | WS_CLIPCHILDREN, 
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						NULL,
						NULL,
						hInstance,
						NULL
					);

// WS_OVERLAPPEDWINDOW ==> WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX
// WS_OVERLAPPEDWINDOW &~ WS_MAXIMIZEBOX ==> remove WS_MAXIMIZEBOX from WS_OVERLAPPEDWINDOW					
		
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	
	while(GetMessage(&msg, NULL, 0, 0))
	{
		if ( !IsDialogMessage(hwnd, &msg) )
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	
	return(msg.wParam);
}


/********************** RELEASE COM Interface Pointers ****************************/
void AMC_ReleaseCOM()
{
	//MessageBox(NULL, TEXT("Release"), TEXT("Release"), MB_OK);
	if(pIReadRecord != NULL)
	{
		pIReadRecord->Release();
		pIReadRecord = NULL;
	}
	if(pIWriteRecord != NULL)
	{ 
		pIWriteRecord->Release();
		pIWriteRecord = NULL;
	}
}


/******************** ListViewCompareFunc ************************/
int CALLBACK ListViewCompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	int a = strcmp((char*) lParam1, (char*) lParam2);
	
	if(sortFlag == SORT_ASCENDING)  //Ascending
	{
		return(a);
	}
	else		//Descending
	{
		return(-a);
	}
	return(a);
}



/*********************** WNDPROC *****************************/
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hwndDataEntry;
	static HWND hwndTable;
	static HWND hwndSearch;
	static HINSTANCE hInstance;
	static BOOL bShowSpashScreen = TRUE;
	
	HBITMAP     hBitmap;
	HDC         hdc, hdcMem;
	PAINTSTRUCT ps;
	BITMAP      bitmap;	
	RECT        rc;
	
	switch(message)
	{
		/**************** WM_CREATE ***********************/
		case WM_CREATE:
			{
					/**
					 * disable menu
					 **/
					EnableMenuItem(GetMenu(hwnd), 0, MF_BYPOSITION | MF_DISABLED);
					
					hInstance = ((LPCREATESTRUCT)lParam)->hInstance;
					WNDCLASSEX   wndclass;
			
					/*******************************************
					 *  DataEntry Window
					 *******************************************/
					wndclass.cbSize        = sizeof(wndclass);
					wndclass.style         = CS_HREDRAW | CS_VREDRAW;
					wndclass.lpfnWndProc   = DataEntryWndProc;
					wndclass.cbClsExtra    = 0;
					wndclass.cbWndExtra    = 0;
					wndclass.hInstance     = hInstance;
					wndclass.hIcon         = NULL;
					wndclass.hIconSm       = NULL;
					wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
					wndclass.hbrBackground = CreateSolidBrush(RGB(37, 172, 168));//GetStockObject(BLACK_BRUSH);
					wndclass.lpszMenuName  = TEXT("DATA");
					wndclass.lpszClassName = TEXT("DATA");
					
					if(!RegisterClassEx(&wndclass))
					{
						MessageBox(NULL, TEXT("This program requires Windows NT or above!!"), TEXT("DATA"), MB_ICONERROR);
						return(0);
					}
					
					
					/*******************************************
					 *  Read Window
					 *******************************************/
					wndclass.cbSize        = sizeof(wndclass);
					wndclass.style         = CS_HREDRAW | CS_VREDRAW;
					wndclass.lpfnWndProc   = ShowRecordWndProc;//TableWndProc;
					wndclass.cbClsExtra    = 0;
					wndclass.cbWndExtra    = 0;
					wndclass.hInstance     = hInstance;
					wndclass.hIcon         = NULL;
					wndclass.hIconSm       = NULL;
					wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
					wndclass.hbrBackground = CreateSolidBrush(RGB(37, 172, 168));//GetStockObject(BLACK_BRUSH);
					wndclass.lpszMenuName  = TEXT("READ");
					wndclass.lpszClassName = TEXT("READ");
					
					if(!RegisterClassEx(&wndclass))
					{
						MessageBox(NULL, TEXT("TABLE ==> This program requires Windows NT or above!!"), TEXT("DATA"), MB_ICONERROR);
						return(0);
					}
					
					/*******************************************
					 *  Search Window
					 *******************************************/
					wndclass.cbSize        = sizeof(wndclass);
					wndclass.style         = CS_HREDRAW | CS_VREDRAW;
					wndclass.lpfnWndProc   = SearchRecordWndProc;//SearchRecordWndProc;
					wndclass.cbClsExtra    = 0;
					wndclass.cbWndExtra    = 0;
					wndclass.hInstance     = hInstance;
					wndclass.hIcon         = NULL;
					wndclass.hIconSm       = NULL;
					wndclass.hCursor       = LoadCursor(NULL, IDC_ARROW);
					wndclass.hbrBackground = CreateSolidBrush(RGB(37, 172, 168));//GetStockObject(BLACK_BRUSH);
					wndclass.lpszMenuName  = TEXT("SEARCH");
					wndclass.lpszClassName = TEXT("SEARCH");
					
					if(!RegisterClassEx(&wndclass))
					{
						MessageBox(NULL, TEXT("TABLE ==> This program requires Windows NT or above!!"), TEXT("DATA"), MB_ICONERROR);
						return(0);
					}
					
					GetClientRect(hwnd, &rc);
					
					//DataEntry
					hwndDataEntry = CreateWindowEx(
										WS_EX_CLIENTEDGE,
										TEXT("DATA"),
										TEXT("DATA"),
										WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN,
										rc.left + rc.right/2 - 400,
										rc.top,
										800,
										rc.bottom - 10,
										hwnd,
										NULL,
										hInstance,
										NULL
									);
									
					ShowWindow(hwndDataEntry, SW_HIDE);
					UpdateWindow(hwndDataEntry);
					
					//Table
					hwndTable = CreateWindowEx(WS_EX_CLIENTEDGE,
										TEXT("READ"),
										TEXT("READ"),
										WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | CS_HREDRAW | CS_VREDRAW,
										rc.left,
										rc.top,
										rc.right - 10,
										rc.bottom - 10,
										hwnd,
										NULL,
										hInstance,
										NULL
									);
									
					ShowWindow(hwndTable, SW_HIDE);
					UpdateWindow(hwndTable);
					
					
					//search table
					hwndSearch = CreateWindowEx(WS_EX_CLIENTEDGE,
										TEXT("SEARCH"),
										TEXT("SEARCH"),
										WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | CS_HREDRAW | CS_VREDRAW,
										rc.left,
										rc.top,
										rc.right - 10,
										rc.bottom - 10,
										hwnd,
										NULL,
										hInstance,
										NULL
									);
									
					ShowWindow(hwndSearch, SW_HIDE);
					UpdateWindow(hwndSearch);
			
					return(0);
			}
		
		/**************** WM_KEYDOWN ***********************/
		case WM_KEYDOWN:
			{
				//If splash screen is ON Then OFF splash screen
				if(bShowSpashScreen)
				{
					GetClientRect(hwnd, &rc);
					bShowSpashScreen = FALSE;
					
					InvalidateRect(hwnd, NULL, TRUE);
					
					/**
					 * enable menu
					 **/
					EnableMenuItem(GetMenu(hwnd), 0, MF_BYPOSITION | MF_ENABLED);
				}
				break;
			}
		
		/**************** WM_PAINT ***********************/
		case WM_PAINT:
			{
				if(bShowSpashScreen)
				{
					hdc     = BeginPaint(hwnd, &ps);
					SetBkColor(hdc, RGB(0, 0, 0));
					
					
					hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(MYBITMAP));
					GetClientRect(hwnd, &rc);
					hdcMem  = CreateCompatibleDC(NULL);
					SelectObject(hdcMem, hBitmap);
					GetObject(hBitmap, sizeof(BITMAP), (PSTR)&bitmap);
					StretchBlt(hdc, 100, 0, (rc.right - 100) - 100, rc.bottom - 50,
										 hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
					DeleteObject(hBitmap);
					DeleteDC(hdcMem);
					
					SetTextColor(hdc, RGB(0, 255, 0));
					
					RECT rect;
					rect.top    = rc.top + 10;
					rect.bottom = rc.top + 50;
					rect.left   = rc.left + 10;
					rect.right  = rc.left + 200;
					
					//Font Height
					long lfHeight = -MulDiv(20, GetDeviceCaps(hdc, LOGPIXELSY), 72);
					//create font
					HFONT hf = CreateFont(lfHeight,   //logical height of font
					                             0,   //logical average character width
																			 0,   //angle of escapement
																			 0,   //base-line orientation angle
																			 0,    //font weight
																			 TRUE, //italic attribute flag
																			 0,    //underline attribute flag
																			 0,    //strikeout attribute flag
																			 0,    //character set identifier
																			 0,    //output precision
																			 0,    //clipping precision
																			 0,    //output quality
																			 0,    //pitch and family
																			 "Segoe UI"  //pointer to typeface name string
																);
					HFONT hOld = (HFONT)SelectObject(hdc, hf);

					int cyChar = HIWORD(GetDialogBaseUnits());
					TextOut(hdc,rect.left, rect.top           , "Name :- Vijaykumar J. Dangi", strlen("Name :- Vijaykumar J. Dangi"));
					TextOut(hdc,rect.left, rect.top + 2*cyChar, "Batch :- WinRT-2019", strlen("Batch :- WinRT-2019"));
					TextOut(hdc,rect.left, rect.top + 4*cyChar, "Group Name:- WM_SIZE", strlen("Group Name:- WM_SIZE"));
					rc.top = rc.bottom - 50;
					

					DrawText(hdc, TEXT("Press Any Key Continue...."),
										-1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
										
					SelectObject(hdc, hOld);										
					EndPaint(hwnd, &ps);
				}
				else
				{
					hdc     = BeginPaint(hwnd, &ps);
					SetBkColor(hdc, RGB(0, 0, 0));
					GetClientRect(hwnd, &rc);
					long lfHeight = -MulDiv(40, GetDeviceCaps(hdc, LOGPIXELSY), 72);
					HFONT hf = CreateFont(lfHeight, 0, 5, 0, 0, TRUE, 0, 0, 0, 0, 0, 0, 0, "Segoe UI");
					HFONT hOld = (HFONT)SelectObject(hdc, hf);
					SetTextColor(hdc, RGB(0, 255, 0));
					DrawText(hdc, TEXT(" Knowledge Is Inter-related   "),
										-1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

					SelectObject(hdc, hOld);
					
					EndPaint(hwnd, &ps);
				}
				break;
			}
		
		/**************** WM_COMMAND ***********************/
		case WM_COMMAND:
			{
				switch(LOWORD(wParam))
				{
					case ID_DATA_ENTRY:
						ShowWindow(hwndDataEntry, SW_SHOW);
						ShowWindow(hwndTable    , SW_HIDE);
						ShowWindow(hwndSearch   , SW_HIDE);
						
						SetWindowText(hwnd, TEXT("AstroMediComp - DataEntry"));
						break;
						
					case ID_SHOW_RECORD:
						ShowWindow(hwndTable    , SW_SHOW);
						ShowWindow(hwndDataEntry, SW_HIDE);
						ShowWindow(hwndSearch   , SW_HIDE);
						
						SetWindowText(hwnd, TEXT("AstroMediComp - Show Record"));
						break;
						
					case ID_SEARCH:
						ShowWindow(hwndSearch   , SW_SHOW);
						ShowWindow(hwndTable    , SW_HIDE);
						ShowWindow(hwndDataEntry, SW_HIDE);
						
						SetWindowText(hwnd, TEXT("AstroMediComp - Search Record"));
						break;
				}
				return(0);
			}
			
		/**************** WM_RBUTTONDOWN ***********************/
		case WM_RBUTTONDOWN:
			{
				ShowWindow(hwndDataEntry, SW_HIDE);
				ShowWindow(hwndTable, SW_HIDE);
				return(0);
			}
			
		/**************** WM_DESTROY ***********************/
		case WM_DESTROY:
			{
				//Release COM Object
				AMC_ReleaseCOM();
				//Destroy Child window
				DestroyWindow(hwndDataEntry);
				DestroyWindow(hwndTable);
				DestroyWindow(hwndSearch);
				//Destroy Parent Window
				PostQuitMessage(0);
				return(0);
			}
	}
	
	return(DefWindowProc(hwnd, message, wParam, lParam));
}


