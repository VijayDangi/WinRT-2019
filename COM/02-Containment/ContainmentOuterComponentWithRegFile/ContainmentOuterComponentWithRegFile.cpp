#include<Windows.h>
#include "ContainmentInnerComponentWithRegFile.h"
#include "ContainmentOuterComponentWithRegFile.h"

//CSumSubtract Component declaration
class CSumSubtract :public ISum, ISubtract, IMultiplication, IDivision
{
	private:
		long m_cRef;
		IMultiplication *m_pIMultiplication;  //===//
		IDivision *m_pIDivision;			//===//
	public:
		//constructor
		CSumSubtract(void);
		//destructor
		~CSumSubtract(void);
		
		//IUnknown specific method (inherited)
		HRESULT __stdcall QueryInterface(REFIID, void**);
		ULONG __stdcall AddRef(void);
		ULONG __stdcall Release(void);

		//ISum specific method declaration (inherited)
		HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
		//ISubtract specific method declaration (inherited)
		HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);
		//IMultiplication specific method declaration (inherited)
		HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);
		//IDivision specific method declaration (inherited)
		HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);

		//custome method for inner component creation
		HRESULT __stdcall InitializeInnerComponent(void);	//===//
};

//CSumSubtractClassFactory component declaration
class CSumSubtractClassFactory :public IClassFactory
{
	private:
		long m_cRef;
	public:
		//constructor
		CSumSubtractClassFactory(void);
		//destructor
		~CSumSubtractClassFactory(void);

		//IUnknown specific method declaration (inherited)
		HRESULT __stdcall QueryInterface(REFIID, void**);
		ULONG __stdcall AddRef(void);
		ULONG __stdcall Release(void);

		//IClassFactory specific method (inherited)
		HRESULT __stdcall CreateInstance(IUnknown*, REFIID, void**);
		HRESULT __stdcall LockServer(BOOL);
};

//global variable declaration
long glNumberOfActiveComponents = 0; //number of active components
long glNumberOfServerLocks = 0; //number of locks on this dll

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

//Implementation of CSumSubtract's Constructor Method
CSumSubtract::CSumSubtract(void)
{
	//code
	//initializeation of private data members
	m_pIMultiplication = NULL;
	m_pIDivision = NULL;
	m_cRef = 1; //hardcoded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents); //increment global counter
}

//Implementation of CSumSubtract's Destructor
CSumSubtract::~CSumSubtract(void)
{
	//code
	InterlockedDecrement(&glNumberOfActiveComponents);
	if (m_pIMultiplication)
	{
		m_pIMultiplication->Release();
		m_pIMultiplication = NULL;
	}
	if (m_pIDivision)
	{
		m_pIDivision->Release();
		m_pIDivision = NULL;
	}
}


//Implementation of CSumSubtract's IUnknown's methods
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
	//code
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract *>(this);
	else if (riid == IID_IMultiplication)
		*ppv = static_cast<IMultiplication *>(this);
	else if (riid == IID_IDivision)
		*ppv = static_cast<IDivision *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

//IUnknown::AddRef()
ULONG CSumSubtract::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

//IUnknown::Release()
ULONG CSumSubtract::Release(void)
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

//Implementation of ISum's Methods
HRESULT CSumSubtract::SumOfTwoIntegers(int num1, int num2, int *pSum)
{
	//code
	*pSum = num1 + num2;
	return(S_OK);
}

//Implementation of ISubtract's Method
HRESULT CSumSubtract::SubtractionOfTwoIntegers(int num1, int num2, int *pSubtraction)
{
	//code
	*pSubtraction = num1 - num2;
	return(S_OK);
}

//Implementation of IMultiplication's Method
HRESULT CSumSubtract::MultiplicationOfTwoIntegers(int num1, int num2, int *pMultiplication)
{
	//code
	//delegate to inner component
	m_pIMultiplication->MultiplicationOfTwoIntegers(num1, num2, pMultiplication);
	return(S_OK);
}

