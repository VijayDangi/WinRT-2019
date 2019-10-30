//Header Files
#include <Windows.h>
#include <stdio.h> //for swprintf_s()
#include "AutomationServerWithRegFile.h"

//class declaration
class CMyMath : public IMyMath
{
	private:
		long m_cRef;
		ITypeInfo *m_pITypeInfo;
	public:
		//constructor
		CMyMath(void);
		//destructor
		~CMyMath(void);
		//IUnknown specific method declarations (inherited)
		HRESULT __stdcall QueryInterface(REFIID, void**);
		ULONG __stdcall AddRef(void);
		ULONG __stdcall Release(void);
		//IDispatch specific method declarations (inherited)
		HRESULT __stdcall GetTypeInfoCount(UINT *);
		HRESULT __stdcall GetTypeInfo(UINT, LCID, ITypeInfo**);
		HRESULT __stdcall GetIDsOfNames(REFIID, LPOLESTR *, UINT, LCID, DISPID*);
		HRESULT __stdcall Invoke(DISPID, REFIID, LCID, WORD, DISPPARAMS*, VARIANT*, EXCEPINFO*, UINT*);
		//ISum specific method declarations (inherited)
		HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
		//ISubtract specific method declarations (inherited)
		HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);
		//custom methods
		HRESULT InitInstance(void);
};

//class factory
class CMyMathClassFactory : public IClassFactory
{
	private:
		long m_cRef;
	public:
		//constructor
		CMyMathClassFactory(void);
		//destructor
		~CMyMathClassFactory(void);
		//IUnknown specific methods declarations (inherited)
		HRESULT __stdcall QueryInterface(REFIID, void**);
		ULONG __stdcall AddRef(void);
		ULONG __stdcall Release(void);
		//IClassFactory specific method declarations (inherited)
		HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
		HRESULT __stdcall LockServer(BOOL);
};

//global variable declarations
long glNumberOfActiveComponents = 0; //Number of active components
long glNumberOfServerLocks = 0; //Number of locks on this Dll

// {E782E3B7-5B66-4BF1-8D5B-438572A7612C}
const GUID LIBID_AutomationServer = { 0xe782e3b7, 0x5b66, 0x4bf1, 0x8d, 0x5b, 0x43, 0x85, 0x72, 0xa7, 0x61, 0x2c };

//DllMain() is known as "Entry Point Function" of dll application.
/**
  * @param hDll {HINSTANCE}
  *		A handle of dll. This value is base address of dll(i.e. 0th position of //FILE pointer).
  *		This handle is passed to your dll by the OS and this is the handle retrieved by the
  *		caller using LoadLibrary().
  *
  * @param dwReason {DWORD}
  *		This is the flag indicating for what reason this dll is called,
  *
  *	@param lpReserved {LPVOID}
  *		This is reserved and usually NULL for dynamic linking.
 **/
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID lpReserved)
{
	//FILE *fp = fopen("ProgramFlow.log","a+");
	//fprintf(fp, " ==> DllMain()\n");
	
	//MessageBox(NULL, 
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		/* Indicates that the dll is called by caller's process.
			The message handler of this value in DllMain() can do process specific initialization.
		*/
		break;

	case DLL_THREAD_ATTACH:
		/* Indicates that the calling process is created a new thread and this new thread wants
			to load this dll.
		*/
		break;

	case DLL_THREAD_DETACH:
		/* Indicates that the calling process's calling thread is exiting.*/
		break;

	case DLL_PROCESS_DETACH:
		/* Indicates that now calling process is unloading the dll from its address space.
			The message handler of this value can do uninitialization of the initializations
			done in DLL_PROCESS_ATTACH.
		*/
		break;
	}
	//fprintf(fp, "INNER ==> OUT ==> DllMain()\n");
	//fclose(fp);
	return TRUE;
}


