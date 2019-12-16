//Headerfiles
#include <Windows.h>

//Callback declaration
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR CmdLine, int iCmdShow)
{
	//local variable
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("HelloWorld");

	//code

	//customize window
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_VREDRAW | CS_HREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	//Regitration of wndclass
	RegisterClassEx(&wndclass);


	//Creation of window
	hwnd = CreateWindow(szAppName,
		TEXT("HelloWorld"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,//0x80000000,
		CW_USEDEFAULT,//0x80000000,
		CW_USEDEFAULT,//0x80000000,
		CW_USEDEFAULT,//0x80000000,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	//Display Window
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	//MessageLoop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ((int)msg.wParam);
}

//Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	RECT rc;
	TCHAR str[] = TEXT("Hello World!!!!");
	HDC hdc;
	PAINTSTRUCT ps;


	switch (iMsg)
	{
	case WM_CREATE:

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_PAINT:
		//get changing rectangle
		GetClientRect(hwnd, &rc);
		//call the specialist i.e. create the HDC
		hdc = BeginPaint(hwnd, &ps);
		//set text color
		SetTextColor(hdc, RGB(0, 255, 0));     //green text
												//default text color is black
		//set background color
		SetBkColor(hdc, RGB(0, 0, 0));         //black background
											   //Default background color is white
		//Draw actual text
		DrawText(hdc,	//specialist
			str,		//text to paint
			-1,			//length of string or how many character want to display (-1 means show whole string)
			&rc,		//client rectangle
			DT_SINGLELINE | DT_CENTER | DT_VCENTER		//show in singleline , horizontally center , vertically center
		);
		//sent back the specialist and stop painting
		EndPaint(hwnd, &ps);
		break;
	}
	
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
