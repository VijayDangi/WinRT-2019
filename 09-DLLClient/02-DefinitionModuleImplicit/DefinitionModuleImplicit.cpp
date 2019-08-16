/*
 * Writing DefinitionModuleImplicit.exe using "module definition file" method dll and by implicit linking.
 */

//include header file
#include <Windows.h>
//Header file from prohect "DLL\DEF\MyMathUsingDllDef"
#include "MyMathUsingDllDef.h"

//add the entry of MyMathUsingDllDef.lib in following method in Visual Studio
/**
 *		right click on Solutionexplore => properties => Linker => commandLine => type "MyMathUsingDllDef.lib" in white area.
 */

//declare Window callback procedue
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR iCmdLine, int iCmdShow)
{
	//local variable
	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("MyMathUsingDef");

	//initialize class
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);

	//register window
	RegisterClassEx(&wndclass);

	//create window in memory
	hwnd = CreateWindow(
					szAppName,
					TEXT("My Math Using Module Definition File"),
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
	return ((int)msg.wParam);
}


//define window callback procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	int num, square;
	TCHAR str[255];

	switch (iMsg)
	{
	case WM_CREATE:
		num = 26;
		square = MakeSquare(num);

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
