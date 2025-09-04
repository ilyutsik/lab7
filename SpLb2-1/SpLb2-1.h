#pragma once
#define MAX_LOADSTRING 100
#include "resource.h"
#include "framework.h"
#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <string>


// Глобальные переменные:
extern HINSTANCE hInst;                                // текущий экземпляр
extern WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
extern WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

extern HANDLE ProcHandle[4]; //Дескрипторы процессов
extern HANDLE TreadHandle[4]; //Дескрипторы потоков
extern DWORD ProcId[4]; //Идентификаторы процессов
extern DWORD ThreadId[4]; //Идентификаторы потоков процессов
extern LPCTSTR ProcImage[4];

extern TCHAR CmdParam[4][260]; //для строк с параметрами 


// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DlgProcInfo(HWND, UINT, WPARAM, LPARAM);