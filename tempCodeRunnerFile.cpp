#include <windows.h>
#include <sstream>
#include <string>


HWND hEdit1, hEdit2, hButtonAdd, hButtonSub, hButtonMul, hButtonDiv;


double GetNumber(HWND hEdit) {
    char buffer[256];
    GetWindowTextA(hEdit, buffer, 256);
    return atof(buffer);
}

void ShowResult(HWND hwnd, double result) {
    std::ostringstream oss;
    oss.precision(6);
    oss << std::fixed << result;

    MessageBoxA(hwnd, oss.str().c_str(), "Result", MB_OK);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE:
     
        CreateWindowA("STATIC", "Please input two numbers:", WS_VISIBLE | WS_CHILD, 20, 10, 200, 20, hwnd, NULL, NULL, NULL);
        hEdit1 = CreateWindowA("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 40, 200, 25, hwnd, NULL, NULL, NULL);
        hEdit2 = CreateWindowA("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 20, 80, 200, 25, hwnd, NULL, NULL, NULL);

    
        hButtonAdd = CreateWindowA("BUTTON", "+", WS_VISIBLE | WS_CHILD, 20, 120, 40, 40, hwnd, (HMENU)1, NULL, NULL);
        hButtonSub = CreateWindowA("BUTTON", "-", WS_VISIBLE | WS_CHILD, 70, 120, 40, 40, hwnd, (HMENU)2, NULL, NULL);
        hButtonMul = CreateWindowA("BUTTON", "*", WS_VISIBLE | WS_CHILD, 120, 120, 40, 40, hwnd, (HMENU)3, NULL, NULL);
        hButtonDiv = CreateWindowA("BUTTON", "/", WS_VISIBLE | WS_CHILD, 170, 120, 40, 40, hwnd, (HMENU)4, NULL, NULL);
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) >= 1 && LOWORD(wParam) <= 4) {
            double num1 = GetNumber(hEdit1);
            double num2 = GetNumber(hEdit2);
            double result = 0.0;

            switch (LOWORD(wParam)) {
            case 1:
                result = num1 + num2;
                break;
            case 2:
                result = num1 - num2;
                break;
            case 3:
                result = num1 * num2;
                break;
            case 4:
                if (num2 != 0)
                    result = num1 / num2;
                else {
                    MessageBoxA(hwnd, "Cannot divide by zero!", "Error", MB_OK | MB_ICONERROR);
                    return 0;
                }
                break;
            }

            ShowResult(hwnd, result);
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    memset(&wc, 0, sizeof(wc));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(209, 0, 107)); 
    wc.lpszClassName = "CalculatorClass";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(0, "CalculatorClass", "My Calculator", WS_VISIBLE | WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 250, 200, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
