#pragma once

struct date //xx:xx.XX.XX.XXXX
{
public:
    unsigned minutes;
    unsigned hours;
    unsigned day;
    unsigned month;
    unsigned year;
};

date FromCharToDate(char* date_str);

int DateCompare(char* date1, char* date2);