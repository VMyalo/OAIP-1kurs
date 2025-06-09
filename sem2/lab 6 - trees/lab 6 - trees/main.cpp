#include <iostream>
#include <locale>

#include "AVL_tree.hpp"
using namespace std;


int main()
{
    setlocale(LC_ALL, "RU");

    AVL_tree tree;
    int choice;

    while (true)
    {
        system("cls");

        std::cout
            << "�������� ��������: " << endl
            << "1. ������� AVL-������/�������� n ��������� � ������." << endl // ������
            << "2. ������� �������� (�������)." << endl // ������
            << "3. ����� ������� �� �����." << endl // ������
            << "4. ������� �������." << endl // ������
            << "5. �������� ������." << endl // ������
            << "6. ���: ���������� ������� ������." << endl // ������
            << "7. ������� �������� ������ ��������." << endl // ������
            << "8. ��������� ���������." << endl // ������
            << "��� �����: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            system("cls");
            int n, buf;
            char c_buf[100];
            std::cout << "������� ���-�� ��������� ��� ������:\n";
            std::cin >> n;
            std::cout << "������� " << n << " ��������� ������:\n";

            for (int i = 0; i < n; i++)
            {
                std::cout << i + 1 << "." << endl;
                std::cout << "������� ����: ";
                std::cin >> buf;
                std::cout << "������� �����: ";
                std::cin.ignore();
                std::cin.getline(c_buf, 100);

                tree.insert(buf, c_buf);
            }
            system("pause");
            break;
        }
        case 2:
        {
            system("cls");

            tree.show();

            system("pause");
            break;
        }
        case 3: 
        {
            system("cls");
            int buf;

            std::cout << "������� ���� ��������, ������� ������ �����: ";
            std::cin >> buf;

            char* result_p = tree.search(buf);

            if (result_p == nullptr)
                std::cout << "������ �������� ���." << endl;
            else
            {
                std::cout << "������� ������: ";
                for (int i = 0; result_p[i] != '\0'; i++)
                {
                    std::cout << result_p[i];
                }
                std::cout << endl;
            }
                
            system("pause");
            break;
        }
        case 4:
        {
            system("cls");
            int buf;

            std::cout << "������� ���� ��������, ������� ������ �������: ";
            std::cin >> buf;
            tree.remove(buf);

            system("pause");
            break;
        }
        case 5:
        {
            system("cls");

            tree.delete_all();

            system("pause");
            break;
        }
        case 6:
        {
            system("cls");

            std::cout << "������ ������: " << endl;

            std::cout << "��������� ���� \"height\" AVL-������: " << tree.depth() << endl;
            std::cout << "��������� ����������� ����� ����� ������: " << tree.calculate_root_depth() << endl;

            system("pause");
            break;
        }
        case 7:
        {
            system("cls");

            tree.direct_output();
            tree.reverse_output();
            tree.sort_output();

            system("pause");
            break;
        }
        case 8:
        {
            system("cls");
            return 0;
        }
        default:
            break;
        }
    }

    return 0;
}