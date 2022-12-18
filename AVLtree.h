#ifndef _AVL_TREE_
#define _AVL_TREE_

#include "Main.h"

template <typename T>
class AVLTree {
protected:
    template <typename U>
    struct Node {
        U data;
        Node* left;
        Node* right;
        int height;
        int bl;
    };

protected:
    Node<T>* root;
    int count;

public:
    AVLTree();
    int size();

protected:
    int getHeight(Node<T>* input);
    int getBalance(Node<T>* input);
    void calHeightAndBalance(Node<T>* input);
    void leftRotate(Node<T>*& input);
    void rightRotate(Node<T>*& input);
    void insertRec(Node<T>*& input, T data);

public:
    void insert(T data);

protected:
    void removeRec(Node<T>*& input, T data);

public:
    void remove(T data);

protected:
    bool isContain(Node<T>* input, T val);

public:
    bool isContain(T val);

protected:
    void delTree(Node<T>*& input);
    void printInOrder(Node<T>* input);    
    string heightToStr(Node<T>* input);
    void printStructure(Node<T>* input, int space);

public:
    void printInOrder();
    void printStructure();
    ~AVLTree();
};

#endif // !_AVL_TREE_
