#include <iostream>
#include <string>

#include <Windows.h>

using namespace std;


int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    
    
    int sym1, sym2;
    int n1, n2, n = 100;
    char* str1 = new char[n];
    char* str2 = new char[n];
    bool flag = 0;

    cout << "Введите размер 1-ой строки: " << endl;
    cin >> n1;

    cout << "Введите первую строку:" << endl;
    cin.ignore();
    cin.getline(str1, n);

    cout << "Введите размер 2-ой строки: " << endl;
    cin >> n2;

    cout << "Введите вторую строку:" << endl;
    cin.ignore();
    cin.getline(str2, n);


    if (n1 > n2) n = n1;
    else n = n2;

    for (int i = 0; i < n; i++)
    {
        if (str1[i] != str2[i])
        {
            sym1 = str1[i];
            sym2 = str2[i];
            cout << "Ответ: " << sym1 - sym2;
            flag = 1;
            break;
        }
    }

    if (flag == 0) cout << "Строки равны.";

    delete[] str1;
    delete[] str2;

    return 0;
}