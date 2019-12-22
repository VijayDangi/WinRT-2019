Compile:

	> cl.exe /EHsc /c  AstroMediComp_Project.cpp AstroMediComp_Project_String.cpp
	
Link:

	> link.exe user32.lib gdi32.lib kernel32.lib ole32.lib oleaut32.lib /DLL /DEF:AstroMediComp_Project.def /MACHINE:x64 AstroMediComp_Project.obj AstroMediComp_Project_String.obj
	