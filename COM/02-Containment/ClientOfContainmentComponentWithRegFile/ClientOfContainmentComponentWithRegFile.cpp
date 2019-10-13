#include<Windows.h>
#include "HeaderForClientOfContainmentComponentWithRegFile.h"

//WndProc Declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("COM Client of Containment");
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
	if (FAILED(hr))
	{
		MessageBox(NULL, TEXT("COM Library Can Not Be Initialized.\nProgram Will Now Exit...\n"),
			TEXT("Program Error"), MB_OK | MB_ICONERROR);
		exit(0);
	}

	//Wndclass initialization
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;

	//register window class
	RegisterClassEx(&wndclass);


	hwnd = CreateWindow(AppName,
		TEXT("Client of COM Dll Server"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	//show window
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//message loop
	while (GetMessage(&msg, NULL, 0, 0))
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
	HRESULT hr;
	int iNum1, iNum2, iResult;
	TCHAR str[255];
	ISum *pISum;
	ISubtract *pISubtract;
	IMultiplication * pIMultiplication;
	IDivision *pIDivision;

	switch (iMsg)
	{
	case WM_CREATE:
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
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);
		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISum Interface Can Not Be Obtained"), TEXT("Error"), MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd);
		}

		//initialize variables
		iNum1 = 55;
		iNum2 = 45;

		//calss SumOfTwoInteger() of ISum to get the sum
		pISum->SumOfTwoIntegers(iNum1, iNum2, &iResult);

		wsprintf(str, TEXT("Sum of %d and %d is %d"), iNum1, iNum2, iResult);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK | MB_ICONINFORMATION);

		//call QueryInterface() on ISum, to get ISubtract's pointer
		hr = pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);

		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("ISubtract Interface Can Not Be Obtained."), TEXT("Error"), MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd);
		}

		//Now onward ISum is not needed, release it
		pISum->Release();
		pISum = NULL; //make released interface NULL

		//agin initialized
		iNum1 = 100;
		iNum2 = 42;
		//call SubtractOfTwoIntegers() of ISubtract to get subtract
		pISubtract->SubtractionOfTwoIntegers(iNum1, iNum2, &iResult);

		wsprintf(str, TEXT("Subtract of %d and %d is %d"), iNum1, iNum2, iResult);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK | MB_ICONINFORMATION);

		//call QueryInterface() on ISubtract, to get IMultiplication's pointer
		hr = pISubtract->QueryInterface(IID_IMultiplication, (void**)&pIMultiplication);

		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IMultiplication Interface Can Not Be Obtained."), TEXT("Error"), MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd);
		}

		//Now onward ISubtract is not neede, released it
		pISubtract->Release();
		pISubtract = NULL;

		//call MultiplicationOfTwoInteger() of IMultiplication to get multiplication
		pIMultiplication->MultiplicationOfTwoIntegers(iNum1, iNum2, &iResult);
		
		wsprintf(str, TEXT("Multiplication of %d and %d is %d"), iNum1, iNum2, iResult);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK | MB_ICONINFORMATION);

		//call QueryInterface() on ISubtract, to get IMultiplication's pointer
		hr = pIMultiplication->QueryInterface(IID_IDivision, (void**)&pIDivision);

		if (FAILED(hr))
		{
			MessageBox(hwnd, TEXT("IDivision Interface Can Not Be Obtained."), TEXT("Error"), MB_OK | MB_ICONERROR);
			DestroyWindow(hwnd);
		}

		//Now onward IMultiplication is not needed, released it
		pIMultiplication->Release();
		pIMultiplication = NULL;

		//call MultiplicationOfTwoInteger() of IMultiplication to get multiplication
		pIDivision->DivisionOfTwoIntegers(iNum1, iNum2, &iResult);

		wsprintf(str, TEXT("Division of %d and %d is %d"), iNum1, iNum2, iResult);
		MessageBox(hwnd, str, TEXT("RESULT"), MB_OK | MB_ICONINFORMATION);

		//Now onward IDivision is not needed, released it
		pIDivision->Release();
		pIDivision = NULL;
		//exit the application

		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
