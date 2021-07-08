#include <windows.h>
#include <thread>

using namespace std;

VOID WINAPI ClickLoop()
{
    while ((GetAsyncKeyState(VK_LBUTTON)&0x8000) == 0)
        Sleep(1);

    INT nCurrKeyState = GetKeyState(VK_LBUTTON);
    INT nPrevKeyState;
    INPUT Input;
    ZeroMemory(&Input, sizeof(INPUT));

    Input.type = INPUT_MOUSE;
   // Sleep(1);
    Input.mi.dwFlags =  MOUSEEVENTF_LEFTUP;
    SendInput(1, &Input, sizeof(INPUT));
    do
    {
        Input.mi.dwFlags =  MOUSEEVENTF_LEFTUP;
        SendInput(1, &Input, sizeof(INPUT));
        Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        SendInput(1, &Input, sizeof(INPUT));
        Sleep(20); // how many miliseconds the click is held.

        nPrevKeyState = nCurrKeyState;
        nCurrKeyState = GetKeyState(VK_LBUTTON);

        if ((GetAsyncKeyState(VK_LBUTTON)&0x8000) == 0){
            Input.mi.dwFlags =  MOUSEEVENTF_LEFTUP;
            SendInput(1, &Input, sizeof(INPUT));
            break;
        }
    }while (nCurrKeyState != nPrevKeyState);
}

int main() {
    while(TRUE)
    {
        Sleep(10);
        printf("In click loop...\n");
        ClickLoop();
    }

    return 0;
}