//Implementation of CMyMath constructor
CMyMath::CMyMath(void)
{
	m_pITypeInfo = NULL;
	m_cRef = 1; //hardcoded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents); //increment global counter
}

//CMyMath destructor
CMyMath::~CMyMath(void)
{
	//code
	InterlockedDecrement(&glNumberOfActiveComponents); //decrement global counter
}

//Implementation of CMyMath's IUnknown's Methods
/**
 * IUnknown::QueryInterface
 *
 * @param {REFIID}
 *		A reference to the interface identifier (IID) of the interface being queried for.
 *
 *	@param {void**} OUT PARAMETER
 *		The address of a pointer to an interface with the IID specified in the riid parameter.
**/
HRESULT CMyMath::QueryInterface(REFIID riid, void **ppv)
{
	if(riid == IID_IUnknown)
		*ppv = static_cast<IMyMath *>(this);
	else if(riid == IID_IDispatch)
		*ppv = static_cast<IMyMath *>(this);
	else if(riid == IID_IMyMath)
		*ppv = static_cast<IMyMath *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

//AddRef()
ULONG CMyMath::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

//Release()
ULONG CMyMath::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if(m_cRef == 0)
	{
		m_pITypeInfo->Release();
		m_pITypeInfo = NULL;
		delete(this);
		return(0);
	}
	return(m_cRef);
}

//Implementation of CMyMath's IDispatch's methods

/**
  * IDispatch::GetTypeInfoCount() :
  *          Retrieves the number of type information interface that an object provides (either 0 or 1).
  *
  *  @param {UINT}
  *			The number of type information interface provided by the object. If the object provides type information,
  * 			this number is 1; otherwise the number is 0.
  *
 **/
HRESULT CMyMath::GetTypeInfoCount(UINT *pCountTypeInfo)
{
	if(pCountTypeInfo == NULL)
		return (E_INVALIDARG);
	*pCountTypeInfo = 1;
	return(S_OK);
}

/**
  * IDispatch::GetTypeInfo() :
  *          Retrieves the type information for an object, which can then be used to get the type information for an interface.
  *
  * @param {UINT}
  *				The type information to return. Pass 0 to retrieve type information for the `IDispatch` implementation.
  *
  * @param {LCID}
  *				The locale identifier for the type information. An object may be able to return different type information for different
  *				languages. This is important for classes that support localized member names. For classes that do not support localized member
  *				names, this parameter can be ignored.
  *
  * @param {ITypeInfo}
  *				The requested type information object.
 **/
HRESULT CMyMath::GetTypeInfo(UINT iTypeInfo, LCID lcid, ITypeInfo **ppITypeInfo)
{
	*ppITypeInfo = NULL;
	if(iTypeInfo != 0)
		return(DISP_E_BADINDEX);
	m_pITypeInfo->AddRef();
	*ppITypeInfo = m_pITypeInfo;
	return(S_OK);
}

/**
  * GetIDsOfNames() : Maps a single member and an optional set of argument names to a corresponding set of integer DISPIDs,
  *						 which can be used on subsequent calls to `Invoke`. The dispatch function `DispGetIDsOfNames` provides a
  *						 standard implementation of `GetIDsOfNames`
  *
  * @param {REFIID}
  *				Reserved for future use. Must be IID_NULL
  *
  * @param {LPOLESTR}
  *				The array of names to be mapped.
  *
  * @param {UINT}
  *				The count of the names to be mapped.
  *
  * @param {LCID}
  *				The Locale context in which to interpret the names.
  *
  * @param {DISPID}
  *				Caller-allocated array, each element of wich contains an identifier (ID) corresponding to one of the names passed in the 
  *				rgszNames array. The first element represents the member name. The subsequent elements represent each of the member's 
  *				parameters.
 **/
HRESULT CMyMath::GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId)
{
	return( DispGetIDsOfNames(m_pITypeInfo, rgszNames, cNames, rgDispId) );
}

