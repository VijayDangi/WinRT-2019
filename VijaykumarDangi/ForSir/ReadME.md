/*******************************/
For SERVER:

Server Files are:
	1) server/AstroMediComp_Project.cpp :-
				This file contains the DllGetClassObject() and DllCanUnloadNow() functions.
				This file also contains the CoClass.
				
				
	2) server/AstroMediComp_Project_String.cpp :-
				This file contains the functions used for string operation and data file creation.
				
		The data (.dat) files are created in path "C:\AMC" folder.
		The AMC folder will create automatically for first time.
		Also when data is write to files the server will generate the Employee Id.

		
To compile and link server dll
	
  Compile:

	  > cl.exe /EHsc /c  AstroMediComp_Project.cpp AstroMediComp_Project_String.cpp
	
  Link:

	  > link.exe user32.lib gdi32.lib kernel32.lib ole32.lib oleaut32.lib /DLL /DEF:AstroMediComp_Project.def /MACHINE:x64 AstroMediComp_Project.obj AstroMediComp_Project_String.obj

		
/******************************/
FOR CLIENT :

Client files are:

	1) client/Main.cpp :-
				This file contains the WinMain() and WndProc() functions.
				
	2) client/AMC_Functions.cpp
				This files contains the some custome function e.g. AMC_GetText()
				
	3) client/DataEntry.cpp
				This file contain the DataEntry window callback to get the data from user.
				
	4) client/SearchRecord.cpp
				This file contain the SearchRecord window callback which get the search the specified record and display in ListView.
				
	5) client/ShowTable.cpp
				This file contain the ShowTable window callback which display the record of employees
				
	6) clent/SaveAsDialog.cpp
				This file contain 2 functions which shows the SaveAs Dialog Box to get the path where the .csv or Excel sheet have to save
				
	7) client/CSVExport.cpp
				This file contain function which write the listed data in table to the .csv file.
				
	8) client/ExcelAutomation.cpp
				This file contain the function which write the listed data in table to the .XLS or .XLSX file using COM Automation.
				

Resource Compile
	
	> rc.exe Menu.rc
	> rc.exe SplashScreen.rc

Compile

	> cl.exe /EHsc /c Main.cpp AMC_Functions.cpp CSVExport.cpp DataEntry.cpp ExcelAutomation.cpp SaveAsDialog.cpp SearchRecord.cpp ShowTable.cpp
	
Link

	> link.exe user32.lib gdi32.lib kernel32.lib comctl32.lib comdlg32.lib ole32.lib oleaut32.lib /SUBSYSTEM:WINDOWS /MACHINE:x64 Main.obj AMC_Functions.obj CSVExport.obj DataEntry.obj ExcelAutomation.obj SaveAsDialog.obj SearchRecord.obj ShowTable.obj Menu.res SplashScreen.res /OUT:Main.exe

/***************************************/
Additional Functionality:

	COM Automation for Excel Sheet.
	The COM Automation (IDispatch) API are used to get the API of Microsoft Office Excel.