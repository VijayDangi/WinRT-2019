#include <Windows.h>
#include "HeaderForClientOfAggregationComponentWithRegFile.h"

//callback WndProc declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//global variables
ISum *pISum = NULL;
ISubtract *pISubtract = NULL;
IMultiplication *pIMultiplication = NULL;
IDivision *pIDivision = NULL;

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("COM Aggragation Client");
	HRESULT hr;
	
	//Com initialization
	/**
	  * Initialize the COM library on the current thread and identifies the concurrency model as 
	  *	single-thread apartment(STA).
	  * You need to initialize the COM library on a thread before you call any of the library functions (except CoGetMalloc).
	  *
	  *	@param pvReserved {LPVOID}
	  *		This parameter is reserved and must be NULL
	 **/
	hr = CoInitialize(NULL);
	if(FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM library can not be Initialized.\nProgram will Now exit."), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		exit(0);
	}
	//Wndclassex initialization
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	
	//register class
	RegisterClassEx(&wndclass);
	//create window in memory
	hwnd = CreateWindow(AppName, TEXT("Client of COM Dll Serevr"),
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						CW_USEDEFAULT,
						NULL,
						NULL,
						hInstance,
						NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);
	//message loop
	while(GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	//COM Un-initialization
	/**
	  * Closes the COM library on the current thread, unloads all DLLs loaded by the thread.
	 **/
	CoUninitialize();
	
	return((int)msg.wParam);
}

