#include "visitor.hpp"

/**
@brief Выводит запись в консоль, ставит один \t перед каждым пунктом
*/
void visitor::visitor_output()
{
    cout << "   1) ФИО посетителя: " << vis_name << endl
         << "   2) Дата рождения: " << b_day << endl
         << "   3) Название услуги: " << service << endl
         << "   4) Дата визита: " << date << endl
         << "   5) ФИО врача: " << doc_name << endl
         << "   6) Цена услуги: " << cost << endl;

    cout << "----------------------------------------------------" << endl;
}

/**
@brief Создает запись, вызывает проверки на ввод
*/
void visitor::create() {
    // Ввод ФИО посетителя
    do {
        Secure_Input(vis_name, sizeof(vis_name),
            "Введите ФИО посетителя (только буквы, пробелы и дефис): ");
    } while (!isValidName(vis_name));

    // Ввод даты рождения
    do {
        Secure_Input(b_day, sizeof(b_day),
            "Введите дату рождения (ДД.ММ.ГГГГ): ");
    } while (!isValidDate(b_day));

    // Ввод услуги
    Secure_Input(service, sizeof(service),
        "Введите название услуги: ");

    // Ввод даты и времени посещения (аналогично дате рождения)
    do {
        Secure_Input(date, sizeof(date),
            "Введите дату посещения (чч:мм.ДД.ММ.ГГГГ): ");
    } while (!isValidDate(date, true));

    // Ввод ФИО врача
    do {
        Secure_Input(doc_name, sizeof(doc_name),
            "Введите ФИО врача (только буквы, пробелы и дефис): ");
    } while (!isValidName(doc_name));

    // Ввод стоимости
    while (true) {
        cout << "Введите стоимость услуги: ";
        cin >> cost;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ошибка: введите числовое значение!\n";
            continue;
        }

        cin.ignore(); // Очистка буфера
        break;
    }
}