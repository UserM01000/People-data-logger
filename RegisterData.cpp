#include <windows.h>
#include <winuser.h>
#include <stdlib.h>

#define FILE_MENU_NEW 101   
#define FILE_MENU_OPEN 102
#define FILE_MENU_EXIT 103
#define ID_BOTONSALIR 104
#define GENERAR_DATOS 105
#define DEVELOPER 106
#define ID_Dev 107

LRESULT CALLBACK WindowProcedure(HWND,UINT,WPARAM,LPARAM);

void AddMenus(HWND);
void datosUsuario(HWND);
void registerDialogClass(HINSTANCE);
void displayDialog(HWND);

HMENU hMenu;
HWND hName,hAge,hSex,hCarre,hOut;

using namespace std;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    WNDCLASSW wc = {0};

    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"RegisterData";
    wc.lpfnWndProc = WindowProcedure;

    if(!RegisterClassW(&wc))
        return -1;
    
        registerDialogClass(hInst);

    CreateWindowW(L"RegisterData",L"Registar Datos",WS_OVERLAPPEDWINDOW | WS_VISIBLE ,400,100,500,500,NULL,NULL,NULL,NULL);

    MSG msg = {0};

    while( GetMessage(&msg,NULL, 0,0) )
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;   
}

LRESULT CALLBACK WindowProcedure(HWND hWnd,UINT msg,WPARAM wp,LPARAM lp)
{
    switch ( msg)
    {
    case WM_COMMAND:
        
        switch (wp)
        {
        case FILE_MENU_EXIT:
            MessageBeep(MB_OK);
            if(MessageBox(hWnd,"DESEA SALIR?","Salir",MB_OKCANCEL|MB_ICONQUESTION)==IDOK){
                PostQuitMessage(0);
            }
            break;
        case GENERAR_DATOS:
            char name[30], age[20], sex[2], profe[100], out[70];

            GetWindowText(hName,name,30);
            GetWindowText(hAge,age,20);
            GetWindowText(hSex,sex,2);
            GetWindowText(hCarre,profe,100);

            strcpy(out,"Nombre: ");
            strcat(out,name);
            strcat(out,"\r\n");
            strcat(out,"Edad: ");
            strcat(out,age);
            strcat(out,"\r\n");
            strcat(out,"Sexo: ");
            strcat(out,sex);
            strcat(out,"\r\n");
            strcat(out,"Carrera: ");
            strcat(out,profe);

            SetWindowText(hOut, out);
            break; 

        case DEVELOPER:
            displayDialog(hWnd);
            break;
        }
        break;

    case WM_CREATE:
        AddMenus(hWnd);
        datosUsuario(hWnd);
        break;

    case WM_CLOSE:
        MessageBeep(MB_OK);
        if(MessageBox(hWnd,"Salir?","Desea salir?",MB_OKCANCEL|MB_ICONQUESTION)==IDOK){
            PostQuitMessage(0);
        }
        break;

    default:
        DefWindowProcW(hWnd, msg, wp, lp);
    } 
}
        
void AddMenus(HWND hWnd)
{
    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hSubMenu = CreateMenu();

    AppendMenu(hSubMenu,MF_STRING,DEVELOPER,"Developer");

    AppendMenu(hFileMenu,MF_STRING,0,"New");
    AppendMenu(hFileMenu,MF_POPUP,(UINT_PTR)hSubMenu,"Open");
    AppendMenu(hFileMenu,MF_SEPARATOR,0,0);
    AppendMenu(hFileMenu,MF_STRING,FILE_MENU_EXIT,"Exit");

    AppendMenu(hMenu,MF_POPUP,(UINT_PTR)hFileMenu,"File");
    AppendMenu(hMenu,MF_STRING,0,"Help");

    SetMenu(hWnd,hMenu);
}

void datosUsuario(HWND hWnd)
{
    CreateWindowW(L"Static", L"Name ", WS_VISIBLE | WS_CHILD,30,20,98,30,hWnd,NULL,NULL,NULL);
    hName = CreateWindowW(L"Edit",L"", WS_VISIBLE | WS_CHILD | WS_BORDER,97,20,98,30,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Static", L"Edad", WS_VISIBLE | WS_CHILD,30,70,98,30,hWnd,NULL,NULL,NULL);
    hAge = CreateWindowW(L"Edit",L"", WS_VISIBLE| WS_CHILD | WS_BORDER,97,70,98,30,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Static", L"Sexo F/M", WS_VISIBLE | WS_CHILD,30,120,98,30,hWnd,NULL,NULL,NULL);
    hSex = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,97,120,98,30,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Static", L"Profesion", WS_VISIBLE | WS_CHILD,27,180,98,30,hWnd,NULL,NULL,NULL);
    hCarre = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER,98,180,98,30,hWnd,NULL,NULL,NULL);

    CreateWindowW(L"Button",L"GENERAR", WS_VISIBLE | WS_CHILD | WS_BORDER,85,235,98,30,hWnd,HMENU(GENERAR_DATOS),NULL,NULL);
    hOut = CreateWindowW(L"Edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER| ES_MULTILINE,230,50,200,200,hWnd,NULL,NULL,NULL);

}

LRESULT CALLBACK DialogProcedure(HWND hWnd,UINT msg,WPARAM wp,LPARAM lp)
{
    switch(msg)
    {
        case WM_COMMAND:
            if (LOWORD(wp)==ID_Dev){
                system("start https://github.com/UserM01000");
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;
        default:
            return DefWindowProcW(hWnd,msg,wp,lp);
    }
}

void registerDialogClass(HINSTANCE hInst)
{
    WNDCLASSW dialog = {0};

    dialog.hbrBackground = (HBRUSH)COLOR_WINDOW;
    dialog.hCursor = LoadCursor(NULL, IDC_ARROW);
    dialog.hInstance = hInst;
    dialog.lpszClassName = L"Developer";
    dialog.lpfnWndProc = DialogProcedure;

    RegisterClassW(&dialog);
    
}

void displayDialog(HWND hWnd)
{
    HWND hButton = CreateWindowW(L"Developer", L"About Dev :D",WS_VISIBLE| WS_OVERLAPPEDWINDOW, 140,150,259,150,hWnd,NULL,NULL,NULL);
    CreateWindowW(L"Button", L"About Dev", WS_VISIBLE| WS_CHILD,65,30,100,40,hButton, (HMENU)ID_Dev, NULL,NULL);

}