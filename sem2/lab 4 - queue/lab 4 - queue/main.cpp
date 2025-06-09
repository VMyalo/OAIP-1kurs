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

		cout << "�������� �����: " << endl
			<< "1. �������� ��������������� ������." << endl
			<< "2. �������� �������� � ������ � ������." << endl
			<< "3. �������� �������� � ������ � �����." << endl
			<< "4. ������� ������� �� ������ (�� ������) (�������������� ���� �������� ������� � ������, ��������)." << endl
			<< "5. ������� ������� �� ������ (�� �����)." << endl
			<< "6. �������� ������, �� �������� ��������." << endl
			<< "7. �������� ������, �� �������� �������� (������)." << endl
			<< "8. ������� ������� �� �����." << endl
			<< "9. ������������� ������ � ������������ � ���." << endl
			<< "10. ����� �� ���������." << endl;
		cout << "��� �����: ";
		cin >> choice;

		switch (choice)
		{
		case 1: // ������� ������
		{
			system("cls");

			list.delete_all();

			cout << "������ ������!" << endl;

			system("pause");
			break;
		}
		case 2: // �������� ������� � ������ ������
		{
			system("cls");

			std::cout << "������� ����� ��������� ��� ����������: ";
			std::cin >> n;
			std::cout << "������� �������� ������:" << endl;

			for (int i = 0; i < n; i++)
			{
				std::cin >> buf;
				list.push_front(buf);
			}

			cout << endl << "������!" << endl;

			system("pause");
			break;
		}
		case 3: // �������� ������� � ������ �����
		{
			system("cls");

			std::cout << "������� ����� ��������� ��� ����������: ";
			std::cin >> n;
			std::cout << "������� �������� ������:" << endl;

			for (int i = 0; i < n; i++)
			{
				std::cin >> buf;
				list.push_back(buf);
			}

			cout << endl << "������!" << endl;

			system("pause");
			break;
		}
		case 4: // ������� ������� �� ������ �� ������
		{
			system("cls");
			cout << "�� ������� �������: " << list.pop_from_front() << endl;

			system("pause");
			break;
		}
		case 5: // ������� ������� �� ������ �� �����
		{
			system("cls");
			cout << "�� ������� �������: " << list.pop_from_back() << endl;

			system("pause");
			break;
		}
		case 6: // ������� ������
		{
			system("cls");
			list.show();

			cout << endl;

			system("pause");
			break;
		}
		case 7: // ������� ������
		{
			system("cls");
			list.show_reverse();

			cout << endl;

			system("pause");
			break;
		}
		case 8: // ������� �� �����
		{
			system("cls");
			
			cout << "������� ���� ��������, ������� ������ �������: ";
			cin >> buf;

			list.delete_item(buf);

			cout << endl;

			system("pause");
			break;
		}
		case 9: // ���
		{
			system("cls");

			list.IDZ();

			system("pause");
			break;
		}
		case 10: // ������� ������ � �����
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