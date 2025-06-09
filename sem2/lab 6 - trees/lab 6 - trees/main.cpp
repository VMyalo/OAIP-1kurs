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
            << "Выберите операцию: " << endl
            << "1. Создать AVL-дерево/Добавить n элементов в дерево." << endl // готово
            << "2. Вывести элементы (красиво)." << endl // готово
            << "3. Найти элемент по ключу." << endl // готово
            << "4. Удалить элемент." << endl // готово
            << "5. Очистить дерево." << endl // готово
            << "6. ИДЗ: Определить глубину дерева." << endl // готово
            << "7. Вывести элементы дерева обходами." << endl // готово
            << "8. Завершить программу." << endl // готово
            << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            system("cls");
            int n, buf;
            char c_buf[100];
            std::cout << "Введите кол-во элементов для дерева:\n";
            std::cin >> n;
            std::cout << "Введите " << n << " элементов дерева:\n";

            for (int i = 0; i < n; i++)
            {
                std::cout << i + 1 << "." << endl;
                std::cout << "Введите ключ: ";
                std::cin >> buf;
                std::cout << "Введите текст: ";
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

            std::cout << "Введите ключ элемента, который хотите найти: ";
            std::cin >> buf;

            char* result_p = tree.search(buf);

            if (result_p == nullptr)
                std::cout << "Такого элемента нет." << endl;
            else
            {
                std::cout << "Элемент найден: ";
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

            std::cout << "Введите ключ элемента, который хотите удалить: ";
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

            std::cout << "Высота дерева: " << endl;

            std::cout << "Используя поле \"height\" AVL-дерева: " << tree.depth() << endl;
            std::cout << "Используя рекурсивный обход всего дерева: " << tree.calculate_root_depth() << endl;

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