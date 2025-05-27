#include <windows.h>
#include "GameObject.h"

HANDLE hConsoleOutput = ::GetStdHandle(STD_OUTPUT_HANDLE);


void draw_char(char ch, double y, double x, COLORS foreground_color, COLORS background_color) {
    CHAR_INFO ch_info;
    ch_info.Char.AsciiChar = ch;
    ch_info.Attributes = foreground_color | (background_color << 4);

    COORD buf_size = {1, 1};
    COORD buf_coord = {0, 0};
    SMALL_RECT screen_pos;
    screen_pos.Left = static_cast<SHORT>(x);
    screen_pos.Top = static_cast<SHORT>(y);
    screen_pos.Right = static_cast<SHORT>(x + 1);
    screen_pos.Bottom = static_cast<SHORT>(y + 1);
    ::WriteConsoleOutput(hConsoleOutput, &ch_info, buf_size, buf_coord, &screen_pos);
}
