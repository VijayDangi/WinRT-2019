//header file
#include <Windows.h>
#include "MyBitmapIcon.h"

//declare callback WndProc
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR iCmdLine, int iCmdShow)
{
	//local variables
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MyBitmapIcon");


	//code
	
	//initialize wndclass
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpszClassName = szAppName;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MYICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszMenuName = NULL;

	//register above class
	RegisterClassEx(&wndclass);

	//create window in memory
	hwnd = CreateWindow(szAppName,
		TEXT("My Bitmap and Icon"),
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


//Define Callback window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HBITMAP hBitmap;
	HDC hdc, hdcMem;
	PAINTSTRUCT ps;
	RECT rc;
	BITMAP bitmap;
	static HINSTANCE hInstance = NULL;

	switch(iMsg)
	{
		case WM_CREATE:
			hInstance = (HINSTANCE)GetModuleHandle(NULL);
			//hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(MYBITMAP));
			break;

		case WM_PAINT:
			hdc = BeginPaint(hwnd, &ps);
			hBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(MYBITMAP));
			GetClientRect(hwnd, &rc);
			hdcMem = CreateCompatibleDC(NULL);
			SelectObject(hdcMem, hBitmap);
			GetObject(hBitmap, sizeof(BITMAP), (PSTR)&bitmap);
			StretchBlt(hdc, 0, 0, rc.right, rc.bottom,
				hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
			DeleteObject(hBitmap);
			DeleteDC(hdcMem);
			EndPaint(hwnd, &ps);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
