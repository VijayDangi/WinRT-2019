## Now create DotNet (.Net) complikant Dll using following command.

	> tlbimp C:\Windows\System32\MyDll\AutomationServerTypeLib.tlb /out:.\AutomationServerTypeLibForDotNet.dll
	
## Now compile and link C# code

	> csc.exe /r:AutomationServerTypeLibForDotNet.dll CSharpAutomation.cs
	
## Run CSharpAutomation.exe
