#include<stdio.h>
#include<Windows.h>

#include "AggregationInnerComponentWithReg//FILE.h"

//interface declaration (for internal use only) //For METHOD COLORING with IUnknown
interface INoAggregationIUnknown
{
	virtual HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void**) = 0;
	virtual ULONG __stdcall AddRef_NoAggregation(void) = 0;
	virtual ULONG __stdcall Release_NoAggregation(void) = 0;
};
/**
 * combaseapi.h
 *
 * #define   __STRUCT__   struct
 * #define   interface    __STRUCT__
**/

#pragma region CLASS_DECLARATIONS
//class declarations
class CMultiplicationDivision : public INoAggregationIUnknown, IMultiplication, IDivision
{
	private:
		long m_cRef;
		IUnknown *m_pIUnknownOuter; 
		//to store the IUnknown of Outer Component
		//(for hand-shaking(binary contract) between outer and inner component)
	
	public:
		//constructor
		CMultiplicationDivision(IUnknown *);
		//destructor
		~CMultiplicationDivision(void);
		
		//Aggregation Supported IUnknown specific methods (inherited)
		HRESULT __stdcall QueryInterface(REFIID, void**);
		ULONG __stdcall AddRef(void);
		ULONG __stdcall Release(void);
		
		//Aggregation NoSupported IUnknown specific methods (inherited)
		HRESULT __stdcall QueryInterface_NoAggregation(REFIID, void**);
		ULONG __stdcall AddRef_NoAggregation(void);
		ULONG __stdcall Release_NoAggregation(void);
		
		//IMultiplication specific method declarations (inherited)
		HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*);
		
		//IDivision specific method declarations (inherited)
		HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*);
};

class CMultiplicationDivisionClassFactory : public IClassFactory
{
	private:
		long m_cRef;
		
	public:
		//constructor
		CMultiplicationDivisionClassFactory(void);
		//destructor
		~CMultiplicationDivisionClassFactory(void);
		
		//IClassFactory's IUnknown's specific methods (inherited)
		HRESULT __stdcall QueryInterface(REFIID, void**);
		ULONG __stdcall AddRef(void);
		ULONG __stdcall Release(void);
		
		//IClassFactory's specific methods (inherited)
		HRESULT __stdcall CreateInstance(IUnknown *, REFIID, void**);
		HRESULT __stdcall LockServer(BOOL);
};

#pragma endregion CLASS_DECLARATIONS

#pragma region GLOBAL_VARIABLES_DEFINE
//global variable
long glNumberOfActiveComponents = 0; //number of active components
long glNumberOfServerLocks = 0; //number of locks on this dll

#pragma endregion GLOBAL_VARIABLES_DEFINE

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
	//FILE *fp = fopen("out.log","a+");
	//fprintf(fp, "INNER ==> IN ==> DllMain()\n");
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


