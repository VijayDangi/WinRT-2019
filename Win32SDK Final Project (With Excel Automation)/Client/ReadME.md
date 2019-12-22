Resource Compile
	
	> rc.exe Menu.rc
	> rc.exe SplashScreen.rc

Compile

	> cl.exe /EHsc /c Main.cpp AMC_Functions.cpp CSVExport.cpp DataEntry.cpp ExcelAutomation.cpp SaveAsDialog.cpp SearchRecord.cpp ShowTable.cpp
	
Link

	> link.exe user32.lib gdi32.lib kernel32.lib comctl32.lib comdlg32.lib ole32.lib oleaut32.lib /SUBSYSTEM:WINDOWS /MACHINE:x64 Main.obj AMC_Functions.obj CSVExport.obj DataEntry.obj ExcelAutomation.obj SaveAsDialog.obj SearchRecord.obj ShowTable.obj Menu.res SplashScreen.res

