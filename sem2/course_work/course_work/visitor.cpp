#include "visitor.hpp"

/**
@brief ������� ������ � �������, ������ ���� \t ����� ������ �������
*/
void visitor::visitor_output()
{
    cout << "   1) ��� ����������: " << vis_name << endl
         << "   2) ���� ��������: " << b_day << endl
         << "   3) �������� ������: " << service << endl
         << "   4) ���� ������: " << date << endl
         << "   5) ��� �����: " << doc_name << endl
         << "   6) ���� ������: " << cost << endl;

    cout << "----------------------------------------------------" << endl;
}

/**
@brief ������� ������, �������� �������� �� ����
*/
void visitor::create() {
    // ���� ��� ����������
    do {
        Secure_Input(vis_name, sizeof(vis_name),
            "������� ��� ���������� (������ �����, ������� � �����): ");
    } while (!isValidName(vis_name));

    // ���� ���� ��������
    do {
        Secure_Input(b_day, sizeof(b_day),
            "������� ���� �������� (��.��.����): ");
    } while (!isValidDate(b_day));

    // ���� ������
    Secure_Input(service, sizeof(service),
        "������� �������� ������: ");

    // ���� ���� � ������� ��������� (���������� ���� ��������)
    do {
        Secure_Input(date, sizeof(date),
            "������� ���� ��������� (��:��.��.��.����): ");
    } while (!isValidDate(date, true));

    // ���� ��� �����
    do {
        Secure_Input(doc_name, sizeof(doc_name),
            "������� ��� ����� (������ �����, ������� � �����): ");
    } while (!isValidName(doc_name));

    // ���� ���������
    while (true) {
        cout << "������� ��������� ������: ";
        cin >> cost;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "������: ������� �������� ��������!\n";
            continue;
        }

        cin.ignore(); // ������� ������
        break;
    }
}