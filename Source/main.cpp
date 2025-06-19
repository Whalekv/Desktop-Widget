#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_NCHITTEST: {
        // �����϶��ޱ߿򴰿�
        LRESULT hit = DefWindowProc(hwnd, msg, wParam, lParam);
        if (hit == HTCLIENT) return HTCAPTION;
        return hit;
    }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // ע�ᴰ����
    WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"PopupWindowClass";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // Ĭ�ϱ���
    RegisterClassEx(&wc);

    // �����ޱ߿򴰿�
    HWND hwnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_LAYERED, // �ö���֧��͸��
        L"PopupWindowClass",           // ��������
        L"Desktop Widget",             // ���ڱ��⣨�ޱ߿�ʱ���ɼ���
        WS_POPUP | WS_VISIBLE,         // ����ʽ���ڣ������ɼ�
        0, 0,                         // �������Ͻ����꣨��Ļ������ࣩ
        800, 100,                     // ���ڿ�Ⱥ͸߶�
        NULL, NULL, hInstance, NULL);

    // ����͸���ȣ���ѡ��0-255��255Ϊ��͸����
    SetLayeredWindowAttributes(hwnd, 0, 200, LWA_ALPHA);

    // ��ʾ����
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // ��Ϣѭ��
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}