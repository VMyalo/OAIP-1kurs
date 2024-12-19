#include <iostream>
#include <locale>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <iomanip>
#include <stdlib.h>
using namespace std;

struct Person {
    string surname = "Null";
    string group = "000000";
    int physics = 0;
    int maths = 0;
    int inform = 0;
    double gpa = 0;
};

bool path_request(string &path)
{
    int choice;
    bool flag = 0;

    string standart_path1("..\\file_folder\\file.txt");
    string standart_path2("..\\file_folder\\");

    system("cls");
    cout << "Требуется путь к файлу/папке. Выберите действие:" << endl;
    cout << "1. Стандартный путь в корне проекта (путь к файлу file.txt)." << endl;
    cout << "2. Стандартный путь в корне проекта (путь к папке file_folder)." << endl;
    cout << "3. Ввести вручную." << endl;

    cin >> choice;

    switch (choice)
    {
        case 1:
            path = standart_path1;
            flag = false;
            break;
        case 2:
            path = standart_path2;
            flag = false;
            break;
        case 3:
            cout << "Введите путь к файлу/папке: " << endl;
            cin.ignore();
            getline(cin, path);
            flag = true;
            break;
    }

    system("cls");
    
    cout << path << endl;

    return flag;
}

void create_file()
{
    string file_path;
    string file_name;

    bool flag = path_request(file_path);
    if (file_path[file_path.size() - 1] != '\\') file_path = file_path + '\\';

    cout << "Введите имя для создаваемого файла:" << endl;

    if (flag == 0) cin.ignore();
    getline(cin, file_name); //Доделывать отсюда

    file_path = file_path + file_name;

    ofstream out;
    out.open(file_path);

    if (!out.is_open()) {
        cout << "Ошибка создания файла!" << endl;
    }
    else {
        cout << "Файл создан!" << endl;
    }

    system("pause");
    out.close();
    system("cls");
}

void view_file()
{
    string file_path;
    string line;
    Person vector_line;
    vector<Person> vector_file;

    path_request(file_path);

    ifstream in;
    in.open(file_path);

    //if (!in.is_open()) {
    //    cout << "Ошибка открытия файла!" << endl;
    //}
    //else {
    //    while (!in.eof()) {
    //        getline(in, line);
    //        cout << line << endl;
    //    }


    //}

    fstream file;
    file.open(file_path);

    if (!file.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
    }
    else {

        while (!file.eof())
        {
            file >> vector_line.surname;
            file >> vector_line.group;
            file >> vector_line.physics;
            file >> vector_line.maths;
            file >> vector_line.inform;
            file >> vector_line.gpa;

            vector_file.push_back(vector_line);
        }

        cout << "x. ";
        cout << setw(15) << "surname";
        cout << setw(10) << "group";
        cout << setw(7) << "phys";
        cout << setw(7) << "math";
        cout << setw(9) << "inform";
        cout << setw(10) << "gpa" << endl;

        for (int i = 0; i < vector_file.size(); i++)
        {
            cout << i << ". ";
            cout << setw(15) << vector_file[i].surname;
            cout << setw(10) << vector_file[i].group;
            cout << setw(7) << vector_file[i].physics;
            cout << setw(7) << vector_file[i].maths;
            cout << setw(9) << vector_file[i].inform;
            cout << setw(10) << vector_file[i].gpa << endl;
        }
    }

    
    system("pause");
    in.close();
    system("cls");
}

void add_to_file()
{
    string file_path;
    Person line;

    path_request(file_path);

    fstream file(file_path, ios::app);

    if (!file.is_open())
    {
        cout << "Ошибка открытия файла!" << endl;
    }
    else
    {
        cout << "Введите строку для дозаписи в файл:" << endl;
        
        cin >> line.surname;
        cin >> line.group;
        cin >> line.physics;
        cin >> line.maths;
        cin >> line.inform;
        line.gpa = (line.physics + line.maths + line.inform) / 3.0;

        file << endl << line.surname << " " << line.group << " " << line.physics << " " << line.maths << " " << line.inform << " " << line.gpa;
    }

    system("pause");
    file.close();
    system("cls");
}

