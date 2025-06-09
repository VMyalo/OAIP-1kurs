#include <iostream>
#include <locale>
using namespace std;

class Stack
{
private:
	struct Cell
	{
		int value;
		Cell* next;
	};

	Cell* top = nullptr;

	void output(Cell* a)
	{
		if (a == nullptr) return;
		output(a->next);
		std::cout << a->value << " ";
	}
	void pass(Cell* a, int& bottom_value, int& top_value, bool& flag)
	{
		if (a->next != nullptr)
		{
			pass(a->next, bottom_value, top_value, flag);
		}
		else
		{
			if (flag == 1)
			{
				bottom_value = a->value;
				a->value = top_value;
				flag = 0;
			}
			return;
		}
	}

public:
	void push(int item)
	{
		Cell* c = new Cell;
		c->value = item;
		c->next = top;
		top = c;
	}
	int pop()
	{
		Cell* a;
		if (top != nullptr)
		{
			a = top;
			top = a->next;
			return a->value;
		}
		else
		{
			cout << endl << "Стек пустой!!!!" << endl;
			return 0;
		}
	}
	void Del_All()
	{
		while (top != nullptr)
		{
			Cell* buf = top;
			top = top->next;
			delete buf;
		}

		std::cout << endl << "Память очищена!" << endl;
	}
	void show()
	{
		std::cout << "Ваш стек в порядке от нижнего элемента до верхнего: " << endl;
		output(top);
		cout << endl;
	}
	void replace()
	{
		int buf_top_value = top->value;
		int buf_bottom_value;
		bool flag = 1;
		pass(top, buf_bottom_value, buf_top_value, flag);

		top->value = buf_bottom_value;
	}

	void smart_replace()
	{
		Cell* a = top;
		Cell* buf = nullptr;

		if (a->next == nullptr)
			return;

		if ((a->next)->next == nullptr)
		{
			buf = a->next;
			top = buf;
			buf->next = a;
			a->next = nullptr;
			
			return;
		}


		while (true)
		{
			if ((a->next)->next == nullptr)
			{
				buf = (a->next);
				(a->next)->next = top->next;
				a->next = top;
				top->next = nullptr;

				break;
			}
			else
				a = a->next;
		}

		top = buf; //(a->next)->next
	}
};

int main()
{
    setlocale(LC_ALL, "RU");
    int n, buf;
	int choice;

	Stack steck;

	while (true)
	{
		system("cls");

		cout << "Выберите опцию: " << endl
			<< "1. Очистить стек." << endl
			<< "2. Добавить элементы в стек (предварительно надо создать стек)." << endl
			<< "3. Достать элемент из стека (предварительно надо добавить элемент в стек)." << endl
			<< "4. Показать стек, не доставая элементы." << endl
			<< "5. Преобразовать стек в соответствии с ИДЗ." << endl
			<< "6. Выйти из программы." << endl;
		cout << "Ваш выбор: ";
		cin >> choice;

		switch (choice)
		{
		case 1: // создать стек
		{
			system("cls");
			steck.Del_All();

			Stack steck;

			

			system("pause");
			break;
		}
		case 2: // добавить элемент в стек
		{
			system("cls");

			std::cout << "Введите число элементов для добавления: ";
			std::cin >> n;
			std::cout << "Вводите элементы стека:" << endl;

			for (int i = 0; i < n; i++)
			{
				std::cin >> buf;
				steck.push(buf);
			}

			cout << endl << "Готово!" << endl;

			system("pause");
			break;
		}
		case 3: // достать элемент из стека
		{
			system("cls");
			cout << "Вы достали элемент: " << steck.pop() << endl;

			system("pause");
			break;
		}
		case 4: // вывести стек
		{
			system("cls");
			steck.show();

			system("pause");
			break;
		}
		case 5: // идз
		{
			system("cls");
			steck.smart_replace();
			cout << "Готово! Используйте опцию \"Показать стек, ...\" для просмотра результата!" << endl;

			system("pause");
			break;
		}
		case 6: // удалить стек и выйти
		{
			steck.Del_All();

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