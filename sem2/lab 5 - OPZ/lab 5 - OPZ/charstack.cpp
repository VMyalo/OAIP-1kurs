#include <iostream>
using namespace std;

class CharStack
{
private:
	struct Cell
	{
		char value;
		Cell* next;
	};

	Cell* top = nullptr;

	void output(Cell* a)
	{
		if (a == nullptr) return;
		output(a->next);
		std::cout << a->value << " ";
	}

public:
	void push(char item)
	{
		Cell* c = new Cell;
		c->value = item;
		c->next = top;
		top = c;
	}
	char pop()
	{
		Cell* a;
		if (top != nullptr)
		{
			a = top;
			char buf = a->value;
			top = a->next;

			delete a;

			return buf;
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
	char top_e()
	{
		if (top == nullptr) return 0;
		return top->value;
	}
	
};