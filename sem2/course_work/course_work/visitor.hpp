#pragma once

#include <iostream>

#include "checks.hpp"

using namespace std;

struct visitor
{
public:
    char vis_name[100];
    char b_day[11];          // XX.XX.XXXX0
    char service[100];
    char date[17];           // xx:xx.XX.XX.XXXX0
    char doc_name[100];
    float cost;

    void create();
    void visitor_output();
};