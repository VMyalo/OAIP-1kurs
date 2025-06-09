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

        cout << "Открыт файл: " << path << endl;

        cout << "1. Создать новый файл (осторожно, если ввести имя существующего файла - он очистится!)." << endl // готово
             << "2. Просмотр записей из файла." << endl // готово
             << "3. Добавить запись в файл." << endl // готово
             << "4. Редактирование записей в файле." << endl // готово
             << "5. Удаление записей в файле." << endl // готово
             << "6. Линейный поиск в файле по ФИО посетителя." << endl // готово
             << "7. Бинарный поиск в файле по названию медицинской услуги." << endl // готово
             << "8. Быстрая сортировка по названию медицинской услуги." << endl // готово
             << "9. Сортировка выбором по дате и времени посещения." << endl // готово
             << "10. Сортировка вставками по ФИО посетителя в алфавитном порядке." << endl // готово
             << "11. Поиск посетителей по услуге и дате." << endl // готово
             << "12. Статистика по посетителям." << endl // готово
             << "13. Использовать другое имя бинарного файла (по умолчанию - \"binary_files/visitors.bin\")." << endl // готово
             << "14. Закрыть программу." << endl; // готово

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
                    "Введите имя для нового файла (допустимы буквы, цифры, пробелы, _-.): ");
            } while (!isValidPath(buf_path));

            strcat_s(direct_path, 150, buf_path); // => binary_files/_name_.bin

            ofstream out;
            out.open(direct_path, ios::out);
            if (out.is_open() == true)
            {
                cout << "Файл для информации о визитах в поликлинику с названием \"" << buf_path << "\" был создан!" << endl;
                strcpy_s(path, 150, direct_path);
            }
            else
                cout << "Ошибка создания файла. Попробуйте еще раз." << endl;
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

            cout << "Запись сохранена в файл!" << endl;

            system("pause");
            break;
        case 4:

            if (EditFile(path) == 1)
            {
                cout << "Файл изменен!" << endl;
            }
            else
            {
                cout << "Файл не изменен!" << endl;
            }

            system("pause");
            break;
        case 5:

            if (DeleteRecordFile(path) == 1)
            {
                cout << "Файл изменен!" << endl;
            }
            else
            {
                cout << "Файл не изменен!" << endl;
            }

            system("pause");
            break;

        case 6:
        {
            visitor* list = new visitor[100];
            int n_visitors = LineSearchInFile(path, list);

            cout << "Найдено: " << n_visitors << "." << endl;

            char file_name[100] = "results\\line_search_result.txt";
            ListToTxt(list, file_name, n_visitors);

            cout << "Результаты поиска записаны в файл \"" << file_name << "\"" << endl;

            system("pause");
            delete[] list;
            break;
        }
        case 7:
        {
            cout << "Введите название услуги, записи на которую хотите найти: ";
            char key[100];
            cin.getline(key, 100);

            visitor* list = new visitor[100];
            int n_visitors = BinarySearch(path, key, list);

            cout << "Найдено: " << n_visitors << "." << endl;

            char file_name[100] = "results\\binary_search_result.txt";
            ListToTxt(list, file_name, n_visitors);

            cout << "Результаты поиска записаны в файл \"" << file_name << "\"" << endl;

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

            cout << "Отсортированный список записан в файл \"" << file_name << "\"" << endl;

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

            cout << "Отсортированный список записан в файл \"" << file_name << "\"" << endl;

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

            cout << "Отсортированный список записан в файл \"" << file_name << "\"" << endl;

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
                "Введите название медицинской услуги: ");

            do {
                Secure_Input(date, sizeof(date),
                    "Введите дату, по которой будут фильтроваться результаты (в формате чч.мм.ДД.ММ.ГГГГ): ");
            } while (!isValidDate(date, true, true));

            int n_visitors = BinarySearch(path, service, list); //после этого останутся только записи с нужной мед. услугой
            n_visitors = FilterByDate(date, list, n_visitors); //после этого останутся только нужные записи
            InsertSort(list, n_visitors);

            ListToTxt(list, file_name, n_visitors);

            cout << "Отсортированный список записан в файл \"" << file_name << "\"" << endl;

            delete[] list;
            system("pause");
            break;
        }
        case 12:
        {
            visitor* list = new visitor[100];

            // След. код очищает директорию перед тем, как добавить туда новые файлы.
            // Нужно, чтобы при полном удалении из бинарного файла какой-то услуги
            // в директории результатов не было результатов по этой услуге.
            system("del /q results\\statistics\\*.txt"); 
            system("del /q results\\statistics\\services\\*.txt");
            system("cls");

            // Еще вариант очищения директории:
            //system("rm -r -Force results/statistics");
            //system("mkdir results/statistics");

            VisitorStat(path, list);
            
            cout << "Результаты составления статистики можно посмотреть в папке \"results/statictics/\"!" << endl;

            system("pause");
            break;
        }
        case 13:
        {
            char buf_path[136]; // 150 - 14
            char direct_path[150] = "binary_files/"; //14

            do {
                Secure_Input(buf_path, sizeof(path),
                    "Введите имя файла (допустимы буквы, цифры, пробелы, _-.): ");
            } while (!isValidPath(buf_path));

            strcat_s(direct_path, 150, buf_path); // => binary_files/_name_.bin

            ofstream in;
            in.open(direct_path, ios::app, ios::binary);
            if (in.is_open() == true)
            {
                cout << "Файл для информации о визитах в поликлинику с названием \"" << buf_path << "\" был открыт!" << endl;
                strcpy_s(path, 150, direct_path);
            }
            else
                cout << "Ошибка открытия. Попробуйте еще раз. Имя файла по умолчанию: visitors.bin" << endl;
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