#pragma region CMultiplicationDivision_Methods_Defination
	//Implementation of CMultiplicationDivision's constructor
	CMultiplicationDivision::CMultiplicationDivision(IUnknown *pIUnknownOuter)
	{
		//FILE *fp = fopen("out.log","a+");
		//fprintf(fp, "INNER ==> IN ==> CMultiplicationDivision()\n");
		//code
		m_cRef = 1;
		
		InterlockedIncrement(&glNumberOfActiveComponents); //increment global count
		
		if(pIUnknownOuter != NULL)
		{
			m_pIUnknownOuter = pIUnknownOuter;
		}
		else
		{
			m_pIUnknownOuter = reinterpret_cast<IUnknown *>(static_cast<INoAggregationIUnknown *>(this));
		}
		
		//fprintf(fp, "INNER ==> OUT ==> CMultiplicationDivision()\n");
		//fclose(fp);
	}

	//Implementation of CMultiplicationDivision's destructor
	CMultiplicationDivision::~CMultiplicationDivision(void)
	{
		//FILE *fp = fopen("out.log","a+");
		//fprintf(fp, "INNER ==> IN ==> ~CMultiplicationDivision()\n");
		//code
		InterlockedDecrement(&glNumberOfActiveComponents);
		//fprintf(fp, "INNER ==> OUT ==> ~CMultiplicationDivision()\n");
		//fclose(fp);
	}
	
	//CMultiplicationDivision's IUnknown's methods defination (inherited)
	/**
	  * IUnknown::QueryInterface
	  *
	  * @param {REFIID}
	  *		A reference to the interface identifier (IID) of the interface being queried for.
	  *
	  *	@param {void**} OUT PARAMETER
	  *		The address of a pointer to an interface with the IID specified in the riid parameter.
	 **/
	HRESULT CMultiplicationDivision::QueryInterface(REFIID riid, void **ppv)
	{
		//FILE *fp = fopen("out.log","a+");
		//fprintf(fp, "INNER ==> IN ==> CMultiplicationDivision::QueryInterface()\n");
		HRESULT hr;
		//code
		
		hr = m_pIUnknownOuter->QueryInterface(riid, ppv);
		//fprintf(fp, "INNER ==> OUT ==> CMultiplicationDivision::QueryInterface()\n");
		//fclose(fp);
		
		return(hr);
	}
	
	//AddRef
	ULONG CMultiplicationDivision::AddRef(void)
	{
		//FILE *fp = fopen("out.log","a+");
		//fprintf(fp, "INNER ==> IN ==> CMultiplicationDivision::AddRef()\n");
		HRESULT hr = m_pIUnknownOuter->AddRef();
		//fprintf(fp, "INNER ==> OUT ==> CMultiplicationDivision::AddRef()\n");
		//fclose(fp);
		return(hr);
	}
	
	//Release
	ULONG CMultiplicationDivision::Release(void)
	{
		//FILE *fp = fopen("out.log","a+");
		//fprintf(fp, "INNER ==> IN ==> CMultiplicationDivision::Release()\n");
		HRESULT hr = m_pIUnknownOuter->Release();
		//fprintf(fp, "INNER ==> OUT ==> CMultiplicationDivision::Release()\n");
		//fclose(fp);
		return(hr);
	}
	
	//CMultiplicationDivision's INoAggregationIUnknown's method (inherited)
	HRESULT CMultiplicationDivision::QueryInterface_NoAggregation(REFIID riid, void **ppv)
	{
		//FILE *fp = fopen("out.log","a+");
		//fprintf(fp, "INNER ==> IN ==> CMultiplicationDivision::QueryInterface_NoAggregation()\n");
		//code
		if(riid == IID_IUnknown)
			*ppv = static_cast<INoAggregationIUnknown *>(this);
		else if(riid == IID_IMultiplication)
			*ppv = static_cast<IMultiplication *>(this);
		else if(riid == IID_IDivision)
			*ppv = static_cast<IDivision *>(this);
		else
		{
			//fprintf(fp, "INNER ==> 1.OUT ==> CMultiplicationDivision::QueryInterface_NoAggregation()\n");
			*ppv = NULL;
			//fclose(fp);
			return(E_NOINTERFACE);
		}
		reinterpret_cast<IUnknown *>(*ppv)->AddRef();
		//fprintf(fp, "INNER ==> 2.OUT ==> CMultiplicationDivision::QueryInterface_NoAggregation()\n");
		//fclose(fp);
		return (S_OK);
	}
	
	//AddRef_NoAggregation
	ULONG CMultiplicationDivision::AddRef_NoAggregation(void)
	{
		//FILE *fp = fopen("out.log","a+");
		//fprintf(fp, "INNER ==> IN ==> CMultiplicationDivision::AddRef_NoAggregation()\n");
		//code
		InterlockedIncrement(&m_cRef);
		//fprintf(fp, "INNER ==> OUT ==> CMultiplicationDivision::AddRef_NoAggregation()\n");
		//fclose(fp);
		return(m_cRef);
	}
	
	//Release_NoAggregation
	ULONG CMultiplicationDivision::Release_NoAggregation(void)
	{
		//FILE *fp = fopen("out.log","a+");
		//fprintf(fp, "INNER ==> IN ==> CMultiplicationDivision::Release_NoAggregation()\n");
		//code
		InterlockedDecrement(&m_cRef);
		if(m_cRef == 0)
		{
			delete(this);
			//fprintf(fp, "INNER ==> 2.OUT ==> CMultiplicationDivision::Release_NoAggregation()\n");
			//fclose(fp);
			return(0);
		}
		//fprintf(fp, "INNER ==> 1.OUT ==> CMultiplicationDivision::Release_NoAggregation()\n");
		//fclose(fp);
		return(m_cRef);
	}
	
	//IMultiplication's specific method
	HRESULT CMultiplicationDivision::MultiplicationOfTwoIntegers(int iNum1, int iNum2, int *iMultiplication)
	{
		//FILE *fp = fopen("out.log","a+");
		//fprintf(fp, "INNER ==> IN ==> CMultiplicationDivision::MultiplicationOfTwoIntegers()\n");
		*iMultiplication = iNum1 * iNum2;
		//fprintf(fp, "INNER ==> OUT ==> CMultiplicationDivision::MultiplicationOfTwoIntegers()\n");
		//fclose(fp);
		return(S_OK);
	}
	
	//IDiviosion's specific method
	HRESULT CMultiplicationDivision::DivisionOfTwoIntegers(int iNum1, int iNum2, int *iDivision)
	{
		//FILE *fp = fopen("out.log","a+");
		//fprintf(fp, "INNER ==> IN ==> CMultiplicationDivision::DivisionOfTwoIntegers()\n");
		*iDivision = iNum1 / iNum2;
		//fprintf(fp, "INNER ==> OUT ==> CMultiplicationDivision::DivisionOfTwoIntegers()\n");
		//fclose(fp);
		return(S_OK);
	}
	
