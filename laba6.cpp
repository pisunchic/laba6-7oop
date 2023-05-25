// laba6.cpp : Определяет точку входа для приложения.
//
//наши библиотеки
#include "framework.h"
#include "laba6.h"
#include <cmath>

//используем пространства имен std
using namespace std;

#define M_PI 3.14159265358979323846
#define _USE_MATH_DEFINES
#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

//Все, что ниже, это настройка нашего финдовс окна{начало

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
    LoadStringW(hInstance, IDC_LABA6, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LABA6));

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

    return (int)msg.wParam;
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

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LABA6));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LABA6);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
//}конец
class Figure {//создаем класс(родитель) с различными параметрами для того, чтобы настраивать фигуру и ее передвижение
protected:
    int x, y;
    int R;
    int Ang; //угол поворота фигуры
    int VAng; //скорость вращения фигуры
    int V; //скорость передвижения фигуры
    int Napr; //направление движения фигуры
    COLORREF col;
    HWND hWnd;
    int N_Reg;
public:
    Figure(int R, int VAng, int V, int Napr, COLORREF col, HWND hWnd);
    virtual void step(); //обновляет координаты фигуры
    virtual void draw(int Reg) = 0;
};
Figure::Figure(int R, int VAng, int V, int Napr, COLORREF col, HWND hWnd) {//конструктор
    this->R = R;
    this->VAng = VAng;
    this->V = V;
    this->Napr = Napr;
    this->col = col;
    this->hWnd = hWnd;
    Ang = 0;
    N_Reg = 1;
    RECT rect;
    GetClientRect(hWnd, &rect);
    x = rect.right / 2; //устанавливает координату x фигуры в середину ширины клиентской области окна
    y = rect.bottom / 2; // устанавливает координату y фигуры в середину высоты клиентской области окна
}

void Figure::step() {//функция шаг(т е каждый раз меняет фигура свое положение)
    Ang += VAng;
    if (Ang >= 360) Ang -= 360;
    RECT rect;
    GetClientRect(hWnd, &rect);
    if (Napr = 1) {
        x += V * N_Reg; //изменяет координату x в зависимости от скорости и направления 
        if (N_Reg == 1) {
            if (x + R >= rect.right) N_Reg = -1;
        }
        else {
            if (x - R <= 0) N_Reg = 1;
        }
    }
    else {
        y += V * N_Reg;
        if (N_Reg == 1) {
            if (y + R >= rect.right) N_Reg = -1;
        }
        else {
            if (y - R <= 0) N_Reg = 1;
        }
    }
}

class MyTri : public Figure {//этот класс и все остальные, это грубо говоря дети класса фигуры. У них есть такие же гены как и у родителя(переменные) и функции(но измененные функции под себя)
protected:
    int N;
    POINT* p; //указатель на вершины
public:
    MyTri(int R, int VAng, int V, int Napr, COLORREF col, HWND hWnd, int N);
    void step();
    void draw(int Reg);
};

MyTri::MyTri(int R, int VAng, int V, int Napr, COLORREF col, HWND hWnd, int N) : //??
    Figure(R, VAng, V, Napr, col, hWnd)
{
    this->N = N;
    p = new POINT[N];
    double A = (Ang + 5) * M_PI / 180 + 25;
    double A1 = 1.75 * M_PI / N + 25;

    for (int i = 0; i < N; i++, A += A1) {
        p[i].x = x + R * cos(A);
        p[i].y = y - R * sin(A);
    }
}

void MyTri::step() {
    Figure::step();
    double A = (Ang + 5) * M_PI / 180 + 25;
    double A1 = 1.75 * M_PI / N + 25;
    for (int i = 0; i < N; i++, A += A1) {
        p[i].x = x + R * cos(A);
        p[i].y = y - R * sin(A);
    }
}

void MyTri::draw(int Reg) {//отрисовка фигуры по заданным координатам,которые мы задаем в конструкторе и в функции step
    HPEN pen;
    if (Reg = 1) pen = CreatePen(PS_SOLID, 1, col);
    else pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    HDC hdc;
    hdc = GetDC(hWnd);
    SelectObject(hdc, pen);
    MoveToEx(hdc, p[0].x, p[0].y, 0); //позиция пера
    for (int i = 1; i < N; i++) LineTo(hdc, p[i].x, p[i].y);
    LineTo(hdc, p[0].x, p[0].y);
    ReleaseDC(hWnd, hdc);
    DeleteObject(pen);
}

