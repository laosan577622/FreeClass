#include <windows.h>
#include <tchar.h>
#include <psapi.h>
#include <stdbool.h>
#include <stdio.h>

#define TARGET_WIDTH 800
#define TARGET_HEIGHT 600

bool running = true;

// �������Ƿ�������
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

// �޸Ĵ�����ʽ�ʹ�С
void ModifyWindowStyleAndSize(HWND hwnd) {
    // ��ȡ��ǰ������ʽ
    LONG_PTR style = GetWindowLongPtr(hwnd, GWL_STYLE);

    // �޸Ĵ�����ʽ����ʾ�������͹رհ�ť
    style |= (WS_OVERLAPPEDWINDOW); // WS_OVERLAPPEDWINDOW ���� WS_OVERLAPPED��WS_CAPTION��WS_SYSMENU��WS_THICKFRAME��WS_MINIMIZEBOX �� WS_MAXIMIZEBOX
    SetWindowLongPtr(hwnd, GWL_STYLE, style);

    // �������ڴ�С
    SetWindowPos(hwnd, NULL, 0, 0, TARGET_WIDTH, TARGET_HEIGHT, SWP_NOZORDER | SWP_NOMOVE | SWP_FRAMECHANGED);
}

// �رմ���
void CloseTargetWindow(HWND hwnd) {
    PostMessage(hwnd, WM_CLOSE, 0, 0);
}

int main() {
    // ���ؿ���̨����
    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_HIDE);

    const TCHAR* targetProcessName = _T("fcs.exe");

    while (running) {
        // ��� fcs.exe �Ƿ�������
        if (!isProcessRunning(targetProcessName)) {
            MessageBox(NULL, _T("�Ҳ���FreeClass���壬���������ѹرա���ע������������Ҫ�ٴο���������Ҫ��FreeClass�򿪺���С��ʹ�á�"), _T("FreeClass��������ģ����ʾ"), MB_ICONWARNING);
            break;
        }

        // ����Ŀ�괰��
        HWND hwndBroadcast = FindWindow(NULL, _T("��Ļ�㲥"));
        HWND hwndBlackScreen = FindWindow(NULL, _T("BlackScreen Window"));

        if (hwndBroadcast) {
            ModifyWindowStyleAndSize(hwndBroadcast);
        }

        if (hwndBlackScreen) {
            CloseTargetWindow(hwndBlackScreen);
        }

        // �ȴ�һ��ʱ���ٽ�����һ�μ��
        Sleep(2000); 
    }

    return 0;
}
