#include <iostream>
#include <locale>

#include "charstack.cpp";
#include "floatstack.cpp";

#define STRING_SIZE 100
#define WRONG_NUM -99999

using namespace std;

int priority(char c)
{
    switch (c)
    {
    case '-':
        return 2;
    case '+':
        return 2;
    case '/':
        return 3;
    case '*':
        return 3;
    case '(':
        return 1;
    case ')':
        return 1;
    }
}

bool isoperation(char c)
{
    return c == '-' || c == '+' || c == '/' || c == '*';
}

void infix_to_OPZ(char* inf_expr, char* opz_expr)
{
    CharStack stack;
    
    int i = 0;
    int j = 0;
    while (inf_expr[i] != '\0')
    {
        if (isoperation(inf_expr[i]) == false && inf_expr[i] != '(' && inf_expr[i] != ')')
        {
            opz_expr[j] = inf_expr[i];
            j++;
        }
        else if (isoperation(inf_expr[i]) == true)
        {
            if (stack.top_e() == '0' || stack.top_e() == '(')
            {
                stack.push(inf_expr[i]);
            }
            else if (priority(inf_expr[i]) > priority(stack.top_e()))
            {
                stack.push(inf_expr[i]);
            }
            else
            {
                while (stack.top_e() >= inf_expr[i] && stack.top_e() != '(')
                {
                    opz_expr[j] = stack.pop();
                    j++;
                }
                stack.push(inf_expr[i]);
            }
        }
        else if (inf_expr[i] == '(') stack.push(inf_expr[i]);
        else if (inf_expr[i] == ')')
        {
            while (stack.top_e() != '(')
            {
                opz_expr[j] = stack.pop();
                j++;
            }
            stack.pop();
        }

        i++;
    }

    while (stack.top_e() != 0)
    {
        opz_expr[j] = stack.pop();
        j++;
    }

    opz_expr[j] = '\0';

    return;
}

double calculation(char operation, float num1, float num2)
{
    switch (operation)
    {
    case '+':
        return num1 + num2;
    case '-':
        return num1 - num2;
    case '*':
        return num1 * num2;
    case '/':
        return num1 / num2;
    }
}



float ReturnValue(char c, float* values)
{
    return values[c - 97];
}

float calculate_OPZ(char* expr, float* values)
{
    int i = 0;

    FloatStack stack;
    float temp1, temp2;

    while (expr[i] != '\0')
    {
        if (isoperation(expr[i]) == false)
        {
            stack.push(ReturnValue(expr[i], values));
        }
        else
        {
            temp2 = stack.pop();
            temp1 = stack.pop();
            switch (expr[i])
            {
            case '-':
                stack.push(temp1 - temp2);
                break;
            case '+':
                stack.push(temp1 + temp2);
                break;
            case '*':
                stack.push(temp1 * temp2);
                break;
            case '/':
                stack.push(temp1 / temp2);
                break;
            }
        }

        i++;
    }

    return stack.top_e();
}

void GetValues(float* values, char* expr)
{
    for (int i = 0; expr[i] != '\0'; i++)
    {
        if (isoperation(expr[i]) == false)
            if (values[expr[i] - 97] == WRONG_NUM)
            {
                cout << "Введите значение " << expr[i] << ": ";
                cin >> values[expr[i] - 97];
            }
    }
    return;
}