void task_solve()
{
    string file_path;
    string line;

    vector<Person> vector_file;
    Person vector_line;

    string output_path("..\\file_folder\\output.txt");

    path_request(file_path);

    fstream file(file_path);
    ofstream output(output_path);

    if (!file.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
    }
    else {
        while (!file.eof())
        {
            file >> vector_line.surname;
            file >> vector_line.group;
            file >> vector_line.physics;
            file >> vector_line.maths;
            file >> vector_line.inform;
            file >> vector_line.gpa;

            vector_file.push_back(vector_line);
        }

        for (int i = 0; i < vector_file.size(); i++)
        {
            cout << vector_file[i].surname << " ";
            cout << vector_file[i].group << " ";
            cout << vector_file[i].physics << " ";
            cout << vector_file[i].maths << " ";
            cout << vector_file[i].inform << " ";
            cout << vector_file[i].gpa << endl;

            if ((vector_file[i].maths == 8 || vector_file[i].maths == 9) && vector_file[i].surname[0] == 'A')
            {
                output << vector_file[i].surname << " ";
                output << vector_file[i].group << " ";
                output << vector_file[i].physics << " ";
                output << vector_file[i].maths << " ";
                output << vector_file[i].inform << " ";
                output << vector_file[i].gpa << endl;
            }
        }
    }

    system("pause");
    file.close();
    output.close();
    system("cls");
}

void edit_file()
{
    string file_path;
    Person vector_line;
    vector<Person> vector_file;
    int x, y;
    int number = 0;
    string surname;

    path_request(file_path);

    fstream file;
    file.open(file_path);

    if (!file.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
    }
    else {

        while (!file.eof())
        {
            file >> vector_line.surname;
            file >> vector_line.group;
            file >> vector_line.physics;
            file >> vector_line.maths;
            file >> vector_line.inform;
            file >> vector_line.gpa;

            vector_file.push_back(vector_line);
        }

        cout << "x. ";
        cout << setw(15) << "0";
        cout << setw(10) << "1";
        cout << setw(5) << "2";
        cout << setw(5) << "3";
        cout << setw(5) << "4";
        cout << setw(10) << "nezya" << endl;

        for (int i = 0; i < vector_file.size(); i++)
        {
            cout << i << ". ";
            cout << setw(15) << vector_file[i].surname;
            cout << setw(10) << vector_file[i].group;
            cout << setw(5) << vector_file[i].physics;
            cout << setw(5) << vector_file[i].maths;
            cout << setw(5) << vector_file[i].inform;
            cout << setw(10) << vector_file[i].gpa << endl;
        }

        cout << "Выберите поле, которое хотите изменить (#строки + пробел + #столбца):" << endl;
        cin >> x;
        cin >> y;

        cout << "Введите значение: ";
        if (x == 0)
        {
            cin.ignore();
            getline(cin, surname);
        }
        else
        {
            cin >> number;
        }

        switch (y)
        {
            case 0:
                vector_file[x].surname = surname;
                break;
            case 1:
                vector_file[x].group = number;
                break;
            case 2:
                vector_file[x].physics = number;
                break;
            case 3:
                vector_file[x].maths = number;
                break;
            case 4:
                vector_file[x].inform = number;
                break;
            default:
                cout << "Ошибка.";
                system("pause");
                file.close();
                system("cls");
                return;
        }

        if (y == 2 || y == 3 || y == 4)
        {
            vector_file[x].gpa = (vector_file[x].physics + vector_file[x].maths + vector_file[x].inform) / 3.0;
        }
        file.close();
        file.open(file_path, ios::out);
        for (int i = 0; i < vector_file.size(); i++)
        {
            file << vector_file[i].surname << " ";
            file << vector_file[i].group << " ";
            file << vector_file[i].physics << " ";
            file << vector_file[i].maths << " ";
            file << vector_file[i].inform << " ";
            file << vector_file[i].gpa;
            if (i != vector_file.size() - 1)
            {
                file << endl;
            }
        }

        cout << endl;
        cout << "Готово!";
    }
        
        

    system("pause");
    file.close();
    system("cls");
}

