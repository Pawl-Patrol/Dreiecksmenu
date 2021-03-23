#include "interaction.hpp"

int getChoice(const char* title, const char** choices, int length)
{
    PrintXY(1, 1, title, TEXT_MODE_NORMAL, TEXT_COLOR_BLUE);
    int index = 0;
    locate_OS(2, 2);
    Print_OS(choices[0], TEXT_MODE_INVERT, 0);
    for (int i = 1; i < length; i++)
    {
        locate_OS(2, 2 + i);
        Print_OS(choices[i], TEXT_MODE_NORMAL, 0);
    }
    int key;
    while (true)
    {
        GetKey(&key);
        if (key == KEY_CTRL_DOWN || key == KEY_CTRL_UP)
        {
            locate_OS(2, 2 + index);
            Print_OS(choices[index], TEXT_MODE_NORMAL, 0);
            index = (index + (key == KEY_CTRL_DOWN ? 1 : -1) + length) % length;
            locate_OS(2, 2 + index);
            Print_OS(choices[index], TEXT_MODE_INVERT, 0);
        }
        else if (key >= KEY_CTRL_F1 && key <= KEY_CTRL_F6)
        {
            index = key - KEY_CTRL_F1;
            break;
        }
        else if (key == KEY_CTRL_EXE)
        {
            break;
        }
        else if (key == KEY_CTRL_EXIT)
        {
            index = -1;
            break;
        }
    }
    Bdisp_Fill_VRAM(COLOR_WHITE, 1);
    return index;
}