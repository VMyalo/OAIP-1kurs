#include "functions.hpp"
/**
@brief Линейный поиск в файле
@param path - путь к файлу
@param list - массив, куда записывается результат
@return 0 - совпадений не найдено
@return i - кол-во совпадений
*/
int LineSearchInFile(const char* path, visitor* list)
{
    ifstream in;
    in.open(path, ios::binary);

    if (in.is_open() == false)
    {
        cout << "Ошибка открытия файла!";
        in.close();
        return 0;
    }

    cout << "Введите ФИО, по которому хотите найти запись:" << endl;

    char buf[100];

    cin.getline(buf, 100);

    visitor vis;
    int i = 0;
    while (in.read(reinterpret_cast<char*>(&vis), sizeof(visitor)))
    {
        if (IsEqual(vis.vis_name, buf))
        {
            list[i] = vis;
            i++;
        }
    }

    return i;

    in.close();

}

void QuickSort_pass(visitor* list, int start, int end)
{
    if (start >= end) return;

    visitor pivot = list[start];

    int l = start;
    int r = end;

    while (l <= r)
    {
        while (strcmp(list[l].service, pivot.service) < 0)
            l += 1;
        while (strcmp(list[r].service, pivot.service) > 0)
            r -= 1;

        if (l <= r)
        {
            visitor buf = list[l];
            list[l] = list[r];
            list[r] = buf;

            l += 1;
            r -= 1;
        }
    }

    QuickSort_pass(list, start, r);
    QuickSort_pass(list, l, end);
}

/**
@brief Вызывающая функция для быстрой сортировки
@param path - путь к файлу
@param vis_list - массив, в который пойдут отсортированные записи
@return n - кол-во записей
*/
int QuickSort(const char* path, visitor* vis_list)
{
    //visitor vis_list[100];
    int n = FileToList(path, vis_list);
    QuickSort_pass(vis_list, 0, n);

    return n;
}



/**
@brief Бинарный поиск по названию услуги
@param path - путь к файлу
@param key - что ищется
@param res_list - массив, куда выводятся найденные результаты
@return j - кол-во найденных записей в массиве, если элемент был найден
@return 0 - если элемент не был найден
*/
int BinarySearch(const char* path, char* key, visitor* res_list)
{
    visitor* vis_list = new visitor[100];
    int n = QuickSort(path, vis_list);

    int l = 0;
    int r = n;
    int m = 0;
    while (r > l) // по итогу получается m - найденный индекс
    {
        m = (l + r) / 2;

        if (strcmp(vis_list[m].service, key) < 0)
            l = m + 1;
        else if (strcmp(vis_list[m].service, key) > 0)
            r = m - 1;
        else // list[m] == key
            break;
    }

    int j = 0;

    for (int i = m; IsEqual(vis_list[i].service, key) && (i >= 0) && (i < 100); i--)
    {
        res_list[j] = vis_list[i];
        j++;
    }

    for (int i = m + 1; (i >= 0) && (i < 100) && IsEqual(vis_list[i].service, key); i++)
    {
        res_list[j] = vis_list[i];
        j++;
    }

    delete[] vis_list;
    return j;
}

/**
@brief Сортировка выбором
@param path - путь к файлу
@param list - массив, в который запишется результат сортировки
@return n - кол-во записей
*/
int ChoiceSort(const char* path, visitor* list)
{
    int n = FileToList(path, list);

    int min;
    visitor buf;

    for (int i = 0; i < n; i++)
    {
        min = i;
        for (int j = i + 1; j < n; j++)
            if (DateCompare(list[j].date, list[min].date) < 0)
                min = j;

        if (i != min)
        {
            buf = list[i];
            list[i] = list[min];
            list[min] = buf;
        }
    }

    return n;
}

/**
@brief Сортировка ФАЙЛА вставками по ФИО
@param path - путь к файлу
@param list - массив, в который запишется результат сортировки
@return n - кол-во записей
*/
int InsertSort(const char* path, visitor* list)
{
    int n = FileToList(path, list);

    for (int i = 1; i < n; i++)
        for (int j = i; j > 0 && strcmp(list[j - 1].vis_name, list[j].vis_name) > 0; j--)
        {
            visitor buf = list[j - 1];
            list[j - 1] = list[j];
            list[j] = buf;
        }

    return n;
}

/**
@brief Сортировка СПИСКА вставками по ФИО
@param list - массив, который сортируется
@param n - кол-во записей
*/
void InsertSort(visitor* list, int n)
{
    for (int i = 1; i < n; i++)
        for (int j = i; j > 0 && strcmp(list[j - 1].vis_name, list[j].vis_name) > 0; j--)
        {
            visitor buf = list[j - 1];
            list[j - 1] = list[j];
            list[j] = buf;
        }

    return;
}