int main()
{
    setlocale(LC_ALL, "RU");
    

    bool main_flag = true;
    
    while (main_flag)
    {
        system("cls");
        // ---- ИНИЦИАЛИЗАЦИЯ ПЕРЕМЕННЫХ ----
        char expr[STRING_SIZE];
        char opz_expr[STRING_SIZE];
        float values[26]; // кол-во маленьких букв в алфавите
        for (int i = 0; i < 26; i++)
        {
            values[i] = WRONG_NUM;
        }
        // -----------------------------------

        cout << "Введите выражение, используя латинские маленькие буквы (abc...) и знаки" << endl
            << "математических операций (+, -, *, /, \")\", \"(\"), выражение записывается без пробелов!" << endl;
        cout << "Ваше выражение: ";
        bool flag = true;

        while (flag)
        {
            cin.getline(expr, STRING_SIZE);
            flag = false;
            int left_br_count = 0;
            int right_br_count = 0;
            for (int i = 0; expr[i] != '\0'; i++)
            {
                if ((expr[i] <= 122 && expr[i] >= 97))
                {
                    if (expr[i + 1] == '\0' || (isoperation(expr[i + 1]) || expr[i + 1] == ')'))
                        continue;
                    else
                    {
                        flag = true;
                        cout << "Ошибка: неверный синтаксис. Повторите ввод: ";
                        break;
                    }
                }
                else if (expr[i] == '(' || expr[i] == ')')
                {
                    if (expr[i] == '(')
                    {
                        left_br_count++;
                        if (expr[i+1] == ')')
                        {
                            cout << "Ошибка: пустые скобки. Повторите ввод: ";
                            flag = true;
                            break;
                        }
                    }
                    if (expr[i] == ')')
                    {
                        right_br_count++;
                        if (i == 0 || expr[i + 1] == '(')
                        {
                            cout << "Ошибка: неправильно расставлены скобки. Повторите ввод: ";
                            flag = true;
                            break;
                        }
                    }

                    if (expr[i+1] == ')' || expr[i+1] == '(')
                    continue;
                }
                else if (isoperation(expr[i]))
                {
                    if ( i!=0 && expr[i + 1] != '\0' && ((expr[i + 1] <= 122 && expr[i + 1] >= 97) || expr[i+1] == '(') && ((expr[i - 1] <= 122 && expr[i - 1] >= 97) || expr[i - 1] == ')'))
                        continue;
                    else
                    {
                        flag = true;
                        cout << "Ошибка: неверный синтаксис. Повторите ввод: ";
                        break;
                    }
                }
                else
                {
                    flag = true;
                    cout << "Ошибка: неизвестный символ \"" << expr[i] << "\". Повторите ввод: ";
                    break;
                }
            }

            if (flag == true) continue;

            if (left_br_count != right_br_count)
            {
                cout << "Ошибка: кол-во левых и правых скобок не соответствует друг другу. Повторите ввод: ";
                flag = true;
                continue;
            }

            int j = 0;
            bool brackets_flag = false;
            for (int i = 0; expr[i] != '\0'; i++)
            {
                if (expr[i] == '(')
                {
                    bool brackets_flag = false;
                    for (int k = j; expr[k] != '\0'; k++)
                    {

                        if (expr[k] == ')')
                        {
                            j = k + 1;
                            brackets_flag = true;
                            break;
                        }
                    }
                    if (brackets_flag == false)
                    {
                        flag = true;
                        cout << "Ошибка: неправильно открыты и закрыты скобки. Повторите ввод: ";
                        break;
                    }
                }
            }
        }

        cout << "------------------------------------" << endl;

        infix_to_OPZ(expr, opz_expr);
        GetValues(values, opz_expr);

        float result = calculate_OPZ(opz_expr, values);

        cout << "------------------------------------" << endl;

        cout << "Ответ: ";
        for (int i = 0; opz_expr[i] != '\0'; i++)
        {
            cout << opz_expr[i];
        }
        cout << endl;

        cout << "Результат вычисления: " << result << endl;

        cout << "------------------------------------" << endl;

        cout << "Выберите пункт: " << endl
            << "1. Продолжить." << endl
            << "2. Закрыть программу." << endl
            << "Ваш выбор: ";
        int choice;
        cin >> choice;

        main_flag = false;
        while (true)
        {
            switch (choice)
            {
            case 1:
                main_flag = true;
                break;
            case 2:
                return 0;
                break;
            default:
                cout << "Повторите ввод: ";
                cin >> choice;
            }

            if (main_flag == true) break;
        }
        cin.ignore();
    }
    return 0;
}