//WndProc
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//function declaration
	void SafeInterfaceRelease(void);
	//variable 
	HRESULT hr;
	
	int iNum1, iNum2, iResult;
	TCHAR str[255];
	
	//code
	switch(iMsg)
	{
		case WM_CREATE:
		{
			//case I
			MessageBox(hwnd, TEXT("CASE I =:> Obtained ISum (outer component)"), TEXT("CASE - I"),  MB_OK | MB_ICONINFORMATION);
			hr = CoCreateInstance(CLSID_CSumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**) &pISum);
			if(FAILED(hr))
			{
				MessageBox(NULL, TEXT("ISUM Interface can not be obtained"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
				DestroyWindow(hwnd);
			}
			//initialize argument hardcoded
			iNum1 = 65;
			iNum2 = 45;
			
			MessageBox(hwnd, TEXT("ISum Obtained"), TEXT("INFO"), MB_OK | MB_ICONINFORMATION);
			//call SumOfTwoIntegers()
			pISum->SumOfTwoIntegers(iNum1, iNum2, &iResult);
			wsprintf(str, TEXT("Sum of %d and %d is %d"), iNum1, iNum2, iResult);
			MessageBox(hwnd, str, TEXT("Result"), MB_OK | MB_ICONINFORMATION);
			
			//------------------------------------------------------------------------//
			
			//case II
			MessageBox(hwnd, TEXT("CASE II =:> Obtained ISubtract(Outer component) from previously obtained ISum (outer component)"), TEXT("CASE - II"), MB_OK | MB_ICONINFORMATION);
			hr = pISum->QueryInterface(IID_ISubtract, (void **)&pISubtract);
			if(FAILED(hr))
			{
				MessageBox(NULL, TEXT("ISUbtract Interface can not be obtained"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
				DestroyWindow(hwnd);
			}
			
			MessageBox(hwnd, TEXT("ISubtract Obtained"), TEXT("INFO"), MB_OK | MB_ICONINFORMATION);
			//call SubtractionOfTwoIntegers()
			pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iResult);
			wsprintf(str, TEXT("Subtraction of %d and %d is %d"), iNum1, iNum2, iResult);
			MessageBox(hwnd, str, TEXT("Result"), MB_OK | MB_ICONINFORMATION);
			
			//------------------------------------------------------------------------//
			
			//case III
			MessageBox(hwnd, TEXT("CASE III =:> Obtained IMultiplication(Inner component) from previously obtained ISubtract (outer component)"), TEXT("CASE - III"), MB_OK | MB_ICONINFORMATION);
			hr = pISubtract->QueryInterface(IID_IMultiplication , (void**) &pIMultiplication);
			if(FAILED(hr))
			{
				MessageBox(NULL, TEXT("IMultiplication Interface can not be obtained"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
				DestroyWindow(hwnd);
			}
			
			MessageBox(hwnd, TEXT("IMultiplication Obtained"), TEXT("INFO"), MB_OK | MB_ICONINFORMATION);
			//call MultiplicationOfTwoIntegers()
			pIMultiplication->MultiplicationOfTwoIntegers(iNum1, iNum2, &iResult);
			wsprintf(str, TEXT("Multiplication of %d and %d is %d"), iNum1, iNum2, iResult);
			MessageBox(hwnd, str, TEXT("Result"), MB_OK | MB_ICONINFORMATION);
			
			//------------------------------------------------------------------------//
			
			//case IV
			MessageBox(hwnd, TEXT("CASE IV =:> Obtained IDivision(Inner component) from previously obtained IMultiplication(inner component)"), TEXT("CASE - IV"), MB_OK | MB_ICONINFORMATION);
			hr = pIMultiplication->QueryInterface(IID_IDivision, (void**) &pIDivision);
			if(FAILED(hr))
			{
				MessageBox(NULL, TEXT("IDivision Interface can not be obtained"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
				DestroyWindow(hwnd);
			}
			
			MessageBox(hwnd, TEXT("IDivision Obtained"), TEXT("INFO"), MB_OK | MB_ICONINFORMATION);
			//call DivisionOfTwoIntegers()
			pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, &iResult);
			wsprintf(str, TEXT("Division of %d and %d is %d"), iNum1, iNum2, iResult);
			MessageBox(hwnd, str, TEXT("Result"), MB_OK | MB_ICONINFORMATION);
			
			//------------------------------------------------------------------------//
			MessageBox(hwnd, TEXT("Releasing ISum"), TEXT("INFO"), MB_OK | MB_ICONINFORMATION);
			pISum->Release();
			pISum = NULL;
			//------------------------------------------------------------------------//
			
			//case V
			MessageBox(hwnd, TEXT("CASE V =:> Obtained ISum(Outer component) using IDivision (Inner component) "), TEXT("CASE - V"), MB_OK | MB_ICONINFORMATION);
			hr = pIDivision->QueryInterface(IID_ISum, (void**) &pISum);
			if(FAILED(hr))
			{
				MessageBox(NULL, TEXT("ISum Interface can not be obtained"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
				DestroyWindow(hwnd);
			}
			
			MessageBox(hwnd, TEXT("ISum Obtained"), TEXT("INFO"), MB_OK | MB_ICONINFORMATION);
			//call SumOfTwoIntegers()
			pISum->SumOfTwoIntegers(iNum1, iNum2, &iResult);
			wsprintf(str, TEXT("Sum of %d and %d is %d"), iNum1, iNum2, iResult);
			MessageBox(hwnd, str, TEXT("Result"), MB_OK | MB_ICONINFORMATION);
			
			
			//case VI
			MessageBox(hwnd,
					TEXT("CASE VI =:> Obtaine IUnknown on IMultiplication and \n \
							Obtaine IUnknown on ISum.\n \
							Check Whether both are same (Identity property of IUnknown).\
							i.e. Client should feel that there should be a single server. There no inner server is availble"),
					TEXT("CASE VI"),
					MB_OK | MB_ICONINFORMATION);
			
			IUnknown *pIUnknownFromIMultiplication = NULL;
			IUnknown *pIUnknownFromISum = NULL;
			
			hr = pIMultiplication->QueryInterface(IID_IUnknown, (void**) &pIUnknownFromIMultiplication);
			if(FAILED(hr))
			{
				MessageBox(NULL, TEXT("IMultiplication's IUnknown Interface can not be obtained"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
				DestroyWindow(hwnd);
			}
			
			hr = pISum->QueryInterface(IID_IUnknown, (void**) &pIUnknownFromISum);
			if(FAILED(hr))
			{
				MessageBox(NULL, TEXT("ISum's IUnknown Interface can not be obtained"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
				DestroyWindow(hwnd);
			}
			
			if(pIUnknownFromIMultiplication == pIUnknownFromISum)
			{
				MessageBox(hwnd, TEXT("BOTH IUnknown's are same (Identity property proofs"), TEXT("INFO"), MB_OK | MB_ICONINFORMATION);
			}
			else
			{
				MessageBox(hwnd, TEXT("BOTH IUnknown's are not same"), TEXT("INFO"), MB_OK | MB_ICONINFORMATION);
			}
			
			pIUnknownFromIMultiplication->Release();
			pIUnknownFromIMultiplication = NULL;
			
			pIUnknownFromISum->Release();
			pIUnknownFromISum = NULL;
			
			
			//------------------------------------------------------------------------//
			MessageBox(hwnd, TEXT("Releasing all interfaces"), TEXT("INFO"), MB_OK | MB_ICONINFORMATION);
			SafeInterfaceRelease();
			//------------------------------------------------------------------------//
			
			//case VII
			MessageBox(hwnd,
					TEXT("CASE VII =:> Without obtaining Outer Component Interface, obtained Inner Component interface"),
					TEXT("CASE VII"),
					MB_OK | MB_ICONINFORMATION);
			
			hr = CoCreateInstance(CLSID_CSumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_IMultiplication, (void**) &pIMultiplication);
			if(FAILED(hr))
			{
				MessageBox(NULL, TEXT("IMultiplication can not be obtained"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
				DestroyWindow(hwnd);
			}
			
			MessageBox(hwnd, TEXT("IMultiplication Obtained"), TEXT("INFO"), MB_OK | MB_ICONINFORMATION);
			
			//--------------------------------------------------------------------------//
			DestroyWindow(hwnd);
			break;
		}
		
		case WM_DESTROY:
		{
			SafeInterfaceRelease();
			break;
		}			
	}
	
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

// SafeInterfaceRelease()
void SafeInterfaceRelease(void)
{
	if(pISum)
	{
		pISum->Release();
		pISum = NULL;
	}
	if(pISubtract)
	{
		pISubtract->Release();
		pISubtract = NULL;
	}
	if(pIMultiplication)
	{
		pIMultiplication->Release();
		pIMultiplication = NULL;
	}
	if(pIDivision)
	{
		pIDivision->Release();
		pIDivision = NULL;
	}
}
