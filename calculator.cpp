#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string>
HWND textfield,button,Textbox1,Textbox2;
char number1[10],number2[10],answ[10];
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		case WM_CREATE:
		textfield = CreateWindow("STATIC","Please input two numbers",WS_VISIBLE | WS_CHILD| WS_BORDER ,40,20,170,25,hwnd,NULL,NULL,NULL );
		button = CreateWindow("BUTTON","+",WS_VISIBLE | WS_CHILD | WS_BORDER ,50,120,25,25,hwnd,(HMENU) 1,NULL,NULL );
		button = CreateWindow("BUTTON","-",WS_VISIBLE | WS_CHILD | WS_BORDER ,90,120,25,25,hwnd,(HMENU) 2,NULL,NULL );
		button = CreateWindow("BUTTON","*",WS_VISIBLE | WS_CHILD | WS_BORDER ,130,120,25,25,hwnd,(HMENU) 3,NULL,NULL );
		button = CreateWindow("BUTTON","/",WS_VISIBLE | WS_CHILD | WS_BORDER ,170,120,25,25,hwnd,(HMENU) 4,NULL,NULL );	
		Textbox1 = CreateWindow("EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER ,50,60,160,25,hwnd,NULL,NULL,NULL );
		Textbox2 = CreateWindow("EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER ,50,90,160,25,hwnd,NULL,NULL,NULL );
		break;

		/* Upon destruction, tell the main thread to stop */
case WM_COMMAND:
        switch (LOWORD(wParam)) {
            case 1:
                ::MessageBeep(MB_ICONERROR);
                float num1, num2, result;
                GetWindowText(Textbox1, number1, 10);
                GetWindowText(Textbox2, number2, 10);
                num1 = atof(number1);
                num2 = atof(number2);
                result = num1 + num2;
                sprintf(answ, "%f", result);
                ::MessageBox(hwnd, answ, "Result", MB_OK);
                break;
            case 2:
                ::MessageBeep(MB_ICONERROR);
                float num1s, num2s, results;
                GetWindowText(Textbox1, number1, 10);
                GetWindowText(Textbox2, number2, 10);
                num1s = atof(number1);
                num2s = atof(number2);
                results = num1s - num2s;
                sprintf(answ, "%f", results);
                ::MessageBox(hwnd, answ, "Result", MB_OK);
                break;
            case 3:
                ::MessageBeep(MB_ICONERROR);
                float num1m, num2m, resultm;
                GetWindowText(Textbox1, number1, 10);
                GetWindowText(Textbox2, number2, 10);
                num1m = atof(number1);
                num2m = atof(number2);
                resultm = num1m * num2m;
                sprintf(answ, "%f", resultm);
                ::MessageBox(hwnd, answ, "Result", MB_OK);
                break;
            case 4:
                ::MessageBeep(MB_ICONERROR);
                float num1d, num2d, resultd;
                GetWindowText(Textbox1, number1, 10);
                GetWindowText(Textbox2, number2, 10);
                num1d = atof(number1);
                num2d = atof(number2);
                if (num2d != 0) {
                    resultd = num1d / num2d;
                    sprintf(answ, "%f", resultd);
                    ::MessageBox(hwnd, answ, "Result", MB_OK);
                } else {
                    ::MessageBox(hwnd, "Division by zero error!", "Error", MB_OK | MB_ICONERROR);
                }
                break;
        }
        break;

		case WM_DESTROY: 
			PostQuitMessage(0);
			break;
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+20);
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}