//Implementation of IDivision's Method
HRESULT CSumSubtract::DivisionOfTwoIntegers(int num1, int num2, int *pDivision)
{
	//code
	//delegate to inner component
	m_pIDivision->DivisionOfTwoIntegers(num1, num2, pDivision);
	return(S_OK);
}

//IniializeInnerComponent
HRESULT CSumSubtract::InitializeInnerComponent(void)
{
	HRESULT hr;
	/**
	  * CoCreateInstance(REFCLSID rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContextm, REFIID riid, LPVOID *ppv)
	  *
	  * @param rclsid {REFCLSID}
	  *		The CLSID associated with the dataand code that will be used to create the object.
	  *
	  * @param pUnkOuter {LPUNKNOWN}
	  *		If NULL, indicates that the object os not being created as part of an aggregate.
	  *		If non-NULL pointer to the aggregate object's IUnknown interface.
	  *
	  * @param dwClsContext {DWORD}
	  *		Context in which the code that manages the newly created object will run.
	  *
	  * @param riid {REFIID}
	  *		A reference to the identifier of the interface to be used to communicate with the object.
	  *
	  * @param ppv {LPVOID*} / {void**}
	  *		Address of pointer variable that receives the interface pointer requested in riid.
	 **/
	hr = CoCreateInstance(CLSID_MultiplicationDivision, NULL, CLSCTX_INPROC_SERVER, 
							IID_IMultiplication, (void**)&m_pIMultiplication);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IMultiplication Interface can not be obtained from Inner Component."), TEXT("ERROR"), MB_OK);
		return(E_FAIL);
	}

	hr = m_pIMultiplication->QueryInterface(IID_IDivision, (void**)&m_pIDivision);

	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("IDivision Interface can not be obtained from Inner Component."), TEXT("ERROR"), MB_OK);
		return(E_FAIL);
	}

	return(S_OK);
}

//Implementation of CSumSubtractClassFactory's Constructor
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	//code
	m_cRef = 1; //hardcoded initialization to anticipate possible failure of QueryInterface()
}

//Implementation of CSumSubtractClassFactory's destructor
CSumSubtractClassFactory::~CSumSubtractClassFactory(void)
{

}

//Implementation of CSumSubtractClassFactory's IClassFactory's IUnknown's method
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
	//code
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else
	{
		*ppv = NULL;	//DECIPLINE
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

//IUnknown::AddRef()
ULONG CSumSubtractClassFactory::AddRef(void)
{
	//code
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

//IUnknown::Release()
ULONG CSumSubtractClassFactory::Release(void)
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

//Implementation of CSumSubtractClassFactory's IClassFactory's Methods
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

	if (pUnkOuter != NULL)
	{
		return(CLASS_E_NOAGGREGATION);
	}

	//create the instance of component i.e. of CSumSubtract class
	pCSumSubtract = new CSumSubtract;
	if (pCSumSubtract == NULL)
	{
		return (E_OUTOFMEMORY);
	}

	//initialize the inner component
	hr = pCSumSubtract->InitializeInnerComponent();
	
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("FAILED To Initialize Inner Component"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		pCSumSubtract->Release();
		return(hr);
	}

	//get the requested interface
	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release(); //anticipate possible failure of QueryInterface()
	return(hr);
}

//LockSerevr
/**
  * IClassFactory::LockServer()
  *
  * @param fLock {BOOL}
  *		If TRUE, increment the lock count, if FALSE, decrement the lock count
 **/
HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
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
	CSumSubtractClassFactory *pCSumSubtractClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_SumSubtract)
	{
		return(CLASS_E_CLASSNOTAVAILABLE);
	}
	//create class factory
	pCSumSubtractClassFactory = new CSumSubtractClassFactory;
	if (pCSumSubtractClassFactory == NULL)
	{
		return(E_OUTOFMEMORY);
	}

	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);
	pCSumSubtractClassFactory->Release(); //anticipate possible failure of QueryInterface()

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
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
	{
		return(S_OK);
	}
	else
	{
		return(S_FALSE);
	}
}
