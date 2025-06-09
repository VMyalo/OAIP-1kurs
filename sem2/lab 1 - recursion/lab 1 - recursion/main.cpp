#include <iostream>
#include <locale>
using namespace std;

float func(float n)
{
    if (n >= 2)
    {
        return (n * n / (n - 1) / (n + 1) * func(n - 2));
    }
    else
        return 1;
}

float func_cycle(float n)
{
    float res = 1;

    while (n >= 2)
    {
        res = res * n * n / (n - 1) / (n + 1);
        n = n - 2;
    }

    return res;
}

int main()
{
    setlocale(LC_ALL, "RU");

    float n;

    std::cout << "Введите n: ";
    std::cin >> n;

    std::cout << "Ответ: " << func(n) << endl;

    std::cout << "Ответ 2: " << func_cycle(n);

    return 0;
}