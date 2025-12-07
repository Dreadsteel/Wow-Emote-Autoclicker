#include "Header.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

void coreFunctions::coreinit()
{
    system("TITLE Autoclicker for Emotes");
    cout << "Select an emote to be spammed by typing a number (1-5) and pressing enter.\n";
    cout << "Acceptable emotes: belfrude (1), belfchicken (2), nelfchicken (3), nelfrude (4), CUSTOM (5)\n\n";
    cout << "IMPORTANT: Before pressing F5 to start clicking, ensure your mouse pointer is already in position\n";
    cin >> emoteActionPerformed;
    cout << "\n";

    if (emoteActionPerformed >= 1 && emoteActionPerformed <= 5)
    {
        fnc_clickingOnly(emoteActionPerformed);
    }
    else
    {
        cout << "Invalid selection!\n";
    }
}

void coreFunctions::fnc_clickingOnly(int emoteActionPerformed)
{
    switch (emoteActionPerformed)
    {
    case 1:
        totalIntervalTimer = 2650;
        cout << "belfrude (1) selected. Interval set to " << totalIntervalTimer << " ms\n";
        break;
    case 2:
        totalIntervalTimer = 3095;
        cout << "belfchicken (2) selected. Interval set to " << totalIntervalTimer << " ms\n";
        break;
    case 3:
        totalIntervalTimer = 3300;
        cout << "nelfchicken (3) selected. Interval set to " << totalIntervalTimer << " ms\n";
        break;
    case 4:
        totalIntervalTimer = 2650;
        cout << "nelfrude (4) selected. Interval set to " << totalIntervalTimer << " ms\n";
        break;
    case 5:
        cout << "CUSTOM selected. Please input your desired time in milliseconds:\n";
        cin >> intervalTimer;
        totalIntervalTimer = intervalTimer;
        cout << "Custom interval set to " << totalIntervalTimer << " ms\n";
        break;
    }

    cout << "\nPress F5 to save mouse location and begin clicking!\n";

    waitForInput = true;
    while (waitForInput)
    {
        if (GetAsyncKeyState(VK_F5) & 0x8000)  // Proper way to check key press
        {
            cout << "Clicking started! Press ESC to exit.\n";

            POINT cursorPos;
            GetCursorPos(&cursorPos);
            x = cursorPos.x;
            y = cursorPos.y;

            cout << "Mouse position saved: X=" << x << " Y=" << y << "\n";

            fnc_beginClickingLoop(x, y, totalIntervalTimer);
            waitForInput = false;
        }
        Sleep(50);  // Prevent 100% CPU usage while waiting
    }
}

void coreFunctions::fnc_beginClickingLoop(int x, int y, int totalIntervalTimer)
{
    clickingStarted = true;

    while (clickingStarted)
    {
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            cout << "Exiting autoclicker...\n";
            clickingStarted = false;
            Sleep(200);
            exit(0);
        }

        SetCursorPos(x, y);
        mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        Sleep(totalIntervalTimer);
    }
}