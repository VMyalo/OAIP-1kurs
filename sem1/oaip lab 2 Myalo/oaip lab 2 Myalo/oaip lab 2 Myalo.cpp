﻿// oaip lab 2 Myalo.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

double min(double a, double b) // функция для нахождения минимального значения
{
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

double max(double a, double b) // функция для нахождения максимального значения
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int main()
{
    double x, y, z, m, d1;
    cout << "Vvedite x = ";
    cin >> x;
    cout << "Vvedite y = ";
    cin >> y;
    cout << "Vvedite z = ";
    cin >> z;

    /*  еще можно:
    *if (x == 0 && y == 0 & z == 0)
    * {
    *   cout << "5";
    *   return 0;
    * }
    */

    d1 = min(max(x, y), max(y, z)); // первое действие

    if (x == 0 && y == 0 && z == 0) //при x, y, z = 0 выводит 5
    {
        cout << "5" << endl;
        return 0;
    }
    else if (max(y, z) == 0) // проверка на "исключительную ситуацию" - деление на ноль
    {
        cout << "Znamenatel ne mozhet bit' raven nulyu!";
        return 0;
    }

    m = d1 / max(y, z); // второе действие, получение ответа в переменную "m"

    cout << "Otvet = " << m; // вывод ответа



    return 0;
}



// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
