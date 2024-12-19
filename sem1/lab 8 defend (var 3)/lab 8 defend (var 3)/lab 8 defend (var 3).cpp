#include <iostream>
#include <locale>
using namespace std;

int cycle_NOD(int M, int N)
{
    int buf;

    if (N > M)
    {
        buf = N;
        N = M;
        M = buf;
    }

    while (1)
    {
        if (M % N == 0)
        {
            return N;
        }
        else
        {
            buf = N;
            N = M % N;
            M = buf;
        }
    }
}

int rec_NOD(int M, int N)
{
    if (M % N == 0)
        return N;
    else
        return rec_NOD(N, M % N);
}

int main()
{
    setlocale(LC_ALL, "RU");

    int M, N;

    int answ = -1;

    cout << "Введите число M: ";
    cin >> M;

    cout << "Введите число N: ";
    cin >> N;

    answ = cycle_NOD(M, N);

    cout << answ << endl;

    answ = rec_NOD(M, N);

    cout << answ << endl;

    return 0;
}