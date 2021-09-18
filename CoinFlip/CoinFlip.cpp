#include <iostream>
#include <windows.h>
#include <string.h>

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

int main()
{
    srand(time(0));
    ShowConsoleCursor(false);
    int amountOfRecords = 1;
    bool isCurrentFlipHeads = false;
    int streak = 0;
    int maxStreak = 0;
    int amountofloops = 0;
    int amountofloopssincelast = 0;
    std::string binaryrepresentation = "";
    while (1)
    {
        amountofloops++;
        amountofloopssincelast++;
        int randnum = rand() % 2;
        bool isHeads = false;
        if (randnum == 1) { isHeads = true; }
        gotoxy(30, 0);
        std::cout << "Current streak: " << streak << "   ";
        gotoxy(60, 0);
        std::cout << "Estimated time to next streak: " << pow(maxStreak + 1, 2) << "   ";

        if (isHeads)
            binaryrepresentation += "1";
        else
            binaryrepresentation += "0";


        gotoxy(0, 2);
        std::cout << "Streak milestones:";

        gotoxy(60, 9);
        std::cout << "Flips: (1 = heads)";

        gotoxy(60, 10);
        std::cout << binaryrepresentation;

        if(amountofloops > 50)
            binaryrepresentation.erase(0, 1);


        if (amountOfRecords < 10) {
            gotoxy(0, 2 + (amountOfRecords));
            std::cout << maxStreak << ":" << amountofloopssincelast;
        }
        if (amountOfRecords >= 10 && amountOfRecords < 20) {
            gotoxy(10, 2 + (amountOfRecords - 9));
            std::cout << maxStreak << ":" << amountofloopssincelast;
        }
        if (amountOfRecords >= 20) {
            gotoxy(20, 2 + (amountOfRecords - 19));
            std::cout << maxStreak << ":" << amountofloopssincelast;

        }

        if (isCurrentFlipHeads)
        {
            if (isHeads)
            {
                streak++;
                //std::cout << "landed on heads with a streak of: " << streak << std::endl;
                if (streak > maxStreak) {
                    amountofloopssincelast = 0;
                    amountOfRecords++;
                    maxStreak = streak;
                    gotoxy(0, 0);
                    std::cout << "New max streak of: " << maxStreak << std::endl;
                }
            }
            else {
                streak = 0;
                isCurrentFlipHeads = false;
            }
        }
        else
        {
            if (!isHeads)
            {
                streak++;
                //std::cout << "landed on tails with a streak of: " << streak << std::endl;
                if (streak > maxStreak) {
                    amountofloopssincelast = 0;
                    amountOfRecords++;
                    maxStreak = streak;
                    gotoxy(0, 0);
                    std::cout << "New max streak of: " << maxStreak << std::endl;
                }
            }
            else {
                streak = 0;
                isCurrentFlipHeads = true;
            }
        }
    }
}