/**
 * @brief Фильтрует список, оставляя записи строго после указанной даты
 * @param filter_date Дата, после которой должны остаться записи (формат "hh:mm.DD.MM.YYYY")
 * @param list Список для фильтрации
 * @param n Исходное количество записей
 * @return Новое количество записей после фильтрации
 */
int FilterByDate(char* filter_date, visitor* list, int n) {

    int write_idx = 0;
    for (int read_idx = 0; read_idx < n; ++read_idx) {
        // Сравниваем дату записи с фильтром
        const int comparison = DateCompare(list[read_idx].date, filter_date);

        // Оставляем только записи ПОСЛЕ фильтруемой даты
        if (comparison > 0) {
            // Копируем элемент на новую позицию при необходимости
            if (write_idx != read_idx) {
                list[write_idx] = list[read_idx];
            }
            ++write_idx;
        }
    }

    return write_idx;
}

/**
@brief Фильтрация списка посетителей по временному диапазону
@param from дата
@param to дата
@param list - список, который фильтруется
@param n - кол-во записей в списке
@return Количество оставшихся записей
 */
int FilterByDateFromTo(char* from, char* to, visitor* list, int n) {

    // Проверка корректности диапазона
    if (DateCompare(from, to) > 0) {
        return 0;
    }

    int write_idx = 0;
    for (int read_idx = 0; read_idx < n; ++read_idx)
    {
        int cmp_from = DateCompare(list[read_idx].date, from);
        int cmp_to = DateCompare(list[read_idx].date, to);

        if (cmp_from >= 0 && cmp_to <= 0) {
            if (write_idx != read_idx) {
                list[write_idx] = list[read_idx];
            }
            ++write_idx;
        }
    }

    return write_idx;
}

/**
@brief Экспортирует информацию о названиях услуг в список res_list, удаляет дубликаты.
@param list - список записей
@param res_list - результирующий список
@param size - кол-во записей в списке list
@param counts - массив для хранения числа дубликатов
@return unique_count - кол-во записей в новом списке (в res_list)
*/
int RemoveDuplicalesService(visitor* list, char** res_list, int size, int*& counts)
{
    if (size == 0)
        return 0;

    // ----- Буфер -----
    char** temp = new char* [size];
    for (int i = 0; i < size; i++)
    {
        temp[i] = new char[100];
    }
    int unique_count = 0;
    int* temp_counts = new int[size](); // Инициализация нулями
    // ----- Буфер -----


    for (int i = 0; i < size; i++)
    {
        bool is_duplicate = false;

        // Проверяем, есть ли этот элемент в temp
        for (int j = 0; j < unique_count; j++)
        {
            if (strcmp(list[i].service, temp[j]) == 0) //list[i].service == temp[j]
            {
                is_duplicate = true;
                temp_counts[j]++;
                break;
            }
        }

        // Если не дубликат - добавляем его
        if (!is_duplicate)
        {
            strcpy_s(temp[unique_count], 100, list[i].service); //temp[unique_count] = list[i].service
            temp_counts[unique_count] = 1; // Первое вхождение
            unique_count++;
        }
    }
    counts = new int[unique_count];
    for (int i = 0; i < unique_count; i++)
    {
        counts[i] = temp_counts[i];
    }
    for (int i = 0; i < unique_count; i++)
    {
        strcpy_s(res_list[i], 100, temp[i]);
        //res_list[i] = temp[i];
    }

    for (int i = 0; i < size; i++)
    {
        delete[] temp[i];
    }
    delete[] temp;
    delete[] temp_counts;

    return unique_count;
}

/**
@brief Экспортирует информацию о врачах в список res_list, удаляет дубликаты.
@param list - список записей
@param res_list - результирующий список
@param size - кол-во записей в списке list
@param counts - массив для хранения числа дубликатов
@return unique_count - кол-во записей в новом списке (в res_list)
*/
int RemoveDuplicalesDoc(visitor* list, char** res_list, int size, int*& counts)
{
    if (size == 0)
        return 0;

    // ----- Буфер -----
    char** temp = new char* [size];
    for (int i = 0; i < size; i++)
    {
        temp[i] = new char[100];
    }
    int unique_count = 0;
    int* temp_counts = new int[size](); // Инициализация нулями
    // ----- Буфер -----


    for (int i = 0; i < size; i++)
    {
        bool is_duplicate = false;

        // Проверяем, есть ли этот элемент в temp
        for (int j = 0; j < unique_count; j++)
        {
            if (strcmp(list[i].doc_name, temp[j]) == 0) //list[i].doc_name == temp[j]
            {
                is_duplicate = true;
                temp_counts[j]++;
                break;
            }
        }

        // Если не дубликат - добавляем его
        if (!is_duplicate)
        {
            strcpy_s(temp[unique_count], 100, list[i].doc_name); //temp[unique_count] = list[i].doc_name
            temp_counts[unique_count] = 1; // Первое вхождение
            unique_count++;
        }
    }
    counts = new int[unique_count];
    for (int i = 0; i < unique_count; i++)
    {
        counts[i] = temp_counts[i];
    }
    for (int i = 0; i < unique_count; i++)
    {
        strcpy_s(res_list[i], 100, temp[i]);
        //res_list[i] = temp[i];
    }

    for (int i = 0; i < size; i++)
    {
        delete[] temp[i];
    }
    delete[] temp;
    delete[] temp_counts;

    return unique_count;
}

