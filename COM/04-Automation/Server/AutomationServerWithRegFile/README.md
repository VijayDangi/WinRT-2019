AutomationServerWithRegFile.dll contains the actual implemantation of `IMyMath` interface methods.


# Compiling Step....

	> cl.exe /EHsc /c AutomationServerWithRegFile.cpp /D UNICODE /DLL /DEF:AutomationServerWithRegFile.def

/D  UNICODE ==> For swprintf_s() function.


## Linking Step....

	> link.exe AutomationServerWithRegFile.obj user32.lib kernel32.lib gdi32.lib ole32.lib advapi32.lib oleaut32.lib /DLL /DEF:AutomationServerWithRegFile.def /SUBSYSTEM:WINDOWS /MACHINE:x64


ole32.lib, oleaut32.lib, advapi32.lib are COM DLL's



OUTPUT FILES

	- AutomationServerWithRegFile.dll
	- AutomationServerWithRegFile.exp
	- AutomationServerWithRegFile.lib

	
### Now copy and paste following files in "C:/Windows/System32/MyDll/" folder 
	
		- AutomationServerWithRegFile.dll

### Then type make appropriate changes in `AutomationServerWithRegFile.reg` file and then double click to register.
