#include <iostream>
using namespace std;

class DLS
{
private:
	struct Cell
	{
		int value;
		Cell* next;
		Cell* prev;
	};

	Cell* begin = nullptr;
	Cell* end = nullptr;

	void add(int item, int option)
	{
		if (begin == nullptr && end == nullptr)
		{
			Cell* c = new Cell;
			c->value = item;
			c->next = c->prev = nullptr;
			begin = end = c;
		}
		else if (option == 1) // в начало
		{
			Cell* c = new Cell;
			c->value = item;
			c->prev = nullptr;
			c->next = begin;
			begin->prev = c;

			begin = c;
		}
		else if (option == 2) // в конец
		{
			Cell* c = new Cell;
			c->value = item;
			c->next = nullptr;
			c->prev = end;
			end->next = c;

			end = c;
		}
	}
	int pop(int option)
	{
		if (begin == nullptr && end == nullptr)
		{
			cout << "¬аш список пустой, просьба заполнить и попробовать снова! „тобы не расстраивались, выдал вам нолик.";
			return 0;
		}

		if (option == 1)
		{
			Cell* a = begin;
			int buf = a->value;
			begin = begin->next;

			delete a;

			if (begin == nullptr)
				end = nullptr;
			else
			{
				begin->prev = nullptr;
			}
			
			return buf;
		}
		else if (option == 2)
		{
			Cell* a = this->end;
			int buf = a->value;
			this->end = this->end->prev;

			delete a;

			if (this->end == nullptr) 
				this->begin = nullptr;
			else
			{
				end->next = nullptr;
			}

			
			
			return buf;
		}
	}


public:

	void push_front(int item)
	{
		add(item, 1);
	}

	void push_back(int item)
	{
		add(item, 2);
	}

	int pop_from_front()
	{
		return pop(1);
	}

	int pop_from_back()
	{
		return pop(2);
	}

	void show()
	{
		cout << "¬аш список с начала до конца: " << endl;
		Cell* p = begin;
		while (p != nullptr)
		{
			cout << p->value << " ";
			p = p->next;
		}
	}

	void delete_item(int item)
	{
		Cell* p = begin;
		while (p != nullptr)
		{
			if (p->value == item)
			{
				if (p->prev != nullptr && p->next != nullptr)
				{
					(p->prev)->next = p->next;
					(p->next)->prev = p->prev;

					delete p;
				}
				else if (p->prev == nullptr)
				{
					this->pop_from_front();
				}
				else if (p->next == nullptr)
				{
					this->pop_from_back();
				}

				cout << "Ёлемент удален!";
				return;
			}

			p = p->next;
		}
		
		cout << "Ёлемент не найден!";
		return;
	}

	void delete_all()
	{
		Cell* p = begin;
		while (p != nullptr)
		{
			Cell* buf = p;
			p = p->next;

			delete buf;
		}

		begin = nullptr;
		end = nullptr;
	}

	void IDZ()
	{
		if (begin == nullptr || end == nullptr)
		{
			cout << "¬аш список пустой, просьба заполнить и попробовать снова!";
			return;
		}
		if (begin->next == nullptr)
		{
			cout << "Ќ≈“!";
			return;
		}

		Cell* p_front = begin;
		Cell* p_back = end;

		begin = p_back;
		end = p_front;

		p_front->prev = p_back->prev;
		p_back->prev->next = p_front;
		p_back->prev = nullptr;

		p_back->next = p_front->next;
		p_front->next->prev = p_back;
		p_front->next = nullptr;

		return;
	}

	void show_reverse()
	{
		cout << "¬аш список с конца до начала: " << endl;
		Cell* p = end;
		while (p != nullptr)
		{
			cout << p->value << " ";
			p = p->prev;
		}
	}
};