#pragma endregion CMultiplicationDivision_Methods_Defination


#pragma region CMultiplicationDivisionClassFactory_Method_Implementation

	//constructor
	CMultiplicationDivisionClassFactory::CMultiplicationDivisionClassFactory(void)
	{
		//FILE *fp = fopen("out.log","a+");
		//fprintf(fp, "INNER ==> IN ==> CMultiplicationDivisionClassFactory()\n");
		m_cRef = 1;
		//fprintf(fp, "INNER ==> OUT ==> CMultiplicationDivisionClassFactory()\n");
		//fclose(fp);
		
	}
	
	//destructor
	CMultiplicationDivisionClassFactory::~CMultiplicationDivisionClassFactory(void)
	{
		//FILE *fp = fopen("out.log","a+");
		//fprintf(fp, "INNER ==> IN ==> ~CMultiplicationDivisionClassFactory()\n");
		//fprintf(fp, "INNER ==> OUT ==> ~CMultiplicationDivisionClassFactory()\n");
		
		//fclose(fp);
		//code
	}
	
	//QueryInterface
	HRESULT CMultiplicationDivisionClassFactory::QueryInterface(REFIID riid, void** ppv)
	{
		//FILE *fp = fopen("out.log","a+");
		//fprintf(fp, "INNER ==> IN ==> CMultiplicationDivisionClassFactory::QueryInterface()\n");
		if(riid == IID_IUnknown)
			*ppv = static_cast<IClassFactory *>(this);
		else if(riid == IID_IClassFactory)
			*ppv = static_cast<IClassFactory *>(this);
		else
		{
			//fprintf(fp, "INNER ==> 2.OUT ==> CMultiplicationDivisionClassFactory::QueryInterface()\n");
			//fclose(fp);
			*ppv = NULL;
			return(E_NOINTERFACE);
		}
		
		reinterpret_cast<IUnknown *>(*ppv)->AddRef();
		
		//fprintf(fp, "INNER ==> 1.OUT ==> CMultiplicationDivisionClassFactory::QueryInterface()\n");
		//fclose(fp);
		return(S_OK);
	}
	
	//AddRef
	ULONG CMultiplicationDivisionClassFactory::AddRef(void)
	{
		//FILE *fp = fopen("out.log","a+");
		//fprintf(fp, "INNER ==> IN ==> CMultiplicationDivisionClassFactory::AddRef()\n");
		InterlockedIncrement(&m_cRef);
		//fprintf(fp, "INNER ==> OUT ==> CMultiplicationDivisionClassFactory::AddRef()\n");
		//fclose(fp);
		return(m_cRef);
	}
	
	//Release
	ULONG CMultiplicationDivisionClassFactory::Release(void)
	{
		
		//FILE *fp = fopen("out.log","a+");
		//fprintf(fp, "INNER ==> IN ==> CMultiplicationDivisionClassFactory::Release()\n");
		InterlockedDecrement(&m_cRef);
		if(m_cRef == 0)
		{
			delete(this);
			//fprintf(fp, "INNER ==> 1.OUT ==> CMultiplicationDivisionClassFactory::Release()\n");
			//fclose(fp);
			return(0);
		}
		//fprintf(fp, "INNER ==> 2.OUT ==> CMultiplicationDivisionClassFactory::Release()\n");
		//fclose(fp);
		return(m_cRef);
	}
	
	//CreateInstance
	HRESULT CMultiplicationDivisionClassFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void** ppv)
	{
		//FILE *fp = fopen("out.log","a+");
		//fprintf(fp, "INNER ==> IN ==> CMultiplicationDivisionClassFactory::CreateInstance()\n");
		
		CMultiplicationDivision *pCMultiplicationDivision;
		HRESULT hr;
		
		if( (pUnkOuter != NULL) && (riid != IID_IUnknown) )
		{
			//fprintf(fp, "INNER ==> 3.OUT ==> CMultiplicationDivisionClassFactory::CreateInstance()\n");
			//fclose(fp);
			return(CLASS_E_NOAGGREGATION);
		}
		
		//create instance of component i.e. CMultiplicationDivision
		pCMultiplicationDivision = new CMultiplicationDivision(pUnkOuter);
		if(pCMultiplicationDivision == NULL)
		{
			//fprintf(fp, "INNER ==> 2.OUT ==> CMultiplicationDivisionClassFactory::CreateInstance()\n");
			//fclose(fp);
			return(E_OUTOFMEMORY);
		}
		
		//get requested  interface
		hr = pCMultiplicationDivision->QueryInterface_NoAggregation(riid, ppv);
		pCMultiplicationDivision->Release_NoAggregation(); //anticipate possible failure of QueryInterface
		//fprintf(fp, "INNER ==> 1.OUT ==> CMultiplicationDivisionClassFactory::CreateInstance()\n");
		//fclose(fp);
		return(hr);
	}
	
	//LockServer
	HRESULT CMultiplicationDivisionClassFactory::LockServer(BOOL fLock)
	{
		//FILE *fp = fopen("out.log","a+");
		//fprintf(fp, "INNER ==> IN ==> CMultiplicationDivisionClassFactory::LockServer()\n");
		if(fLock)
			InterlockedIncrement(&glNumberOfServerLocks);
		else
			InterlockedDecrement(&glNumberOfServerLocks);
		
		//fprintf(fp, "INNER ==> OUT ==> CMultiplicationDivisionClassFactory::LockServer()\n");
		//fclose(fp);
		return(S_OK);
	}

