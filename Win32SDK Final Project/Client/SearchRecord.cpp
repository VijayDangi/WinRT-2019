#include "Main.h"


/******************** SearchRecordWndProc ******************************************/
LRESULT CALLBACK SearchRecordWndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hwndListDepartment;
	static HWND hwndStaticDepartment;
	static HWND hwndButtonDepartment;
	static int  flagDepartment = 0;
	
	static HWND hwndRadioFirstName;
	static HWND hwndRadioLastName;
	static HWND hwndRadioEmailId;
	static HWND hwndRadioMobileNo;
	
	static HWND hwndEditSearchString;
	
	static HWND hwndStaticCountDisplay;
	
	static HWND hwndSearchButton;
	
	static HWND hListView;
	
	static int iSearchByCategory = SEARCH_BY_FIRST_NAME;  //By default
	
	static int cxChar = LOWORD(GetDialogBaseUnits());
	static int cyChar = HIWORD(GetDialogBaseUnits());

	RECT rect;
	LVITEM lvi = {0};
	static struct EmployeeDetails *employee = NULL;
	
	
		
	switch(message)
	{
		/******************* WM_CTLCOLORSTATIC ******************/			
		case WM_CTLCOLORSTATIC:
		{
			if((HWND) lParam == hwndStaticDepartment)
			{
				SetBkColor((HDC)wParam, RGB(255, 255, 255));
				return((INT_PTR)CreateSolidBrush(RGB(255, 255, 255)));
			}
			else
			{
				SetTextColor((HDC)wParam, RGB(255, 255, 255));
				SetBkColor((HDC)wParam, RGB(37, 172, 168));
				return((INT_PTR)CreateSolidBrush(RGB(37, 172, 168)));
			}
		}
		
		/******************* WM_CREATE ******************/			
		case WM_CREATE:							
		{
				GetClientRect(hwnd, &rect);
			
				CreateWindow(TEXT("static"),
									TEXT("SEARCH IN"),
									WS_CHILD | WS_VISIBLE | SS_LEFT,
									(rect.right/4) - (15 * cxChar),
									rect.top + 10,
									10 * cxChar,
									cyChar * 1.3,
									hwnd,
									(HMENU) -1,
									((LPCREATESTRUCT) lParam) -> hInstance,// OR (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),
									NULL
									);
										
						//SendMessage(h, WM_SETTEXT, 0, (LPARAM) TEXT("SEARCH IN"));
				
				//DEPARTMENT
						//static
						hwndStaticDepartment = CreateWindow(TEXT("static"),
											NULL,
											WS_CHILD | WS_VISIBLE | SS_LEFT | WS_BORDER,
											(rect.right/4),
											rect.top + 10,
											18 * cxChar,
											cyChar * 1.3,
											hwnd,
											(HMENU) ID_STATIC_DEPARTMENT,
											((LPCREATESTRUCT) lParam) -> hInstance,// OR (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),
											NULL
									);
									
						//btn
						hwndButtonDepartment = CreateWindow( 
						 /* Class  Name     */      TEXT("button"),  //This is predefined name
						 /* Window text     */      TEXT("V"),
						 /* Window Style    */      WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
						 /* x Position      */      (rect.right/4) + (18 * cxChar),
							 /* y Position      */    rect.top + 10,
						 /* Width           */      5 * cxChar,
						 /* Height          */      cyChar * 1.3,
						 /* Parent window   */      hwnd,
						 /* Child window ID */      (HMENU) ID_BUTTON_DEPARTMENT,
						 /* Instance Handle */      ((LPCREATESTRUCT) lParam)->hInstance,
						 /* Extra Prameters */      NULL
							);

						//list
						hwndListDepartment = CreateWindow(
												TEXT("listbox"),
												TEXT(""),
												WS_CHILD | WS_VISIBLE | LBS_STANDARD | WS_CLIPSIBLINGS,
												(rect.right/4),
												(rect.top + 10) + (cyChar * 1.3),
												18 * cxChar,
												 5 * cyChar,
												hwnd,
												(HMENU) ID_LIST_DEPARTMENT,
												((LPCREATESTRUCT) lParam) -> hInstance,
												NULL										
											);
						
								SendMessage(hwndListDepartment, LB_INSERTSTRING,  0, (LPARAM) "<DEPARTMENT>");
								SendMessage(hwndListDepartment, LB_INSERTSTRING,  1, (LPARAM) "ALL");
								SendMessage(hwndListDepartment, LB_INSERTSTRING,  2, (LPARAM) Department_WM_CREATE);
								SendMessage(hwndListDepartment, LB_INSERTSTRING,  3, (LPARAM) Department_WM_LBUTTONDOWN);
								SendMessage(hwndListDepartment, LB_INSERTSTRING,  4, (LPARAM) Department_WM_SIZE);
								SendMessage(hwndListDepartment, LB_INSERTSTRING,  5, (LPARAM) Department_WM_KEYUP);
								SendMessage(hwndListDepartment, LB_INSERTSTRING,  6, (LPARAM) Department_WM_KEYDOWN);
								SendMessage(hwndListDepartment, LB_INSERTSTRING,  7, (LPARAM) Department_WM_COMMAND);
								SendMessage(hwndListDepartment, LB_INSERTSTRING,  8, (LPARAM) Department_WM_DRAWITEM);
								SendMessage(hwndListDepartment, LB_INSERTSTRING,  9, (LPARAM) Department_WM_PAINT);
								SendMessage(hwndListDepartment, LB_INSERTSTRING, 10, (LPARAM) Department_WM_CHAR);
								SendMessage(hwndListDepartment, LB_INSERTSTRING, 11, (LPARAM) Department_WM_DESTROY);
								SendMessage(hwndListDepartment, LB_INSERTSTRING, 12, (LPARAM) Department_WM_SETFOCUS);
								SendMessage(hwndListDepartment, LB_INSERTSTRING, 13, (LPARAM) Department_WM_ENABLE);
								SendMessage(hwndListDepartment, LB_INSERTSTRING, 14, (LPARAM) Department_WM_MOUSEMOVE);
								SendMessage(hwndListDepartment, LB_INSERTSTRING, 15, (LPARAM) Department_WM_RBUTTONDOWN);
								
						AMC_SetIndex(hwndListDepartment, hwndStaticDepartment, 0);
							
						ShowWindow(hwndListDepartment, SW_HIDE);
							
						flagDepartment = 0;
				
				
				
	////SEARCH BY
						CreateWindow(TEXT("static"),
										TEXT("SEARCH BY"),
										WS_CHILD | WS_VISIBLE | SS_LEFT,
										(rect.right/4) - (15 * cxChar),
										rect.top + 40,
										13 * cxChar,
										cyChar * 1.3,
										hwnd,
										(HMENU) -1,
										((LPCREATESTRUCT) lParam) -> hInstance,// OR (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),
										NULL
										);
				
						hwndRadioFirstName = CreateWindow(
								TEXT("button"),
								TEXT("First Name"),
								WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
								(rect.right/4),
								rect.top + 40,
								15 * cxChar,
								cyChar * 1.3,
								hwnd,
								(HMENU) ID_EDIT_FIRSTNAME,
								((LPCREATESTRUCT) lParam)->hInstance,
								NULL
							);
							
						hwndRadioLastName = CreateWindow(
								TEXT("button"),
								TEXT("Last Name"),
								WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
								(rect.right/4) + (22 * cxChar),
								rect.top + 40,
								15 * cxChar,
								cyChar * 1.3,
								hwnd,
								(HMENU) ID_EDIT_LASTNAME,
								((LPCREATESTRUCT) lParam)->hInstance,
								NULL
							);
							
						hwndRadioEmailId = CreateWindow(
								TEXT("button"),
								TEXT("Email Id"),
								WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
								(rect.right/4) + 2 * (22 * cxChar),
								rect.top + 40,
								15 * cxChar,
								cyChar * 1.3,
								hwnd,
								(HMENU) ID_EDIT_EMAIL,
								((LPCREATESTRUCT) lParam)->hInstance,
								NULL
							);
							
						hwndRadioMobileNo = CreateWindow(
								TEXT("button"),
								TEXT("Mobile NO."),
								WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
								(rect.right/4) + 3 * (22 * cxChar),
								rect.top + 40,
								15 * cxChar,
								cyChar * 1.3,
								hwnd,
								(HMENU) ID_EDIT_MOBILE,
								((LPCREATESTRUCT) lParam)->hInstance,
								NULL
							);
							
							//set checked to FirstName by default
						SendMessage(hwndRadioFirstName, BM_SETCHECK, (WPARAM) 1, (LPARAM) 0);

	///////Search String
					CreateWindow(TEXT("static"),
										TEXT("SEARCH STRING"),
										WS_CHILD | WS_VISIBLE | SS_LEFT,
										(rect.right/4) - (15 * cxChar),
										rect.top + 70,
										17 * cxChar,
										cyChar * 1.3,
										hwnd,
										(HMENU) -1,
										((LPCREATESTRUCT) lParam) -> hInstance,// OR (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),
										NULL
										);
				
					hwndEditSearchString = CreateWindow(
												TEXT("edit"),
												NULL,
												WS_CHILD | WS_VISIBLE | SS_LEFT | WS_BORDER | ES_AUTOHSCROLL,
												(rect.right/4) + (8 * cxChar),
												rect.top + 70,
												20 * cxChar,
												cyChar * 1.3,
												hwnd,
												(HMENU) ID_SEARCH_EDIT,
												((LPCREATESTRUCT) lParam)->hInstance,
												NULL
										);
				
				//**** Search Button
					//btn
						hwndSearchButton = CreateWindow( 
						 /* Class  Name     */      TEXT("button"),  //This is predefined name
						 /* Window text     */      TEXT("SEARCH"),
						 /* Window Style    */      WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
						 /* x Position      */      (rect.right/4) + (40 * cxChar),
						 /* y Position      */      (rect.top + 90),
						 /* Width           */      13 * cxChar,
																				cyChar * 1.3,
						 /* Parent window   */      hwnd,
						 /* Child window ID */      (HMENU) ID_READ_BUTTON,
						 /* Instance Handle */      ((LPCREATESTRUCT) lParam)->hInstance,
						 /* Extra Prameters */      NULL
							);
							
							EnableWindow(hwndSearchButton, FALSE);

			
							
			//count display
			//static
						hwndStaticCountDisplay = CreateWindow(TEXT("static"),
											NULL,
											WS_CHILD | WS_VISIBLE | SS_LEFT | WS_BORDER,
											(rect.right - 10) - (18 * cxChar),
											rect.top + 115,
											18 * cxChar,
											cyChar * 1.3,
											hwnd,
											(HMENU) ID_STATIC_DEPARTMENT,
											((LPCREATESTRUCT) lParam) -> hInstance,// OR (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),
											NULL
									);
				
				
				
				
				
				
				InitCommonControls();   //INITIALIZE COMMON CONTROL'S  //declare in "commctrl.h"
				
				
				hListView = CreateWindow(
								WC_LISTVIEW,
								"",
								WS_VISIBLE | WS_BORDER | WS_CHILD | LVS_REPORT | LVS_EX_GRIDLINES,
								rect.left + 5,
								rect.top + 140,
								rect.right - 10,
								rect.bottom - 155,
								hwnd,
								(HMENU)5,
								((LPCREATESTRUCT) lParam)->hInstance,
								0
							);
					
				ListView_SetExtendedListViewStyle(hListView, LVS_EX_GRIDLINES | LVS_EX_AUTOSIZECOLUMNS | LVS_EX_FULLROWSELECT);
							
				/***Create Column ***/
				LVCOLUMN lvc;
					lvc.mask = LVCF_WIDTH | LVCF_TEXT;
					lvc.fmt  = LVCFMT_RIGHT;
					lvc.cx = ( (rect.right - 10) - (rect.left + 5) ) / 9.8;
					lvc.pszText = "Employee ID";
					lvc.iSubItem = 1;
				ListView_InsertColumn(hListView, 1, &lvc);
				
					lvc.pszText = "Department";
				ListView_InsertColumn(hListView, 1, &lvc);
				
					lvc.pszText = "Date Of Joining";
				ListView_InsertColumn(hListView, 1, &lvc);
				
					lvc.pszText = "Date Of Birth";
				ListView_InsertColumn(hListView, 1, &lvc);

					lvc.pszText = "Address";
				ListView_InsertColumn(hListView, 1, &lvc);

					lvc.cx = ( (rect.right - 10) - (rect.left + 5) ) / 15;
					lvc.pszText = "Gender";
				ListView_InsertColumn(hListView, 1, &lvc);

					lvc.cx = ( (rect.right - 10) - (rect.left + 5) ) / 9.8;
					lvc.pszText = "Mobile No.";
				ListView_InsertColumn(hListView, 1, &lvc);
				
					lvc.pszText = "Email Id";
				ListView_InsertColumn(hListView, 1, &lvc);
				
					lvc.pszText = "LastName";
				ListView_InsertColumn(hListView, 1, &lvc);
				
					lvc.pszText = "FirstName";
				//ListView_InsertColumn(hListView, 1, &lvc);
				SendMessage(hListView, LVM_INSERTCOLUMN, (WPARAM) 1, (LPARAM)  &lvc);
				
			
			return(0);
		}
	
		/******************* WM_COMMAND ******************/			
		case WM_COMMAND:
		{
/*******************************************************
 * ID_BUTTON_DEPARTMENT
 *******************************************************/					
			//department
				if(LOWORD(wParam) == ID_BUTTON_DEPARTMENT  && HIWORD(wParam) == BN_CLICKED)
				{
					if(flagDepartment)
					{
						ShowWindow(hwndListDepartment, SW_HIDE);
						flagDepartment = 0;
					}
					else
					{
						//show list window
						ShowWindow(hwndListDepartment, SW_SHOW);
						flagDepartment = 1;				
					}
				}
				
				else if(LOWORD(wParam) == ID_LIST_DEPARTMENT)
				{
					if(HIWORD(wParam) == LBN_SELCHANGE)
					{
						int index = AMC_SetSelectedText(hwndListDepartment, hwndStaticDepartment);
						if(index != 0)
						{
							EnableWindow(hwndSearchButton, TRUE);
						}
						else
						{
							EnableWindow(hwndSearchButton, FALSE);
						}
						flagDepartment = 0;
					}
				}
				
				else if(LOWORD(wParam) == ID_EDIT_FIRSTNAME)
				{
					if(SendMessage(hwndRadioFirstName, BM_GETCHECK, (WPARAM)0, (LPARAM)0) == BST_UNCHECKED)
					{
						SendMessage(hwndRadioFirstName, BM_SETCHECK, (WPARAM)1, (LPARAM) 0);
						SendMessage(hwndRadioLastName , BM_SETCHECK, (WPARAM)0, (LPARAM) 0);
						SendMessage(hwndRadioEmailId  , BM_SETCHECK, (WPARAM)0, (LPARAM) 0);
						SendMessage(hwndRadioMobileNo , BM_SETCHECK, (WPARAM)0, (LPARAM) 0);
						
						iSearchByCategory = SEARCH_BY_FIRST_NAME;
					}
				}
				else if(LOWORD(wParam) == ID_EDIT_LASTNAME)
				{
					if(SendMessage(hwndRadioLastName, BM_GETCHECK, (WPARAM)0, (LPARAM)0) == BST_UNCHECKED)
					{
						SendMessage(hwndRadioFirstName, BM_SETCHECK, (WPARAM)0, (LPARAM) 0);
						SendMessage(hwndRadioLastName , BM_SETCHECK, (WPARAM)1, (LPARAM) 0);
						SendMessage(hwndRadioEmailId  , BM_SETCHECK, (WPARAM)0, (LPARAM) 0);
						SendMessage(hwndRadioMobileNo , BM_SETCHECK, (WPARAM)0, (LPARAM) 0);
						
						iSearchByCategory = SEARCH_BY_LAST_NAME;
					}
				}
				else if(LOWORD(wParam) == ID_EDIT_EMAIL)
				{
					if(SendMessage(hwndRadioEmailId, BM_GETCHECK, (WPARAM)0, (LPARAM)0) == BST_UNCHECKED)
					{
						SendMessage(hwndRadioFirstName, BM_SETCHECK, (WPARAM)0, (LPARAM) 0);
						SendMessage(hwndRadioLastName , BM_SETCHECK, (WPARAM)0, (LPARAM) 0);
						SendMessage(hwndRadioEmailId  , BM_SETCHECK, (WPARAM)1, (LPARAM) 0);
						SendMessage(hwndRadioMobileNo , BM_SETCHECK, (WPARAM)0, (LPARAM) 0);
						
						iSearchByCategory = SEARCH_BY_EMAIL_ID;
					}
				}
				else if(LOWORD(wParam) == ID_EDIT_MOBILE)
				{
					if(SendMessage(hwndRadioMobileNo, BM_GETCHECK, (WPARAM)0, (LPARAM)0) == BST_UNCHECKED)
					{
						SendMessage(hwndRadioFirstName, BM_SETCHECK, (WPARAM)0, (LPARAM) 0);
						SendMessage(hwndRadioLastName , BM_SETCHECK, (WPARAM)0, (LPARAM) 0);
						SendMessage(hwndRadioEmailId  , BM_SETCHECK, (WPARAM)0, (LPARAM) 0);
						SendMessage(hwndRadioMobileNo , BM_SETCHECK, (WPARAM)1, (LPARAM) 0);
					
						iSearchByCategory = SEARCH_BY_MOBILE_NUMBER;
					}
				}
				
				
				else if(LOWORD(wParam) == ID_READ_BUTTON)
				{
					if(HIWORD(wParam) == BN_CLICKED)
					{
						//Set number of entries in table
							TCHAR str[15];
							wsprintf(str, TEXT("TOTAL : 0"));
							SendMessage(hwndStaticCountDisplay, WM_SETTEXT, (WPARAM)0, (LPARAM) str);
							
							
						//disable Search button
						EnableWindow(hwndSearchButton, FALSE);
						
						//Empty List View first
						SendMessage(hListView, LVM_DELETEALLITEMS, 0, 0);
						
						char* department = NULL;
						char* searchString = NULL;

						//Free employee struct list first
						AMC_FreeEmployeeStructMemory(employee);
						employee = NULL;
						
						//get search string
						AMC_GetText(hwndEditSearchString, &searchString);
						
						int length = 0;
						int index = SendMessage(hwndListDepartment, LB_GETCURSEL, 0, 0);
						if(index == 1)
						{
							//CALL TO READ RECORD
							pIReadRecord->ReadRecord(NULL, iSearchByCategory, searchString, &employee, &length);
						}
						else
						{
							AMC_GetText(hwndStaticDepartment, &department);
							//CALL TO READ RECORD
							pIReadRecord->ReadRecord(department, iSearchByCategory, searchString, &employee, &length);
						
							//free memory
							free(department);
							department = NULL;
						}
						
						//free memory
							free(searchString);
							searchString = NULL;
						
						if(length > 0)
						{
							int ret;
							LVITEM lvi = {0};
							lvi.mask = LVIF_TEXT;
							lvi.iItem = 0;
							
							//Set number of entries in table
							TCHAR str[15];
							wsprintf(str, TEXT("TOTAL : %3d"), length);
							SendMessage(hwndStaticCountDisplay, WM_SETTEXT, (WPARAM)0, (LPARAM) str);
							
							SendMessage(hListView, LVM_SETTEXTCOLOR, 0, (LPARAM)RGB(58, 151, 144));
							while(length--)
							{
								
							
								lvi.pszText = employee->employeeId;
								lvi.lParam  = (LPARAM) employee->employeeId;
								ret = ListView_InsertItem(hListView, &lvi);
								
								lvi.lParam  = (LPARAM) employee->firstName;
								ListView_SetItemText(hListView,ret, 1, employee->firstName);
								
								lvi.lParam  = (LPARAM) employee->lastName;
								ListView_SetItemText(hListView,ret, 2, employee->lastName);
								
								lvi.lParam  = (LPARAM) employee->email_id;
								ListView_SetItemText(hListView,ret, 3, employee->email_id);
								
								lvi.lParam  = (LPARAM) employee->mobile_no;
								ListView_SetItemText(hListView,ret, 4, employee->mobile_no);
								
								lvi.lParam  = (LPARAM) employee->gender;
								ListView_SetItemText(hListView,ret, 5, employee->gender);
								
								lvi.lParam  = (LPARAM) employee->address;
								ListView_SetItemText(hListView,ret, 6, employee->address);
								
								lvi.lParam  = (LPARAM) employee->dateOfBirth;
								ListView_SetItemText(hListView,ret, 7, employee->dateOfBirth);
								
								lvi.lParam  = (LPARAM) employee->dateOfJoining;
								ListView_SetItemText(hListView,ret, 8, employee->dateOfJoining);
								
								lvi.lParam  = (LPARAM) employee->department_name;
								ListView_SetItemText(hListView,ret, 9, employee->department_name);
								
								(lvi.iItem)++;
								
								employee = employee->nextDetails;
							}
						}	

						//enable READ button
						EnableWindow(hwndSearchButton, TRUE);						
					}
				}

				return(0);
		}
		
		/******************* WM_NOTIFY ******************/			
		case WM_NOTIFY:
		{
				if(((LPNMHDR) lParam)->code == LVN_COLUMNCLICK)
				{
					
					#define pnm ((NM_LISTVIEW*) lParam)
						
						ListView_SortItems(
										pnm->hdr.hwndFrom,
										ListViewCompareFunc,
										(LPARAM)(pnm->iSubItem)
									);
					#undef pnm
					
					sortFlag = !sortFlag;
				}
			
			return(0);	
		}
		
		/******************* WM_DESTROY ******************/			
		case WM_DESTROY:
		{
				AMC_FreeEmployeeStructMemory(employee);
				MessageBox(hwnd, TEXT("SearchRecordWndProc"), TEXT("FREE"), MB_OK);
				PostQuitMessage(0);
				return(0);
		}
	}
	return(DefWindowProc(hwnd, message, wParam, lParam));
}
