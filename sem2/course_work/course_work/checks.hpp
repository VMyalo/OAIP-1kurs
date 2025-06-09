#pragma once

#include <iostream>
#include <cctype>

#include "visitor.hpp"

bool isValidName(char* str, bool print_error = true);
bool isLeapYear(int year);
bool isValidDate(char* date, bool check_time = false, bool print_error = true);
bool isValidPath(char* path, bool print_error = true);

void Secure_Input(char* buffer, int buffer_size, const char* prompt);
void ClearInputBuffer();