/**
  * IDispatch::Invoke() : Provide access to properties and methods exposed by an object. The dispatch function `DispInvoke` provides a standard
  *						  implementation of Invoke.
  *
  * @param {DISPID}
  *				Identifies the member, Use `GetIDsOfNames` or the object's documentation to obtain the dispatch identifier.
  *
  * @param {REFIID}
  *				Reserved for future use. Must be IID_NULL.
  *
  * @param {LCID}
  *				The locale context in which to interpret arguments.
  *
  * @param {WORD}
  *				flags describing the context of the `Invoke` call.
  *
  *	    DISPATCH_METHOD         ==> The member is invoked as a method. If a property has a same name, both this and DISPATCH_PROPERTYGET flag can be set.
  *		DISPATCH_PROPERTYGET    ==> The member is retrived as a property or data member.
  *		DISPATCH_PROPERTYPUT    ==> The member is changed as a property or data member.
  *		DISPATCH_PROPERTYPUTREF ==> The member is changed by a reference assignment, rather than a value assignment. This flag is valid only when the
  *										property accepts a reference to an object.
  *
  * @param {DISPPARAMS}
  *				Pointer to a DISPPARAMS structure containing an array of arguments, an array of argument DISPIDs for named arguments, and counts for
  *				the number of elements in the arrays.
  *
  * @param {VARIANT}
  *				Pointer to the location where the result is to be stored, or NULL if the caller expects no result. This  argument is ignored if 
  *				DISPATCH_PROPERTYPUT or DISPATCH_PROPERTYPUTREF is specified.
  *
  * @param {EXCEPINFO}
  *				Pointer to a structure that contains exception information. This structure should be filled in if DISP_E_EXCEPTION is returned. Can be NULL.
  *
  * @param {UINT}
  *				The index within rgvarg of the first argument that has an error. Arguments are stored in pDispParams->rgvarg in reverse order, so the first
  *				argument is the one with the highest index in the array. This parameter is returned only when the resulting return value is
  *				DISP_E_TYPEMISMATCH or DISP_E_PARAMNOTFOUND.
 **/
HRESULT CMyMath::Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr)
{
	HRESULT hr;
	
	hr = DispInvoke(
		this,
		m_pITypeInfo,
		dispIdMember,
		wFlags,
		pDispParams,
		pVarResult,
		pExcepInfo,
		puArgErr
	);
	
	return (hr);
}

//IMyaMath's SumOfTwoIntegers() implementation
HRESULT CMyMath::SumOfTwoIntegers(int num1, int num2, int *pSum)
{
	*pSum = num1 + num2;
	return(S_OK);
}

//IMyMath's SubtractionOfTwoIntegers() implementation
HRESULT CMyMath::SubtractionOfTwoIntegers(int num1, int num2, int *pSubtraction)
{
	*pSubtraction = num1 - num2;
	return(S_OK);
}

//CMyMath's InitInstance()
HRESULT CMyMath::InitInstance(void)
{
	//function declarations
	void ComErrorDescriptionString(HWND, HRESULT);
	//variable declarations
	HRESULT hr;
	ITypeLib *pITypeLib = NULL;
	//code
	if(m_pITypeInfo == NULL)
	{
		/**
		  * LoadRegTypeLib() : Uses registry information to load a type library
		  *
		  * @param {REFGUID}
		  *				The GUID of the library.
		  * @param {WORD}
		  *				The major version of the library.
		  * @param {WORD}
		  *				The minor version of the library.
		  * @param {LCID}
		  *				The national language code of the library.
		  * @param {ITypeLib}
		  *				The loaded type library.
		 **/
		hr = LoadRegTypeLib(LIBID_AutomationServer,
							1, 0, //major_number, minor_number
							0x00, //LANG_NEUTRAL
							&pITypeLib
				);
		
		if(FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			return(hr);
		}
		/**
		  * ITypeLib::GetTypeInfoOfGuid() : Retrieves the type description that corresponds to the specified GUID.
		  *
		  * @param {REFGUID}
		  *				The GUID of the type description
		  *	@param {ITypeInfo}
		  *				Th `ITypeInfo` interface.
		 **/
		hr = pITypeLib->GetTypeInfoOfGuid(IID_IMyMath, &m_pITypeInfo);
		if(FAILED(hr))
		{
			ComErrorDescriptionString(NULL, hr);
			pITypeLib->Release();
			return(hr);
		}
		pITypeLib->Release();
	}
	return(S_OK);
}



