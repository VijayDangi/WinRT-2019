#include "Main.h"

/******************** ShowRecordWndProc ******************************************/
LRESULT CALLBACK ShowRecordWndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HINSTANCE hInstance;
	
	static HWND hwndListDepartment;
	static HWND hwndStaticDepartment;
	static HWND hwndButtonDepartment;
	static int  flagDepartment = 0;
	
	static HWND hwndStaticCountDisplay;
	
	static HWND hwndReadButton;
	
	static HWND hListView;
	
	
	static int cxChar = LOWORD(GetDialogBaseUnits());
	static int cyChar = HIWORD(GetDialogBaseUnits());
	
	RECT rect;
	LVITEM lvi = {0};
	static struct EmployeeDetails *employee = NULL;
	
	
		
	switch(message)
	{
		
		/******************* WM_CREATE ******************/			
		case WM_CREATE:							
		{		
					GetClientRect(hwnd, &rect);
				
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
				
				
				
				//**** Read Button
					//btn
						hwndReadButton = CreateWindow( 
						 /* Class  Name     */      TEXT("button"),  //This is predefined name
						 /* Window text     */      TEXT("READ"),
						 /* Window Style    */      WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
						 /* x Position      */      (rect.right/4) + (25 * cxChar),
							 /* y Position      */    (rect.top + 10),
						 /* Width           */      13 * cxChar,
																				cyChar * 1.3,
						 /* Parent window   */      hwnd,
						 /* Child window ID */      (HMENU) ID_READ_BUTTON,
						 /* Instance Handle */      ((LPCREATESTRUCT) lParam)->hInstance,
						 /* Extra Prameters */      NULL
							);
							
							EnableWindow(hwndReadButton, FALSE);

			//count display
			//static
						hwndStaticCountDisplay = CreateWindow(TEXT("static"),
											NULL,
											WS_CHILD | WS_VISIBLE | SS_LEFT | WS_BORDER,
											(rect.right - 10) - (18 * cxChar),
											95,
											18 * cxChar,
											cyChar * 1.3,
											hwnd,
											(HMENU) ID_STATIC_DEPARTMENT,
											((LPCREATESTRUCT) lParam) -> hInstance,// OR (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),
											NULL
									);
				
				
				
				
				
				
				InitCommonControls();   //INITIALIZE COMMON CONTROL'S  //declare in "commctrl.h"
				
				
				//ListView
				hListView = CreateWindow(
								WC_LISTVIEW,
								"",
								WS_VISIBLE | WS_BORDER | WS_CHILD | LVS_REPORT | LVS_EX_GRIDLINES,
								rect.left + 5,
								120,
								rect.right - 10,
								rect.bottom - 135,
								hwnd,
								(HMENU)5,
								((LPCREATESTRUCT) lParam)->hInstance,
								0
							);
					
				ListView_SetExtendedListViewStyle(hListView, LVS_EX_GRIDLINES | LVS_EX_AUTOSIZECOLUMNS | LVS_EX_FULLROWSELECT);
							
				/***Create Column ***/
				LVCOLUMN lvc;
					lvc.mask = LVCF_WIDTH | LVCF_TEXT | LVCF_FMT | LVCF_SUBITEM;
					lvc.fmt  = LVCFMT_LEFT;
					lvc.cx = ( (rect.right - 10) - (rect.left + 5) ) / 9.8;
					lvc.pszText = "Employee ID";
					lvc.iSubItem = 1;
				ListView_InsertColumn(hListView, 1, &lvc);
				
					lvc.pszText = "Department";
					lvc.iSubItem = 10;
				ListView_InsertColumn(hListView, 1, &lvc);
				
					lvc.pszText = "Date Of Joining";
					lvc.iSubItem = 9;
				ListView_InsertColumn(hListView, 1, &lvc);
				
					lvc.pszText = "Date Of Birth";
					lvc.iSubItem = 8;
				ListView_InsertColumn(hListView, 1, &lvc);

					lvc.pszText = "Address";
					lvc.iSubItem = 7;
				ListView_InsertColumn(hListView, 1, &lvc);

					lvc.cx = ( (rect.right - 10) - (rect.left + 5) ) / 15;
					lvc.pszText = "Gender";
					lvc.iSubItem = 6;
				ListView_InsertColumn(hListView, 1, &lvc);

					lvc.cx = ( (rect.right - 10) - (rect.left + 5) ) / 9.8;
					lvc.pszText = "Mobile No.";
					lvc.iSubItem = 5;
				ListView_InsertColumn(hListView, 1, &lvc);
				
					lvc.pszText = "Email Id";
					lvc.iSubItem = 4;
				ListView_InsertColumn(hListView, 1, &lvc);
				
					lvc.pszText = "LastName";
					lvc.iSubItem = 3;
				ListView_InsertColumn(hListView, 1, &lvc);
				
					lvc.pszText = "FirstName";
					lvc.iSubItem = 2;
				//ListView_InsertColumn(hListView, 1, &lvc);
				SendMessage(hListView, LVM_INSERTCOLUMN, (WPARAM) 1, (LPARAM)  &lvc);
				
			return(0);
		}
		
		/******************* WM_CTLCOLORSTATIC ******************/			
		case WM_CTLCOLORSTATIC:
		{
				SetBkColor((HDC)wParam, RGB(255, 255, 255));
				return((INT_PTR)CreateSolidBrush(RGB(255, 255, 255)));
			
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
				
				if(LOWORD(wParam) == ID_LIST_DEPARTMENT)
				{
					if(HIWORD(wParam) == LBN_SELCHANGE)
					{
						int index = AMC_SetSelectedText(hwndListDepartment, hwndStaticDepartment);
						if(index != 0)
						{
							EnableWindow(hwndReadButton, TRUE);
						}
						else
						{
							EnableWindow(hwndReadButton, FALSE);
						}
						flagDepartment = 0;
					}
				}
				
				if(LOWORD(wParam) == ID_READ_BUTTON)
				{
					if(HIWORD(wParam) == BN_CLICKED)
					{
						TCHAR str[15];
						wsprintf(str, TEXT("TOTAL : 0"));
						SendMessage(hwndStaticCountDisplay, WM_SETTEXT, (WPARAM)0, (LPARAM) str);
							
						//disable READ button
						EnableWindow(hwndReadButton, FALSE);
						
						//Empty List View first
						SendMessage(hListView, LVM_DELETEALLITEMS, 0, 0);
						
						char* department = NULL;

						//Free employee struct list first
						AMC_FreeEmployeeStructMemory(employee);
						employee = NULL;
						
						int length = 0;
						int index = SendMessage(hwndListDepartment, LB_GETCURSEL, 0, 0);
						if(index == 1)
						{
							pIReadRecord->ReadRecord(NULL, SEARCH_NONE, NULL, &employee, &length);
						}
						else
						{
							AMC_GetText(hwndStaticDepartment, &department);
							pIReadRecord->ReadRecord(department, SEARCH_NONE, NULL, &employee, &length);
						}
						if(length > 0)
						{
							int ret;
							LVITEM lvi = {0};
							lvi.mask = LVIF_TEXT | LVIF_PARAM;
							lvi.iItem = 0;
							
							//Set number of entries in table
							TCHAR str[15];
							wsprintf(str, TEXT("TOTAL : %3d"), length);
							SendMessage(hwndStaticCountDisplay, WM_SETTEXT, (WPARAM)0, (LPARAM) str);
							
							SendMessage(hListView, LVM_SETTEXTCOLOR, 0, (LPARAM)RGB(58, 151, 144));
							
							while(length--)
							{							
								lvi.pszText = employee->employeeId;
								lvi.lParam = (LPARAM)employee->employeeId;  //send as LPARAM to CompareFunc
								ret = ListView_InsertItem(hListView, &lvi);
								
								lvi.lParam = (LPARAM)employee->firstName;  //send as LPARAM to CompareFunc
								ListView_SetItemText(hListView,ret, 1, employee->firstName);
								
								lvi.lParam = (LPARAM)employee->lastName;  //send as LPARAM to CompareFunc
								ListView_SetItemText(hListView,ret, 2, employee->lastName);
								
								lvi.lParam = (LPARAM)employee->email_id;  //send as LPARAM to CompareFunc
								ListView_SetItemText(hListView,ret, 3, employee->email_id);
								
								lvi.lParam = (LPARAM)employee->mobile_no;  //send as LPARAM to CompareFunc
								ListView_SetItemText(hListView,ret, 4, employee->mobile_no);
								
								lvi.lParam = (LPARAM)employee->gender;  //send as LPARAM to CompareFunc
								ListView_SetItemText(hListView,ret, 5, employee->gender);
								
								lvi.lParam = (LPARAM)employee->address;  //send as LPARAM to CompareFunc
								ListView_SetItemText(hListView,ret, 6, employee->address);
								
								lvi.lParam = (LPARAM)employee->dateOfBirth;  //send as LPARAM to CompareFunc
								ListView_SetItemText(hListView,ret, 7, employee->dateOfBirth);
								
								lvi.lParam = (LPARAM)employee->dateOfJoining;  //send as LPARAM to CompareFunc
								ListView_SetItemText(hListView,ret, 8, employee->dateOfJoining);
								
								lvi.lParam = (LPARAM)employee->department_name;  //send as LPARAM to CompareFunc
								ListView_SetItemText(hListView,ret, 9, employee->department_name);
								
								(lvi.iItem)++;
								
								employee = employee->nextDetails;
							}
						}	

						//enable READ button
						//EnableWindow(hwndReadButton, TRUE);						
					}
				}

				return(0);
		}
			
		/******************* WM_NOTIFY ******************/			
		case WM_NOTIFY:
		{
				if(((LPNMHDR) lParam)->code == LVN_COLUMNCLICK)
				{
					int CALLBACK ListViewCompareFunc(LPARAM, LPARAM, LPARAM);	
					
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
				PostQuitMessage(0);
				return(0);
		}
	}
	return(DefWindowProc(hwnd, message, wParam, lParam));
}
