#include "misc.hpp"

/**
@brief ���������� ��� ������.
*/
bool IsEqual(char* a, char* b)
{
    int i = 0;
    while (true)
    {
        if (b[i] == '\0')
            break;

        if (a[i] != b[i])
            return false;
        i++;
    }

    return true;
}