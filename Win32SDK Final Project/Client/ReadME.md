Resource Compile
	
	> rc.exe Menu.rc
	> rc.exe SplashScreen.rc

Compile and Link

	> cl.exe /EHsc Main.cpp AMC_Functions.cpp DataEntry.cpp SearchRecord.cpp ShowTable.cpp Menu.res SplashScreen.res /link user32.lib gdi32.lib kernel32.lib ole32.lib comctl32.lib /SUBSYSTEM:WINDOWS /MACHINE:x64

