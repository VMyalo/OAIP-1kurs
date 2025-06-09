#include <iostream>
#include <iomanip>
#include "AVL_tree.hpp"

unsigned char AVL_tree::height(node* p)
{
    return p ? p->height : 0; // ���� ��������� �� �������, ���������� ������; ����� ���������� 0
}

// ��������� ��������������� ������ ����
int AVL_tree::bfactor(node* p)
{
    return height(p->right) - height(p->left);
}

// ��������������� ���������� �������� ���� height ��������� ���� 
void AVL_tree::fixheight(node* p)
{
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

// ----------------------------------------------
// ������� ������������
AVL_tree::node* AVL_tree::balance(node* p)
{
    if (!p) return nullptr;

    fixheight(p);
    int balanceFactor = bfactor(p);

    // ������ ��������� ������� �������
    if (balanceFactor == 2) {
        if (bfactor(p->right) < 0) {
            p->right = rotateright(p->right);  // ������� ��������
        }
        return rotateleft(p);
    }

    // ����� ��������� ������� �������
    if (balanceFactor == -2) {
        if (bfactor(p->left) > 0) {
            p->left = rotateleft(p->left);  // ������� ��������
        }
        return rotateright(p);
    }

    return p;  // ������������ �� ���������
}

// ������� �������� �����
AVL_tree::node* AVL_tree::rotateleft(node* q)
{
    if (!q || !q->right) return q;

    node* p = q->right;
    node* B = p->left;

    // ��������� �������
    p->left = q;
    q->right = B;

    // ��������� ������
    fixheight(q);
    fixheight(p);

    return p;
}

// ������� �������� ������
AVL_tree::node* AVL_tree::rotateright(node* p)
{
    if (!p || !p->left) return p;  // ���������� ��������

    node* q = p->left;
    node* B = q->right;

    // ��������� �������
    q->right = p;
    p->left = B;

    fixheight(p);
    fixheight(q);

    return q;
}

// ������� �������
AVL_tree::node* AVL_tree::insert(node* p, int k, char* t)
{
    if (!p) return new node(k, t);

    if (k < p->key) {
        p->left = insert(p->left, k, t);
    }
    else if (k > p->key) {
        p->right = insert(p->right, k, t);
    }
    // ���� ����� �����, ������ �� ������

    return balance(p);
}
// --------------------------------------------

void AVL_tree::show_pass(node* p, int indent = 0, const std::string& prefix = "", bool isRoot = true)
{
    if (p == nullptr) return;

    if (isRoot) {
        std::cout << "ROOT> " << p->key << ": ";
        for (int i = 0; p->text[i] != '\0'; i++)
            std::cout << p->text[i];
            
        std::cout << std::endl;
    }
    else {
        std::cout << std::string(indent, ' ') << prefix << p->key << ": ";
        for (int i = 0; p->text[i] != '\0'; i++)
            std::cout << p->text[i];

        std::cout << std::endl;
    }

    // ������� ������ ���������
    show_pass(p->right, indent + 4, "R--> ", false);
    // ����� ����� ���������
    show_pass(p->left, indent + 4, "L--> ", false);
}

// ����� ���� � ����������� ������ � ������ p 
AVL_tree::node* AVL_tree::findmin(node* p) 
{
    return p->left ? findmin(p->left) : p;
}

// �������� ���� � ����������� ������ �� ������ p
AVL_tree::node* AVL_tree::removemin(node* p) 
{
    if (p->left == 0)
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

// �������� ����� k �� ������ p
AVL_tree::node* AVL_tree::remove(node* p, int k) 
{
    if (!p) return 0;
    if (k < p->key)
        p->left = remove(p->left, k);
    else if (k > p->key)
        p->right = remove(p->right, k);
    else //  k == p->key 
    {
        node* q = p->left;
        node* r = p->right;
        delete p;
        if (!r) return q;
        node* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

AVL_tree::node* AVL_tree::search_pass(node* p, int k)
{
    if (!p) return nullptr;

    if (p->key == k) return p;

    if (k > p->key)
        return search_pass(p->right, k);
    else if (k < p->key)
        return search_pass(p->left, k);

    return nullptr;
}

void AVL_tree::insert(int k, char* t)
{
    root = insert(root, k, t);
}

// �������, ���������������� ������� ������
void AVL_tree::show()
{
    std::cout << "��������� AVL-������:" << std::endl;
    show_pass(root); 
}

void AVL_tree::remove(int k)
{
    root = remove(root, k);
}

char* AVL_tree::search(int k)
{
    node* p = search_pass(root, k);
    if (p == nullptr)
        return nullptr;
    else
        return p->text;
}

void AVL_tree::delete_subtree(node* p)
{
    if (p != nullptr)
    {
        delete_subtree(p->left);
        delete_subtree(p->right);
        delete p;
    }
}

void AVL_tree::delete_all()
{
    delete_subtree(root);
    root = nullptr;
}

int AVL_tree::depth()
{
    fixheight(root);

    return root->height;
}

int AVL_tree::calculate_depth(node* p)
{
    if (!p) return 0;
    int leftHeight = calculate_depth(p->left);
    int rightHeight = calculate_depth(p->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

int AVL_tree::calculate_root_depth()
{
    return calculate_depth(root);
}

void AVL_tree::direct_pass(node* p)
{
    if (!p) return;

    std::cout << p->key << "(";
    for (int i = 0; p->text[i] != '\0'; i++)
    {
        std::cout << p->text[i];
    }
    std::cout << ") ";

    direct_pass(p->left);
    direct_pass(p->right);
}

void AVL_tree::direct_output()
{
    std::cout << "������ �����: " << std::endl;
    direct_pass(root);
    std::cout << std::endl;
}

void AVL_tree::reverse_pass(node* p)
{
    if (!p) return;

    reverse_pass(p->left);
    reverse_pass(p->right);

    std::cout << p->key << "(";
    for (int i = 0; p->text[i] != '\0'; i++)
    {
        std::cout << p->text[i];
    }
    std::cout << ") ";
}

void AVL_tree::reverse_output()
{
    std::cout << "�������� �����: " << std::endl;
    reverse_pass(root);
    std::cout << std::endl;
}

void AVL_tree::sort_pass(node* p)
{
    if (!p) return;

    sort_pass(p->left);

    std::cout << p->key << "(";
    for (int i = 0; p->text[i] != '\0'; i++)
    {
        std::cout << p->text[i];
    }
    std::cout << ") ";

    sort_pass(p->right);
}

void AVL_tree::sort_output()
{
    std::cout << "����� � ������� �����������: " << std::endl;
    sort_pass(root);
    std::cout << std::endl;
}