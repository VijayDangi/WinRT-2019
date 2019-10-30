## Now create DotNet (.Net) complikant Dll using following command.

	> tlbimp C:\Windows\System32\MyDll\AutomationServerTypeLib.tlb /out:.\AutomationServerTypeLibForDotNet.dll
	
## Now compile and link VB code

	> vbc.exe /t:winexe /r:AutomationServerTypeLibForDotNet.dll VBAutomation.vb
	
## Run VBAutomation.exe
