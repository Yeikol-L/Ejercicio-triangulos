#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>

static TCHAR szWindowClass[] = _T("DesktopApp");
static TCHAR szTitle[] = _T("Apliación tendencia de triángulo");


static const int anchoTriangulo = 300;
static const int altoTriangulo = 200;

static POINT punto1 = { (800 - anchoTriangulo) / 2, 350 };
static POINT punto2 = { (800 + anchoTriangulo) / 2, 350 };
static POINT punto3 = { 400, 350 - altoTriangulo };
static POINT puntoExterior = { 400, 350 - (altoTriangulo / 2) };



HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Llamada a RegisterClassEx fallida!"),
            _T("Apliación tendencia de triángulo"),
            NULL);

        return 1;
    }

    hInst = hInstance;

    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        800, 600,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Llamada a CreateWindow fallida!"),
            _T("Apliación tendencia de triángulo"),
            NULL);

        return 1;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

POINT PuntoMedio(POINT puntoA, POINT puntoB) {
    POINT puntoMedio = { (puntoA.x + puntoB.x) / 2, (puntoA.y + puntoB.y) / 2 };
    return puntoMedio;
}

int Dice() {
    return rand() % 3 + 1;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    TCHAR greeting[] = _T("Hola, escritorio de Windows!");
    POINT puntoMedio = puntoExterior;
    COLORREF black = RGB(0, 0, 0);
    COLORREF red = RGB(255, 0, 0);
    COLORREF green = RGB(0, 255, 0);
    COLORREF blue = RGB(0, 0, 255);
    COLORREF currentColor;
    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        SetPixel(hdc, punto1.x, punto1.y, red);
        SetPixel(hdc, punto2.x, punto2.y, green);
        SetPixel(hdc, punto3.x, punto3.y, blue);
        SetPixel(hdc, puntoMedio.x, puntoMedio.y, black);

        for (int i = 0; i <= 10000; i++) {

            switch (Dice())
            {
            case 1:
                puntoMedio = PuntoMedio(punto1, puntoMedio);
                currentColor = red;
                break;
            case 2:
                puntoMedio = PuntoMedio(punto2, puntoMedio);
                currentColor = green;
                break;
            case 3:
                puntoMedio = PuntoMedio(punto3, puntoMedio);
                currentColor = blue;
                break;
            default:
                break;
            }
            SetPixel(hdc, puntoMedio.x, puntoMedio.y, currentColor
);
        }

        EndPaint(hWnd, &ps);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}
