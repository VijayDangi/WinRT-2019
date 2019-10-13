#include<Windows.h>
#include "ContainmentInnerComponentWithRegFile.h"

//CMultiplicationDivision Component declaration
class CMultiplicationDivision : public IMultiplication, IDivision
{
	private:
		long m_cRef;
	public:
		//constructor
		CMultiplicationDivision(void);
		//destructor
		~CMultiplicationDivision(void);
		//IUnknown specific method declarations (inherited)
		HRESULT __stdcall QueryInterface(REFIID, void**);
		ULONG __stdcall AddRef(void);
		ULONG __stdcall Release(void);
		//IMultiplication specific method declarations (inherited)
		HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);
		//IDivision specific method declarations (inherited)
		HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);
};

//CMultiplicationDivisionClassFactory component declaration
class CMultiplicationDivisionClassFactory : public IClassFactory
{
	private:
		long m_cRef;
	public:
		//constructor
		CMultiplicationDivisionClassFactory(void);
		//destructor
		~CMultiplicationDivisionClassFactory(void);
		//IUnknown specific method declarations (inherited)
		HRESULT __stdcall QueryInterface(REFIID, void**);
		ULONG __stdcall AddRef(void);
		ULONG __stdcall Release(void);
		//IClassFactory specific method declarations (inherited)
		HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void**);
		HRESULT __stdcall LockServer(BOOL);
};

//global variable declarations
long glNumberOfActiveComponents = 0; //Number of active components.
long glNumberOfServerLocks = 0; //number of locks on this dll.

//DllMain() is known as "Entry Point Function" of dll application.
/**
  * @param hDll {HINSTANCE}
  *		A handle of dll. This value is base address of dll(i.e. 0th position of file pointer).
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
	return TRUE;
}

//Implementation of CMultiplicationDivision Constructor
CMultiplicationDivision::CMultiplicationDivision(void)
{
	//code
	m_cRef = 1; //hardcoded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents); //increment global counter
}

//Implementation of CMultiplicationDivision Destructor
CMultiplicationDivision::~CMultiplicationDivision(void)
{
	//code
	InterlockedDecrement(&glNumberOfActiveComponents); //decrement global counter
}

//Implementation of CMultiplicationDivision's IUnknown's method
/**
  * IUnknown::QueryInterface
  * 
  * @param {REFIID}
  *		A reference to the interface identifier (IID) of the interface being queried for.
  *
  *	@param {void**} OUT PARAMETER
  *		The address of a pointer to an interface with the IID specified in the riid parameter.
 **/
HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void** ppv)
{
	//code
	if (riid == IID_IUnknown)
		*ppv = static_cast<IMultiplication *>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication *>(this);
	else if (riid == IID_IDivision)
		*ppv = static_cast<IDivision *>(this);
	else {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

//IUnknown::AddRef
ULONG CMultiplicationDivision::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

//IUnknown::Release
ULONG CMultiplicationDivision::Release(void)
{
	//code
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

//Implementation of IMultiplication's method
HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int num1, int num2, int *pMultiplication)
{
	//code
	*pMultiplication = num1 * num2;
	return(S_OK);
}

//Implementation of IDivision's method
HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int num1, int num2, int *pDivision)
{
	//code
	*pDivision = num1 / num2;
	return(S_OK);
}



//Implementation of CMultiplicationDivisionClassFactory's constructor
CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void)
{
	//code
	m_cRef = 1; //hardcoded initialization to anticipate possible failure of QueryInterface()
}

//Implementation of CMultiplicationDivisionClassFactory's destructor
CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void)
{

}

//Implementation of CMultiplicationDivisionClassFactory's IClassFactory's IUnknown's method
/**
  * IUnknown::QueryInterface
  *
  * @param {REFIID}
  *		A reference to the interface identifier (IID) of the interface being queried for.
  *
  *	@param {void**} OUT PARAMETER
  *		The address of a pointer to an interface with the IID specified in the riid parameter.
 **/
HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void** ppv)
{
	//code
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

//IUnknown::AddRef
ULONG CMultiplicationDivisionClassFactory::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

//IUnknown::Release
ULONG CMultiplicationDivisionClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}



//Implementation of CMultiplicationDivisionClassFactory's IClassFactory's method
/**
  * IClassFactory::CreateInstance()
  *
  * @param pUnkOuter {IUnknown}
  *		If the object created as part of an aggregate, specify a pointer to the controlling 
  *		IUnknown interface of the aggregate. Otherwise, this parameter must be NULL
  *
  * @param riid {REFIID}
  *		A reference to the identifier of the interface to be used to communicate with the newly 
  *		created object. If pUnkOuter is NULL, this parameter is generally the IID of the initializing
  *		interface; if pUnkOuter is non-NULL, riid must be IID_IUnknown.
  *
  * @param ppv {void**}
  *		The address of the pointer variable that receives the interface pointer requested in riid.
 **/
HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	//variable declarations
	CMultiplicationDivision *pCMultiplicationDivision = NULL;
	HRESULT hr;
	//code
	if (pUnkOuter != NULL)
	{
		return(CLASS_E_NOAGGREGATION);
	}
	//create the instance of component i.e. of CMultiplicationDivision class
	pCMultiplicationDivision = new CMultiplicationDivision;
	if (pCMultiplicationDivision == NULL)
	{
		return(E_OUTOFMEMORY);
	}
	//get the requested interface
	hr = pCMultiplicationDivision->QueryInterface(riid, ppv);
	pCMultiplicationDivision->Release(); //anticipate possible failure of QueryInterface
	return(hr);
}

//LockSerevr
/**
  * IClassFactory::LockServer()
  *
  * @param fLock {BOOL}
  *		If TRUE, increment the lock count, if FALSE, decrement the lock count
 **/
HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock)
{
	//code
	if (fLock)
	{
		InterlockedIncrement(&glNumberOfServerLocks);
	}
	else
	{
		InterlockedDecrement(&glNumberOfServerLocks);
	}
	return(S_OK);
}

//Implementation of Exported functions from this dll.
/**
  * @param rclsid {REFCLSID}
  *		The CLSID that will associate the correct data and code.
  *
  * @parm riid {REFIID}
  *		A reference to the identifier of the interface that the caller is to use to communicate with the
  *		class object. Usually, this is IID_IClassFactory (defined in the OLE headers as the interface
  *		identifier for IClassFactory).
  *
  *	@param ppv {void**}
  *		The address of a pointer variable that receives the interface pointer requested in riid.
 **/
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	//variable declarations
	CMultiplicationDivisionClassFactory *pCMultiplicationDivisionClassFactory = NULL;
	HRESULT hr;
	//code
	if (rclsid != CLSID_MultiplicationDivision)
	{
		return(CLASS_E_CLASSNOTAVAILABLE);
	}
	//create class factory
	pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;
	if (pCMultiplicationDivisionClassFactory == NULL)
	{
		return(E_OUTOFMEMORY);
	}
	hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);
	pCMultiplicationDivisionClassFactory->Release(); //anticipate possible failure of QueryInterface()
	return(hr);
}

//DllCanUnloadNow
/**
 * Determines whether the DLL that implements this function is in use. If not, the caller can unload the DLL from memory.
 *
 * OLE does not provide this function. DLLs that support the OLE Component Object Model(COM) should implement and export DllCanUnloadNow.
 *
 * OLE calls it only through a call to the CoFreeUnUsedLibraries() function.
 **/
extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	//code
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
	{
		return(S_OK);
	}
	else
	{
		return(S_FALSE);
	}
}
