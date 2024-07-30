#include <windows.h>
#include <tchar.h>
#include <psapi.h>
#include <stdbool.h>
#include <stdio.h>

#define TARGET_WIDTH 800
#define TARGET_HEIGHT 600

bool running = true;

// 检查进程是否在运行
bool isProcessRunning(const TCHAR* processName) {
    DWORD processIds[1024], cbNeeded, processCount;
    if (!EnumProcesses(processIds, sizeof(processIds), &cbNeeded)) {
        return false;
    }

    processCount = cbNeeded / sizeof(DWORD);
    for (DWORD i = 0; i < processCount; ++i) {
        if (processIds[i] != 0) {
            TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processIds[i]);
            if (hProcess != NULL) {
                HMODULE hMod;
                DWORD cbNeeded;
                if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {
                    GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
                }
                CloseHandle(hProcess);
            }

            if (_tcscmp(szProcessName, processName) == 0) {
                return true;
            }
        }
    }
    return false;
}

// 修改窗口样式和大小
void ModifyWindowStyleAndSize(HWND hwnd) {
    // 获取当前窗口样式
    LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);

    // 修改窗口样式以显示标题栏和关闭按钮
    style |= (WS_OVERLAPPEDWINDOW); // WS_OVERLAPPEDWINDOW 包含 WS_OVERLAPPED、WS_CAPTION、WS_SYSMENU、WS_THICKFRAME、WS_MINIMIZEBOX 和 WS_MAXIMIZEBOX
    SetWindowLongPtr(hwnd, GWL_STYLE, style);

    // 调整窗口大小
    SetWindowPos(hwnd, NULL, 0, 0, TARGET_WIDTH, TARGET_HEIGHT, SWP_NOZORDER | SWP_NOMOVE | SWP_FRAMECHANGED);
}

// 关闭窗口
void CloseTargetWindow(HWND hwnd) {
    PostMessage(hwnd, WM_CLOSE, 0, 0);
}

int main() {
    // 隐藏控制台窗口
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_HIDE);

    const TCHAR* targetProcessName = _T("fcs.exe");

    while (running) {
        // 检查 fcs.exe 是否在运行
        if (!isProcessRunning(targetProcessName)) {
            MessageBox(NULL, _T("找不到FreeClass本体，主动防御已关闭。请注意防护！如果需要再次开启，您需要将FreeClass打开后最小化使用。"), _T("FreeClass主动防御模块提示"), MB_ICONWARNING);
            break;
        }

        // 查找目标窗口
        HWND hwndBroadcast = FindWindow(NULL, _T("屏幕广播"));
        HWND hwndBlackScreen = FindWindow(NULL, _T("BlackScreen Window"));

        if (hwndBroadcast) {
            ModifyWindowStyleAndSize(hwndBroadcast);
        }

        if (hwndBlackScreen) {
            CloseTargetWindow(hwndBlackScreen);
        }

        // 等待一段时间再进行下一次检测
        Sleep(2000); 
    }

    return 0;
}