/**
@brief Экспортирует информацию о посетителях в список res_list, удаляет дубликаты.
@param list - список записей
@param res_list - результирующий список (без дубликатов)
@param size - кол-во записей в списке list
@param counts - массив для хранения числа дубликатов
@return unique_count - кол-во записей в новом списке (в res_list)
*/
int RemoveDuplicatesVis(visitor* list, visitor*& res_list, int size, int*& counts)
{
    if (size == 0)
        return 0;

    // Временные буферы для хранения уникальных записей и счетчиков
    visitor* temp = new visitor[size];
    int* temp_counts = new int[size](); // Инициализация нулями
    int unique_count = 0;

    for (int i = 0; i < size; i++)
    {
        bool is_duplicate = false;

        // Проверяем, есть ли этот элемент в temp
        for (int j = 0; j < unique_count; j++)
        {
            // Сравниваем все значимые поля структуры
            if (strcmp(list[i].vis_name, temp[j].vis_name) == 0 &&
                strcmp(list[i].b_day, temp[j].b_day) == 0)
            {
                is_duplicate = true;
                temp_counts[j]++;
                break;
            }
        }

        // Если не дубликат - добавляем его
        if (!is_duplicate)
        {
            // Копируем всю структуру
            strcpy_s(temp[unique_count].vis_name, 100, list[i].vis_name);
            strcpy_s(temp[unique_count].b_day, 11, list[i].b_day);
            strcpy_s(temp[unique_count].service, 100, list[i].service);
            strcpy_s(temp[unique_count].date, 17, list[i].date);
            strcpy_s(temp[unique_count].doc_name, 100, list[i].doc_name);
            temp[unique_count].cost = list[i].cost;

            temp_counts[unique_count] = 1; // Первое вхождение
            unique_count++;
        }
    }

    // Выделяем память под результаты
    res_list = new visitor[unique_count];
    counts = new int[unique_count];

    // Копируем данные в выходные массивы
    for (int i = 0; i < unique_count; i++)
    {
        strcpy_s(res_list[i].vis_name, 100, temp[i].vis_name);
        strcpy_s(res_list[i].b_day, 11, temp[i].b_day);
        strcpy_s(res_list[i].service, 100, temp[i].service);
        strcpy_s(res_list[i].date, 17, temp[i].date);
        strcpy_s(res_list[i].doc_name, 100, temp[i].doc_name);
        res_list[i].cost = temp[i].cost;

        counts[i] = temp_counts[i];
    }

    // Освобождаем временную память
    delete[] temp;
    delete[] temp_counts;

    return unique_count;
}

/**
@brief Находит и выводит самые частовстречающиеся услуги/врачей
@param n - число записей в списках
@param counts - список с числом вхождений
@param list - список с названиями/именами
@param choice - 1 - выведет про посещения
              - 2 - выведет про приемы
*/
void SearchForMax(int n, int* counts, char** list, int choice)
{
    int max = 0;
    for (int i = 0; i < n; i++) // Найти макс число посещений/приемов
    {
        if (max < counts[i]) max = counts[i];
    }
    switch (choice)
    {
    case 1:
    {
        ofstream out;
        out.open("results\\statistics\\_best_service.txt", ios::out);

        out << "Наибольшее число посещений: " << max << endl;
        out << "Услуга/услуги, которым соотв. такое число посещений: " << endl;

        for (int i = 0; i < n; i++)
        {
            if (counts[i] == max)
                out << list[i] << endl;
        }

        out.close();
        break;
    }
    case 2:
    {
        ofstream out;
        out.open("results\\statistics\\_best_doctor.txt", ios::out);

        out << "Наибольшее число приемов: " << max << endl;
        out << "Врач/врачи, которым соотв. такое число приемов: " << endl;

        for (int i = 0; i < n; i++)
        {
            if (counts[i] == max)
                out << list[i] << endl;
        }

        out.close();
        break;
    }
    }
}

