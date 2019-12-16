/*
 * Writing DeclSpec.exe using declspec method dll and by explicit linking.
 */

 //include header file
#include <Windows.h>

//declare window procedure
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR iCmdLine, int iCmdShow)
{
	//local variable
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyMathUsingDeclSpecExplicit");

	//initialize window class
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.hInstance = hInstance;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);

	//register window class
	RegisterClassEx(&wndclass);

	//create window in memory
	hwnd = CreateWindow(
		szAppName,
		TEXT("MYMATH USING DECLSPEC EXPLICIT LINKING"),
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
	while (GetMessage(&msg, hwnd, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

//define window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HINSTANCE hDll = NULL;
	typedef int (*MakeSquareFn)(int);
	MakeSquareFn pfn = NULL;

	int num, square;
	TCHAR str[255];

	switch (iMsg)
	{
	case WM_CREATE:
		num = 25;

		//load dll
		hDll = LoadLibrary(TEXT("MyMath.dll"));

		if (hDll == NULL) 
		{
			MessageBox(hwnd, TEXT("MyMath.dll Not Found"), TEXT("ERROR"), MB_OK );
			DestroyWindow(hwnd);
		}

		pfn = (MakeSquareFn)GetProcAddress(hDll, "MakeSquare");

		if (pfn == NULL)
		{
			MessageBox(hwnd, TEXT("MakeSquare function Not Found"), TEXT("ERROR"), MB_OK);
			DestroyWindow(hwnd);
		}

		square = pfn(num);
		wsprintf(str, TEXT("Square of %d is %d"), num, square);
		MessageBox(hwnd, str, TEXT("Square"), MB_OK);
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
