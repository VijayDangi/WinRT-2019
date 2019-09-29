#include<Windows.h>
#include "ClassFactoryDllServerWithRegFile.h"

//WndProc Declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("COM Client of Class Factory");
	HRESULT hr;

	//Com initialization
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

	switch (iMsg)
	{
		case WM_CREATE:
			hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);
			if (FAILED(hr))
			{
				MessageBox(hwnd, TEXT("ISum Interfaace Can Not Be Obtained"), TEXT("Error"), MB_OK | MB_ICONERROR);
				DestroyWindow(hwnd);
			}

			//initialize variables
			iNum1 = 55;
			iNum2 = 45;

			//calss SumOfTwoInteger() of ISum to get the sum
			pISum->SumOfTwoInteger(iNum1, iNum2, &iResult);

			wsprintf(str, TEXT("Sum of %d and %d is %d"), iNum1, iNum2, iResult);
			MessageBox(hwnd, str, TEXT("Result"), MB_OK);

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
			pISubtract->SubtractOfTwoInteger(iNum1, iNum2, &iResult);

			wsprintf(str, TEXT("Subtract of %d and %d is %d"), iNum1, iNum2, iResult);
			MessageBox(hwnd, str, TEXT("Result"), MB_OK);

			//Now onward ISubtract is not neede, released it
			pISubtract->Release();
			pISubtract = NULL;

			//exit the application
			DestroyWindow(hwnd);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
