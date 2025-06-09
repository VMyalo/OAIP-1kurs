#include "file_functions.hpp"



void ViewFile(const char* file_path)
{
    ifstream in;
    in.open(file_path, ios::binary);

    if (in.is_open() == false)
        cout << "������ �������� �����!" << endl;
    else
    {
        visitor vis;
        int num = 1;
        cout << "���� \"" << file_path << "\":" << endl;
        cout << "X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X" << endl;
        while (in.read(reinterpret_cast<char*>(&vis), sizeof(visitor)))
        {
            cout << num << ". " << endl;
            vis.visitor_output();

            num++;
        }
    }
    in.close();
}

void SaveToFile(visitor& vis, const char* path)
{
    ofstream out;
    out.open(path, ios::binary | ios::app);
    if (!out.is_open())
    {
        cout << "������ �������� �����!";
    }
    else
    {
        out.write((char*)&vis, sizeof(visitor));
    }
    out.close();
}

int DeleteRecordFile(const char* path)
{
    ifstream in;
    ofstream out;

    in.open(path, ios::binary);
    out.open("temp.bin", ios::binary);

    if (in.is_open() == false || out.is_open() == false)
    {
        cout << "������ �������� �����!/������ �������� ����� temp.bin!";
        in.close();
        out.close();
        return 0;
    }
    else
    {
        ViewFile(path);

        int choice;
        visitor vis;

        cout << "������� ����� ������, ������� ������ �������: ";
        cin >> choice;

        int i = 1;
        while (in.read(reinterpret_cast<char*>(&vis), sizeof(visitor)))
        {
            if (i != choice)
            {
                out.write(reinterpret_cast<char*>(&vis), sizeof(visitor));
            }

            i++;
        }
    }

    in.close();
    out.close();
    remove(path);
    int a = rename("temp.bin", path);
    return 1;
}

/**
@brief ����������� ������ � �������� ����� � ��������� �������� ������
@param path ���� � �������������� �����
@return 1 � ������ ��������� ��������������, 0 ��� ������ �������� ������
*/
int EditFile(const char* path)
{
    ifstream in;
    ofstream out;

    in.open(path, ios::binary);
    out.open("temp.bin", ios::binary);

    if (!in.is_open() || !out.is_open())
    {
        cout << "������ �������� �����!/������ �������� ����� temp.bin!";
        in.close();
        out.close();
        return 0;
    }

    ViewFile(path);

    int choice;
    visitor vis;

    cout << "������� ����� ������, ������� ������ ��������: ";
    cin >> choice;
    ClearInputBuffer(); // ������� ������ ����� ����� �����

    int i = 1;
    while (in.read(reinterpret_cast<char*>(&vis), sizeof(visitor)))
    {
        if (i == choice)
        {
            system("cls");
            cout << "������, ������� �� �������:" << endl;
            cout << "X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X" << endl;
            vis.visitor_output();

            bool flag = true;
            while (flag)
            {
                cout << "������� ����� ���������, ������� ������ ��������: ";
                int par_choice;
                cin >> par_choice;
                ClearInputBuffer(); // ������� ������ ����� ����� �����

                flag = false;
                switch (par_choice)
                {
                case 1:
                    do {
                        Secure_Input(vis.vis_name, sizeof(vis.vis_name),
                            "������� ����� ��� ���������� (������ �����, ������� � �����): ");
                    } while (!isValidName(vis.vis_name));
                    break;

                case 2:
                    do {
                        Secure_Input(vis.b_day, sizeof(vis.b_day),
                            "������� ����� ���� �������� ���������� (��.��.����): ");
                    } while (!isValidDate(vis.b_day, false, true));
                    break;

                case 3:
                    Secure_Input(vis.service, sizeof(vis.service),
                        "������� ����� �������� ������: ");
                    break;

                case 4:
                    do {
                        Secure_Input(vis.date, sizeof(vis.date),
                            "������� ����� ���� � ����� ��������� (��:��.��.��.����): ");
                    } while (!isValidDate(vis.date, true, true));
                    break;

                case 5:
                    do {
                        Secure_Input(vis.doc_name, sizeof(vis.doc_name),
                            "������� ����� ��� ����� (������ �����, ������� � �����): ");
                    } while (!isValidName(vis.doc_name));
                    break;

                case 6:
                    while (true) {
                        cout << "������� ����� ��������� ������: ";
                        cin >> vis.cost;
                        if (cin.fail()) {
                            cin.clear();
                            ClearInputBuffer();
                            cout << "������: ������� �������� ��������!\n";
                            continue;
                        }
                        ClearInputBuffer();
                        break;
                    }
                    break;

                default:
                    cout << "����� ��������� ��������� � �������� 1-6." << endl;
                    flag = true; // ��������� ������ ������ ���������
                    break;
                }
            }

            out.write(reinterpret_cast<char*>(&vis), sizeof(visitor));
        }
        else
        {
            out.write(reinterpret_cast<char*>(&vis), sizeof(visitor));
        }

        i++;
    }

    in.close();
    out.close();
    remove(path);
    if (rename("temp.bin", path)); // �������� ���������� if, ����� �� ���� ��������������.
    // � ������ ������ ���� ������ �� ����� �� ���������������.
    return 1;
}

