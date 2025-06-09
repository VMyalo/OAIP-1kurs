#pragma once
class AVL_tree
{
private:
    // Структура для представления узлов дерева 
    struct node
    {
        int key; // Ключ
        char* text; // Текстовая информация 
        unsigned char height; // Высота
        node* left; // Указатели на левый и правый узел соответственно
        node* right;

        // Конструктор узла/ноды
        node(int k, char* t)
        {
            key = k;
            text = new char[100] {'\0'};
            for (int i = 0; i < 100 && t[i] != '\0'; i++)
                text[i] = t[i];
            left = nullptr;
            right = nullptr;
            height = 1;
        }
    };

    node* root = nullptr;

    unsigned char height(node* p);

    int bfactor(node* p);

    void fixheight(node* p);

    node* rotateright(node* p);

    node* rotateleft(node* q);

    node* balance(node* p);

    node* insert(node* p, int k, char* t);

    void show_pass(node* p, int indent, const std::string& prefix, bool isRoot);

    node* findmin(node* p);

    node* removemin(node* p);

    node* remove(node* p, int k);

    node* search_pass(node* p, int k);

    void delete_subtree(node* p);

    int calculate_depth(node* p);

    void direct_pass(node* p);

    void reverse_pass(node* p);

    void sort_pass(node* p);
public:
    
    void insert(int k, char* t);

    void show();

    void remove(int k);

    char* search(int k);

    void delete_all();

    int depth();

    int calculate_root_depth();

    void direct_output();

    void reverse_output();

    void sort_output();
};