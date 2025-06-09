#include <iostream>
#include <locale>
#include "queue.cpp"
using namespace std;

int main()
{
	setlocale(LC_ALL, "RU");

	int n, buf;
	int choice;

	DLS list;

	while (true)
	{
		system("cls");

		cout << "Выберите опцию: " << endl
			<< "1. Очистить двунаправленный список." << endl
			<< "2. Добавить элементы в список В НАЧАЛО." << endl
			<< "3. Добавить элементы в список В КОНЕЦ." << endl
			<< "4. Достать элемент из списка (из начала) (предварительно надо добавить элемент в список, очевидно)." << endl
			<< "5. Достать элемент из списка (из конца)." << endl
			<< "6. Показать список, не доставая элементы." << endl
			<< "7. Показать список, не доставая элементы (реверс)." << endl
			<< "8. Удалить элемент по ключу." << endl
			<< "9. Преобразовать список в соответствии с ИДЗ." << endl
			<< "10. Выйти из программы." << endl;
		cout << "Ваш выбор: ";
		cin >> choice;

		switch (choice)
		{
		case 1: // создать список
		{
			system("cls");

			list.delete_all();

			cout << "Список очищен!" << endl;

			system("pause");
			break;
		}
		case 2: // добавить элемент в список вперед
		{
			system("cls");

			std::cout << "Введите число элементов для добавления: ";
			std::cin >> n;
			std::cout << "Вводите элементы списка:" << endl;

			for (int i = 0; i < n; i++)
			{
				std::cin >> buf;
				list.push_front(buf);
			}

			cout << endl << "Готово!" << endl;

			system("pause");
			break;
		}
		case 3: // добавить элемент в список назад
		{
			system("cls");

			std::cout << "Введите число элементов для добавления: ";
			std::cin >> n;
			std::cout << "Вводите элементы списка:" << endl;

			for (int i = 0; i < n; i++)
			{
				std::cin >> buf;
				list.push_back(buf);
			}

			cout << endl << "Готово!" << endl;

			system("pause");
			break;
		}
		case 4: // достать элемент из списка из начала
		{
			system("cls");
			cout << "Вы достали элемент: " << list.pop_from_front() << endl;

			system("pause");
			break;
		}
		case 5: // достать элемент из списка из конца
		{
			system("cls");
			cout << "Вы достали элемент: " << list.pop_from_back() << endl;

			system("pause");
			break;
		}
		case 6: // вывести список
		{
			system("cls");
			list.show();

			cout << endl;

			system("pause");
			break;
		}
		case 7: // вывести список
		{
			system("cls");
			list.show_reverse();

			cout << endl;

			system("pause");
			break;
		}
		case 8: // удалить по ключу
		{
			system("cls");
			
			cout << "Введите ключ элемента, который хотите удалить: ";
			cin >> buf;

			list.delete_item(buf);

			cout << endl;

			system("pause");
			break;
		}
		case 9: // идз
		{
			system("cls");

			list.IDZ();

			system("pause");
			break;
		}
		case 10: // удалить список и выйти
		{
			list.delete_all();

			return 0;
		}
		default:
		{
			break;
		}
		}
	}

	return 0;
}