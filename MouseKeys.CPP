#include <windows.h>
#include <iostream>

bool mouseMode = false;
bool lastCapsState = false;

void LeftClick()
{
    INPUT input = {0};

    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &input, sizeof(INPUT));

    ZeroMemory(&input, sizeof(INPUT));

    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &input, sizeof(INPUT));
}

void RightClick()
{
    INPUT input = {0};

    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, &input, sizeof(INPUT));

    ZeroMemory(&input, sizeof(INPUT));

    input.type = INPUT_MOUSE;
    input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    SendInput(1, &input, sizeof(INPUT));
}

int main()
{

    std::cout << "Mouse Keys Running...\n";

    while (true)
    {
        // Toggle with Caps Lock
        bool capsPressed = GetAsyncKeyState(VK_CAPITAL) & 0x8000;

        if (capsPressed && !lastCapsState)
        {
            mouseMode = !mouseMode;

            std::cout << "Mouse Mode: "
                      << (mouseMode ? "ON" : "OFF")
                      << std::endl;
        }

        lastCapsState = capsPressed;

        if (mouseMode)
        {
            POINT p;
            GetCursorPos(&p);

            int speed = 7;

            if (GetAsyncKeyState(VK_UP) & GetAsyncKeyState(VK_CONTROL) & 0x8000){
                p.y -= speed;
            }

            if (GetAsyncKeyState(VK_DOWN) & GetAsyncKeyState(VK_CONTROL) & 0x8000){
                p.y += speed;
            }

            if (GetAsyncKeyState(VK_LEFT) & GetAsyncKeyState(VK_CONTROL) & 0x8000){
                p.x -= speed;
            }

            if (GetAsyncKeyState(VK_RIGHT) & GetAsyncKeyState(VK_CONTROL) & 0x8000){
                p.x += speed;
            }


            SetCursorPos(p.x, p.y);

            // Space = left click
            static bool prevSpace = false;

            if (GetAsyncKeyState(VK_CONTROL) & 0x8000)
            {
                bool spaceDown = GetAsyncKeyState(VK_SPACE) & 0x8000;

                if (spaceDown && !prevSpace)
                {
                    LeftClick();
                }

                prevSpace = spaceDown;
            }
            else
            {
                prevSpace = false; 
            }

            // Enter = right click
            if (GetAsyncKeyState(VK_RETURN) & 1){
                RightClick();
            }

        }

        Sleep(10);
    }

    return 0;
}