#include<stdio.h>
#include<Windows.h>
#include "AggregationInnerComponentWithRegFile.h"
#include "AggregationOuterComponentWithRegFile.h"

//declaration of class
class CSumSubtract: public ISum, ISubtract
{
	private:
		long m_cRef;
		IUnknown *m_pIUnknownInner;
		IMultiplication *m_pIMultiplication;
		IDivision *m_pIDivision;
	public:
		//constructor
		CSumSubtract(void);
		//destructor
		~CSumSubtract(void);
		//IUnknow's specific methods (inherited)
		HRESULT __stdcall QueryInterface(REFIID, void**);
		ULONG __stdcall AddRef(void);
		ULONG __stdcall Release(void);
		//ISum specific methods (inherited)
		HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
		//ISubtract's specific methods (inherited)
		HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);
		// custom method for inner component creation
		HRESULT __stdcall InitializeInnerComponent(void);
};

class CSumSubtractClassFactory: public IClassFactory
{
	private:
		long m_cRef;
	public:
		//constructor
		CSumSubtractClassFactory(void);
		//destructor
		~CSumSubtractClassFactory(void);
		//IUnknow's specific methods (inherited)
		HRESULT __stdcall QueryInterface(REFIID, void**);
		ULONG __stdcall AddRef(void);
		ULONG __stdcall Release(void);
		//IClassFactory's specific methods (inherited)
		HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void**);
		HRESULT __stdcall LockServer(BOOL);
};

//global variables
long glNumberOfActiveComponents = 0; //number of active components
long glNumberOfServerLocks = 0; //number of locks on this Dll

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

//CSumSubtract Methods Implementation
CSumSubtract::CSumSubtract(void)
{
	m_pIUnknownInner = NULL;
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;
	m_cRef = 1; //hardcoded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents);
}

//destructor
CSumSubtract::~CSumSubtract(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents);
	if(m_pIMultiplication)
	{
		m_pIMultiplication->Release();
		m_pIMultiplication = NULL;
	}
	if(m_pIDivision)
	{
		m_pIDivision->Release();
		m_pIDivision = NULL;
	}
	if(m_pIUnknownInner)
	{
		m_pIUnknownInner->Release();
		m_pIUnknownInner = NULL;
	}
}

//IUnknow's method
//QueryInterface
/**
  * IUnknown::QueryInterface
  *
  * @param {REFIID}
  *		A reference to the interface identifier (IID) of the interface being queried for.
  *
  *	@param {void**} OUT PARAMETER
  *		The address of a pointer to an interface with the IID specified in the riid parameter.
 **/
HRESULT CSumSubtract::QueryInterface(REFIID riid, void **ppv)
{
	if(riid == IID_IUnknown)
		*ppv = static_cast<ISum *>(this);
	else if(riid == IID_ISum)
		*ppv = static_cast<ISum *>(this);
	else if(riid == IID_ISubtract)
		*ppv = static_cast<ISubtract *>(this);
	else if(riid == IID_IMultiplication)
		return(m_pIUnknownInner->QueryInterface(riid, ppv));
	else if(riid == IID_IDivision)
		return(m_pIUnknownInner->QueryInterface(riid, ppv));
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

//AddRef()
ULONG CSumSubtract::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

//Release
ULONG CSumSubtract::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if(m_cRef == 0)
	{
		delete(this);
		return (0);
	}
	return(m_cRef);
}

//ISum methods
HRESULT CSumSubtract::SumOfTwoIntegers(int iNum1, int iNum2, int* iSum)
{
	*iSum = iNum1 + iNum2;
	return(S_OK);
}

//ISubtract methods
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int iNum1, int iNum2, int *iSubtraction)
{
	*iSubtraction = iNum1 - iNum2;
	return(S_OK);
}

//InitializeInnerComponent
HRESULT CSumSubtract::InitializeInnerComponent(void)
{
	HRESULT hr;
	hr = CoCreateInstance(CLSID_MultiplicationDivision, reinterpret_cast<IUnknown *>(this), CLSCTX_INPROC_SERVER, IID_IUnknown, (void**) &m_pIUnknownInner);
	if(FAILED(hr))
	{
		//MessageBox(NULL, TEXT("IUnknown Interface can not be obtained from Inner Component"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		return(E_FAIL);
	}
	
	hr = m_pIUnknownInner->QueryInterface(IID_IMultiplication, (void **) &m_pIMultiplication);
	if(FAILED(hr))
	{
		//MessageBox(NULL, TEXT("IMultiplication Interface can not be obtained from Inner Component"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		m_pIUnknownInner->Release();
		m_pIUnknownInner = NULL;
		return(E_FAIL);
	}
	
	hr = m_pIUnknownInner->QueryInterface(IID_IDivision, (void**) &m_pIDivision);
	if(FAILED(hr))
	{
		//MessageBox(NULL, TEXT("IDivision Interface can not be obtained from Inner Component"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		m_pIUnknownInner->Release();
		m_pIUnknownInner = NULL;
		return(E_FAIL);
	}
	return(S_OK);
}


//CSumSubtractClassFactory methods Implementation
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	m_cRef = 1; //hardcoded initialization to anticipate possible failure of QueryInterface()
}

//destructor
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{
	
}

//IUnknown's specific methods
/**
  * IUnknown::QueryInterface
  *
  * @param {REFIID}
  *		A reference to the interface identifier (IID) of the interface being queried for.
  *
  *	@param {void**} OUT PARAMETER
  *		The address of a pointer to an interface with the IID specified in the riid parameter.
 **/
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void** ppv)
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

//AddRef
ULONG CSumSubtractClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(S_OK);
}

//Release
ULONG CSumSubtractClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if(m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}

//IClassFactory's methods Implementation
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
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	CSumSubtract *pCSumSubtract = NULL;
	HRESULT hr;
	
	if(pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);
	
	//create instance
	pCSumSubtract = new CSumSubtract;
	if(pCSumSubtract == NULL)
		return(E_OUTOFMEMORY);
	
	//initialize inner component
	hr = pCSumSubtract->InitializeInnerComponent();
	if(FAILED(hr))
	{
		//MessageBox(NULL, TEXT("Failed to Initialize Inner Component"), TEXT("Error"), MB_OK | MB_ICONERROR);
		pCSumSubtract->Release();
		return(hr);
	}
	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release(); //release possible failure of QueryInterface()
	return(hr);
}

//LockServer
HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	if(fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}




//Implemetation of Exported Functions From This Dll
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
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppv)
{
	//FILE *fp = fopen("out.log","a+");
	//fprintf(fp, "Outer ==> IN ==> DllGetClassObject()\n");
	
	CSumSubtractClassFactory *pCSumSubtractClassFactory = NULL;
	HRESULT hr;
	
	if(rclsid != CLSID_CSumSubtract)
		return(CLASS_E_CLASSNOTAVAILABLE);
	
	//create instance
	pCSumSubtractClassFactory = new CSumSubtractClassFactory;
	if(pCSumSubtractClassFactory == NULL)
		return(E_OUTOFMEMORY);
	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release(); // anticipate possible failure of QueryInterface
	
		//fprintf(fp, "Outer ==> Out ==> DllGetClassObject()\n");
	//fclose(fp);
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
HRESULT __stdcall DllCanUnloadNow(void)
{
	if( (glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0) )
		return(S_OK);
	else
		return(S_FALSE);
}
