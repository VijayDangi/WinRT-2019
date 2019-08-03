//header files
#include <Windows.h>

//declare callback window procedure
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//local variable
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("ColorChangeOnKey");

	//code

	//initialize wndclass
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hInstance = hInstance;
	wndclass.lpszMenuName = NULL;


	//register class 
	RegisterClassEx(&wndclass);

	//create window in memory
	hwnd = CreateWindow(szAppName,					//send WM_PAINT message
		TEXT("ColorChangeOnKey"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

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


LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static int iPaintFlag = 0;

	RECT rc;
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH hBrush;

	switch (iMsg)
	{
	case WM_CREATE:
		break;

	case WM_CHAR:
		switch (wParam)
		{
			//Red
		case 'r':
		case 'R':
			iPaintFlag = 1;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

			//Green
		case 'g':
		case 'G':
			iPaintFlag = 2;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

			//Blue
		case 'b':
		case 'B':
			iPaintFlag = 3;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

			//Cyan
		case 'c':
		case 'C':
			iPaintFlag = 4;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

			//Maginta
		case 'm':
		case 'M':
			iPaintFlag = 5;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

			//Yellow
		case 'y':
		case 'Y':
			iPaintFlag = 6;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

			//White
		case 'w':
		case 'W':
			iPaintFlag = 7;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

			//Black
		case 'k':
		case 'K':
		default:
			iPaintFlag = 0;
			InvalidateRect(hwnd, NULL, TRUE);
			break;
		}

		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);

		switch (iPaintFlag)
		{
			//Black
		case 0:
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;

			//Red
		case 1:
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;

			//Green
		case 2:
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;

			//Blue
		case 3:
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;

			//Cyan
		case 4:
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;

			//Maginta
		case 5:
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;

			//Yellow
		case 6:
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;

			//White
		case 7:
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rc, hBrush);
			break;
		}

		EndPaint(hwnd, &ps);

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}

