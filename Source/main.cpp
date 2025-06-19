#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_NCHITTEST: {
        // 允许拖动无边框窗口
        LRESULT hit = DefWindowProc(hwnd, msg, wParam, lParam);
        if (hit == HTCLIENT) return HTCAPTION;
        return hit;
    }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 注册窗口类
    WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"PopupWindowClass";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 默认背景
    RegisterClassEx(&wc);

    // 创建无边框窗口
    HWND hwnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_LAYERED, // 置顶和支持透明
        L"PopupWindowClass",           // 窗口类名
        L"Desktop Widget",             // 窗口标题（无边框时不可见）
        WS_POPUP | WS_VISIBLE,         // 弹出式窗口，立即可见
        0, 0,                         // 窗口左上角坐标（屏幕顶部左侧）
        800, 100,                     // 窗口宽度和高度
        NULL, NULL, hInstance, NULL);

    // 设置透明度（可选，0-255，255为不透明）
    SetLayeredWindowAttributes(hwnd, 0, 200, LWA_ALPHA);

    // 显示窗口
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // 消息循环
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}