void delete_in_file()
{
    string file_path;
    Person vector_line;
    vector<Person> vector_file;
    int x;

    path_request(file_path);

    fstream file;
    file.open(file_path);

    if (!file.is_open()) {
        cout << "Ошибка создания файла!" << endl;
    }
    else {

        while (!file.eof())
        {
            file >> vector_line.surname;
            file >> vector_line.group;
            file >> vector_line.physics;
            file >> vector_line.maths;
            file >> vector_line.inform;
            file >> vector_line.gpa;

            vector_file.push_back(vector_line);
        }

        for (int i = 0; i < vector_file.size(); i++)
        {
            cout << i << ". ";
            cout << setw(15) << vector_file[i].surname;
            cout << setw(10) << vector_file[i].group;
            cout << setw(5) << vector_file[i].physics;
            cout << setw(5) << vector_file[i].maths;
            cout << setw(5) << vector_file[i].inform;
            cout << setw(10) << vector_file[i].gpa << endl;
        }

        cout << "Выберите строку, которую хотите удалить: ";
        cin >> x;

        file.close();
        file.open(file_path, ios::out);
        for (int i = 0; i < vector_file.size(); i++)
        {
            if (i != x) {
                file << vector_file[i].surname << " ";
                file << vector_file[i].group << " ";
                file << vector_file[i].physics << " ";
                file << vector_file[i].maths << " ";
                file << vector_file[i].inform << " ";
                file << vector_file[i].gpa;
                if (i != vector_file.size() - 1 && i != vector_file.size())
                {
                    file << endl;
                }
            }
        }

        cout << endl;
        cout << "Готово!";
    }

    system("pause");
    file.close();
    system("cls");
}

bool sort_choice(int choice, vector<Person>& vector_file, unsigned i)
{
    if (i == 0 || i >= vector_file.size()) {
        return false;
    }

    switch (choice)
    {
    case 1:
        return (vector_file[i - 1].group < vector_file[i].group);
    case 2:
        return (vector_file[i - 1].physics < vector_file[i].physics);
    case 3:
        return (vector_file[i - 1].maths < vector_file[i].maths);
    case 4:
        return (vector_file[i - 1].inform < vector_file[i].inform);
    case 5:
        return (vector_file[i - 1].gpa < vector_file[i].gpa);
    case 6:
        return (vector_file[i - 1].group > vector_file[i].group);
    case 7:
        return (vector_file[i - 1].physics > vector_file[i].physics);
    case 8:
        return (vector_file[i - 1].maths > vector_file[i].maths);
    case 9:
        return (vector_file[i - 1].inform > vector_file[i].inform);
    case 10:
        return (vector_file[i - 1].gpa > vector_file[i].gpa);
    default:
        return false;
    }
}

