#ifndef _RB_TREE_
#define _RB_TREE_

#include "Main.h"

using namespace std;

enum class Color { RED, BLACK };
template <typename T>
class RedBlackTree {
protected:
    template <typename U>
    struct Node {
        U data;
        Node* left;
        Node* right;
        Node* parent;
        Color color;
        Node(U data, Color color);
    };

protected:
    Node<T>* root;
    bool LEFT_LEFT;
    bool LEFT_RIGHT;
    bool RIGHT_RIGHT;
    bool RIGHT_LEFT;
    int count;

public:
    RedBlackTree();

protected:
    void leftRotate(Node<T>*& input);
    void rightRotate(Node<T>*& input);

protected:
    void insertNonRoot(Node<T>*& input, T data);

public:
    void insert(T data);

protected:
    Node<T>* getSibling(Node<T>* input);
    bool checkRedChild(Node<T>* input);
    void fixDoubleBlack(Node<T>* input);
    void remove(Node<T>* delNode);
    Node<T>* findNode(Node<T>* input, T val);

public:
    void remove(T val);
    bool isContain(T val);

protected:
    bool isValidKey(Node<T>* input, int key);
    T get(Node<T>* input, int key);

public:
    bool isValidKey(int key);
    T get(int key);

protected:
    void printListRec(Node<T>* input);

public:
    void printList();

protected:
    void delTree(Node<T>*& input);
    void printInOrder(Node<T>* input);
    string getColor(Node<T>* input);
    void printStructure(Node<T>* input, int space);

public:
    void printInOrder();
    void printStructure();
    ~RedBlackTree();
};

#endif // !_RB_TREE_