/**
@brief Статистика по посетителям: для каждой медицинской услуги выводит список посещений
       в порядке возрастания длины и времени. Находит услугу с наибольшим кол-вом посещений.
       Определяет врача, который принял наибольшее кол-во посетителей. Выводит список
       посетителей, которые воспользовались услугами за определенный период
       (например, за последний месяц). Рассчитывает общую выручку медцентра за указанный период.
@param path - путь к файлу
@param list - список, где будут хранится записи из файла
@return
*/
int VisitorStat(char* path, visitor* list)
{
    int n = ChoiceSort(path, list);
    //int n = FileToList(path, list); 

    // ---- БУФЕР ----
    char** service_list = new char* [n];
    for (int i = 0; i < n; i++)
    {
        service_list[i] = new char[100];
    }

    char** doc_list = new char* [n];
    for (int i = 0; i < n; i++)
    {
        doc_list[i] = new char[100];
    }

    visitor* visitor_list;
    int* counts = nullptr;
    // ----------------

    int service_n = RemoveDuplicalesService(list, service_list, n, counts);
    // На этом этапе у нас есть список list, в котором хранятся все записи из файла,
    // отсортированные в порядке возрастания даты и времени, также список service_list, 
    // в котором хранятся названия всех услуг, и список counts, соотв. service_list.

    // Вывод файлов с разными услугами
    ServiceTxtOutput(list, service_list, service_n, n);

    // Найти услугу с наибольшим кол-вом посетителей
    SearchForMax(service_n, counts, service_list, 1);

    // Найти врача, принявшего наиб. кол-во посетителей:
    delete[] counts;
    counts = nullptr;
    int doc_n = RemoveDuplicalesDoc(list, doc_list, n, counts);

    SearchForMax(doc_n, counts, doc_list, 2);

    // Вывод за период

    char from_date[17];
    char to_date[17];

    // Ввод начальной даты с проверкой
    do {
        Secure_Input(from_date, sizeof(from_date),
            "Вывести список посетителей с (дата в формате чч:мм.ДД.ММ.ГГГГ): ");
    } while (!isValidDate(from_date, true, true));

    // Ввод конечной даты с проверкой
    do {
        Secure_Input(to_date, sizeof(to_date),
            "До (дата в формате чч:мм.ДД.ММ.ГГГГ): ");
    } while (!isValidDate(to_date, true, true));

    // Дополнительная проверка, что начальная дата не позже конечной
    while (DateCompare(from_date, to_date) > 0) {
        cout << "Ошибка: начальная дата позже конечной! Повторите ввод." << endl;

        do {
            Secure_Input(from_date, sizeof(from_date),
                "Введите начальную дату снова (чч:мм.ДД.ММ.ГГГГ): ");
        } while (!isValidDate(from_date, true, true));

        do {
            Secure_Input(to_date, sizeof(to_date),
                "Введите конечную дату снова (чч:мм.ДД.ММ.ГГГГ): ");
        } while (!isValidDate(to_date, true, true));
    }

    int visitors_n = FilterByDateFromTo(from_date, to_date, list, n);
    // Теперь в списке только отфильтрованные по дате результаты

    delete[] counts;
    counts = nullptr;

    // Подсчет выручки
    float summary = 0;
    for (int i = 0; i < visitors_n; i++)
    {
        summary = summary + list[i].cost;
    }

    // Удаление дубликатов, подсчет вхождений
    visitors_n = RemoveDuplicatesVis(list, visitor_list, visitors_n, counts);

    // Теперь выведем список посетителей в файл
    ofstream out;
    out.open("results\\statistics\\visitors_fromto.txt", ios::out);

    out << "Результаты с " << from_date << " по " << to_date << ":" << endl;
    for (int i = 0; i < visitors_n; i++)
    {
        out << "--------------------------------------------------------------" << endl;
        out << i + 1 << "." << endl;
        out << "ФИО: " << visitor_list[i].vis_name << endl
            << "Дата рождения: " << visitor_list[i].b_day << endl
            << "Число посещений: " << counts[i] << endl
            << "Дата посещения: " << visitor_list[i].date << endl;

    }
    out << "X------------------------------------------------------------X" << endl;
    out << "Общая выручка за период: " << summary;

    // ---- ОЧИСТКА ПАМЯТИ ----
    for (int i = 0; i < n; i++)
    {
        delete[] service_list[i];
    }
    delete[] service_list;

    for (int i = 0; i < n; i++)
    {
        delete[] doc_list[i];
    }
    delete[] doc_list;

    delete[] visitor_list;

    delete[] counts;
    return 0;
}
