//include headers
#include <Windows.h>

//declare window procedure
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//local variable
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("IndiaPledge");

	//code

	//initialize wndclass
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbWndExtra = 0;
	wndclass.cbClsExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;


	//Register above class
	RegisterClassEx(&wndclass);

	//create window in memory
	hwnd = CreateWindow(szAppName,
		TEXT("India Pledge"),
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

	//messsage loop
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return ((int)msg.wParam);
}



//Defination of window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	//font size
	static int cyChar;
	int X, Y;
	TEXTMETRIC tm;



	switch (iMsg)
	{

	case WM_CREATE:
		hdc = GetDC(hwnd);
		GetTextMetrics(hdc, &tm);
		cyChar = tm.tmHeight + tm.tmExternalLeading;
		break;

	case WM_PAINT:

		X = 5;
		Y = 5;

		//call specialist
		hdc = BeginPaint(hwnd, &ps);

		//set backgroud color
		SetBkColor(hdc, RGB(0, 0, 0));

		//Orange
		SetTextColor(hdc, RGB(255, 125, 0));

		TextOut(hdc, X, Y, TEXT("India is my country;"), strlen("India is my country;"));
		Y = Y + cyChar;
		TextOut(hdc, X, Y, TEXT("all Indians are my brothers and sisters."), strlen("all Indians are my brothers and sisters."));
		Y = Y + cyChar;
		TextOut(hdc, X, Y, TEXT("I love my country, and"), strlen("I love my country, and"));
		Y = Y + cyChar;
		TextOut(hdc, X, Y, TEXT("I am proud of its rich and varied heritage."), strlen("I am proud of its rich and varied heritage."));
		Y = Y + cyChar;

		//White
		SetTextColor(hdc, RGB(255, 255, 255));

		TextOut(hdc, X, Y, TEXT("I shall always strive to be worthy of it."), strlen("I shall always strive to be worthy of it."));
		Y = Y + cyChar;
		TextOut(hdc, X, Y, TEXT("I shall respect my parents,"), strlen("I shall respect my parents,"));
		Y = Y + cyChar;
		TextOut(hdc, X, Y, TEXT("teachers and all elders and"), strlen("teachers and all elders and"));
		Y = Y + cyChar;
		TextOut(hdc, X, Y, TEXT("treat everyone with courtesy."), strlen("treat everyone with courtesy."));
		Y = Y + cyChar;

		//Green
		SetTextColor(hdc, RGB(0, 255, 0));

		TextOut(hdc, X, Y, TEXT("To my country and my people,"), strlen("To my country and my people,"));
		Y = Y + cyChar;
		TextOut(hdc, X, Y, TEXT("I pledge my devotion."), strlen("I pledge my devotion."));
		Y = Y + cyChar;
		TextOut(hdc, X, Y, TEXT("In their well being and"), strlen("In their well being and"));
		Y = Y + cyChar;
		TextOut(hdc, X, Y, TEXT("prosperity lies my happiness."), strlen("prosperity lies my happiness."));


		//sent back the specialist
		EndPaint(hwnd, &ps);

		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}


