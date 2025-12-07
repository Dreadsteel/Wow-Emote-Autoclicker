#pragma once
#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>

class coreFunctions
{
public:
    int emoteActionPerformed = 0;
    int totalIntervalTimer = 2650;
    int x = 0;
    int y = 0;
    bool clickingStarted = false;
    bool running = true;

    void coreinit();

private:
    void ClickingLoop();
    void ShowFeedback(const char* message);
};