//CMyMathClassFactory's method implementations
//CMyMathClassFactory's construct
CMyMathClassFactory::CMyMathClassFactory(void)
{
	m_cRef = 1; //hardcoded initialization to anticipate possible failure of QueryInterface()
}

//CMyMathClassFactory destructor
CMyMathClassFactory::~CMyMathClassFactory(void)
{
	
}

//CMyMathClassFactory's IUnknown's Methods
/**
 * IUnknown::QueryInterface
 *
 * @param {REFIID}
 *		A reference to the interface identifier (IID) of the interface being queried for.
 *
 *	@param {void**} OUT PARAMETER
 *		The address of a pointer to an interface with the IID specified in the riid parameter.
**/
HRESULT CMyMathClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	if(riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if(riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

//AddRef()
ULONG CMyMathClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

//Release()
ULONG CMyMathClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if(m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

//CMyMathClassFactory's IClassFactory methods
HRESULT CMyMathClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	CMyMath *pCMyMath = NULL;
	HRESULT hr;
	
	if(pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);
	
	//create instance of component
	pCMyMath = new CMyMath;
	if(pCMyMath == NULL)
		return(E_OUTOFMEMORY);
	
	//call automation related init method
	pCMyMath->InitInstance();
	
	//get the requested interface
	hr = pCMyMath->QueryInterface(riid, ppv);
	pCMyMath->Release();
	return(hr);
}

HRESULT CMyMathClassFactory::LockServer(BOOL fLock)
{
	if(fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}



//DllGetClassObject()
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	CMyMathClassFactory *pCMyMathClassFactory = NULL;
	HRESULT hr;
	
	if(rclsid != CLSID_MyMath)
		return(CLASS_E_CLASSNOTAVAILABLE);
	
	//create instance of class factory
	pCMyMathClassFactory = new CMyMathClassFactory;
	if(pCMyMathClassFactory == NULL)
		return(E_OUTOFMEMORY);
	
	hr = pCMyMathClassFactory->QueryInterface(riid, ppv);
	pCMyMathClassFactory->Release(); //anticipate possible failure of QueryInterface()
	return(hr);
}

//DllCanUnloadNow
extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if( (glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0) )
		return(S_OK);
	else
		return(S_FALSE);
}

//ComErrorDescriptionString
void ComErrorDescriptionString(HWND hwnd, HRESULT hr)
{
	TCHAR *szErrorMessage = NULL;
	TCHAR str[255];
	
	if(FACILITY_WINDOWS == HRESULT_FACILITY(hr))     //#define HRESULT_FACILITY(hr)  ( ( (hr) >> 16 ) & 0x1FFF )
		hr = HRESULT_CODE(hr);    //#define HRESULT_CODE(hr)    ( (hr) & 0xFFFF )
	
	if(FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, 
					 NULL,
					 hr, 
					 MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					 (LPTSTR)&szErrorMessage,
					 0,
					 NULL
		)  != 0 )
	{
		swprintf_s(str, TEXT("%#x : %s"), hr, szErrorMessage);
		LocalFree(szErrorMessage);
	}
	else
	{
		swprintf_s(str, TEXT("[Could not find a description for error # %#x.]\n"), hr);
	}
	
	MessageBox(hwnd, str, TEXT("COM Error"), MB_OK);
}
