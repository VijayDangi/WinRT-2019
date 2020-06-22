Using Command Line

> cl.exe /EHsc /c MyMathUsingDllDef.cpp

> link.exe user32.lib gdi32.lib kernel32.lib /DLL /DEF:MyMathUsingDllDef.def MyMathUsingDllDef.obj