class MyOtrezok : public Figure {
protected:
    int x1, y1, x2, y2;
public:
    MyOtrezok(int R, int VAng, int V, int Napr, COLORREF col, HWND hWnd);
    void step(); //обновление координат фигуры 
    void draw(int Reg);
};

MyOtrezok::MyOtrezok(int R, int VAng, int V, int Napr, COLORREF col, HWND hWnd) :
    Figure(R, VAng, V, Napr, col, hWnd)
{
    double A = Ang * M_PI / 180;
    x1 = x + R * cos(A);
    x2 = x - R * cos(A);
    y1 = y + R * sin(A);
    y2 = y - R * sin(A);
}

void MyOtrezok::step() {
    Figure::step();
    double A = Ang * M_PI / 180;
    x1 = x + R * cos(A);
    x2 = x - R * cos(A);
    y1 = y + R * sin(A);
    y2 = y - R * sin(A);
}

void MyOtrezok::draw(int Reg) {
    HPEN pen;
    if (Reg = 1) pen = CreatePen(PS_SOLID, 1, col);
    else pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    HDC hdc; //контекст устройства
    hdc = GetDC(hWnd);
    SelectObject(hdc, pen); //выбираем перо
    MoveToEx(hdc, x1, y1, 0); //перо на начало
    LineTo(hdc, x2, y2); //рисуем
    ReleaseDC(hWnd, hdc); //освобождаем
    DeleteObject(pen);
}

class MyPoluKrug :public Figure {
public:
    MyPoluKrug(int R, int VAng, int V, int Napr, COLORREF col, HWND hWnd);
    void draw(int Reg);
};

MyPoluKrug::MyPoluKrug(int R, int VAng, int V, int Napr, COLORREF col, HWND hWnd) :
    Figure(R, VAng, V, Napr, col, hWnd) {}
void MyPoluKrug::draw(int Reg) {
    HPEN pen;
    if (Reg = 1) pen = CreatePen(PS_SOLID, 1, col);
    else pen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    HDC hdc;
    hdc = GetDC(hWnd);
    SelectObject(hdc, pen);
    MoveToEx(hdc, x, y, 0);
    AngleArc(hdc, x, y, R, Ang, 270);
    LineTo(hdc, x, y);
    ReleaseDC(hWnd, hdc);
    DeleteObject(pen);
}
Figure* pF[9];//Создаеи массив фигур
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
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;
    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 1, 10, 0);//задаем таймер, по истечении которого будут передвигаться фигуры
        //задаем массив наших фигур
        pF[0] = new MyTri(85, 1, 10, 0, RGB(255, 0, 0), hWnd, 3); //размер,начальное положение, скорость, направление, цвет
        pF[1] = new MyTri(79, 2, 5, 0, RGB(0, 255, 0), hWnd, 3);
        pF[2] = new MyTri(70, 3, 3, 1, RGB(0, 0, 255), hWnd, 3);
        pF[3] = new MyOtrezok(50, 4, 2, 1, RGB(255, 0, 255), hWnd);
        pF[4] = new MyOtrezok(100, 2, 1, 1, RGB(0, 255, 255), hWnd);
        pF[5] = new MyOtrezok(102, 1, 2, 0, RGB(0, 0, 255), hWnd);
        pF[6] = new MyPoluKrug(50, 2, 2, 0, RGB(255, 0, 255), hWnd);
        pF[7] = new MyPoluKrug(100, 1, 3, 0, RGB(0, 255, 255), hWnd);
        pF[8] = new MyPoluKrug(98, 3, 4, 1, RGB(0, 0, 255), hWnd);
        break;
    case WM_TIMER:
        for (int i = 0; i < 9; i++) {
            pF[i]->draw(0);
            pF[i]->step();
            pF[i]->draw(1);
        }
        break;
    case WM_COMMAND:// Разобрать выбор в меню:
    {
        wmId = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        switch (wmId)
        {
        case IDM_ABOUT: // при нажатии about
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT://выход из программы
            KillTimer(hWnd, 1);
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        KillTimer(hWnd, 1);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

//настройка вкладки about
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) // объявление функции с возвращаемым значением
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
