#include "checks.hpp"

using namespace std;

bool isValidName(char* str, bool print_error) {
    for (int i = 0; str[i] != '\0'; ++i) {
        if (!isalpha(str[i]) && str[i] != ' ' && str[i] != '-') {
            if (print_error)
                cout << "Введенная строка содержит недопустимые символы. Повторите ввод." << endl;
            return false;
        }
    }
    return true;
}

bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

void ClearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool isValidDate(char* date, bool check_time, bool print_error) {
    int day, month, year, hours = 0, mins = 0;
    int read = 0;
    bool is_correct = true;

    if (check_time) {
        read = sscanf_s(date, "%d:%d.%d.%d.%d", &hours, &mins, &day, &month, &year);
        if (read != 5 || hours < 0 || hours > 23 || mins < 0 || mins > 59) is_correct = false;
    }
    else {
        read = sscanf_s(date, "%d.%d.%d", &day, &month, &year);
        if (read != 3) is_correct = false;
    }

    if (year < 1900 || month < 1 || month > 12 || day < 1) is_correct = false;

    const int daysInMonth[] = { 31,28 + isLeapYear(year),31,30,31,30,31,31,30,31,30,31 };
    if (is_correct)
        is_correct = (day <= daysInMonth[month - 1]);
    
    if (!is_correct && print_error)
        cout << "Ошибка! Повторите ввод." << endl;
    return is_correct;
}

// Функция безопасного ввода
void Secure_Input(char* buffer, int buffer_size, const char* prompt) {
    while (true) {
        cout << prompt;
        cin.getline(buffer, buffer_size);

        // Проверка на переполнение буфера
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка: превышена максимальная длина ("
                << (buffer_size - 1) << " символов)!\n";
            continue;
        }

        // Проверка на пустой ввод
        if (buffer[0] == '\0') {
            cout << "Ошибка: ввод не может быть пустым!\n";
            continue;
        }

        break;
    }
}

// Функция для проверки валидности пути
bool isValidPath(char* path, bool print_error)
{
    // Допустимые символы в пути
    const char* valid_chars =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789"
        " _-.";

    // Проверка на пустой путь
    if (path[0] == '\0') {
        if (print_error) {
            cout << "Ошибка: путь не может быть пустым" << endl;
        }
        return false;
    }

    for (int i = 0; path[i] != '\0'; i++)
    {
        bool valid = false;

        // Проверяем, что символ есть в списке допустимых
        for (const char* c = valid_chars; *c != '\0'; c++)
        {
            if (path[i] == *c)
            {
                valid = true;
                break;
            }
        }

        if (!valid)
        {
            if (print_error)
            {
                cout << "Ошибка: путь содержит недопустимый символ '"
                    << path[i] << "'" << endl;
                cout << "Допустимы только: буквы, цифры, пробелы, _-./\\" << endl;
            }
            return false;
        }

        // Проверка на ".." в пути
        if (i > 0 && path[i] == '.' && path[i - 1] == '.')
        {
            if (print_error)
            {
                cout << "Ошибка: в пути не должно быть '..'" << endl;
            }
            return false;
        }
    }

    return true;
}