#include "functions.hpp"
/**
@brief �������� ����� � �����
@param path - ���� � �����
@param list - ������, ���� ������������ ���������
@return 0 - ���������� �� �������
@return i - ���-�� ����������
*/
int LineSearchInFile(const char* path, visitor* list)
{
    ifstream in;
    in.open(path, ios::binary);

    if (in.is_open() == false)
    {
        cout << "������ �������� �����!";
        in.close();
        return 0;
    }

    cout << "������� ���, �� �������� ������ ����� ������:" << endl;

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
@brief ���������� ������� ��� ������� ����������
@param path - ���� � �����
@param vis_list - ������, � ������� ������ ��������������� ������
@return n - ���-�� �������
*/
int QuickSort(const char* path, visitor* vis_list)
{
    //visitor vis_list[100];
    int n = FileToList(path, vis_list);
    QuickSort_pass(vis_list, 0, n);

    return n;
}



/**
@brief �������� ����� �� �������� ������
@param path - ���� � �����
@param key - ��� ������
@param res_list - ������, ���� ��������� ��������� ����������
@return j - ���-�� ��������� ������� � �������, ���� ������� ��� ������
@return 0 - ���� ������� �� ��� ������
*/
int BinarySearch(const char* path, char* key, visitor* res_list)
{
    visitor* vis_list = new visitor[100];
    int n = QuickSort(path, vis_list);

    int l = 0;
    int r = n;
    int m = 0;
    while (r > l) // �� ����� ���������� m - ��������� ������
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
@brief ���������� �������
@param path - ���� � �����
@param list - ������, � ������� ��������� ��������� ����������
@return n - ���-�� �������
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
@brief ���������� ����� ��������� �� ���
@param path - ���� � �����
@param list - ������, � ������� ��������� ��������� ����������
@return n - ���-�� �������
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
@brief ���������� ������ ��������� �� ���
@param list - ������, ������� �����������
@param n - ���-�� �������
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
 * @brief ��������� ������, �������� ������ ������ ����� ��������� ����
 * @param filter_date ����, ����� ������� ������ �������� ������ (������ "hh:mm.DD.MM.YYYY")
 * @param list ������ ��� ����������
 * @param n �������� ���������� �������
 * @return ����� ���������� ������� ����� ����������
 */
int FilterByDate(char* filter_date, visitor* list, int n) {

    int write_idx = 0;
    for (int read_idx = 0; read_idx < n; ++read_idx) {
        // ���������� ���� ������ � ��������
        const int comparison = DateCompare(list[read_idx].date, filter_date);

        // ��������� ������ ������ ����� ����������� ����
        if (comparison > 0) {
            // �������� ������� �� ����� ������� ��� �������������
            if (write_idx != read_idx) {
                list[write_idx] = list[read_idx];
            }
            ++write_idx;
        }
    }

    return write_idx;
}

/**
@brief ���������� ������ ����������� �� ���������� ���������
@param from ����
@param to ����
@param list - ������, ������� �����������
@param n - ���-�� ������� � ������
@return ���������� ���������� �������
 */
int FilterByDateFromTo(char* from, char* to, visitor* list, int n) {

    // �������� ������������ ���������
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
@brief ������������ ���������� � ��������� ����� � ������ res_list, ������� ���������.
@param list - ������ �������
@param res_list - �������������� ������
@param size - ���-�� ������� � ������ list
@param counts - ������ ��� �������� ����� ����������
@return unique_count - ���-�� ������� � ����� ������ (� res_list)
*/
int RemoveDuplicalesService(visitor* list, char** res_list, int size, int*& counts)
{
    if (size == 0)
        return 0;

    // ----- ����� -----
    char** temp = new char* [size];
    for (int i = 0; i < size; i++)
    {
        temp[i] = new char[100];
    }
    int unique_count = 0;
    int* temp_counts = new int[size](); // ������������� ������
    // ----- ����� -----


    for (int i = 0; i < size; i++)
    {
        bool is_duplicate = false;

        // ���������, ���� �� ���� ������� � temp
        for (int j = 0; j < unique_count; j++)
        {
            if (strcmp(list[i].service, temp[j]) == 0) //list[i].service == temp[j]
            {
                is_duplicate = true;
                temp_counts[j]++;
                break;
            }
        }

        // ���� �� �������� - ��������� ���
        if (!is_duplicate)
        {
            strcpy_s(temp[unique_count], 100, list[i].service); //temp[unique_count] = list[i].service
            temp_counts[unique_count] = 1; // ������ ���������
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
@brief ������������ ���������� � ������ � ������ res_list, ������� ���������.
@param list - ������ �������
@param res_list - �������������� ������
@param size - ���-�� ������� � ������ list
@param counts - ������ ��� �������� ����� ����������
@return unique_count - ���-�� ������� � ����� ������ (� res_list)
*/
int RemoveDuplicalesDoc(visitor* list, char** res_list, int size, int*& counts)
{
    if (size == 0)
        return 0;

    // ----- ����� -----
    char** temp = new char* [size];
    for (int i = 0; i < size; i++)
    {
        temp[i] = new char[100];
    }
    int unique_count = 0;
    int* temp_counts = new int[size](); // ������������� ������
    // ----- ����� -----


    for (int i = 0; i < size; i++)
    {
        bool is_duplicate = false;

        // ���������, ���� �� ���� ������� � temp
        for (int j = 0; j < unique_count; j++)
        {
            if (strcmp(list[i].doc_name, temp[j]) == 0) //list[i].doc_name == temp[j]
            {
                is_duplicate = true;
                temp_counts[j]++;
                break;
            }
        }

        // ���� �� �������� - ��������� ���
        if (!is_duplicate)
        {
            strcpy_s(temp[unique_count], 100, list[i].doc_name); //temp[unique_count] = list[i].doc_name
            temp_counts[unique_count] = 1; // ������ ���������
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
@brief ������������ ���������� � ����������� � ������ res_list, ������� ���������.
@param list - ������ �������
@param res_list - �������������� ������ (��� ����������)
@param size - ���-�� ������� � ������ list
@param counts - ������ ��� �������� ����� ����������
@return unique_count - ���-�� ������� � ����� ������ (� res_list)
*/
int RemoveDuplicatesVis(visitor* list, visitor*& res_list, int size, int*& counts)
{
    if (size == 0)
        return 0;

    // ��������� ������ ��� �������� ���������� ������� � ���������
    visitor* temp = new visitor[size];
    int* temp_counts = new int[size](); // ������������� ������
    int unique_count = 0;

    for (int i = 0; i < size; i++)
    {
        bool is_duplicate = false;

        // ���������, ���� �� ���� ������� � temp
        for (int j = 0; j < unique_count; j++)
        {
            // ���������� ��� �������� ���� ���������
            if (strcmp(list[i].vis_name, temp[j].vis_name) == 0 &&
                strcmp(list[i].b_day, temp[j].b_day) == 0)
            {
                is_duplicate = true;
                temp_counts[j]++;
                break;
            }
        }

        // ���� �� �������� - ��������� ���
        if (!is_duplicate)
        {
            // �������� ��� ���������
            strcpy_s(temp[unique_count].vis_name, 100, list[i].vis_name);
            strcpy_s(temp[unique_count].b_day, 11, list[i].b_day);
            strcpy_s(temp[unique_count].service, 100, list[i].service);
            strcpy_s(temp[unique_count].date, 17, list[i].date);
            strcpy_s(temp[unique_count].doc_name, 100, list[i].doc_name);
            temp[unique_count].cost = list[i].cost;

            temp_counts[unique_count] = 1; // ������ ���������
            unique_count++;
        }
    }

    // �������� ������ ��� ����������
    res_list = new visitor[unique_count];
    counts = new int[unique_count];

    // �������� ������ � �������� �������
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

    // ����������� ��������� ������
    delete[] temp;
    delete[] temp_counts;

    return unique_count;
}

/**
@brief ������� � ������� ����� ������������������ ������/������
@param n - ����� ������� � �������
@param counts - ������ � ������ ���������
@param list - ������ � ����������/�������
@param choice - 1 - ������� ��� ���������
              - 2 - ������� ��� ������
*/
void SearchForMax(int n, int* counts, char** list, int choice)
{
    int max = 0;
    for (int i = 0; i < n; i++) // ����� ���� ����� ���������/�������
    {
        if (max < counts[i]) max = counts[i];
    }
    switch (choice)
    {
    case 1:
    {
        ofstream out;
        out.open("results\\statistics\\_best_service.txt", ios::out);

        out << "���������� ����� ���������: " << max << endl;
        out << "������/������, ������� �����. ����� ����� ���������: " << endl;

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

        out << "���������� ����� �������: " << max << endl;
        out << "����/�����, ������� �����. ����� ����� �������: " << endl;

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
@brief ���������� �� �����������: ��� ������ ����������� ������ ������� ������ ���������
       � ������� ����������� ����� � �������. ������� ������ � ���������� ���-��� ���������.
       ���������� �����, ������� ������ ���������� ���-�� �����������. ������� ������
       �����������, ������� ��������������� �������� �� ������������ ������
       (��������, �� ��������� �����). ������������ ����� ������� ��������� �� ��������� ������.
@param path - ���� � �����
@param list - ������, ��� ����� �������� ������ �� �����
@return
*/
int VisitorStat(char* path, visitor* list)
{
    int n = ChoiceSort(path, list);
    //int n = FileToList(path, list); 

    // ---- ����� ----
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
    // �� ���� ����� � ��� ���� ������ list, � ������� �������� ��� ������ �� �����,
    // ��������������� � ������� ����������� ���� � �������, ����� ������ service_list, 
    // � ������� �������� �������� ���� �����, � ������ counts, �����. service_list.

    // ����� ������ � ������� ��������
    ServiceTxtOutput(list, service_list, service_n, n);

    // ����� ������ � ���������� ���-��� �����������
    SearchForMax(service_n, counts, service_list, 1);

    // ����� �����, ���������� ����. ���-�� �����������:
    delete[] counts;
    counts = nullptr;
    int doc_n = RemoveDuplicalesDoc(list, doc_list, n, counts);

    SearchForMax(doc_n, counts, doc_list, 2);

    // ����� �� ������

    char from_date[17];
    char to_date[17];

    // ���� ��������� ���� � ���������
    do {
        Secure_Input(from_date, sizeof(from_date),
            "������� ������ ����������� � (���� � ������� ��:��.��.��.����): ");
    } while (!isValidDate(from_date, true, true));

    // ���� �������� ���� � ���������
    do {
        Secure_Input(to_date, sizeof(to_date),
            "�� (���� � ������� ��:��.��.��.����): ");
    } while (!isValidDate(to_date, true, true));

    // �������������� ��������, ��� ��������� ���� �� ����� ��������
    while (DateCompare(from_date, to_date) > 0) {
        cout << "������: ��������� ���� ����� ��������! ��������� ����." << endl;

        do {
            Secure_Input(from_date, sizeof(from_date),
                "������� ��������� ���� ����� (��:��.��.��.����): ");
        } while (!isValidDate(from_date, true, true));

        do {
            Secure_Input(to_date, sizeof(to_date),
                "������� �������� ���� ����� (��:��.��.��.����): ");
        } while (!isValidDate(to_date, true, true));
    }

    int visitors_n = FilterByDateFromTo(from_date, to_date, list, n);
    // ������ � ������ ������ ��������������� �� ���� ����������

    delete[] counts;
    counts = nullptr;

    // ������� �������
    float summary = 0;
    for (int i = 0; i < visitors_n; i++)
    {
        summary = summary + list[i].cost;
    }

    // �������� ����������, ������� ���������
    visitors_n = RemoveDuplicatesVis(list, visitor_list, visitors_n, counts);

    // ������ ������� ������ ����������� � ����
    ofstream out;
    out.open("results\\statistics\\visitors_fromto.txt", ios::out);

    out << "���������� � " << from_date << " �� " << to_date << ":" << endl;
    for (int i = 0; i < visitors_n; i++)
    {
        out << "--------------------------------------------------------------" << endl;
        out << i + 1 << "." << endl;
        out << "���: " << visitor_list[i].vis_name << endl
            << "���� ��������: " << visitor_list[i].b_day << endl
            << "����� ���������: " << counts[i] << endl
            << "���� ���������: " << visitor_list[i].date << endl;

    }
    out << "X------------------------------------------------------------X" << endl;
    out << "����� ������� �� ������: " << summary;

    // ---- ������� ������ ----
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
