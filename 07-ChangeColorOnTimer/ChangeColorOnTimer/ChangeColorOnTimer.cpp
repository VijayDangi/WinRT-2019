//header file
#include <Windows.h>

//define timer id
#define MYTIMER 101

//Declare callback procedure
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//WinMain
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR iCmdLine, int iCmdShow)
{
	//local variable
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("ChangeColorOnTimer");

	//code

	//initialize window class
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hInstance = hInstance;

	//register class
	RegisterClassEx(&wndclass);

	//create window in memory
	hwnd = CreateWindow(szAppName,
		TEXT("Color Change on Timer"),
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

//Define Window procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static int iPaintFlag = 0;
	RECT rc, rcTemp;
	PAINTSTRUCT ps;
	HDC hdc;
	HBRUSH hBrush;


	switch (iMsg)
	{
	case WM_CREATE:

		/* SetTimer();
		 * 1st parameter : handler
		 * 2nd parameter : Unique ID to Timer Since it used to kill the timer
		 * 3rd parameter : time(intterval) in millisecond
		 * 4th parameter : callback function for timer (i.e. after WM_TIMER arrived what should happened)
		 */
		SetTimer(hwnd, MYTIMER, 2000, NULL);		//set time when WM_TIMER message sent by OS

		break;

	case WM_TIMER:
		//MessageBox(hwnd, TEXT("MSG"), TEXT("Message"),MB_OK);


				/* KillTimer();
				 * 1st parameter : handler
				 * 2nd parameter : Unique ID of timer on which time is set
				 */
		KillTimer(hwnd, MYTIMER);		//kill the timer set by SetTimer();


		iPaintFlag++;
		if (iPaintFlag > 7)		//7 as we uses only 7 colors
		{
			iPaintFlag = 0;
		}



		/*
		 * InvalidateRect();
		 * 1st parameter : handler
		 * 2nd parameter : address of rectangle coordinates i.e. RECT variable
		 * 3rd parameter : erase background or not i.e. (TRUE or FALSE)
		 */
		InvalidateRect(hwnd, NULL, FALSE);

		SetTimer(hwnd, MYTIMER, 2000, NULL);
		break;


	case WM_SIZE:
		//MessageBox(hwnd, TEXT("RESIZE"), TEXT("MSG"), MB_OK);
		iPaintFlag = 0;		//when screen resized start painting from beginig
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);

		rcTemp.top = rc.top;
		rcTemp.bottom = rc.bottom;
		rcTemp.right = rc.right / 8;

		rcTemp.left = rc.left + (iPaintFlag) * (rcTemp.right);
		//rcTemp.right = (rc.right/8) + (iPaintFlag-1) * (rc.right/8);
		rcTemp.right = rcTemp.left + (rcTemp.right);
		//rc.right = (rc.right) - (iPaintFlag-1) * (rc.right/8);


		/*rcTemp.left = rc.left;
		rcTemp.top = rc.top;
		rcTemp.right = rc.right/8;
		rcTemp.bottom = rc.bottom;

		if(iPaintFlag != 0){
			rcTemp.left = rcTemp.left + (iPaintFlag-1)*(rcTemp.right);
		}else{
			rcTemp.left = rcTemp.left +  7*(rcTemp.right);
		}
		*/
		switch (iPaintFlag)
		{

			//Red
		case 0:
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;

			//Green
		case 1:
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;

			//Blue
		case 2:
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;

			//Black
		case 3:
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;

			//Cyan
		case 4:
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;

			//Maginta
		case 5:
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;

			//Yellow
		case 6:
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
			break;

			//White
		case 7:
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, hBrush);
			FillRect(hdc, &rcTemp, hBrush);
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

