//include header files
#include <Windows.h>

//declare Window Callback procedure
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//Thread Procedure
DWORD WINAPI ThreadProcOne(LPVOID);
DWORD WINAPI ThreadProcTwo(LPVOID);

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevINSTANCE, LPSTR iCmdLine, int iCmdShow)
{
	//local variable
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MultiThreading");

	//initialize window
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//register window
	RegisterClassEx(&wndclass);

	//create window
	hwnd = CreateWindow(szAppName,
		TEXT("Multi-Threading"),
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


//wndProc

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HANDLE hThreadOne = NULL;
	HANDLE hThraedTwo = NULL;

	switch (iMsg)
	{
	case WM_CREATE:
		hThreadOne = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcOne, (LPVOID) hwnd, 0, NULL);

		hThraedTwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProcTwo, (LPVOID)hwnd, 0, NULL);
		break;

	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("LBUTTONCOWN"), TEXT("Message"), MB_OK);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}


DWORD WINAPI ThreadProcOne(LPVOID param)
{
	HDC hdc;
	long int i;
	TCHAR str[255];

	hdc = GetDC((HWND)param);

	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 0));


	for (i = 0; i < 42947295; i++)
	{
		wsprintf(str, TEXT("ThreadOne => Increasing Order : %ld"), i);
		TextOut(hdc, 5, 5, str, wcslen(str));
	}

	ReleaseDC((HWND)param, hdc);

	return 0;
}

DWORD WINAPI ThreadProcTwo(LPVOID param)
{
	HDC hdc;
	long int i;
	TCHAR str[255];

	hdc = GetDC((HWND)param);

	SetBkColor(hdc, RGB(0, 0, 0));
	SetTextColor(hdc, RGB(0, 255, 0));


	for (i = 42947295;i >= 0 ;i--)
	{
		wsprintf(str, TEXT("ThreadTwo => Decreasing Order : %ld"), i);
		TextOut(hdc, 5, 20, str, wcslen(str));
	}

	ReleaseDC((HWND)param, hdc);

	return 0;
}
