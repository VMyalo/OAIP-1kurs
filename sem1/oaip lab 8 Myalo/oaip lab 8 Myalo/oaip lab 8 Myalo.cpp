#include <iostream>
#include <locale>
using namespace std;

int function_fib(int n)
{
    if (n == 1 || n == 2)
        return 1;

    return function_fib(n - 1) + function_fib(n - 2);
}

int function_fib_cycle(int n)
{
    int fib_1 = 1;
    int fib_2 = 1;
    int buf;

    for (int i = 2; i < n; i++)
    {
        buf = fib_2;
        fib_2 = fib_1 + fib_2;
        fib_1 = buf;
    }

    return fib_2;
}

int main()
{
    setlocale(LC_ALL, "RU");

    int n;


    cout << "Введите n для числа Фибоначчи: ";
    cin >> n;
    cout << "Число, найденное с помощью цикла: " << function_fib_cycle(n);


    cout << "Число, найденное с помощью рекурсии: " << function_fib(n) << endl;


    return 0;
}