#include "Main.h"

/******************** DataEntryWndProc ******************************************/
//DataEntryWndProc
LRESULT CALLBACK DataEntryWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static  HWND   hwndTextFirstName;  //firstname
	static  HWND   hwndTextLastName;   //lastname
  static  HWND   hwndTextAddress;    //address
	static  HWND   hwndTextEmail;      //email
	static  HWND   hwndTextMobile;     //mobile
	static  HWND   hwndTextEmployeeID; //employee ID
	
	static  HWND   hwndRadioButtonMale , hwndRadioButtonFemale;  //gender
	
				   //Day - DOB			 //Month - DOB			 //Year - DOB
	static  HWND   hwndListDayOfDOB    , hwndListMonthOfDOB    , hwndListYearOfDOB;
	static  HWND   hwndStaticDayDOB    , hwndStaticMonthDOB    , hwndStaticYearDOB;
	static  HWND   hwndButtonDayDOB    , hwndButtonMonthDOB    , hwndButtonYearDOB;
	static  short  dayFlagDOB          , monthFlagDOB          , yearFlagDOB;

				   //Day - JOINING		 //Month - JOINING		 //Year - JOINING
 	static  HWND   hwndListDayOfJoining, hwndListMonthOfJoining, hwndListYearOfJoining;
	static  HWND   hwndStaticDayJoining, hwndStaticMonthJoining, hwndStaticYearJoining;
	static  HWND   hwndButtonDayJoining, hwndButtonMonthJoining, hwndButtonYearJoining;
	static  short  dayFlagJoining      , monthFlagJoining      , yearFlagJoining;

				   //Department
	static  HWND   hwndListDepartment;
	static  HWND   hwndStaticDepartment;
	static  HWND   hwndButtonDepartment;
	static  short  flagDepartment;
	
	static  HWND   focusHandle;
	        HWND   hwndTemp;
					
	static  HWND   hwndOkButton;
	static  HWND   hwndResetButton;
	
	static  bool   firstNameTextFocused         = false;
	static  bool   lastNameTextFocused          = false;
	static  bool   addressTextFocused           = false;
	static  bool   emailTextFocused             = false;
	static  bool   mobileTextFocused            = false;
	
	static  bool   male_RadioButton_Focused     = false;
	static  bool   female_RadioButton_Focused   = false;
	
	static  bool   year_DOB_Button_Focused      = false;
	static  bool   month_DOB_Button_Focused     = false;
	static  bool   day_DOB_Button_Focused       = false;
	
	static  bool   year_Joining_Button_Focused  = false;
	static  bool   month_Joining_Button_Focused = false;
	static  bool   day_Joining_Button_Focused   = false;
	
	static  bool   departmentButtonFocused      = false;
	static  bool   okButtonFocused              = false;
	static  bool   resetButtonFocused           = false;
	
	static  int    cxChar;
	static  int    cyChar;
	
	
	HDC         hdc;
	PAINTSTRUCT ps;
	RECT        rc;
	HBRUSH      hBrush;
	TCHAR       text[10];
	
	switch(message)
	{
		
		/********************  WM_CREATE ******************************/			
		case WM_CREATE:
			{
				cxChar = LOWORD(GetDialogBaseUnits());
				cyChar = HIWORD(GetDialogBaseUnits());

				
		//FirstName
				HWND h = CreateWindow (
						TEXT ("static"),
						NULL,
						WS_CHILD | WS_VISIBLE | ES_LEFT ,
						cxChar,
						cyChar,
						16 * cxChar,
						 7 * cyChar / 5,
						hwnd,
						(HMENU) -1,
						((LPCREATESTRUCT) lParam) -> hInstance,
						NULL
					);

				SendMessage(h, WM_SETTEXT, 0, (LPARAM) TEXT("First Name"));
				
				
				hwndTextFirstName    = CreateWindow(
									TEXT("edit"),
									NULL,
									WS_CHILD | WS_VISIBLE  | ES_LEFT | ES_AUTOHSCROLL | WS_TABSTOP,
									18 * cxChar,
									cyChar,
									20 * cxChar,
									 7 * cyChar / 5,
									hwnd,
									(HMENU) ID_EDIT_FIRSTNAME,
									((LPCREATESTRUCT) lParam) -> hInstance,
									NULL
								);
								
		//LastName
				h = CreateWindow (
						TEXT ("static"),
						NULL,
											WS_CHILD | WS_VISIBLE | ES_LEFT ,
											42 * cxChar,
						cyChar,
						16 * cxChar,
						 7 * cyChar / 5,
						hwnd,
						(HMENU) -1,
						((LPCREATESTRUCT) lParam) -> hInstance,
						NULL
					);

				SendMessage(h, WM_SETTEXT, 0, (LPARAM) TEXT("Last Name"));
				
				hwndTextLastName    = CreateWindow(
									TEXT("edit"),
									NULL,
									WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL | WS_TABSTOP,
									60 * cxChar,
									cyChar,
									20 * cxChar,
									 7 * cyChar / 5,
									hwnd,
									(HMENU) ID_EDIT_LASTNAME,
									((LPCREATESTRUCT) lParam) -> hInstance,
									NULL
								);
				
		
		//Address
				h = CreateWindow (
						TEXT ("static"),
						NULL,
											WS_CHILD | WS_VISIBLE | ES_LEFT ,
											cxChar,
						cyChar * 3,
						16 * cxChar,
						 7 * cyChar / 5,
						hwnd,
						(HMENU) -1,
						((LPCREATESTRUCT) lParam) -> hInstance,
						NULL
					);

				SendMessage(h, WM_SETTEXT, 0, (LPARAM) TEXT("Address"));
				
				hwndTextAddress = CreateWindow(
									TEXT("edit"),
									NULL,
									WS_CHILD | WS_VISIBLE | WS_HSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL | WS_TABSTOP,
									18 * cxChar,
									cyChar * 3,
									20 * cxChar,
									21 * cyChar/5,
									hwnd,
									(HMENU) ID_EDIT_ADDRESS,
									((LPCREATESTRUCT) lParam) -> hInstance,
									NULL
								);
					
		//Email
				h = CreateWindow (
						TEXT ("static"),
						NULL,
											WS_CHILD | WS_VISIBLE | ES_LEFT ,
											42 * cxChar,
						cyChar * 3,
						16 * cxChar,
						 7 * cyChar / 5,
						hwnd,
						(HMENU) -1,
						((LPCREATESTRUCT) lParam) -> hInstance,
						NULL
					);
				SendMessage(h, WM_SETTEXT, 0, (LPARAM) TEXT("Email Id"));
				
				hwndTextEmail   = CreateWindow(
									TEXT("edit"),
									NULL,
									WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,
									60 * cxChar,
									cyChar * 3,
									20 * cxChar,
									 7 * cyChar / 5,
									hwnd,
									(HMENU) ID_EDIT_EMAIL,
									((LPCREATESTRUCT) lParam) -> hInstance,
									NULL
								);

	
		//mobile
				h = CreateWindow (
						TEXT ("static"),
						NULL,
											WS_CHILD | WS_VISIBLE | ES_LEFT,
											cxChar,
						cyChar * 9,
						16 * cxChar,
						 7 * cyChar / 5,
						hwnd,
						(HMENU) -1,
						((LPCREATESTRUCT) lParam) -> hInstance,
						NULL
					);
				SendMessage(h, WM_SETTEXT, 0, (LPARAM) TEXT("Mobile Number"));
				
				hwndTextMobile  = CreateWindow(
									TEXT("edit"),
									NULL,
									WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL | ES_NUMBER,
									18 * cxChar,
									cyChar * 9,
									20 * cxChar,
									 7 * cyChar / 5,
									hwnd,
									(HMENU) ID_EDIT_MOBILE,
									((LPCREATESTRUCT) lParam) -> hInstance,
									NULL
								);

	
		//gender
				h = CreateWindow (
						TEXT ("static"),
						NULL,
						WS_CHILD | WS_VISIBLE | ES_LEFT ,
						cxChar,
						cyChar * 12,
						16 * cxChar,
						 7 * cyChar / 5,
						hwnd,
						(HMENU) -1,
						((LPCREATESTRUCT) lParam) -> hInstance,
						NULL
					);
				SendMessage(h, WM_SETTEXT, 0, (LPARAM) TEXT("Gender"));
			//male gender
				hwndRadioButtonMale = CreateWindow(
										TEXT("button"),
										TEXT("Male"),
										WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
										20 * cxChar,
										cyChar * 12,
										10 * cxChar,
										 7 * cyChar / 5,
										hwnd,
										(HMENU) ID_RADIOBUTTON_MALE,
										((LPCREATESTRUCT) lParam) -> hInstance,
										NULL
									);
									
						//Set male selection by default
							SendMessage(hwndRadioButtonMale, BM_SETCHECK, 1, 0);
				
			//female gender
				hwndRadioButtonFemale = CreateWindow(
											TEXT("button"),
											TEXT("Female"),
											WS_CHILD | WS_VISIBLE | BS_RADIOBUTTON,
											32 * cxChar,
											cyChar * 12,
											10 * cxChar,
											 7 * cyChar / 5,
											hwnd,
											(HMENU) ID_RADIOBUTTON_FEMALE,
											((LPCREATESTRUCT) lParam) -> hInstance,
											NULL
										);
				

		//DOB
					h = CreateWindow (
						TEXT ("static"),
						NULL,
											WS_CHILD | WS_VISIBLE | ES_LEFT ,
											cxChar,
						cyChar * 15,
						16 * cxChar,
						 7 * cyChar / 5,
						hwnd,
						(HMENU) -1,
						((LPCREATESTRUCT) lParam) -> hInstance,
						NULL
					);
					SendMessage(h, WM_SETTEXT, 0, (LPARAM) TEXT("Date Of Birth"));
				/*******************************************************
				 * YEAR OF BIRTH
				 *******************************************************/	
					//YEAR
						//static
						hwndStaticYearDOB = CreateWindow(TEXT("static"),
											NULL,
											WS_CHILD | WS_VISIBLE | SS_LEFT,
											20*cxChar,
											cyChar * 15,
											8 * cxChar,
											cyChar,
											hwnd,
											(HMENU) ID_STATIC_YEAR_DOB,
											((LPCREATESTRUCT) lParam) -> hInstance,// OR (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),
											NULL
									);
									
						//btn
						hwndButtonYearDOB = CreateWindow( 
						 /* Class  Name     */      TEXT("button"),  //This is predefined name
						 /* Window text     */      TEXT("V"),
						 /* Window Style    */      WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
						 /* x Position      */      28 * cxChar,
						 /* y Position      */      cyChar * 15,
						 /* Width           */      3 * cxChar,
						 /* Height          */      cyChar,  //push button looks best when it's height is 7/4 times the height of a text charachter.
						 /* Parent window   */      hwnd,
						 /* Child window ID */      (HMENU) ID_BUTTON_YEAR_DOB,
						 /* Instance Handle */      ((LPCREATESTRUCT) lParam)->hInstance,
						 /* Extra Prameters */      NULL
							);

						//list
						hwndListYearOfDOB = CreateWindow(
												TEXT("listbox"),
												TEXT(""),
												WS_CHILD | WS_VISIBLE | LBS_STANDARD | WS_CLIPSIBLINGS,
												20*cxChar,
												cyChar * 16,
												11 * cxChar,
												7 * cyChar,
												hwnd,
												(HMENU) ID_LIST_YEAR_DOB,
												((LPCREATESTRUCT) lParam) -> hInstance,
												NULL										
											);
						
						//Insert string in list box
							SendMessage(hwndListYearOfDOB, LB_INSERTSTRING, 0, (LPARAM) TEXT("<YEAR>"));
							for(short i = 1950 ; i <= 2019; i++)
							{
								TCHAR str[5];
								wsprintf(str, TEXT("%d"), i);
								SendMessage(hwndListYearOfDOB, LB_INSERTSTRING, (i - 1949), (LPARAM) str);
							}
						
						//SET SELECTION TO 0
						//WPARAM ==> index
							AMC_SetIndex(hwndListYearOfDOB, hwndStaticYearDOB, 0);
							// SendMessage(hwndListYearOfDOB, LB_SETCURSEL, (WPARAM)0, (LPARAM) 0);
							// SendMessage(hwndStaticYearDOB, WM_SETTEXT, (WPARAM)0, (LPARAM) TEXT("<YEAR>"));
						
						//Hide list box
						ShowWindow(hwndListYearOfDOB, SW_HIDE);
						
						yearFlagDOB = 0;
					
					/*******************************************************
					 * MONTH OF BIRTH
					 *******************************************************/
				//Month
						hwndStaticMonthDOB = CreateWindow(TEXT("static"),
											NULL,
											WS_CHILD | WS_VISIBLE | SS_LEFT,
											33 * cxChar,
											cyChar * 15,
											8 * cxChar,
											cyChar,
											hwnd,
											(HMENU) ID_STATIC_MONTH_DOB,
											((LPCREATESTRUCT) lParam) -> hInstance,// OR (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),
											NULL
									);
									
						//btn
						hwndButtonMonthDOB = CreateWindow( 
						 /* Class  Name     */      TEXT("button"),  //This is predefined name
						 /* Window text     */      TEXT("V"),
						 /* Window Style    */      WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
						 /* x Position      */      41 * cxChar,
						 /* y Position      */      cyChar * 15,
						 /* Width           */      3 * cxChar,
						 /* Height          */      cyChar,  //push button looks best when it's height is 7/4 times the height of a text charachter.
						 /* Parent window   */      hwnd,
						 /* Child window ID */      (HMENU) ID_BUTTON_MONTH_DOB,
						 /* Instance Handle */      ((LPCREATESTRUCT) lParam)->hInstance,
						 /* Extra Prameters */      NULL
							);

						//list
						hwndListMonthOfDOB = CreateWindow(
												TEXT("listbox"),
												TEXT(""),
												WS_CHILD | WS_VISIBLE | LBS_STANDARD | WS_CLIPSIBLINGS,
												33 * cxChar,
												cyChar * 16,
												11 * cxChar,
												7 * cyChar,
												hwnd,
												(HMENU) ID_LIST_MONTH_DOB,
												((LPCREATESTRUCT) lParam) -> hInstance,
												NULL										
											);
						
						//Insert string in list box
							SendMessage(hwndListMonthOfDOB, LB_INSERTSTRING, NONE      , (LPARAM) "<MONTH>");
							SendMessage(hwndListMonthOfDOB, LB_INSERTSTRING, JANUARY   , (LPARAM) "Jan");
							SendMessage(hwndListMonthOfDOB, LB_INSERTSTRING, FEBRUARY  , (LPARAM) "Feb");
							SendMessage(hwndListMonthOfDOB, LB_INSERTSTRING, MARCH     , (LPARAM) "Mar");
							SendMessage(hwndListMonthOfDOB, LB_INSERTSTRING, APRIL     , (LPARAM) "Apr");
							SendMessage(hwndListMonthOfDOB, LB_INSERTSTRING, MAY       , (LPARAM) "May");
							SendMessage(hwndListMonthOfDOB, LB_INSERTSTRING, JUNE      , (LPARAM) "Jun");
							SendMessage(hwndListMonthOfDOB, LB_INSERTSTRING, JULY      , (LPARAM) "Jul");
							SendMessage(hwndListMonthOfDOB, LB_INSERTSTRING, AUGUST    , (LPARAM) "Aug");
							SendMessage(hwndListMonthOfDOB, LB_INSERTSTRING, SEPTEMBER , (LPARAM) "Sept");
							SendMessage(hwndListMonthOfDOB, LB_INSERTSTRING, OCTOMBER  , (LPARAM) "Oct");
							SendMessage(hwndListMonthOfDOB, LB_INSERTSTRING, NOVEMBER  , (LPARAM) "Nov");
							SendMessage(hwndListMonthOfDOB, LB_INSERTSTRING, DECEMBER  , (LPARAM) "Dec");
						
						//hide list
						ShowWindow(hwndListMonthOfDOB, SW_HIDE);
						//Disable button
						 EnableWindow(hwndButtonMonthDOB, FALSE);
						monthFlagDOB = 0;
						
				
					/*******************************************************
					 * DAY OF BIRTH
					 *******************************************************/
				
				//DAY
						//static
						hwndStaticDayDOB = CreateWindow(TEXT("static"),
											NULL,
											WS_CHILD | WS_VISIBLE | SS_LEFT,
											46 * cxChar,
											cyChar * 15,
											8 * cxChar,
											cyChar,
											hwnd,
											(HMENU) ID_STATIC_DAYOFWEEK_DOB,
											((LPCREATESTRUCT) lParam) -> hInstance,// OR (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),
											NULL
									);
									
						//btn
						hwndButtonDayDOB = CreateWindow( 
						 /* Class  Name     */      TEXT("button"),  //This is predefined name
						 /* Window text     */      TEXT("V"),
						 /* Window Style    */      WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
						 /* x Position      */      54 * cxChar,
						 /* y Position      */      cyChar * 15,
						 /* Width           */      3 * cxChar,
						 /* Height          */      cyChar,  //push button looks best when it's height is 7/4 times the height of a text charachter.
						 /* Parent window   */      hwnd,
						 /* Child window ID */      (HMENU) ID_BUTTON_DAYOFWEEK_DOB,
						 /* Instance Handle */      ((LPCREATESTRUCT) lParam)->hInstance,
						 /* Extra Prameters */      NULL
							);
						
						//list
						hwndListDayOfDOB = CreateWindow(
												TEXT("listbox"),
												TEXT(""),
												WS_CHILD | WS_VISIBLE | LBS_STANDARD | WS_CLIPSIBLINGS,
												46 * cxChar,
												cyChar * 16,
												11 * cxChar,
												7 * cyChar,
												hwnd,
												(HMENU) ID_LIST_DAYOFWEEK_DOB,
												((LPCREATESTRUCT) lParam) -> hInstance,
												NULL										
											);
						
						ShowWindow(hwndListDayOfDOB, SW_HIDE);
						
						//Disable button
						 EnableWindow(hwndButtonDayDOB, FALSE);
						
						dayFlagDOB = 0;
					
						// SendMessage(hwndListDayOfDOB, LB_ADDSTRING, 0, (LPARAM) "Vikas1");
						// SendMessage(hwndListDayOfDOB, LB_ADDSTRING, 1, (LPARAM) "Vikas2");
						// SendMessage(hwndListDayOfDOB, LB_ADDSTRING, 2, (LPARAM) "Vikas3");
					

	/*******************************************************
	 * DATE OF JOINING
	 *******************************************************/				
				//JOINING
					h = CreateWindow (
						TEXT ("static"),
						NULL,
											WS_CHILD | WS_VISIBLE | ES_LEFT ,
											cxChar,
						cyChar * 18,
						16 * cxChar,
						 7 * cyChar / 5,
						hwnd,
						(HMENU) -1,
						((LPCREATESTRUCT) lParam) -> hInstance,
						NULL
					);
					SendMessage(h, WM_SETTEXT, 0, (LPARAM) TEXT("Date Of Joining"));
					
					/*******************************************************
					 * YEAR OF JOINING
					 *******************************************************/
					//YEAR
						//static
						hwndStaticYearJoining = CreateWindow(TEXT("static"),
											NULL,
											WS_CHILD | WS_VISIBLE | SS_LEFT,
											20*cxChar,
											cyChar * 18,
											8 * cxChar,
											cyChar,
											hwnd,
											(HMENU) ID_STATIC_YEAR_JOINING,
											((LPCREATESTRUCT) lParam) -> hInstance,// OR (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),
											NULL
									);
									
						//btn
						hwndButtonYearJoining = CreateWindow( 
						 /* Class  Name     */      TEXT("button"),  //This is predefined name
						 /* Window text     */      TEXT("V"),
						 /* Window Style    */      WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
						 /* x Position      */      28 * cxChar,
						 /* y Position      */      cyChar * 18,
						 /* Width           */      3 * cxChar,
						 /* Height          */      cyChar,  //push button looks best when it's height is 7/4 times the height of a text charachter.
						 /* Parent window   */      hwnd,
						 /* Child window ID */      (HMENU) ID_BUTTON_YEAR_JOINING,
						 /* Instance Handle */      ((LPCREATESTRUCT) lParam)->hInstance,
						 /* Extra Prameters */      NULL
							);

						//list
						hwndListYearOfJoining = CreateWindow(
													TEXT("listbox"),
													TEXT(""),
													WS_CHILD | WS_VISIBLE | LBS_STANDARD | WS_CLIPSIBLINGS,
													20*cxChar,
													cyChar * 19,
													11 * cxChar,
													7 * cyChar,
													hwnd,
													(HMENU) ID_LIST_YEAR_JOINING,
													((LPCREATESTRUCT) lParam) -> hInstance,
													NULL										
												);
						
							//Insert string in list box
								SendMessage(hwndListYearOfJoining, LB_INSERTSTRING, 0, (LPARAM) TEXT("<YEAR>"));
								for(short i = 1950 ; i <= 2019; i++)
								{
									TCHAR str[5];
									wsprintf(str, TEXT("%d"), i);
									SendMessage(hwndListYearOfJoining, LB_INSERTSTRING, (i - 1949), (LPARAM) str);
								}
								
							//SET SELECTION TO 0
							//WPARAM ==> index
								AMC_SetIndex(hwndListYearOfJoining, hwndStaticYearJoining, 0);
								// SendMessage(hwndListYearOfJoining, LB_SETCURSEL, (WPARAM)0, (LPARAM) 0);
								// SendMessage(hwndStaticYearJoining, WM_SETTEXT, (WPARAM)0, (LPARAM) TEXT("<YEAR>"));
						
						ShowWindow(hwndListYearOfJoining, SW_HIDE);					
						
						yearFlagJoining = 0;
					
					/*******************************************************
					 * MONTH OF JOINING
					 *******************************************************/
					//Month
						//static
						hwndStaticMonthJoining = CreateWindow(TEXT("static"),
											NULL,
											WS_CHILD | WS_VISIBLE | SS_LEFT,
											33 * cxChar,
											cyChar * 18,
											8 * cxChar,
											cyChar,
											hwnd,
											(HMENU) ID_STATIC_MONTH_JOINING,
											((LPCREATESTRUCT) lParam) -> hInstance,// OR (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),
											NULL
									);
									
						//btn
						hwndButtonMonthJoining = CreateWindow( 
						 /* Class  Name     */      TEXT("button"),  //This is predefined name
						 /* Window text     */      TEXT("V"),
						 /* Window Style    */      WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
						 /* x Position      */      41 * cxChar,
						 /* y Position      */      cyChar * 18,
						 /* Width           */      3 * cxChar,
						 /* Height          */      cyChar,  //push button looks best when it's height is 7/4 times the height of a text charachter.
						 /* Parent window   */      hwnd,
						 /* Child window ID */      (HMENU) ID_BUTTON_MONTH_JOINING,
						 /* Instance Handle */      ((LPCREATESTRUCT) lParam)->hInstance,
						 /* Extra Prameters */      NULL
							);

						//list
						hwndListMonthOfJoining = CreateWindow(
												TEXT("listbox"),
												TEXT(""),
												WS_CHILD | WS_VISIBLE | LBS_STANDARD | WS_CLIPSIBLINGS,
												33 * cxChar,
												cyChar * 19,
												11 * cxChar,
												7 * cyChar,
												hwnd,
												(HMENU) ID_LIST_MONTH_JOINING,
												((LPCREATESTRUCT) lParam) -> hInstance,
												NULL										
											);
						
						//Insert string in list box
							SendMessage(hwndListMonthOfJoining, LB_INSERTSTRING, NONE      , (LPARAM) "<MONTH>");
							SendMessage(hwndListMonthOfJoining, LB_INSERTSTRING, JANUARY   , (LPARAM) "Jan");
							SendMessage(hwndListMonthOfJoining, LB_INSERTSTRING, FEBRUARY  , (LPARAM) "Feb");
							SendMessage(hwndListMonthOfJoining, LB_INSERTSTRING, MARCH     , (LPARAM) "Mar");
							SendMessage(hwndListMonthOfJoining, LB_INSERTSTRING, APRIL     , (LPARAM) "Apr");
							SendMessage(hwndListMonthOfJoining, LB_INSERTSTRING, MAY       , (LPARAM) "May");
							SendMessage(hwndListMonthOfJoining, LB_INSERTSTRING, JUNE      , (LPARAM) "Jun");
							SendMessage(hwndListMonthOfJoining, LB_INSERTSTRING, JULY      , (LPARAM) "Jul");
							SendMessage(hwndListMonthOfJoining, LB_INSERTSTRING, AUGUST    , (LPARAM) "Aug");
							SendMessage(hwndListMonthOfJoining, LB_INSERTSTRING, SEPTEMBER , (LPARAM) "Sept");
							SendMessage(hwndListMonthOfJoining, LB_INSERTSTRING, OCTOMBER  , (LPARAM) "Oct");
							SendMessage(hwndListMonthOfJoining, LB_INSERTSTRING, NOVEMBER  , (LPARAM) "Nov");
							SendMessage(hwndListMonthOfJoining, LB_INSERTSTRING, DECEMBER  , (LPARAM) "Dec");
						
						ShowWindow(hwndListMonthOfJoining, SW_HIDE);
						//Disable button
						 EnableWindow(hwndButtonMonthJoining, FALSE);
						
						monthFlagJoining = 0;
						
				/*******************************************************
				 * DAY OF JOINING
				 *******************************************************/
					//DAY
						//static
						hwndStaticDayJoining = CreateWindow(TEXT("static"),
											NULL,
											WS_CHILD | WS_VISIBLE | SS_LEFT,
											46 * cxChar,
											cyChar * 18,
											8 * cxChar,
											cyChar,
											hwnd,
											(HMENU) ID_STATIC_DAYOFWEEK_JOINING,
											((LPCREATESTRUCT) lParam) -> hInstance,// OR (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE),
											NULL
									);
									
						//btn
						hwndButtonDayJoining = CreateWindow( 
						 /* Class  Name     */      TEXT("button"),  //This is predefined name
						 /* Window text     */      TEXT("V"),
						 /* Window Style    */      WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
						 /* x Position      */      54 * cxChar,
						 /* y Position      */      cyChar * 18,
						 /* Width           */      3 * cxChar,
						 /* Height          */      cyChar,  //push button looks best when it's height is 7/4 times the height of a text charachter.
						 /* Parent window   */      hwnd,
						 /* Child window ID */      (HMENU) ID_BUTTON_DAYOFWEEK_JOINING,
						 /* Instance Handle */      ((LPCREATESTRUCT) lParam)->hInstance,
						 /* Extra Prameters */      NULL
							);
							
						//list
						hwndListDayOfJoining = CreateWindow(
												TEXT("listbox"),
												TEXT(""),
												WS_CHILD | WS_VISIBLE | LBS_STANDARD | WS_CLIPSIBLINGS,
												46 * cxChar,
												cyChar *19,
												11 * cxChar,
												7 * cyChar,
												hwnd,
												(HMENU) ID_LIST_DAYOFWEEK_JOINING,
												((LPCREATESTRUCT) lParam) -> hInstance,
												NULL										
											);
							
						
						
						ShowWindow(hwndListDayOfJoining, SW_HIDE);
						//Disable button
						 EnableWindow(hwndButtonDayJoining, FALSE);
							
						dayFlagJoining = 0;
					
						// SendMessage(hwndListDayOfDOB, LB_ADDSTRING, 0, (LPARAM) "Vikas1");
						// SendMessage(hwndListDayOfDOB, LB_ADDSTRING, 1, (LPARAM) "Vikas2");
						// SendMessage(hwndListDayOfDOB, LB_ADDSTRING, 2, (LPARAM) "Vikas3");

	/*******************************************************
	 * DEPARTMENT
	 *******************************************************/					
				//DEPARTMENT
					h = CreateWindow (
						TEXT ("static"),
						NULL,
						WS_CHILD | WS_VISIBLE | ES_LEFT ,
						cxChar,
						cyChar * 21,
						16 * cxChar,
						 7 * cyChar / 5,
						hwnd,
						(HMENU) -1,
						((LPCREATESTRUCT) lParam) -> hInstance,
						NULL
					);
					SendMessage(h, WM_SETTEXT, 0, (LPARAM) TEXT("Department"));
					//static
					hwndStaticDepartment = CreateWindow(TEXT("static"),
										NULL,
										WS_CHILD | WS_VISIBLE | SS_LEFT,
										20*cxChar,
										cyChar * 21,
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
					 /* x Position      */      38 * cxChar,
						 /* y Position      */    cyChar * 21,
					 /* Width           */      5 * cxChar,
					 /* Height          */      cyChar * 1.3,  //push button looks best when it's height is 7/4 times the height of a text charachter.
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
											20*cxChar,
											cyChar * 22.3,
											23 * cxChar,
											6 * cyChar,
											hwnd,
											(HMENU) ID_LIST_DEPARTMENT,
											((LPCREATESTRUCT) lParam) -> hInstance,
											NULL										
										);
					
							SendMessage(hwndListDepartment, LB_INSERTSTRING,  0, (LPARAM) "<DEPARTMENt>");
							SendMessage(hwndListDepartment, LB_INSERTSTRING,  1, (LPARAM) Department_WM_CREATE);
							SendMessage(hwndListDepartment, LB_INSERTSTRING,  2, (LPARAM) Department_WM_LBUTTONDOWN);
							SendMessage(hwndListDepartment, LB_INSERTSTRING,  3, (LPARAM) Department_WM_SIZE);
							SendMessage(hwndListDepartment, LB_INSERTSTRING,  4, (LPARAM) Department_WM_KEYUP);
							SendMessage(hwndListDepartment, LB_INSERTSTRING,  5, (LPARAM) Department_WM_KEYDOWN);
							SendMessage(hwndListDepartment, LB_INSERTSTRING,  6, (LPARAM) Department_WM_COMMAND);
							SendMessage(hwndListDepartment, LB_INSERTSTRING,  7, (LPARAM) Department_WM_DRAWITEM);
							SendMessage(hwndListDepartment, LB_INSERTSTRING,  8, (LPARAM) Department_WM_PAINT);
							SendMessage(hwndListDepartment, LB_INSERTSTRING,  9, (LPARAM) Department_WM_CHAR);
							SendMessage(hwndListDepartment, LB_INSERTSTRING, 10, (LPARAM) Department_WM_DESTROY);
							SendMessage(hwndListDepartment, LB_INSERTSTRING, 11, (LPARAM) Department_WM_SETFOCUS);
							SendMessage(hwndListDepartment, LB_INSERTSTRING, 12, (LPARAM) Department_WM_ENABLE);
							SendMessage(hwndListDepartment, LB_INSERTSTRING, 13, (LPARAM) Department_WM_MOUSEMOVE);
							SendMessage(hwndListDepartment, LB_INSERTSTRING, 14, (LPARAM) Department_WM_RBUTTONDOWN);
					// for(short i = 1 ; i <= 31; i++)
					// {
						// SendMessage(hwndListDepartment, LB_ADDSTRING, i - 1, (LPARAM) i);
					// }
						
					ShowWindow(hwndListDepartment, SW_HIDE);
						
					
					flagDepartment = 0;
			
	/*******************************************************
	 * EMPLOYEE ID
	 *******************************************************/		
				// //employee ID
				// h = CreateWindow (
						// TEXT ("static"),
						// NULL,
						// WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT ,
						// cxChar,
						// cyChar * 24,
						// 16 * cxChar,
						 // 7 * cyChar / 5,
						// hwnd,
						// (HMENU) -1,
						// ((LPCREATESTRUCT) lParam) -> hInstance,
						// NULL
					// );
				// SendMessage(h, WM_SETTEXT, 0, (LPARAM) TEXT("Employee ID"));
				
				// // hwndTextEmployeeID  = CreateWindow(
									// // TEXT("edit"),
									// // NULL,
									// // WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL | ES_NUMBER,
									// // 20 * cxChar,
									// // cyChar * 24,
									// // 15 * cxChar,
									 // // 7 * cyChar / 5,
									// // hwnd,
									// // (HMENU) ID_EDIT_EMPLOYEE_ID,
									// // ((LPCREATESTRUCT) lParam) -> hInstance,
									// // NULL
								// // );
								
								
	/*******************************************************
	 * OK BUTTON
	 *******************************************************/		
				hwndOkButton = CreateWindow(
									TEXT("button"),
									TEXT("OK"),
									WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW | WS_BORDER,
									30 * cxChar,
									cyChar * 25,
									15 * cxChar,
									cyChar * 2,
									hwnd,
									(HMENU) ID_BUTTON_OK,
									((LPCREATESTRUCT) lParam)->hInstance,
									NULL
								);
	/*******************************************************
	 * RESET BUTTON
	 *******************************************************/									
				hwndResetButton = CreateWindow(
									TEXT("button"),
									TEXT("RESET"),
									WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW | WS_BORDER,
									55 * cxChar,
									cyChar * 25,
									15 * cxChar,
									cyChar * 2,
									hwnd,
									(HMENU) ID_BUTTON_RESET,
									((LPCREATESTRUCT) lParam)->hInstance,
									NULL
								);
				
								
				focusHandle = hwndTextFirstName;
				// SetFocus(focusHandle);
				
						
				
				return(0);
			}
			
		
		/***************** WM_SETFOCUS **************/
		case WM_SETFOCUS:
			{
					firstNameTextFocused         = false;
					lastNameTextFocused          = false;
					addressTextFocused           = false;
					emailTextFocused             = false;
					mobileTextFocused            = false;
					
					male_RadioButton_Focused     = false;
					female_RadioButton_Focused   = false;
					
					year_DOB_Button_Focused      = false;
					month_DOB_Button_Focused     = false;
					day_DOB_Button_Focused       = false;
					
					year_Joining_Button_Focused  = false;
					month_Joining_Button_Focused = false;
					day_Joining_Button_Focused   = false;
					
					departmentButtonFocused      = false;
					okButtonFocused              = false;
					resetButtonFocused           = false;
					
					
					if(focusHandle == hwndTextFirstName)
					{
						focusHandle         = hwndTextLastName;
						lastNameTextFocused = true;
					}
					else if(focusHandle == hwndTextLastName)
					{
						focusHandle         = hwndTextAddress;
						addressTextFocused  = true;
					}
					else if(focusHandle == hwndTextAddress)
					{
						focusHandle         = hwndTextEmail;
						emailTextFocused    = true;
					}
					else if(focusHandle == hwndTextEmail)
					{
						focusHandle         = hwndTextMobile;
						mobileTextFocused   = true;
					}
					else if(focusHandle == hwndTextMobile)
					{
						focusHandle              = hwndRadioButtonMale;
						male_RadioButton_Focused = true;
					}
					else if(focusHandle == hwndRadioButtonMale)
					{
						focusHandle                = hwndRadioButtonFemale;
						female_RadioButton_Focused = true;
					}
					else if(focusHandle == hwndRadioButtonFemale)
					{
						focusHandle             = hwndButtonYearDOB;
						year_DOB_Button_Focused = true;
					}
					else if(focusHandle == hwndButtonYearDOB)
					{
						if(IsWindowEnabled(hwndButtonMonthDOB))
						{
							focusHandle              = hwndButtonMonthDOB;
							month_DOB_Button_Focused = true;
						}
						else
						{
							focusHandle                 = hwndButtonYearJoining;
							year_Joining_Button_Focused = true;
						}
					}
					else if(focusHandle == hwndButtonMonthDOB)
					{
						if(IsWindowEnabled(hwndButtonDayDOB))
						{
							focusHandle            = hwndButtonDayDOB;
							day_DOB_Button_Focused = true;
						}
						else
						{
							focusHandle                 = hwndButtonYearJoining;
							year_Joining_Button_Focused = true;
						}
					}
					else if(focusHandle == hwndButtonDayDOB)
					{
						focusHandle                 = hwndButtonYearJoining;
						year_Joining_Button_Focused = true;
					}
					
					else if(focusHandle == hwndButtonYearJoining)
					{
						if(IsWindowEnabled(hwndButtonMonthJoining))
						{
							focusHandle                  = hwndButtonMonthJoining;
							month_Joining_Button_Focused = true;
						}
						else
						{
							focusHandle             = hwndButtonDepartment;
							departmentButtonFocused = true;
						}
					}
					else if(focusHandle == hwndButtonMonthJoining)
					{
						if(IsWindowEnabled(hwndButtonDayJoining))
						{
							focusHandle                = hwndButtonDayJoining;
							day_Joining_Button_Focused = true;
						}
						else
						{
							focusHandle             = hwndButtonDepartment;
							departmentButtonFocused = true;
						}
					}
					else if(focusHandle == hwndButtonDayJoining)
					{
						focusHandle             = hwndButtonDepartment;
						departmentButtonFocused = true;
					}
					
					else if(focusHandle == hwndButtonDepartment)
					{
						focusHandle     = hwndOkButton;
						okButtonFocused = true;
					}
					else if(focusHandle == hwndOkButton)
					{
						focusHandle        = hwndResetButton;
						resetButtonFocused = true;
					}
					else if(focusHandle == hwndResetButton)
					{
						focusHandle          = hwndTextFirstName;
						firstNameTextFocused = true;
					}
					SetFocus(focusHandle);
					break;
			}
			
		
		// case WM_MOUSEMOVE:
		  // {
				// int x = LOWORD(lParam);
				// int y = HIWORD(lParam);
				// if( x > 55*cxChar-2 && x < (55*cxChar + 15*cxChar)+2)
				// {
					// if(y > cyChar*25 -2 && y < (cyChar*25 + cyChar*2)+2)
					// {
						// // hdc = BeginPaint(hwndResetButton, &ps);
						// // // SetTextColor(hdc, RGB(0, 0, 0));
						// // // EndPaint(hwndResetButton, &ps);
						// // flag = 1;
						// // SendMessage(hwnd, WM_CTLCOLORBTN, (WPARAM) hdc, (LPARAM) hwndResetButton);
					// }
				// }
				// break;
			// }
			
						/*
				WM_CTLCOLORBTN
				WM_CTLCOLOREDIT
				WM_CTLCOLORDLG
				WM_CTLCOLORLISTBOX
				WM_CTLCOLORSCROLLBAR
				WM_CTLCOLORSTATIC
						*/

			/***************** WM_DRAWITEM **************/					
		case WM_DRAWITEM:
			{
				DRAWITEMSTRUCT* dis = (DRAWITEMSTRUCT*) lParam;
				if(dis->CtlID == ID_BUTTON_OK || dis->CtlID == ID_BUTTON_RESET)
				{
					//MessageBox(hwnd, TEXT("M"), TEXT("M"), MB_OK);
					GetClientRect(dis->hwndItem, &rc);
					SetBkColor(dis->hDC,RGB(255, 255, 255));
					SetTextColor(dis->hDC, RGB(255, 215, 0));
					
					if(dis->CtlID == ID_BUTTON_OK )
						wsprintf(text, TEXT("OK"));
						 
					else
						wsprintf(text, TEXT("RESET"));
				
					DrawText(dis->hDC, text,-1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					
					
					return((LRESULT) CreateSolidBrush(RGB(255, 255, 255)));
				}
				break;
			}
		
		 /***************** WM_CTLCOLORBTN **************/
		case WM_CTLCOLORBTN:
			{
				focusHandle = (HWND)lParam;
				{	
					if((HWND)lParam == hwndOkButton || (HWND)lParam == hwndResetButton)
					{
						//MessageBox(hwnd, TEXT("BTN"), TEXT("BTN"), MB_OK);
						COLORREF back = RGB(255, 255, 255);
						hdc = (HDC)wParam;
						HWND h = (HWND) lParam;
						GetClientRect(h, &rc);
						SetBkColor((HDC) wParam, back);
						SetTextColor((HDC)wParam, RGB(255, 215, 0));
						
						if((HWND)lParam == hwndOkButton)
							wsprintf(text, TEXT("OK"));
						else
							wsprintf(text,TEXT("RESET"));
					
						DrawText(hdc, text,-1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					
						return((LRESULT) CreateSolidBrush(back));
					}
				}
				break;
			}
		
		/***************** WM_CTLCOLORSTATIC **************/
		case WM_CTLCOLORSTATIC:
			{
				if((HWND)lParam != hwndStaticDepartment   &&
					 (HWND)lParam != hwndStaticDayDOB       &&
					 (HWND)lParam != hwndStaticMonthDOB     &&
					 (HWND)lParam != hwndStaticYearDOB      &&
					 (HWND)lParam != hwndStaticDayJoining   &&
					 (HWND)lParam != hwndStaticMonthJoining &&
					 (HWND)lParam != hwndStaticYearJoining
				)
				{
					SetTextColor((HDC)wParam, RGB(255, 255, 255));
					SetBkColor((HDC)wParam, RGB(37, 172, 168));
					return((INT_PTR)CreateSolidBrush(RGB(37, 172, 168)));
				}
				else
				{
					SetBkColor((HDC)wParam, RGB(255, 255, 255));
					return((INT_PTR)CreateSolidBrush(RGB(255, 255, 255)));
				}
				break;
			}		
		
		/**************** WM_CTLCOLOREDIT ****************/
		case WM_CTLCOLOREDIT:
			{
				focusHandle = (HWND)lParam;
				// if((HWND)lParam == hwndTextLastName)
				// {
					// if(setFlag)
					// {
						// // SetTextColor((HDC) wParam, RGB(255, 173, 58));
						// // SetBkColor((HDC) wParam, RGB(189, 215, 224));
						// GetClientRect((HWND)lParam, &rc);
						// SelectObject((HDC) wParam, GetStockObject(DC_PEN));
						// SetDCPenColor((HDC) wParam, RGB(255, 0, 0));
						// // Rectangle((HDC) wParam, rc.left+2, rc.top+3, rc.left+3, rc.bottom-3);
						// POINT p;
						// MoveToEx((HDC)wParam, rc.left, rc.top+2, &p);
						// LineTo((HDC)wParam, rc.right, rc.bottom-1);
						// return (INT_PTR)CreateSolidBrush(RGB(255, 255, 255));
					// }
					// else
					// {
						// // SetTextColor((HDC) wParam, RGB(189, 215, 224));
						// // SetBkColor((HDC) wParam, RGB(255, 173, 58));
						// // return (INT_PTR)CreateSolidBrush(RGB(255, 173, 58));
						// GetClientRect((HWND)lParam, &rc);
						// SelectObject((HDC) wParam, GetStockObject(DC_PEN));
						// SetDCPenColor((HDC) wParam, RGB(255, 0, 0));
						// Rectangle((HDC) wParam, rc.left+2, rc.top+3, rc.right-10, rc.bottom-3);
						// return (INT_PTR)CreateSolidBrush(RGB(255, 255, 255));
					// }
				// }
				
				/*******************************************/
				// if((HWND)lParam == hwndTextFirstName)
				// {
					// if(firstNameTextFocused)
					// {
						// // GetClientRect((HWND) lParam, &rc);
						// // //SelectObject((HDC)wParam, GetStockObject(DC_PEN));
						// // SetDCPenColor((HDC) wParam, RGB(0, 0, 255));
						// // POINT p;
						// // MoveToEx((HDC)wParam, rc.left, rc.bottom-1, &p);
						// // LineTo((HDC)wParam, rc.right, rc.bottom-1);
						// // return((INT_PTR)CreateSolidBrush(RGB(255, 255, 255)));
					// }
					// else
					// {
						// // GetClientRect((HWND) lParam, &rc);
						// // TCHAR str[122];
						// // wsprintf(str, TEXT("Left : %d\nTop : %d\nRight : %d\nBottom : %d\n"), rc.left, rc.top, rc.right, rc.bottom);
						// // MessageBox(hwnd, str, TEXT("MSG"), MB_OK);
						// // SelectObject((HDC)wParam, GetStockObject(DC_PEN));
						// // SetDCPenColor((HDC) wParam, RGB(255, 0, 0));
						// // POINT p;
						// // // MoveToEx((HDC)wParam, rc.left, rc.bottom-1, &p);
						// // // LineTo((HDC)wParam, rc.right, rc.bottom-1);
						// // Rectangle((HDC) wParam, rc.left, rc.bottom-3, rc.right, rc.bottom-2);
						// // return((INT_PTR)CreateSolidBrush(RGB(255, 255, 255)));
					// }
				// }
				// else if((HWND) lParam == hwndTextLastName)
				// {
					// if(lastNameTextFocused){
						
					// }
					// else{}
				// }
				// else if((HWND) lParam == hwndTextAddress)
				// {
					// if(addressTextFocused){}
					// else{}
				// }
				// else if((HWND) lParam == hwndTextEmail)
				// {
					// if(emailTextFocused){}
					// else{}
				// }
				// else if((HWND) lParam == hwndTextMobile)
				// {
					// if(mobileTextFocused){}
					// else{}
				// }
				break;
			}
				
			
		/******************* WM_PAINT ******************/			
		case WM_PAINT:
		{
			POINT p;
			GetClientRect(hwnd, &rc);
			hdc = BeginPaint(hwnd, &ps);
			SelectObject(hdc, GetStockObject(DC_PEN));
			SetDCPenColor(hdc, RGB(0, 99, 177));
			
			MoveToEx(hdc, rc.left  + 1, rc.top    + 1    , &p);
			LineTo(hdc  , rc.left  + 1, rc.bottom - 1);
			LineTo(hdc  , rc.right - 1, rc.bottom - 1);
			LineTo(hdc  , rc.right - 1, rc.top    + 1);
			LineTo(hdc  , rc.left  + 1, rc.top    + 1);
			
			MoveToEx(hdc, rc.left  + 2, rc.top    + 2    , &p);
			LineTo(hdc  , rc.left  + 2, rc.bottom - 2);
			LineTo(hdc  , rc.right - 2, rc.bottom - 2);
			LineTo(hdc  , rc.right - 2, rc.top    + 2);
			LineTo(hdc  , rc.left  + 2, rc.top    + 2);
			
			MoveToEx(hdc, rc.left  + 3, rc.top    + 3    , &p);
			LineTo(hdc  , rc.left  + 3, rc.bottom - 3);
			LineTo(hdc  , rc.right - 3, rc.bottom - 3);
			LineTo(hdc  , rc.right - 3, rc.top    + 3);
			LineTo(hdc  , rc.left  + 3, rc.top    + 3);
			
			EndPaint(hwnd, &ps);
		}
		break;
	
		/******************* WM_COMMAND ******************/				
		case WM_COMMAND:
		{
/*******************************************************
 * ID_BUTTON_OK
 *******************************************************/
			if(LOWORD(wParam) == ID_BUTTON_OK)
			{
				char *firstName       = NULL;
				char *lastName        = NULL;
				char *address         = NULL;
				char *email_id        = NULL;
				char *mobile_no       = NULL;
				char *gender          = NULL;
				char *dayOfDOB        = NULL;
				char *monthOfDOB      = NULL;
				char *yearOfDOB       = NULL;
				char *dayOfJoining    = NULL;
				char *monthOfJoining  = NULL;
				char *yearOfJoining   = NULL;
				char *department      = NULL;

				char dateOfBirth[12];
				char dateOfJoining[12];
				
				AMC_GetText(hwndTextFirstName      , &firstName      );
				AMC_GetText(hwndTextLastName       , &lastName       );
				AMC_GetText(hwndTextAddress        , &address        );
				AMC_GetText(hwndTextEmail          , &email_id       );
				AMC_GetText(hwndTextMobile         , &mobile_no      );
				AMC_GetText(hwndStaticDayDOB       , &dayOfDOB       );
				AMC_GetText(hwndStaticMonthDOB     , &monthOfDOB     );
				AMC_GetText(hwndStaticYearDOB      , &yearOfDOB      );
				AMC_GetText(hwndStaticDayJoining   , &dayOfJoining   );
				AMC_GetText(hwndStaticMonthJoining , &monthOfJoining );
				AMC_GetText(hwndStaticYearJoining  , &yearOfJoining  );
				AMC_GetText(hwndStaticDepartment   , &department     );
				
				if(SendMessage(hwndRadioButtonFemale, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
				{
					AMC_GetText(hwndRadioButtonMale   , &gender);		
				}
				else
				{
					AMC_GetText(hwndRadioButtonFemale   , &gender);		
				}
				
				//validation
				if(
						firstName      == NULL ||
						lastName       == NULL ||
						address        == NULL ||
						email_id       == NULL ||
						mobile_no      == NULL ||
						dayOfDOB       == NULL ||
						monthOfDOB     == NULL ||
						yearOfDOB      == NULL ||
						dayOfJoining   == NULL ||
						monthOfJoining == NULL ||
						yearOfJoining  == NULL ||
						department     == NULL
					)
				{
					MessageBox(hwnd, TEXT("SOME FILLED ARE EMPTY"), TEXT("ERROR"), MB_ICONERROR);
					return(0);
				}
				
				TCHAR str[2048];
				// wsprintf(str,TEXT("FirstName       : %s\nLastName        : %s\nEmail_Id        : %s\nMobile_No       : %s\nGender          : %s\nAddress         : %s\nDataOfBirth     : %s-%s-%s\nDataOfJoining   : %s-%s-%s\nDepartment_Name : %s\n"),firstName, lastName, email_id, mobile_no, gender, address, dayOfDOB, monthOfDOB, yearOfDOB, dayOfJoining, monthOfJoining, yearOfJoining, department);
				// MessageBox(hwnd, str, TEXT("DATA"), MB_OK);
				
				sprintf(dateOfBirth  , "%s-%s-%s", dayOfDOB    , monthOfDOB    , yearOfDOB);
				sprintf(dateOfJoining, "%s-%s-%s", dayOfJoining, monthOfJoining, yearOfJoining);
				
				struct EmployeeDetails employee;
				strcpy(employee.firstName       , firstName);
				strcpy(employee.lastName        , lastName);
				strcpy(employee.email_id        , email_id);
				strcpy(employee.mobile_no       , mobile_no);
				strcpy(employee.gender          , gender);
				strcpy(employee.address         , address);
				strcpy(employee.dateOfBirth     , dateOfBirth);
				strcpy(employee.dateOfJoining   , dateOfJoining);
				strcpy(employee.department_name , department);
				
				employee.nextDetails = NULL;
				
				wsprintf(str,TEXT("FirstName       : %s\nLastName        : %s\nEmail_Id        : %s\nMobile_No       : %s\nGender          : %s\nAddress         : %s\nDataOfBirth     : %s\nDataOfJoining   : %s\nDepartment_Name : %s\n"),employee.firstName, employee.lastName, employee.email_id, employee.mobile_no, employee.gender, employee.address, employee.dateOfBirth, employee.dateOfJoining, employee.department_name);
				int sel = MessageBox(hwnd, str, TEXT("Confirm Data"), MB_OKCANCEL |  MB_ICONINFORMATION);
				
				if(sel == IDOK)
				{
					int len = 1;
					HRESULT hr = pIWriteRecord->WriteRecord(department, &employee, &len);
					if(FAILED(hr))
					{
						MessageBox(hwnd, TEXT("Error while writing..."), TEXT("ERROR"), MB_ICONERROR);
					}
					else
					{
						TCHAR str[127];
						wsprintf(str, TEXT("employee id : %s"), employee.employeeId);
						MessageBox(hwnd, str, TEXT("IDOK"), MB_OK);
						
						AMC_SetText(hwndTextFirstName      , "" );
						AMC_SetText(hwndTextLastName       , "" );
						AMC_SetText(hwndTextAddress        , "" );
						AMC_SetText(hwndTextEmail          , "" );
						AMC_SetText(hwndTextMobile         , "" );
						
						AMC_SetIndex(hwndListYearOfDOB     , hwndStaticYearDOB    , 0);
						
						AMC_SetIndex(hwndListMonthOfDOB    , hwndStaticMonthDOB    , 0);
						EnableWindow(hwndButtonMonthDOB    , FALSE);
						
						AMC_SetIndex(hwndListDayOfDOB      , hwndStaticDayDOB    , 0);
						EnableWindow(hwndButtonDayDOB      , FALSE);
						
						AMC_SetIndex(hwndListYearOfJoining , hwndStaticYearJoining, 0);
						
						AMC_SetIndex(hwndListMonthOfJoining, hwndStaticMonthJoining, 0);
						EnableWindow(hwndButtonMonthJoining, FALSE);
						
						AMC_SetIndex(hwndListDayOfJoining  , hwndStaticDayJoining, 0);
						EnableWindow(hwndButtonDayJoining  , FALSE);
						
						AMC_SetIndex(hwndListDepartment    , hwndStaticDepartment , 0);
					}
				}
				
				free(firstName);
				free(lastName);
				free(address);
				free(email_id);
				free(mobile_no);
				free(gender);
				free(dayOfDOB);
				free(monthOfDOB);
				free(yearOfDOB);
				free(dayOfJoining);
				free(monthOfJoining);
				free(yearOfJoining);
				free(department);
				
			}
			
/*******************************************************
 * ID_BUTTON_RESET
 *******************************************************/
		else if(LOWORD(wParam) == ID_BUTTON_RESET)
		{
			AMC_SetText(hwndTextFirstName      , "" );
			AMC_SetText(hwndTextLastName       , "" );
			AMC_SetText(hwndTextAddress        , "" );
			AMC_SetText(hwndTextEmail          , "" );
			AMC_SetText(hwndTextMobile         , "" );
			
			AMC_SetIndex(hwndListYearOfDOB     , hwndStaticYearDOB    , 0);
			
			AMC_SetIndex(hwndListMonthOfDOB    , hwndStaticMonthDOB    , 0);
			EnableWindow(hwndButtonMonthDOB    , FALSE);
			
			AMC_SetIndex(hwndListDayOfDOB      , hwndStaticDayDOB    , 0);
			EnableWindow(hwndButtonDayDOB      , FALSE);
			
			AMC_SetIndex(hwndListYearOfJoining , hwndStaticYearJoining, 0);
			
			AMC_SetIndex(hwndListMonthOfJoining, hwndStaticMonthJoining, 0);
			EnableWindow(hwndButtonMonthJoining, FALSE);
			
			AMC_SetIndex(hwndListDayOfJoining   , hwndStaticDayJoining, 0);
			EnableWindow(hwndButtonDayJoining   , FALSE);
			
			AMC_SetIndex(hwndListDepartment     , hwndStaticDepartment , 0);
		}		
/*******************************************************
 * ID_RADIOBUTTON_MALE
 *******************************************************/			
			//male
			else if(LOWORD(wParam) == ID_RADIOBUTTON_MALE)
			{
				if(HIWORD(wParam) == BN_CLICKED)
				{
					if(SendMessage(hwndRadioButtonMale, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
					{
						//wparam ==> check or uncheck
						SendMessage(hwndRadioButtonMale, BM_SETCHECK, 1, 0);
						SendMessage(hwndRadioButtonFemale, BM_SETCHECK, 0, 0);
					}
				}
			}
/*******************************************************
 * ID_RADIOBUTTON_FEMALE
 *******************************************************/				
			//female
			else if(LOWORD(wParam) == ID_RADIOBUTTON_FEMALE)
			{
				if(HIWORD(wParam) == BN_CLICKED)
				{
					if(SendMessage(hwndRadioButtonFemale, BM_GETCHECK, 0, 0) == BST_UNCHECKED)
					{
						//wparam ==> check or uncheck
						SendMessage(hwndRadioButtonFemale, BM_SETCHECK, 1, 0);
						SendMessage(hwndRadioButtonMale, BM_SETCHECK, 0, 0);
					}
				}
			}
/*******************************************************
 * ID_BUTTON_DAYOFWEEK_DOB
 *******************************************************/				
			//day-DOB
			else if(LOWORD(wParam) == ID_BUTTON_DAYOFWEEK_DOB  && HIWORD(wParam) == BN_CLICKED)
				{
					if(dayFlagDOB)
					{
						ShowWindow(hwndListDayOfDOB, SW_HIDE);
						dayFlagDOB = 0;
					}
					else
					{
						//show list window
						ShowWindow(hwndListDayOfDOB, SW_SHOW);
						dayFlagDOB = 1;
						
						//hide other list windows
						ShowWindow(hwndListMonthOfDOB, SW_HIDE);
						monthFlagDOB = 0;
						
						ShowWindow(hwndListYearOfDOB, SW_HIDE);
						yearFlagDOB = 0;
						
						ShowWindow(hwndListDayOfJoining, SW_HIDE);
						dayFlagJoining = 0;
						
						ShowWindow(hwndListMonthOfJoining, SW_HIDE);
						monthFlagJoining = 0;
						
						ShowWindow(hwndListYearOfJoining, SW_HIDE);
						yearFlagJoining = 0;
						
						ShowWindow(hwndListDepartment, SW_HIDE);
						flagDepartment = 0;
					}
				}
				
			else if(LOWORD(wParam) == ID_LIST_DAYOFWEEK_DOB)
				{
					if(HIWORD(wParam) == LBN_SELCHANGE)
					{
						int index = AMC_SetSelectedText(hwndListDayOfDOB, hwndStaticDayDOB);
						
						dayFlagDOB = 0;
					}
				}
/*******************************************************
 * ID_BUTTON_MONTH_DOB
 *******************************************************/					
			//month-DOB
			else if(LOWORD(wParam) == ID_BUTTON_MONTH_DOB  && HIWORD(wParam) == BN_CLICKED)
				{
					if(monthFlagDOB)
					{
						ShowWindow(hwndListMonthOfDOB, SW_HIDE);
						monthFlagDOB = 0;
					}
					else
					{
						//show list window
						ShowWindow(hwndListMonthOfDOB, SW_SHOW);
						monthFlagDOB = 1;
						
						//hide other list windows
						ShowWindow(hwndListDayOfDOB, SW_HIDE);
						dayFlagDOB = 0;
						
						ShowWindow(hwndListYearOfDOB, SW_HIDE);
						yearFlagDOB = 0;
						
						ShowWindow(hwndListDayOfJoining, SW_HIDE);
						dayFlagJoining = 0;
						
						ShowWindow(hwndListMonthOfJoining, SW_HIDE);
						monthFlagJoining = 0;
						
						ShowWindow(hwndListYearOfJoining, SW_HIDE);
						yearFlagJoining = 0;
						
						ShowWindow(hwndListDepartment, SW_HIDE);
						flagDepartment = 0;
					}
				}
				
			else if(LOWORD(wParam) == ID_LIST_MONTH_DOB)
				{
					if(HIWORD(wParam) == LBN_SELCHANGE)
					{
						AMC_SetSelectedText(hwndListMonthOfDOB, hwndStaticMonthDOB);
						monthFlagDOB = 0;

						int index = SendMessage(hwndListYearOfDOB, LB_GETCURSEL, 0, 0);
						if(index != 0)
						{
							index = SendMessage(hwndListMonthOfDOB, LB_GETCURSEL, 0, 0);
							//If other than "<MONTH> is selected
							if(index != 0)
							{
								char *yearString = NULL;
								AMC_GetText(hwndStaticYearDOB, &yearString);

								//Remove All Item from listbox
								SendMessage(hwndListDayOfDOB, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

								//insert new items
								SendMessage(hwndListDayOfDOB, LB_INSERTSTRING, (WPARAM)0, (LPARAM) TEXT("<DAY>"));
								switch(index)
								{
									case JANUARY:
									case MARCH:
									case MAY:
									case JULY:
									case AUGUST:
									case OCTOMBER:
									case DECEMBER:
												for(short i = 1 ; i <= 31; i++)
												{
													TCHAR str[255];
													wsprintf(str, TEXT("%d"), i);
													SendMessage(hwndListDayOfDOB, LB_INSERTSTRING, i , (LPARAM) str);
												}
												break;
									
									case APRIL:
									case JUNE:
									case SEPTEMBER:
									case NOVEMBER:
												for(short i = 1 ; i <= 30; i++)
												{
													TCHAR str[255];
													wsprintf(str, TEXT("%d"), i);
													SendMessage(hwndListDayOfDOB, LB_INSERTSTRING, i , (LPARAM) str);
												}
												break;
												
									case FEBRUARY:
												int year = atoi(yearString);
												if( ( (year%4 == 0) && (year%100 != 0) ) || (year%400 == 0))  
												{
													//leap year
													for(short i = 1 ; i <= 29; i++)
													{
														TCHAR str[255];
														wsprintf(str, TEXT("%d"), i);
														SendMessage(hwndListDayOfDOB, LB_INSERTSTRING, i , (LPARAM) str);
													}
												}
												else
												{
													//not a leap year
													for(short i = 1 ; i <= 28; i++)
													{
														TCHAR str[255];
														wsprintf(str, TEXT("%d"), i);
														SendMessage(hwndListDayOfDOB, LB_INSERTSTRING, i , (LPARAM) str);
													}
												}
												break;
								}
								free(yearString);
								//Set day to 0th index
								AMC_SetIndex(hwndListDayOfDOB, hwndStaticDayDOB, 0);
								//Enable Day button
								EnableWindow(hwndButtonDayDOB, TRUE);
							}
							else
							{
								//If "<MONTH>" selected
								AMC_SetIndex(hwndListDayOfDOB, hwndStaticDayDOB, -1);
								//disable button
								EnableWindow(hwndButtonDayDOB, FALSE);
							}
						}
					}
				}
/*******************************************************
 * ID_BUTTON_YEAR_DOB
 *******************************************************/					
			//year-DOB
			else if(LOWORD(wParam) == ID_BUTTON_YEAR_DOB  && HIWORD(wParam) == BN_CLICKED)
				{
					if(yearFlagDOB)
					{
						ShowWindow(hwndListYearOfDOB, SW_HIDE);
						yearFlagDOB = 0;
					}
					else
					{
						//show list window
						ShowWindow(hwndListYearOfDOB, SW_SHOW);
						yearFlagDOB = 1;
						
						//hide other list windows
						ShowWindow(hwndListDayOfDOB, SW_HIDE);
						dayFlagDOB = 0;
						
						ShowWindow(hwndListMonthOfDOB, SW_HIDE);
						monthFlagDOB = 0;
						
						ShowWindow(hwndListDayOfJoining, SW_HIDE);
						dayFlagJoining = 0;
						
						ShowWindow(hwndListMonthOfJoining, SW_HIDE);
						monthFlagJoining = 0;
						
						ShowWindow(hwndListYearOfJoining, SW_HIDE);
						yearFlagJoining = 0;
						
						ShowWindow(hwndListDepartment, SW_HIDE);
						flagDepartment = 0;
					}
				}
				
			else if(LOWORD(wParam) == ID_LIST_YEAR_DOB)
				{
					if(HIWORD(wParam) == LBN_SELCHANGE)
					{
						int index = AMC_SetSelectedText(hwndListYearOfDOB, hwndStaticYearDOB);
						yearFlagDOB = 0;
						
						//Set month to 0th index
							AMC_SetIndex(hwndListMonthOfDOB, hwndStaticMonthDOB, 0);
						//Set day to 0th index
							AMC_SetIndex(hwndListDayOfDOB, hwndStaticDayDOB, -1);
						//Disable day button
							EnableWindow(hwndButtonDayDOB, FALSE);
						if(index != 0)
						{
							//enable window
							EnableWindow(hwndButtonMonthDOB, TRUE);
						}
						else
						{
							//enable window
							EnableWindow(hwndButtonMonthDOB, FALSE);
						}
					}
				}

/*******************************************************
 * ID_BUTTON_DAYOFWEEK_JOINING
 *******************************************************/					
			//day-Joining
			else if(LOWORD(wParam) == ID_BUTTON_DAYOFWEEK_JOINING  && HIWORD(wParam) == BN_CLICKED)
				{
					if(dayFlagJoining)
					{
						ShowWindow(hwndListDayOfJoining, SW_HIDE);
						dayFlagJoining = 0;
					}
					else
					{
						//show list window
						ShowWindow(hwndListDayOfJoining, SW_SHOW);
						dayFlagJoining = 1;
						
						//hide other list windows
						ShowWindow(hwndListDayOfDOB, SW_HIDE);
						dayFlagDOB = 0;
						
						ShowWindow(hwndListMonthOfDOB, SW_HIDE);
						monthFlagDOB = 0;
						
						ShowWindow(hwndListYearOfDOB, SW_HIDE);
						yearFlagDOB = 0;
						
						ShowWindow(hwndListMonthOfJoining, SW_HIDE);
						monthFlagJoining = 0;
						
						ShowWindow(hwndListYearOfJoining, SW_HIDE);
						yearFlagJoining = 0;
						
						ShowWindow(hwndListDepartment, SW_HIDE);
						flagDepartment = 0;
					}
				}
				
				if(LOWORD(wParam) == ID_LIST_DAYOFWEEK_JOINING)
				{
					if(HIWORD(wParam) == LBN_SELCHANGE)
					{
						AMC_SetSelectedText(hwndListDayOfJoining, hwndStaticDayJoining);
						dayFlagJoining = 0;
					}
				}
				
/*******************************************************
 * ID_BUTTON_MONTH_JOINING
 *******************************************************/					
			//month-Joining
			else if(LOWORD(wParam) == ID_BUTTON_MONTH_JOINING  && HIWORD(wParam) == BN_CLICKED)
				{
					if(monthFlagJoining)
					{
						ShowWindow(hwndListMonthOfJoining, SW_HIDE);
						monthFlagJoining = 0;
					}
					else
					{
						//show list window
						ShowWindow(hwndListMonthOfJoining, SW_SHOW);
						monthFlagJoining = 1;
						
						//hide other list windows
						ShowWindow(hwndListDayOfDOB, SW_HIDE);
						dayFlagDOB = 0;
						
						ShowWindow(hwndListMonthOfDOB, SW_HIDE);
						monthFlagDOB = 0;
						
						ShowWindow(hwndListYearOfDOB, SW_HIDE);
						yearFlagDOB = 0;
						
						ShowWindow(hwndListDayOfJoining, SW_HIDE);
						dayFlagJoining = 0;
						
						ShowWindow(hwndListYearOfJoining, SW_HIDE);
						yearFlagJoining = 0;
						
						ShowWindow(hwndListDepartment, SW_HIDE);
						flagDepartment = 0;
					}
				}
				
			else if(LOWORD(wParam) == ID_LIST_MONTH_JOINING)
				{
					if(HIWORD(wParam) == LBN_SELCHANGE)
					{
						AMC_SetSelectedText(hwndListMonthOfJoining, hwndStaticMonthJoining);
						monthFlagJoining = 0;
						
						int index = SendMessage(hwndListYearOfJoining, LB_GETCURSEL, 0, 0);
						if(index != 0)
						{
							index = SendMessage(hwndListMonthOfJoining, LB_GETCURSEL, 0, 0);
							if(index != 0)
							{
								char *yearString = NULL;
								AMC_GetText(hwndStaticYearJoining, &yearString);

								//Remove All Item from listbox
								SendMessage(hwndListDayOfJoining, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

								//insert new items
								SendMessage(hwndListDayOfJoining, LB_INSERTSTRING, (WPARAM)0, (LPARAM) TEXT("<DAY>"));
								switch(index)
								{
									//31 days month
									case JANUARY:
									case MARCH:
									case MAY:
									case JULY:
									case AUGUST:
									case OCTOMBER:
									case DECEMBER:
												for(short i = 1 ; i <= 31; i++)
												{
													TCHAR str[255];
													wsprintf(str, TEXT("%d"), i);
													SendMessage(hwndListDayOfJoining, LB_INSERTSTRING, i , (LPARAM) str);
												}
												break;
									
											//30 days month
									case APRIL:
									case JUNE:
									case SEPTEMBER:
									case NOVEMBER:
												for(short i = 1 ; i <= 30; i++)
												{
													TCHAR str[255];
													wsprintf(str, TEXT("%d"), i);
													SendMessage(hwndListDayOfJoining, LB_INSERTSTRING, i , (LPARAM) str);
												}
												break;
												
												//28 / 29 month
									case FEBRUARY:
												int year = atoi(yearString);
												if( ( (year%4 == 0) && (year%100 != 0) ) || (year%400 == 0))  
												{
													//leap year
													for(short i = 1 ; i <= 29; i++)
													{
														TCHAR str[255];
														wsprintf(str, TEXT("%d"), i);
														SendMessage(hwndListDayOfJoining, LB_INSERTSTRING, i , (LPARAM) str);
													}
												}
												else
												{
													//not a leap year
													for(short i = 1 ; i <= 28; i++)
													{
														TCHAR str[255];
														wsprintf(str, TEXT("%d"), i);
														SendMessage(hwndListDayOfJoining, LB_INSERTSTRING, i , (LPARAM) str);
													}
												}
												break;
								}
								free(yearString);
								//Set day to 0th index
								AMC_SetIndex(hwndListDayOfJoining, hwndStaticDayJoining, 0);
								//Enable Day button
								EnableWindow(hwndButtonDayJoining, TRUE);
							}
							else
							{
								//If "<MONTH>" selected
								AMC_SetIndex(hwndListDayOfJoining, hwndStaticDayJoining, -1);
								//disable button
								EnableWindow(hwndButtonDayJoining, FALSE);
							}
						}
					}
				}

/*******************************************************
 * ID_BUTTON_YEAR_JOINING
 *******************************************************/					
			//year-Joining
			else if(LOWORD(wParam) == ID_BUTTON_YEAR_JOINING  && HIWORD(wParam) == BN_CLICKED)
				{
					if(yearFlagJoining)
					{
						ShowWindow(hwndListYearOfJoining, SW_HIDE);
						yearFlagJoining = 0;
					}
					else
					{
						//show list window
						ShowWindow(hwndListYearOfJoining, SW_SHOW);
						yearFlagJoining = 1;
						
						//hide other list windows
						ShowWindow(hwndListDayOfDOB, SW_HIDE);
						dayFlagDOB = 0;
						
						ShowWindow(hwndListMonthOfDOB, SW_HIDE);
						monthFlagDOB = 0;
						
						ShowWindow(hwndListYearOfDOB, SW_HIDE);
						yearFlagDOB = 0;
						
						ShowWindow(hwndListDayOfJoining, SW_HIDE);
						dayFlagJoining = 0;
						
						ShowWindow(hwndListMonthOfJoining, SW_HIDE);
						monthFlagJoining = 0;
												
						ShowWindow(hwndListDepartment, SW_HIDE);
						flagDepartment = 0;
					}
				}
				
			else if(LOWORD(wParam) == ID_LIST_YEAR_JOINING)
				{
					if(HIWORD(wParam) == LBN_SELCHANGE)
					{
						int index = AMC_SetSelectedText(hwndListYearOfJoining, hwndStaticYearJoining);
						yearFlagJoining = 0;
						
						//Set month to 0th index
							AMC_SetIndex(hwndListMonthOfJoining, hwndStaticMonthJoining, 0);
						//Set day to 0th index
							AMC_SetIndex(hwndListDayOfJoining, hwndStaticDayJoining, -1);
						//Disable
							EnableWindow(hwndButtonDayJoining, FALSE);
						
						if(index != 0)
						{
							//enable window
							EnableWindow(hwndButtonMonthJoining, TRUE);
						}
						else
						{
							//enable window
							EnableWindow(hwndButtonMonthJoining, FALSE);
						}
					}
				}

/*******************************************************
 * ID_BUTTON_DEPARTMENT
 *******************************************************/					
			//department
			else if(LOWORD(wParam) == ID_BUTTON_DEPARTMENT  && HIWORD(wParam) == BN_CLICKED)
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
						
						//hide other list windows
						ShowWindow(hwndListDayOfDOB, SW_HIDE);
						dayFlagDOB = 0;
						
						ShowWindow(hwndListMonthOfDOB, SW_HIDE);
						monthFlagDOB = 0;
						
						ShowWindow(hwndListYearOfDOB, SW_HIDE);
						yearFlagDOB = 0;
						
						ShowWindow(hwndListDayOfJoining, SW_HIDE);
						dayFlagJoining = 0;
						
						ShowWindow(hwndListMonthOfJoining, SW_HIDE);
						monthFlagJoining = 0;
						
						ShowWindow(hwndListYearOfJoining, SW_HIDE);
						yearFlagJoining = 0;						
					}
				}
				
			else if(LOWORD(wParam) == ID_LIST_DEPARTMENT)
				{
					if(HIWORD(wParam) == LBN_SELCHANGE)
					{
						AMC_SetSelectedText(hwndListDepartment, hwndStaticDepartment);
						flagDepartment = 0;
					}
				}
			
			return(0);
		}
		
	  /********************** WM_LBUTTONDOWN *********************/			
		case WM_LBUTTONDOWN:
		{
						
						//hide other list windows
						ShowWindow(hwndListYearOfDOB     , SW_HIDE);
						yearFlagDOB      = 0;

						ShowWindow(hwndListDayOfDOB      , SW_HIDE);
						dayFlagDOB       = 0;
						
						ShowWindow(hwndListMonthOfDOB    , SW_HIDE);
						monthFlagDOB     = 0;
						
						ShowWindow(hwndListDayOfJoining  , SW_HIDE);
						dayFlagJoining   = 0;
						
						ShowWindow(hwndListMonthOfJoining, SW_HIDE);
						monthFlagJoining = 0;
						
						ShowWindow(hwndListYearOfJoining , SW_HIDE);
						yearFlagJoining  = 0;
						
						ShowWindow(hwndListDepartment    , SW_HIDE);
						flagDepartment   = 0;
						
						return(0);
		}


	 /************************** WM_DESTROY *************************/					
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return(0);
		}
	}
	return(DefWindowProc(hwnd, message, wParam, lParam));
}
