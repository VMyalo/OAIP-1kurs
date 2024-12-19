#include <iostream>
#include <locale>
using namespace std;

int main()
{
    setlocale(LC_ALL, "RU");

    int n;

    cout << "Введите n = ";
    cin >> n;

    int** arr = new int*[n];
    int** arr_res = new int*[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = new int[n];
        arr_res[i] = new int[n];
    }

    for (int i = 0; i < n; i++)
    {
        cout << "Введите " << i << "-ую строку массива : ";
        for (int j = 0; j < n; j++)
        {
            cin >> arr[i][j];
        }
    }

    cout << "Ответ:" << endl;


    for (int i = 0; i < n; i++) //
    {
        for (int j = (n - 1); j >= 0; j--)
        {
            arr_res[i][n - 1 - j] = arr[j][i];
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << arr_res[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Старый ответ: " << endl;

    for (int i = 0; i < n; i++)
    {
        for (int j = (n - 1); j >= 0; j--)
            cout << arr[j][i] << " ";

        cout << endl;
    }

    for (int i = 0; i < n; i++)
    {
        delete[] arr[i];
        delete[] arr_res[i];
    }

    delete[] arr;
    delete[] arr_res;

    return 0;
}