#pragma once

#include <iostream>
#include <fstream>

#include "checks.hpp"
#include "visitor.hpp"
#include "misc.hpp"
#include "file_functions.hpp"
#include "date.hpp"
#include "cstring"

int LineSearchInFile(const char* path, visitor* list);
void QuickSort_pass(visitor* list, int start, int end);
int QuickSort(const char* path, visitor* vis_list);
int BinarySearch(const char* path, char* key, visitor* res_list);
int ChoiceSort(const char* path, visitor* list);
int InsertSort(const char* path, visitor* list);
void InsertSort(visitor* list, int n);
int FilterByDate(char* filter_date, visitor* list, int n);
int FilterByDateFromTo(char* from, char* to, visitor* list, int n);
int RemoveDuplicalesService(visitor* list, char** res_list, int size, int*& counts);
int RemoveDuplicalesDoc(visitor* list, char** res_list, int size, int*& counts);
int RemoveDuplicatesVis(visitor* list, visitor*& res_list, int size, int*& counts);
void SearchForMax(int n, int* counts, char** list, int choice);
int VisitorStat(char* path, visitor* list);