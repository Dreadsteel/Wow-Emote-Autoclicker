#include "Header.h"
#include <cstdlib>  // Fixed: for system() and exit()

void coreFunctions::ShowFeedback(const char* message)
{
    HWND console = GetConsoleWindow();
    system("CLS");
    std::cout << message << "\n\n";
    std::cout << "Target position: X=" << x << " Y=" << y << "\n";
    std::cout << "Interval: " << totalIntervalTimer << " ms\n\n";
    std::cout << "F5 = Toggle clicking\n";
    std::cout << "F6 = Re-lock mouse to current position\n";
    std::cout << "ESC = Quit\n";
}

void coreFunctions::coreinit()
{
    system("CLS");
    system("TITLE Emote Autoclicker v2");
    std::cout << " Select an emote to spam from the list below. Type a number and press enter to confirm your choice\n\n";
    std::cout << "  1 - belfrude\n";
    std::cout << "  2 - belfchicken\n";
    std::cout << "  3 - nelfchicken\n";
    std::cout << "  4 - nelfrude\n";
    std::cout << "  5 - CUSTOM\n\n";
    std::cout << "Your choice (1-5): ";
    std::cin >> emoteActionPerformed;

    switch (emoteActionPerformed)
    {
    case 1: case 2: case 3: case 4:
        totalIntervalTimer = 2650;
        break;
    case 5:
        std::cout << "Custom interval (ms): ";
        std::cin >> totalIntervalTimer;
        break;
    default:
        std::cout << "Invalid choice!\n";
        Sleep(2000);
        exit(0);
    }

    std::cout << "\nMove mouse over the emote, then press F5 to lock position & start!\n";
    std::cout << "F6 = Change position mid-run | ESC = Quit\n";

    // Wait for initial F5 press to lock & start
    while (true)
    {
        if (GetAsyncKeyState(VK_F5) & 0x8000)
        {
            POINT p;
            GetCursorPos(&p);
            x = p.x;
            y = p.y;
            clickingStarted = true;
            break;
        }
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            exit(0);
        }
        Sleep(50);
    }

    ShowFeedback("=== AUTOCICKER STARTED ===");

    ClickingLoop();
}

void coreFunctions::ClickingLoop()
{
    INPUT down = { 0 };
    down.type = INPUT_MOUSE;
    down.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

    INPUT up = down;
    up.mi.dwFlags = MOUSEEVENTF_LEFTUP;

    auto lastClick = std::chrono::steady_clock::now() - std::chrono::milliseconds(totalIntervalTimer);  // Click immediately on first loop

    while (running)
    {
        // ESC = quit
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            running = false;
            std::cout << "\nProgram stopped. Goodbye!\n";
            Sleep(1000);
            break;
        }

        // F6 = re-lock to current mouse position
        if (GetAsyncKeyState(VK_F6) & 0x8000)
        {
            POINT p;
            GetCursorPos(&p);
            x = p.x;
            y = p.y;

            ShowFeedback("Mouse position changed");

            Sleep(300);  // Debounce
        }

        // F5 = toggle clicking on/off
        if (GetAsyncKeyState(VK_F5) & 0x8000)
        {
            clickingStarted = !clickingStarted;
            ShowFeedback(clickingStarted ? "AUTOCICKING RESUMED" : "AUTOCICKING PAUSED");
            Sleep(300); 
        }

        // Click if time elapsed
        if (clickingStarted)
        {
            auto now = std::chrono::steady_clock::now();
            if (now - lastClick >= std::chrono::milliseconds(totalIntervalTimer))
            {
                SetCursorPos(x, y);
                SendInput(1, &down, sizeof(INPUT));
                SendInput(1, &up, sizeof(INPUT));
                lastClick = now;
            }
        }

        // Efficient sleep: short poll for keys (low CPU)
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}