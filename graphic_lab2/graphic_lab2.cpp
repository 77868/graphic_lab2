// graphic_lab2.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "graphic_lab2.h"
#include "MyRect.h"

#define MAX_LOADSTRING 100

#define PI 3.14159265358979323846

// макрос преобразования X градусов в радианы 
#define gradToRad(x) x * PI/180 
// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
MyRect rectangle;                               // отрисовываемый объект
float movingSpeed = 4.0f;                       // скорость перемещения фигуры

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GRAPHICLAB2, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GRAPHICLAB2));
    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GRAPHICLAB2));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = nullptr;
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_GRAPHICLAB2);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        InvalidateRect(hWnd, NULL, true);//обзначение перерисовываемой области окна
        UpdateWindow(hWnd);// отправление сообщения WM_PAINT
        break;
    case WM_KEYDOWN :
    {
        int key = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (key)
        {
        case 0x57:// нажата клавиша W
            rectangle.move(AXIS_Y, -movingSpeed);
            break;
        case 0x53:// нажата клавиша S
            rectangle.move(AXIS_Y, movingSpeed);
            break;
        case 0x41:// нажата клавиша A
            rectangle.move(AXIS_X, -movingSpeed);
            break;
        case 0x44:// нажата клавиша D
            rectangle.move(AXIS_X, movingSpeed);
            break;
        case 0x45:// нажата клавиша E
            rectangle.rotate(gradToRad(15));
            break;
        case 0x51:// нажата клавиша q
            rectangle.rotate(gradToRad(-15));
            break;
        case 0x52:// нажата клавиша R
            rectangle.scale(1.2f);
            break;
        case 0x46:// нажата клавиша F
            rectangle.scale(0.8f);
            break;
        case 0x1B:// // нажата клавиша ESC
            PostQuitMessage(0);
            break;
        }
    }
    InvalidateRect(hWnd, NULL, true);//обзначение перерисовываемой области окна
    UpdateWindow(hWnd);// отправление сообщения WM_PAINT
    break;
    case WM_PAINT:
        {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);// получение десриптора графического устройства

        // создание совместимого битмапа для создания буфера(совпадает с клиенсткой областью), 
        //в котором будет предварительная отрисовка окна для избежания мерцаний из-за постепеной отрисовки окна
        HDC bufferDC = CreateCompatibleDC(hdc);
        HBITMAP bufferBM = CreateCompatibleBitmap(hdc, ps.rcPaint.right - ps.rcPaint.left, ps.rcPaint.bottom - ps.rcPaint.top);

        SelectObject(bufferDC, bufferBM);

        //отрисовка:
        // 
        //Заполнение буфера белым цветом
        FillRect(bufferDC, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
       
        rectangle.draw(bufferDC,RGB(0,0,255));

        //Загрузка буфера в битмап графического устройства и освобождение памяти выделенной на буфер
        BitBlt(hdc, 0, 0, ps.rcPaint.right - ps.rcPaint.left, ps.rcPaint.bottom - ps.rcPaint.top, bufferDC, 0, 0, SRCCOPY);
        DeleteDC(bufferDC);
        DeleteObject(bufferBM);

        EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
