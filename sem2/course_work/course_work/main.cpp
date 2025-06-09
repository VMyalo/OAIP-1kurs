#include <iostream>
#include <fstream>
#include <locale>
#include <Windows.h>
#include <cctype>

#include "visitor.hpp"
#include "date.hpp"
#include "checks.hpp"
#include "file_functions.hpp"
#include "functions.hpp"

using namespace std;

int main()
{
    setlocale(LC_ALL, "RU");
    char path[150] = "binary_files/visitors.bin";

    while (true)
    {
        system("cls");
        int choice;

        cout << "������ ����: " << path << endl;

        cout << "1. ������� ����� ���� (���������, ���� ������ ��� ������������� ����� - �� ���������!)." << endl // ������
             << "2. �������� ������� �� �����." << endl // ������
             << "3. �������� ������ � ����." << endl // ������
             << "4. �������������� ������� � �����." << endl // ������
             << "5. �������� ������� � �����." << endl // ������
             << "6. �������� ����� � ����� �� ��� ����������." << endl // ������
             << "7. �������� ����� � ����� �� �������� ����������� ������." << endl // ������
             << "8. ������� ���������� �� �������� ����������� ������." << endl // ������
             << "9. ���������� ������� �� ���� � ������� ���������." << endl // ������
             << "10. ���������� ��������� �� ��� ���������� � ���������� �������." << endl // ������
             << "11. ����� ����������� �� ������ � ����." << endl // ������
             << "12. ���������� �� �����������." << endl // ������
             << "13. ������������ ������ ��� ��������� ����� (�� ��������� - \"binary_files/visitors.bin\")." << endl // ������
             << "14. ������� ���������." << endl; // ������

        cin >> choice;
        cin.ignore();
        system("cls");
        switch (choice)
        {
        case 1:
        {
            char buf_path[136]; // 150 - 14
            char direct_path[150] = "binary_files/"; //14
            do {
                Secure_Input(buf_path, sizeof(buf_path),
                    "������� ��� ��� ������ ����� (��������� �����, �����, �������, _-.): ");
            } while (!isValidPath(buf_path));

            strcat_s(direct_path, 150, buf_path); // => binary_files/_name_.bin

            ofstream out;
            out.open(direct_path, ios::out);
            if (out.is_open() == true)
            {
                cout << "���� ��� ���������� � ������� � ����������� � ��������� \"" << buf_path << "\" ��� ������!" << endl;
                strcpy_s(path, 150, direct_path);
            }
            else
                cout << "������ �������� �����. ���������� ��� ���." << endl;
            out.close();

            system("pause");
            break;
        }
        case 2:

            ViewFile(path);

            system("pause");
            break;
        case 3:
            visitor vis;

            vis.create();
            SaveToFile(vis, path);

            cout << "������ ��������� � ����!" << endl;

            system("pause");
            break;
        case 4:

            if (EditFile(path) == 1)
            {
                cout << "���� �������!" << endl;
            }
            else
            {
                cout << "���� �� �������!" << endl;
            }

            system("pause");
            break;
        case 5:

            if (DeleteRecordFile(path) == 1)
            {
                cout << "���� �������!" << endl;
            }
            else
            {
                cout << "���� �� �������!" << endl;
            }

            system("pause");
            break;

        case 6:
        {
            visitor* list = new visitor[100];
            int n_visitors = LineSearchInFile(path, list);

            cout << "�������: " << n_visitors << "." << endl;

            char file_name[100] = "results\\line_search_result.txt";
            ListToTxt(list, file_name, n_visitors);

            cout << "���������� ������ �������� � ���� \"" << file_name << "\"" << endl;

            system("pause");
            delete[] list;
            break;
        }
        case 7:
        {
            cout << "������� �������� ������, ������ �� ������� ������ �����: ";
            char key[100];
            cin.getline(key, 100);

            visitor* list = new visitor[100];
            int n_visitors = BinarySearch(path, key, list);

            cout << "�������: " << n_visitors << "." << endl;

            char file_name[100] = "results\\binary_search_result.txt";
            ListToTxt(list, file_name, n_visitors);

            cout << "���������� ������ �������� � ���� \"" << file_name << "\"" << endl;

            delete[] list;
            system("pause");
            break;
        }
        case 8:
        {
            visitor* list = new visitor[100];
            int n_visitors = QuickSort(path, list);

            char file_name[100] = "results\\quick_sort_result.txt";
            ListToTxt(list, file_name, n_visitors);

            cout << "��������������� ������ ������� � ���� \"" << file_name << "\"" << endl;

            delete[] list;
            system("pause");
            break;
        }
        case 9:
        {
            visitor* list = new visitor[100];
            int n_visitors = ChoiceSort(path, list);

            char file_name[100] = "results\\choice_sort_result.txt";
            ListToTxt(list, file_name, n_visitors);

            cout << "��������������� ������ ������� � ���� \"" << file_name << "\"" << endl;

            delete[] list;
            system("pause");
            break;
        }
        case 10:
        {
            visitor* list = new visitor[100];
            int n_visitors = InsertSort(path, list);

            char file_name[100] = "results\\insert_sort_result.txt";
            ListToTxt(list, file_name, n_visitors);

            cout << "��������������� ������ ������� � ���� \"" << file_name << "\"" << endl;

            delete[] list;
            system("pause");
            break;
        }
        case 11:
        {
            visitor* list = new visitor[100];
            char service[100];
            char date[17];
            char file_name[100] = "results\\search_for_service_and_date_result.txt";

            Secure_Input(service, sizeof(service),
                "������� �������� ����������� ������: ");

            do {
                Secure_Input(date, sizeof(date),
                    "������� ����, �� ������� ����� ������������� ���������� (� ������� ��.��.��.��.����): ");
            } while (!isValidDate(date, true, true));

            int n_visitors = BinarySearch(path, service, list); //����� ����� ��������� ������ ������ � ������ ���. �������
            n_visitors = FilterByDate(date, list, n_visitors); //����� ����� ��������� ������ ������ ������
            InsertSort(list, n_visitors);

            ListToTxt(list, file_name, n_visitors);

            cout << "��������������� ������ ������� � ���� \"" << file_name << "\"" << endl;

            delete[] list;
            system("pause");
            break;
        }
        case 12:
        {
            visitor* list = new visitor[100];

            // ����. ��� ������� ���������� ����� ���, ��� �������� ���� ����� �����.
            // �����, ����� ��� ������ �������� �� ��������� ����� �����-�� ������
            // � ���������� ����������� �� ���� ����������� �� ���� ������.
            system("del /q results\\statistics\\*.txt"); 
            system("del /q results\\statistics\\services\\*.txt");
            system("cls");

            // ��� ������� �������� ����������:
            //system("rm -r -Force results/statistics");
            //system("mkdir results/statistics");

            VisitorStat(path, list);
            
            cout << "���������� ����������� ���������� ����� ���������� � ����� \"results/statictics/\"!" << endl;

            system("pause");
            break;
        }
        case 13:
        {
            char buf_path[136]; // 150 - 14
            char direct_path[150] = "binary_files/"; //14

            do {
                Secure_Input(buf_path, sizeof(path),
                    "������� ��� ����� (��������� �����, �����, �������, _-.): ");
            } while (!isValidPath(buf_path));

            strcat_s(direct_path, 150, buf_path); // => binary_files/_name_.bin

            ofstream in;
            in.open(direct_path, ios::app, ios::binary);
            if (in.is_open() == true)
            {
                cout << "���� ��� ���������� � ������� � ����������� � ��������� \"" << buf_path << "\" ��� ������!" << endl;
                strcpy_s(path, 150, direct_path);
            }
            else
                cout << "������ ��������. ���������� ��� ���. ��� ����� �� ���������: visitors.bin" << endl;
            in.close();

            system("pause");
            break;
        }
        case 14:
            return 0;
        default:
        {
            break;
        }
        }
    }
}