/**
@brief ��������� ������ � ���� � �������� ���������
@param list - ������� �������
@param new_file_name - �������� ��������� �����
@param n - ���-�� ������� � �������
*/
int ListToTxt(visitor* list, char* new_file_name, int n)
{
    ofstream out;
    out.open(new_file_name, ios::out);
    if (out.is_open() == false) return -1;

    for (int i = 0; i < n; i++)
    {
        out << (i + 1) << "." << endl;

        out << "   1) ��� ����������: " << list[i].vis_name << endl
            << "   2) ���� ��������: " << list[i].b_day << endl
            << "   3) �������� ������: " << list[i].service << endl
            << "   4) ���� ������: " << list[i].date << endl
            << "   5) ��� �����: " << list[i].doc_name << endl
            << "   6) ���� ������: " << list[i].cost << endl;

        out << "----------------------------------------------------" << endl;
    }

    out.close();
    return 0;
}

/**
@brief ��������� �������� ���� � ������
@param path - ���� � �����
@param list - ������, � ������� ������������� ����
@return i - ����� �������
*/
int FileToList(const char* path, visitor* list)
{
    ifstream in;
    in.open(path, ios::binary);

    if (in.is_open() == false)
        return 0;

    visitor vis;
    int i = 0;
    while (in.read(reinterpret_cast<char*>(&vis), sizeof(visitor)))
    {
        list[i] = vis;
        i++;
    }

    return i;
}

/**
@brief �������� ������ ���� visitor � txt-����
@param path - ���� � �����
@param vis - ������, ������� ����� �������� � ����
@param i - ���������� ����� � �����
*/
int VisToTxt(char* path, visitor vis, int& i)
{
    ofstream out;
    out.open(path, ios::app);
    if (out.is_open() == false) return -1;

    out << i << "." << endl;

    out << "   1) ��� ����������: " << vis.vis_name << endl
        << "   2) ���� ��������: " << vis.b_day << endl
        << "   3) �������� ������: " << vis.service << endl
        << "   4) ���� ������: " << vis.date << endl
        << "   5) ��� �����: " << vis.doc_name << endl
        << "   6) ���� ������: " << vis.cost << endl;

    out << "----------------------------------------------------" << endl;
    i++;
    out.close();
    return 0;
}

/**
@brief ������� ������ � ������� �������� � ������ �����
@param list - ������ � ��������
@param service_list - ������ � ��������, ��� ��������
@param service_n - ����� �����
@param n - ����� ������� � list
*/
void ServiceTxtOutput(visitor* list, char** service_list, int service_n, int n)
{
    char* stat_path = new char[170];
    char std_path[35] = "results\\statistics\\services\\";

    for (int i = 0; i < service_n; i++)
    {
        strcpy_s(stat_path, 130, std_path);

        strcat_s(stat_path, 130, service_list[i]);
        strcat_s(stat_path, 130, "_statistics.txt");
        ofstream out;
        out.open(stat_path, ios::out);
        out.close();

        int k = 1;
        for (int j = 0; j < n; j++)
        {
            if (strcmp(service_list[i], list[j].service) == 0)
                VisToTxt(stat_path, list[j], k);
        }
    }

    delete[] stat_path;
}