#include<Windows.h>
#include "ClassFactoryDllServerWithRegFile.h"

//class declaration
class CSumSubtract : public ISum, ISubtract
{
	private:
		long m_cRef;

	public:
		//constructor
		CSumSubtract(void);
		//destructor
		~CSumSubtract(void);

		//IUnknown specific method declarations (inherited)
		HRESULT __stdcall QueryInterface(REFIID, void **);
		ULONG   __stdcall AddRef(void);
		ULONG   __stdcall Release(void);

		//ISum specific method declarations (inherited)
		HRESULT __stdcall SumOfTwoInteger(int, int, int*);

		//ISubtract specific method declarations (inherited)
		HRESULT __stdcall SubtractOfTwoInteger(int, int, int*);
};

// class CSumSubtractClassFactory
class CSumSubtractClassFactory : public IClassFactory
{
	private:
		long m_cRef;

	public:
		//constructor
		CSumSubtractClassFactory(void);
		//destructor
		~CSumSubtractClassFactory(void);

		//IUnknown specific method declarations (inherited)
		HRESULT __stdcall QueryInterface(REFIID, void**);
		ULONG   __stdcall AddRef(void);
		ULONG   __stdcall Release(void);

		//IClassFactory specific method declarations (inherited)
		HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void**);
		HRESULT __stdcall LockServer(BOOL);
};

//global variable declarations
	//g=> global, l=> long 
long glNumberOfActiveComponents = 0;  //number of active components
long glNumberOfServerLocks = 0; //number of locks on this dll

//DllMain
BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved)
{
	//code
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			break;
	}

	return (TRUE);
}

//Implementation of CSumSubtract's Constructor Method
CSumSubtract :: CSumSubtract(void)
{
	m_cRef = 1; //hardcoded initialization to anticipate possible failure of QueryInterface()
	InterlockedIncrement(&glNumberOfActiveComponents); //increment global counter
}

//Implementation of CsumSubtract's destructor method
CSumSubtract :: ~CSumSubtract(void)
{
	InterlockedDecrement(&glNumberOfActiveComponents); //decrement global counter
}

//Implementation of CSumSubtract's IUnknown's methods
HRESULT CSumSubtract :: QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISum)
		*ppv = static_cast<ISum *>(this);
	else if (riid == IID_ISubtract)
		*ppv = static_cast<ISubtract *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}

	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CSumSubtract::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubtract :: Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}


//Implementation of ISum's Methods
HRESULT CSumSubtract::SumOfTwoInteger(int num1, int num2, int *result)
{
	*result = num1 + num2;
	return(S_OK);
}

//Implementation of ISubtract's Methods
HRESULT CSumSubtract::SubtractOfTwoInteger(int num1, int num2, int *result)
{
	*result = num1 - num2;
	return(S_OK);
}


//Implementation of CSumSubtractClassFactory's constructor
CSumSubtractClassFactory::CSumSubtractClassFactory(void)
{
	m_cRef = 1; //hardcoded initialization to anticipate possible failure of QueryInterface()
}

//Implementation of CSumSubtractClassfactory's destructor
CSumSubtractClassFactory ::~CSumSubtractClassFactory(void)
{
}

//Implementation of CSumSubtractClassFactory's IClassFactory's IUnknown's methods
HRESULT CSumSubtractClassFactory::QueryInterface(REFIID riid, void **ppv)
{
	if (riid == IID_IUnknown)
		*ppv = static_cast<IClassFactory *>(this);
	else if (riid == IID_IClassFactory)
		*ppv = static_cast<IClassFactory *>(this);
	else
	{
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown *>(*ppv)->AddRef();
	return(S_OK);
}

ULONG CSumSubtractClassFactory::AddRef(void)
{
	InterlockedIncrement(&m_cRef);
	return(m_cRef);
}

ULONG CSumSubtractClassFactory::Release(void)
{
	InterlockedDecrement(&m_cRef);
	if (m_cRef == 0)
	{
		delete(this);
		return(0);
	}
	return(m_cRef);
}


//Implementation of CSumSubtractClassFactory's IClassFactory's Methods
HRESULT CSumSubtractClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void **ppv)
{
	CSumSubtract *pCSumSubtract = NULL;
	HRESULT hr;

	if (pUnkOuter != NULL)
		return(CLASS_E_NOAGGREGATION);

	//create the instance of component i.e. of CSumSubtract class
	pCSumSubtract = new CSumSubtract;

	if (pCSumSubtract == NULL)
		return (E_OUTOFMEMORY);

	//get the requested interface
	hr = pCSumSubtract->QueryInterface(riid, ppv);
	pCSumSubtract->Release(); //anticipate possible failure of QueryInterface()

	return(hr);
}

HRESULT CSumSubtractClassFactory::LockServer(BOOL fLock)
{
	if (fLock)
		InterlockedIncrement(&glNumberOfServerLocks);
	else
		InterlockedDecrement(&glNumberOfServerLocks);
	return(S_OK);
}



//Implementation of Exported Functions From this Dll
extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
{
	CSumSubtractClassFactory * pCSumSubtractClassFactory = NULL;
	HRESULT hr;

	if (rclsid != CLSID_SumSubtract)
		return(CLASS_E_CLASSNOTAVAILABLE);

	//create classs factory
	pCSumSubtractClassFactory = new CSumSubtractClassFactory;
	if (pCSumSubtractClassFactory == NULL)
		return (E_OUTOFMEMORY);

	hr = pCSumSubtractClassFactory->QueryInterface(riid, ppv);	//the value of m_cRef become 2
	pCSumSubtractClassFactory->Release();	//anticipate possible failure of QueryInterface //change valueof m_cRef to 1

	return(hr);
}

extern "C" HRESULT __stdcall DllCanUnloadNow(void)
{
	if ((glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0))
		return(S_OK);
	else
		return(S_FALSE);
}

