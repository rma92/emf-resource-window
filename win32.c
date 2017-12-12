#include <windows.h>
#include "res.h"

HENHMETAFILE hemf;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  HDC hdc;
  HANDLE hres;
  PAINTSTRUCT ps;
  RECT rct;
  DWORD dw;
  HRSRC hrsrc;
  switch(message)
  {
    case WM_CREATE:
    { 
      hrsrc = FindResource( GetModuleHandle( NULL ),MAKEINTRESOURCE(ID_EMF1), "ENHANCEDMETAFILE"); 
      hres = LoadResource( GetModuleHandle( NULL ), hrsrc);
      dw = SizeofResource( GetModuleHandle( NULL ), hrsrc);
      hemf = SetEnhMetaFileBits( dw , hres );
    }
    break;
    case WM_PAINT:
      hdc = BeginPaint( hWnd, &ps );
      GetClientRect( hWnd, &rct );
      PlayEnhMetaFile( hdc, hemf, &rct );
      EndPaint( hWnd, &ps );
    break;
    case WM_DESTROY:
      PostQuitMessage(0);
    break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
  MSG msg1;
  WNDCLASS wc1;
  HWND hWnd1;
  ZeroMemory(&wc1, sizeof wc1);
  wc1.hInstance = hInst;
  wc1.lpszClassName = AppName;
  wc1.lpfnWndProc = (WNDPROC)WndProc;
  wc1.style = CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW;
  wc1.hbrBackground = GetSysColorBrush(COLOR_WINDOW);
  wc1.hIcon = LoadIcon(NULL, IDI_INFORMATION);
  wc1.hCursor = LoadCursor(NULL, IDC_ARROW);
  if(RegisterClass(&wc1) == FALSE) return 0;
  hWnd1 = CreateWindow(AppName, AppName, WS_OVERLAPPEDWINDOW | WS_VISIBLE, 10, 10, 360, 240, 0, 0, hInst, 0);
  if(hWnd1 == NULL) return 0;
  while(GetMessage(&msg1,NULL,0,0) > 0){
    TranslateMessage(&msg1);
    DispatchMessage(&msg1);
  }
  return msg1.wParam;
}

