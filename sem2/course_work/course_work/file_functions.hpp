#pragma once
#include <fstream>

#include "visitor.hpp"

void ViewFile(const char* file_path);
void SaveToFile(visitor& vis, const char* path);
int EditFile(const char* path);
int DeleteRecordFile(const char* path);
int ListToTxt(visitor* list, char* new_file_name, int n);
int FileToList(const char* path, visitor* list);
int VisToTxt(char* path, visitor vis, int& i);
void ServiceTxtOutput(visitor* list, char** service_list, int service_n, int n);

void yooo();