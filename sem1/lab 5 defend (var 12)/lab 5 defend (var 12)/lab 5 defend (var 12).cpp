#include <iostream>
#include <locale>
using namespace std;

int main()
{
    setlocale(LC_ALL, "RU");
    int n;
    int sum = 0;
    int prod = 1;

    cin >> n;

    int** array = new int* [n];

    for (int i = 0; i < n; i++)
    {
        array[i] = new int[n];
    }

    for (int i = 0; i < n; i++)
    {
        cout << "Введите " << i << "-ую строку массива : ";
        for (int j = 0; j < n; j++)
        {
            cin >> array[i][j];
        }
    }

    for (int i = 0; i < n / 2; i++)
    {
        for (int j = i; j < n - i; j++)
        {
            sum = sum + array[i][j];
            prod = prod * array[i][j];
        }
    }

    for (int i = n - 1; i >= n / 2; i--)
    {
        for (int j = i ; j >= n - i - 1; j--)
        {
            sum = sum + array[i][j];
            prod = prod * array[i][j];
        }
    }


    cout << "sum: " << sum << endl;
    cout << "prod: " << prod << endl;

    for (int i = 0; i < n; i++)
    {
        delete[] array[i];
    }

    delete[] array;
    
    return 0;
}
