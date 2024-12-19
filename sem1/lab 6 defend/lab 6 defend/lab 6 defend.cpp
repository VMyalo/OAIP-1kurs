#include <iostream>
#include <locale>
using namespace std;

int main()
{
    setlocale(LC_ALL, "RU");

    int n = 100;
    int n_start = 0;
    int n_sub = 0;
    char* str = new char[n];

    cout << "Введите строку: ";
    cin.getline(str, 100);

    cout << endl;

    for (int i = 0; i < 100; i++)
    {
        if (str[i] == ' ' || str[i] == '\0')
        {
            if (n_sub % 2 == 1 && n_sub != 1)
            {

                str[n_start + n_sub / 2] = '-';
            }
            else if (n_sub % 2 == 0 && n_sub != 2)
            {
                str[n_start + n_sub / 2] = '-';
                str[n_start + n_sub / 2 - 1] = '-';
            }
            n_start = i + 1;
            n_sub = 0;
            
            if (str[i] == '\0') break;
        }
        else n_sub++;
    }

    int i = 0;
    while (str[i] != '\0')
    {
        cout << str[i];
        i++;
    }

    return 0;
}