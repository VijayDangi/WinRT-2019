IDL (INTERFACE DEFINITION LANGUAGE)

 -------------------------------------------------------------------
 [                                                                 
    /*Interface attributes go here*/ /*Attribute block*/        
 ]                                                                
  interface INTERFACE_NAME                                         
  {                                                                
   /*The interface body goes here*/ /*Object Block*/          
  }                                                                
 -------------------------------------------------------------------
 
 
 
To generate the `CPP` files from `idl` type following command..
The following command will generate 3 X .cpp files, 1 X .h file and 1 X .tlb file


	> MIDL /env x64 AutomationServerTypeLib.idl
	
Genarated files
	|- AutomationServerTypeLib_i.c
	|- AutomationServerTypeLib_p.c
	|- dlldata.c
	|- AutomationServerTypeLib.h
	|- AutomationServerTypeLib.tlb

	
								OR

	> MIDL /env x64 /h AutomationProxyStubHeader.h  /iid AutomationProxyStubGuids.c  /dlldata AutomationProxyStubDllData.c  /proxy AutomationProxyStub.c AutomationServerTypeLib.idl
	
Genarated Files
	|- AutomationProxyStubGuids.c 
	|- AutomationProxyStub.c
	|- AutomationProxyStubDllData.c
	|- AutomationProxyStubHeader.h
	|- AutomationServerTypeLib.tlb	



##Now create the DLL using generated files from above command

 1. Create .def as named `AutomationProxyStub.def`
 2. Type following command for compile and linking
 
 Compiling...
 
	> cl.exe /EHsc /c AutomationProxyStubGuids.c  AutomationProxyStub.c  AutomationProxyStubDllData.c  /D UNICODE /D REGISTER_PROXY_DLL /DLL /DEF:AutomationProxyStub.def

REGISTER_PROXY_DLL ==> Generates DllMain, DllRegisterServer, and DllUnregisterServer functions for automatically registering a proxy DLL.


	
 Linking...
 
	> link.exe AutomationProxyStub.obj AutomationProxyStubDllData.obj AutomationProxyStubGuids.obj user32.lib kernel32.lib gdi32.lib ole32.lib advapi32.lib oleaut32.lib rpcrt4.lib rpcns4.lib /DLL /DEF:AutomationProxyStub.def /MACHINE:x64 /SUBSYSTEM:WINDOWS
	
rpcns4.lib ==> Name-service functions
rpcrt4.lib ==> Windows run-time functions


After compiling and linking generated files
	|- AutomationProxyStub.dll
	|- AutomationProxyStub.exp
	|- AutomationProxyStub.lib

	

	
### Now copy and paste following files in "C:/Windows/System32/MyDll/" folder 
	
		- AutomationProxyStub.dll
		- AutomationServerTypeLib.tlb

### Then type following command to regiter the AutomationProxyStub.dll and open `CMD` in `Run As Administrator`.

	RegSvr32 AutomationProxyStub.dll
