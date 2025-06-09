#include "file_functions.hpp"



void ViewFile(const char* file_path)
{
    ifstream in;
    in.open(file_path, ios::binary);

    if (in.is_open() == false)
        cout << "Ошибка открытия файла!" << endl;
    else
    {
        visitor vis;
        int num = 1;
        cout << "Файл \"" << file_path << "\":" << endl;
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
        cout << "Ошибка открытия файла!";
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
        cout << "Ошибка открытия файла!/Ошибка создания файла temp.bin!";
        in.close();
        out.close();
        return 0;
    }
    else
    {
        ViewFile(path);

        int choice;
        visitor vis;

        cout << "Введите номер записи, которую хотите удалить: ";
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
@brief Редактирует запись в бинарном файле с проверкой вводимых данных
@param path Путь к редактируемому файлу
@return 1 в случае успешного редактирования, 0 при ошибке открытия файлов
*/
int EditFile(const char* path)
{
    ifstream in;
    ofstream out;

    in.open(path, ios::binary);
    out.open("temp.bin", ios::binary);

    if (!in.is_open() || !out.is_open())
    {
        cout << "Ошибка открытия файла!/Ошибка создания файла temp.bin!";
        in.close();
        out.close();
        return 0;
    }

    ViewFile(path);

    int choice;
    visitor vis;

    cout << "Введите номер записи, которую хотите изменить: ";
    cin >> choice;
    ClearInputBuffer(); // Очистка буфера после ввода числа

    int i = 1;
    while (in.read(reinterpret_cast<char*>(&vis), sizeof(visitor)))
    {
        if (i == choice)
        {
            system("cls");
            cout << "Запись, которую Вы выбрали:" << endl;
            cout << "X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X-X" << endl;
            vis.visitor_output();

            bool flag = true;
            while (flag)
            {
                cout << "Введите номер параметра, который хотите изменить: ";
                int par_choice;
                cin >> par_choice;
                ClearInputBuffer(); // Очистка буфера после ввода числа

                flag = false;
                switch (par_choice)
                {
                case 1:
                    do {
                        Secure_Input(vis.vis_name, sizeof(vis.vis_name),
                            "Введите новое ФИО посетителя (только буквы, пробелы и дефис): ");
                    } while (!isValidName(vis.vis_name));
                    break;

                case 2:
                    do {
                        Secure_Input(vis.b_day, sizeof(vis.b_day),
                            "Введите новую дату рождения посетителя (ДД.ММ.ГГГГ): ");
                    } while (!isValidDate(vis.b_day, false, true));
                    break;

                case 3:
                    Secure_Input(vis.service, sizeof(vis.service),
                        "Введите новое название услуги: ");
                    break;

                case 4:
                    do {
                        Secure_Input(vis.date, sizeof(vis.date),
                            "Введите новую дату и время посещения (чч:мм.ДД.ММ.ГГГГ): ");
                    } while (!isValidDate(vis.date, true, true));
                    break;

                case 5:
                    do {
                        Secure_Input(vis.doc_name, sizeof(vis.doc_name),
                            "Введите новое ФИО врача (только буквы, пробелы и дефис): ");
                    } while (!isValidName(vis.doc_name));
                    break;

                case 6:
                    while (true) {
                        cout << "Введите новую стоимость услуги: ";
                        cin >> vis.cost;
                        if (cin.fail()) {
                            cin.clear();
                            ClearInputBuffer();
                            cout << "Ошибка: введите числовое значение!\n";
                            continue;
                        }
                        ClearInputBuffer();
                        break;
                    }
                    break;

                default:
                    cout << "Номер параметра находится в пределах 1-6." << endl;
                    flag = true; // Повторный запрос номера параметра
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
    if (rename("temp.bin", path)); // Пришлось прикрутить if, чтобы не было предупреждений.
    // В данном случае файл просто не может не переименоваться.
    return 1;
}

/**
@brief Переводит массив в файл с заданным названием
@param list - входной масссив
@param new_file_name - название выходного файла
@param n - кол-во записей в массиве
*/
int ListToTxt(visitor* list, char* new_file_name, int n)
{
    ofstream out;
    out.open(new_file_name, ios::out);
    if (out.is_open() == false) return -1;

    for (int i = 0; i < n; i++)
    {
        out << (i + 1) << "." << endl;

        out << "   1) ФИО посетителя: " << list[i].vis_name << endl
            << "   2) Дата рождения: " << list[i].b_day << endl
            << "   3) Название услуги: " << list[i].service << endl
            << "   4) Дата визита: " << list[i].date << endl
            << "   5) ФИО врача: " << list[i].doc_name << endl
            << "   6) Цена услуги: " << list[i].cost << endl;

        out << "----------------------------------------------------" << endl;
    }

    out.close();
    return 0;
}

/**
@brief Переводит бинарный файл в список
@param path - путь к файлу
@param list - список, в который импортируется файл
@return i - число записей
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
@brief Печатает запись типа visitor в txt-файл
@param path - путь к файлу
@param vis - запись, которая будет записана в файл
@param i - порядковый номер в файле
*/
int VisToTxt(char* path, visitor vis, int& i)
{
    ofstream out;
    out.open(path, ios::app);
    if (out.is_open() == false) return -1;

    out << i << "." << endl;

    out << "   1) ФИО посетителя: " << vis.vis_name << endl
        << "   2) Дата рождения: " << vis.b_day << endl
        << "   3) Название услуги: " << vis.service << endl
        << "   4) Дата визита: " << vis.date << endl
        << "   5) ФИО врача: " << vis.doc_name << endl
        << "   6) Цена услуги: " << vis.cost << endl;

    out << "----------------------------------------------------" << endl;
    i++;
    out.close();
    return 0;
}

/**
@brief Выводит записи с разными услугами в разные файлы
@param list - список с записями
@param service_list - список с услугами, без повторов
@param service_n - число услуг
@param n - число записей в list
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