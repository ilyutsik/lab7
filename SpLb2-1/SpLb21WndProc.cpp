#include "SpLb2-1.h"

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

// Function to find the process ID by its name
DWORD FindProcessId(const std::wstring& processName)
{
    DWORD processId = 0;
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 pe32;
        pe32.dwSize = sizeof(PROCESSENTRY32);
        if (Process32First(hProcessSnap, &pe32))
        {
            do
            {
                if (!_wcsicmp(pe32.szExeFile, processName.c_str()))
                {
                    processId = pe32.th32ProcessID;
                    break;
                }
            } while (Process32Next(hProcessSnap, &pe32));
        }
        CloseHandle(hProcessSnap);
    }
    return processId;
}



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
        case IDM_PROC_NOTEPAD:
        {
            SECURITY_ATTRIBUTES sap, sat;
            sap.nLength = sizeof(SECURITY_ATTRIBUTES);
            sap.lpSecurityDescriptor = nullptr;
            sap.bInheritHandle = FALSE;

            sat.nLength = sizeof(SECURITY_ATTRIBUTES);
            sat.lpSecurityDescriptor = nullptr;
            sat.bInheritHandle = FALSE;

            STARTUPINFO si;
            ZeroMemory(&si, sizeof(STARTUPINFO));
            si.cb = sizeof(STARTUPINFO);
            PROCESS_INFORMATION pi;
            BOOL fCP = CreateProcess(ProcImage[1], nullptr, &sap, &sat, FALSE, 0,
                nullptr, nullptr, &si, &pi);
            ProcHandle[1] = pi.hProcess; CloseHandle(pi.hProcess);
            TreadHandle[1] = pi.hThread; CloseHandle(pi.hThread);
            ProcId[1] = pi.dwProcessId;
            ThreadId[1] = pi.dwThreadId;

        }break;
        //===============================================================//
        case IDM_PROC_TXT:
        {
            SECURITY_ATTRIBUTES sap, sat;
            sap.nLength = sizeof(SECURITY_ATTRIBUTES);
            sap.lpSecurityDescriptor = nullptr;
            sap.bInheritHandle = FALSE;

            sat.nLength = sizeof(SECURITY_ATTRIBUTES);
            sat.lpSecurityDescriptor = nullptr;
            sat.bInheritHandle = FALSE;

            STARTUPINFO si;
            ZeroMemory(&si, sizeof(STARTUPINFO));
            si.cb = sizeof(STARTUPINFO);
            PROCESS_INFORMATION pi;
            //TCHAR PCmdLine[] = TEXT("C:\\Windows\\Notepad.exe SpLb2-1.h");
            TCHAR PCmdLine[] = TEXT(" SpLb2-1.h");
            lstrcpy(CmdParam[2], PCmdLine);
            BOOL fCP = CreateProcess(ProcImage[2], PCmdLine, &sap, &sat, FALSE, 0,
                nullptr, nullptr, &si, &pi);
            ProcHandle[2] = pi.hProcess;
            TreadHandle[2] = pi.hThread;
            ProcId[2] = pi.dwProcessId;
            ThreadId[2] = pi.dwThreadId;
        }break;
        //===============================================================//
        case IDM_PROC_CALC:

        {
        
            SECURITY_ATTRIBUTES sap, sat;
            sap.nLength = sizeof(SECURITY_ATTRIBUTES);
            sap.lpSecurityDescriptor = nullptr;
            sap.bInheritHandle = FALSE;

            sat.nLength = sizeof(SECURITY_ATTRIBUTES);
            sat.lpSecurityDescriptor = nullptr;
            sat.bInheritHandle = FALSE;

            STARTUPINFO si;
            ZeroMemory(&si, sizeof(STARTUPINFO));
            si.cb = sizeof(STARTUPINFO);
            PROCESS_INFORMATION pi;
            BOOL fCP = CreateProcess(ProcImage[3], nullptr, &sap, &sat,
                FALSE, 0, nullptr, nullptr, &si, &pi);
            ProcHandle[3] = pi.hProcess;
            TreadHandle[3] = pi.hThread;
            ProcId[3] = pi.dwProcessId;
            ThreadId[3] = pi.dwThreadId;
        }break;
        //===============================================================//
        case IDM_PROC_CLOSE:
        {
            std::wstring processName = L"Notepad.exe"; // Name of the process to terminate
            ProcId[3] = FindProcessId(processName);
            HANDLE hProc;
            if (ProcId[3] != 0)
            {
                hProc = OpenProcess(PROCESS_TERMINATE, FALSE, ProcId[2]);
                if (hProc != NULL)
                {
                    TerminateProcess(hProc, 0);
                    CloseHandle(hProc);
                    MessageBox(hWnd, TEXT("PROCESS terminated successfully.\n"), TEXT(""), MB_OK);
                }
                else {
                    MessageBox(hWnd, TEXT("Failed to open PROCESS.\n"), TEXT(""), MB_OK);
                }
            }
        }break;
        //===============================================================//
        case IDM_INFO_CUR:
        {
            DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProcInfo, 0);
        }break;
        //===============================================================//
        case IDM_INFO_NOT:
        {
            DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProcInfo, 1);
        }break;
        //===============================================================//
        case IDM_INFO_TXT:
        {
            DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProcInfo, 2);
        }break;
        //===============================================================//
        case IDM_INFO_CALC:
        {
            DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DlgProcInfo, 3);
        }break;
        //===============================================================//

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
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
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


// Обработчик сообщений для вывода информации о процессах.
INT_PTR CALLBACK DlgProcInfo(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
        SetDlgItemText(hDlg, IDC_EDIT1, ProcImage[lParam]);
        TCHAR buff[200];
        wsprintf(buff, TEXT("Дескриптор %d (0x%08X)"), ProcHandle[lParam], ProcHandle[lParam]);
        SetDlgItemText(hDlg, IDC_EDIT2, buff);
        wsprintf(buff, TEXT("Идентификатор %d"), ProcId[lParam]);
        SetDlgItemText(hDlg, IDC_EDIT3, buff);
        DWORD dwExitCode = -555;
        if (!GetExitCodeProcess(ProcHandle[lParam], &dwExitCode))
        {
            //Действия в случае ошибки
            wsprintf(buff, TEXT("%s"), TEXT("Ошибка выполнения запроса"));
        }
        else
            if (dwExitCode == STILL_ACTIVE)
            {
                //Процесс еще не завершен
                wsprintf(buff, TEXT("%s"), TEXT("Процесс еще не завершился"));
            }
            else
            {
                //Процесс завершился
                wsprintf(buff, TEXT("%s    %d"), TEXT("Код завершения "), dwExitCode);
            }
        SetDlgItemText(hDlg, IDC_EDIT4, buff);
        
    }
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