#pragma endregion CMultiplicationDivisionClassFactory_Method_Implementation


#pragma region ExportFunctions
	//DllGetClassObject
	extern "C" HRESULT __stdcall DllGetClassObject(REFCLSID rclsid, REFIID riid, void **ppv)
	{
		//FILE *fp = fopen("out.log","a+");
		//fprintf(fp, "INNER ==> IN ==> DllGetClassObject()\n");
		CMultiplicationDivisionClassFactory *pCMultiplicationDivisionClassFactory = NULL;
		HRESULT hr;
		
		if(rclsid != CLSID_MultiplicationDivision)
		{
			//fprintf(fp, "INNER ==> 3.OUT ==> DllGetClassObject()\n");
			//fclose(fp);
			return(CLASS_E_CLASSNOTAVAILABLE);
		}
		
		//create class factory
		pCMultiplicationDivisionClassFactory = new CMultiplicationDivisionClassFactory;
		
		if(pCMultiplicationDivisionClassFactory == NULL)
		{
			//fprintf(fp, "INNER ==> 2.IN ==> DllGetClassObject()\n");
			//fclose(fp);
			return(E_OUTOFMEMORY);
		}
		
		hr = pCMultiplicationDivisionClassFactory->QueryInterface(riid, ppv);
		pCMultiplicationDivisionClassFactory->Release(); //anticipate possible failure of QueryInterface()
		//fprintf(fp, "INNER ==> 1.IN ==> DllGetClassObject()\n");
		//fclose(fp);
		return (hr);
	}
	
	//DllCanUnloadNow
	extern "C" HRESULT __stdcall DllCanUnloadNow(void)
	{
		//FILE *fp = fopen("out.log","a+");
		//fprintf(fp, "INNER ==> IN ==> DllCanUnloadNow()\n");
		if( (glNumberOfActiveComponents == 0) && (glNumberOfServerLocks == 0) )
		{
			//fprintf(fp, "INNER ==> 2.OUT ==> DllCanUnloadNow()\n");
			//fclose(fp);
			return(S_OK);
		}
		else
		{
			//fprintf(fp, "INNER ==> 1.OUT ==> DllCanUnloadNow()\n");
			//fclose(fp);
			return(S_FALSE);
		}
	}
	
#pragma endregion ExportFunctions
