#include "date.hpp"

/**
 @brief ����������� ������ ������� "hh:mm.DD.MM.YYYY" � ��������� date
 @param date_str ������ � ����� � �������� (������ 16 ��������)
 @return ��������� date � ������������ ������
 */
date FromCharToDate(char* date_str)
{
    date result;

    // ��������� ���� (hh)
    result.hours = (date_str[0] - '0') * 10 + (date_str[1] - '0');

    // ��������� ������ (mm)
    result.minutes = (date_str[3] - '0') * 10 + (date_str[4] - '0');

    // ��������� ���� (DD)
    result.day = (date_str[6] - '0') * 10 + (date_str[7] - '0');

    // ��������� ����� (MM)
    result.month = (date_str[9] - '0') * 10 + (date_str[10] - '0');

    // ��������� ��� (YYYY)
    result.year = (date_str[12] - '0') * 1000 +
        (date_str[13] - '0') * 100 +
        (date_str[14] - '0') * 10 +
        (date_str[15] - '0');

    return result;
}

/**
@brief ��������� ��� ���� "xx:xx.XX.XX.XX"
@param date1
@param date2
@return 1 - ���� date1 ����� date2
@return -1 - ���� date1 ������ date2
@return 0 - ���� ���� �����
*/
int DateCompare(char* date1, char* date2)
{
    date date1_ = FromCharToDate(date1);
    date date2_ = FromCharToDate(date2);

    if (date1_.year < date2_.year) return -1;
    if (date1_.year > date2_.year) return 1;

    if (date1_.month < date2_.month) return -1;
    if (date1_.month > date2_.month) return 1;

    if (date1_.day < date2_.day) return -1;
    if (date1_.day > date2_.day) return 1;

    if (date1_.hours < date2_.hours) return -1;
    if (date1_.hours > date2_.hours) return 1;

    if (date1_.minutes < date2_.minutes) return -1;
    if (date1_.minutes > date2_.minutes) return 1;

    return 0;
}