void sort_file()
{
    string file_path;
    Person vector_line;
    vector<Person> vector_file;
    vector<string> str_queue;


    int choice, choice_2;

    path_request(file_path);

    fstream file;
    file.open(file_path);

    if (!file.is_open()) {
        cout << "Ошибка создания файла!" << endl;

        system("pause");
        file.close();
        system("cls");

        return;
    }

    while (!file.eof())
    {
        file >> vector_line.surname;
        file >> vector_line.group;
        file >> vector_line.physics;
        file >> vector_line.maths;
        file >> vector_line.inform;
        file >> vector_line.gpa;

        vector_file.push_back(vector_line);
    }

    for (int i = 0; i < vector_file.size(); i++)
    {
        cout << i << ". ";
        cout << setw(15) << vector_file[i].surname;
        cout << setw(10) << vector_file[i].group;
        cout << setw(5) << vector_file[i].physics;
        cout << setw(5) << vector_file[i].maths;
        cout << setw(5) << vector_file[i].inform;
        cout << setw(10) << vector_file[i].gpa << endl;
    }

    cout << "Выберите, по какому параметру будет выполняться сортировка:" << endl
         << "1. По символьным данным (по алфавиту)" << endl
         << "2. По числовым данным." << endl;
    cout << "Ваш выбор: ";
    cin >> choice;

    switch (choice)
    {
        case 1:
        {
            bool sorted{};
            do
            {
                sorted = true;      // остается true, если строки отсортированы
                Person temp;   // переменная для обмена значениями
                for (unsigned i{ 1 }; i < vector_file.size(); i++)
                {
                    // если предыдущая строка больше последующей
                    if (vector_file[i - 1].surname > vector_file[i].surname)
                    {
                        // обмениваем значения
                        temp = vector_file[i];
                        vector_file[i] = vector_file[i - 1];
                        vector_file[i - 1] = temp;
                        sorted = false;
                    }
                }
            } while (!sorted);

            break;
        }
        case 2:
        {
            cout << "Выберите, по какому числовому параметру будет выполнятся сортировка:" << endl
                << "1. По номеру группы." << endl
                << "2. По оценке по физике." << endl
                << "3. По оценке по математике." << endl
                << "4. По оценке по информатике." << endl
                << "5. По среднему баллу." << endl
                << "6. По номеру группы (убывание)." << endl
                << "7. По оценке по физике (убывание)." << endl
                << "8. По оценке по математике (убывание)." << endl
                << "9. По оценке по информатике (убывание)." << endl
                << "10. По среднему баллу (убывание)." << endl;
            cout << "Ваш выбор: ";
            cin >> choice_2;

            bool sorted{};
            do
            {
                sorted = true;      // остается true, если строки отсортированы
                Person temp;   // переменная для обмена значениями
                for (unsigned i{ 1 }; i < vector_file.size(); i++)
                {
                    // если предыдущая строка меньше последующей
                    if (sort_choice(choice_2, vector_file, i))
                    {
                        // обмениваем значения
                        temp = vector_file[i];
                        vector_file[i] = vector_file[i - 1];
                        vector_file[i - 1] = temp;
                        sorted = false;
                    }
                }
            } while (!sorted);

            break;
        }
    }

    file.close();
    file.open(file_path, ios::out);
    for (int i = 0; i < vector_file.size(); i++)
    {
            file << vector_file[i].surname << " ";
            file << vector_file[i].group << " ";
            file << vector_file[i].physics << " ";
            file << vector_file[i].maths << " ";
            file << vector_file[i].inform << " ";
            file << vector_file[i].gpa;
            if (i != vector_file.size() - 1)
            {
                file << endl;
            }
    }

    cout << endl;
    cout << "Готово!";

    system("pause");
    file.close();
    system("cls");
}

int main()
{
    setlocale(LC_ALL, "RU");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    int choice;

    while (1)
    {
        cout << "Меню:" << endl << endl;

        cout << "1. Создание." << endl
             << "2. Просмотр." << endl
             << "3. Добавление." << endl
             << "4. Решение индивидуального задания." << endl
             << "5. Редактирование." << endl
             << "6. Удаление." << endl
             << "7. Сортировка." << endl << endl;

        cout << "Выберите пункт: ";
        cin >> choice;

        system("cls");
        switch (choice)
        {
            case 1:
                create_file();
                break;
            case 2:
                view_file();
                break;
            case 3:
                add_to_file();
                break;
            case 4:
                task_solve();
                break;
            case 5:
                edit_file();
                break;
            case 6:
                delete_in_file();
                break;
            case 7:
                sort_file();
                break;
            default:
                cout << "Повторите ввод.";
                system("cls");
                break;
        }
    }

    return 0;
}