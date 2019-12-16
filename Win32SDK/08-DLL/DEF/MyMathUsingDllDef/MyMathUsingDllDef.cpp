/*
 * Writing DLL using Module Definition File.
 */


//include header files
#include <Windows.h>

//DllMain() is known as "Entry Point Function" of dll application.
BOOL WINAPI DllMain(
				HINSTANCE hDll,	  /* A handle of dll. This value is base address od dll(i.e. 0th position of file pointer).
								     This handle is passed to your dll by the OS and this is the handle retrieved by the 
								     caller using LoadLibrary().
								  */
		
				DWORD dwReason,   /* This is the flag indicating for what reason this dll is called.
								  */

				LPVOID lpReserved /* This is reserved and usually NULL for dynamic linking.
								  */
			)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:	/* Indicates that the dll is called by caller's process. 
							       The message handler of this value in DllMain() can do process specific initialization.
								*/
		break;

	case DLL_THREAD_ATTACH:     /* Indicates that the calling process is created a new thread and this new thread wants 
							       to load this dll.
							    */
		break;

	case DLL_THREAD_DETACH:     /* Indicates that the calling process's calling thread is exiting.
							    */
		break;

	case DLL_PROCESS_DETACH:    /* Indicates that now calling process is unloading the dll from its address space.
								   The message handler of this value can do uninitialization of the initializations 
								   done in DLL_PROCESS_ATTACH.
							    */
		break;

	}
	return TRUE;
}

//
extern "C" int MakeSquare(int num)
{
	return (num * num);
}

//
extern "C" BOOL IsNumberNegative(int num)
{
	if (num < 0)
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}
