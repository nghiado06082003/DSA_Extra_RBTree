#include "RedBlackTree.h"

template<typename T>
template<typename U>
RedBlackTree<T>::Node<U>::Node(U data, Color color)
{
    this->data = data;
    this->left = this->right = this->parent = NULL;
    this->color = color;
}

template<typename T>
RedBlackTree<T>::RedBlackTree()
{
    this->root = NULL;
    this->count = 0;
    LEFT_LEFT = LEFT_RIGHT = RIGHT_RIGHT = RIGHT_LEFT = false;
}

template<typename T>
void RedBlackTree<T>::leftRotate(Node<T>*& input)
{
    //---------------------------------------------------------------//
    //This part is required in remove method only
    Node<T>* grandPa = input->parent;
    bool left = false, right = false;
    if (grandPa != NULL && grandPa->left == input)
        left = true;
    else if (grandPa != NULL && grandPa->right == input)
        right = true;
    //---------------------------------------------------------------//

    Node<T>* temp = input->right;
    input->right = temp->left;
    if (input->right != NULL)
        input->right->parent = input;
    temp->parent = input->parent;
    temp->left = input;
    input->parent = temp;
    input = temp;

    //---------------------------------------------------------------//
    //This part is required in remove method only
    if (left == false && right == false)
        this->root = input;
    else if (left)
        grandPa->left = input;
    else
        grandPa->right = input;
    //---------------------------------------------------------------//
}

template<typename T>
void RedBlackTree<T>::rightRotate(Node<T>*& input)
{
    //---------------------------------------------------------------//
    //This part is required in remove method only
    Node<T>* grandPa = input->parent;
    bool left = false, right = false;
    if (grandPa != NULL && grandPa->left == input)
        left = true;
    else if (grandPa != NULL && grandPa->right == input)
        right = true;
    //---------------------------------------------------------------//

    Node<T>* temp = input->left;
    input->left = temp->right;
    if (input->left != NULL)
        input->left->parent = input;
    temp->parent = input->parent;
    temp->right = input;
    input->parent = temp;
    input = temp;

    //---------------------------------------------------------------//
    //This part is required in remove method only
    if (left == false && right == false)
        this->root = input;
    else if (left)
        grandPa->left = input;
    else
        grandPa->right = input;
    //---------------------------------------------------------------//
}

template<typename T>
void RedBlackTree<T>::insertNonRoot(Node<T>*& input, T data)
{
    bool redCollision = false;
    if (input == NULL)
        input = new Node<T>(data, Color::RED);
    else if (input->data > data)
    {
        insertNonRoot(input->left, data);
        input->left->parent = input;
        if (this->root != input)
        {
            if (input->color == Color::RED && input->left->color == Color::RED)
                redCollision = true;
        }
    }
    else
    {
        insertNonRoot(input->right, data);
        input->right->parent = input;
        if (this->root != input)
        {
            if (input->color == Color::RED && input->right->color == Color::RED)
                redCollision = true;
        }
    }

    if (this->LEFT_LEFT)
    {
        rightRotate(input);
        input->color = Color::BLACK;
        input->right->color = Color::RED;
        this->LEFT_LEFT = false;
    }
    else if (this->RIGHT_RIGHT)
    {
        leftRotate(input);
        input->color = Color::BLACK;
        input->left->color = Color::RED;
        this->RIGHT_RIGHT = false;
    }
    else if (this->LEFT_RIGHT)
    {
        leftRotate(input->left);
        input->left->parent = input;
        rightRotate(input);
        input->color = Color::BLACK;
        input->right->color = Color::RED;
        this->LEFT_RIGHT = false;
    }
    else if (this->RIGHT_LEFT)
    {
        rightRotate(input->right);
        input->right->parent = input;
        leftRotate(input);
        input->color = Color::BLACK;
        input->left->color = Color::RED;
        this->RIGHT_LEFT = false;
    }

    if (redCollision)
    {
        if (input->parent->left == input)
        {
            if (input->parent->right == NULL || input->parent->right->color == Color::BLACK)
            {
                if (input->left != NULL && input->left->color == Color::RED)
                    this->LEFT_LEFT = true;
                else if (input->right != NULL && input->right->color == Color::RED)
                    this->LEFT_RIGHT = true;
            }
            else
            {
                input->color = input->parent->right->color = Color::BLACK;
                if (input->parent != this->root)
                    input->parent->color = Color::RED;
            }
        }
        else
        {
            if (input->parent->left == NULL || input->parent->left->color == Color::BLACK)
            {
                if (input->left != NULL && input->left->color == Color::RED)
                    this->RIGHT_LEFT = true;
                else if (input->right != NULL && input->right->color == Color::RED)
                    this->RIGHT_RIGHT = true;
            }
            else
            {
                input->color = input->parent->left->color = Color::BLACK;
                if (input->parent != this->root)
                    input->parent->color = Color::RED;
            }
        }
        redCollision = false;
    }
}

template<typename T>
void RedBlackTree<T>::insert(T data)
{
    if (this->root == NULL)
        this->root = new Node<T>(data, Color::BLACK);
    else
    {
        insertNonRoot(this->root, data);
        if (this->root->color == Color::RED)
            this->root->color = Color::BLACK;
    }
    this->count++;
}

template<typename T>
RedBlackTree<T>::Node<T>* RedBlackTree<T>::getSibling(RedBlackTree<T>::Node<T>* input)
{
    if (input == NULL || input->parent == NULL)
        return NULL;
    if (input->parent->left == input)
        return input->parent->right;
    return input->parent->left;
}

template<typename T>
bool RedBlackTree<T>::checkRedChild(RedBlackTree<T>::Node<T>* input)
{
    if (input == NULL)
        return false;
    if (input->right != NULL)
    {
        if (input->right->color == Color::RED)
            return true;
    }
    if (input->left != NULL)
    {
        if (input->left->color == Color::RED)
            return true;
    }
    return false;
}

template<typename T>
void RedBlackTree<T>::fixDoubleBlack(RedBlackTree<T>::Node<T>* input)
{
    if (input == this->root)
        return;
    Node<T>* sibling = getSibling(input);
    Node<T>* parent = input->parent;
    if (sibling == NULL)
        fixDoubleBlack(parent);
    else
    {
        if (sibling->color == Color::RED)
        {
            sibling->color = Color::BLACK;
            parent->color = Color::RED;
            if (sibling->parent->left == sibling)
                rightRotate(parent);
            else
                leftRotate(parent);
            fixDoubleBlack(input);
        }
        else
        {
            if (checkRedChild(sibling))
            {
                if (sibling->parent->left == sibling)
                {
                    if (sibling->left != NULL && sibling->left->color == Color::RED)
                    {
                        sibling->left->color = sibling->color;
                        sibling->color = parent->color;
                        parent->color = Color::BLACK;
                        rightRotate(parent);
                    }
                    else
                    {
                        sibling->right->color = parent->color;
                        parent->color = Color::BLACK;
                        leftRotate(sibling);
                        rightRotate(parent);
                    }
                }
                else
                {
                    if (sibling->right != NULL && sibling->right->color == Color::RED)
                    {
                        sibling->right->color = sibling->color;
                        sibling->color = parent->color;
                        parent->color = Color::BLACK;
                        leftRotate(parent);
                    }
                    else
                    {
                        sibling->left->color = parent->color;
                        parent->color = Color::BLACK;
                        rightRotate(sibling);
                        leftRotate(parent);
                    }
                }
            }
            else
            {
                sibling->color = Color::RED;
                if (parent->color == Color::BLACK)
                    fixDoubleBlack(parent);
                else
                    parent->color = Color::BLACK;
            }
        }
    }
}

template<typename T>
void RedBlackTree<T>::remove(RedBlackTree<T>::Node<T>* delNode)
{
    if (delNode == NULL)
        return;
    Node<T>* repNode = NULL;
    if (delNode->left != NULL && delNode->right != NULL)
    {
        repNode = delNode->right;
        while (repNode->left != NULL)
            repNode = repNode->left;
    }
    else if (delNode->left != NULL)
        repNode = delNode->left;
    else if (delNode->right != NULL)
        repNode = delNode->right;
    else
        repNode = NULL;
    bool isBothBlack = ((repNode == NULL) || (repNode->color == Color::BLACK)) && (delNode->color == Color::BLACK);
    Node<T>* parent = delNode->parent;
    Node<T>* sibling = getSibling(delNode);
    if (repNode == NULL)
    {
        if (delNode == this->root)
        {
            this->root = NULL;
        }
        else
        {
            if (isBothBlack)
                fixDoubleBlack(delNode);
            else if (sibling != NULL)
                sibling->color = Color::RED;
            if (parent->left == delNode)
                parent->left = NULL;
            else
                parent->right = NULL;
        }
        delete delNode;
        this->count--;
        return;
    }
    if (delNode->left == NULL || delNode->right == NULL)
    {
        if (delNode == this->root)
        {
            delNode->data = repNode->data;
            delNode->left = NULL;
            delNode->right = NULL;
            delete repNode;
            this->count--;
        }
        else
        {
            if (parent->left == delNode)
                parent->left = repNode;
            else
                parent->right = repNode;
            delete delNode;
            this->count--;
            repNode->parent = parent;
            if (isBothBlack)
                fixDoubleBlack(repNode);
            else
                repNode->color = Color::BLACK;
        }
        return;
    }
    else
    {
        T temp = delNode->data;
        delNode->data = repNode->data;
        repNode->data = temp;
        remove(repNode);
    }
}

template<typename T>
RedBlackTree<T>::Node<T>* RedBlackTree<T>::findNode(RedBlackTree<T>::Node<T>* input, T val)
{
    if (input == NULL)
        return NULL;
    if (input->data > val)
        return findNode(input->left, val);
    else if (input->data < val)
        return findNode(input->right, val);
    else
        return input;
}

template<typename T>
void RedBlackTree<T>::remove(T val)
{
    Node<T>* temp = findNode(this->root, val);
    if (temp != NULL)
        remove(temp);
}

template<typename T>
bool RedBlackTree<T>::isContain(T val)
{
    Node<T>* test = findNode(this->root, val);
    if (test != NULL)
        return true;
    return false;
}

template<typename T>
bool RedBlackTree<T>::isValidKey(Node<T>* input, int key)
{
    if (input == NULL)
        return false;
    else if (input->data > key)
        return isValidKey(input->left, key);
    else if (input->data < key)
        return isValidKey(input->right, key);
    else
        return true;
}

template<typename T>
T RedBlackTree<T>::get(Node<T>* input, int key)
{
    if (input == NULL)
        throw out_of_range("Key is not exist in tree");
    if (input->data > key)
        return get(input->left, key);
    else if (input->data < key)
        return get(input->right, key);
    else
        return input->data;
}

template<typename T>
bool RedBlackTree<T>::isValidKey(int key)
{
    return isValidKey(this->root, key);
}

template<typename T>
T RedBlackTree<T>::get(int key)
{
    return get(this->root, key);
}

template<typename T>
void RedBlackTree<T>::printListRec(Node<T>* input)
{
    if (input == NULL)
        return;
    printListRec(input->left);
    cout << input->data;
    cout << "---------------------" << endl;
    printListRec(input->right);
    return;
}

template<typename T>
void RedBlackTree<T>::printList()
{
    printListRec(this->root);
}

template<typename T>
void RedBlackTree<T>::delTree(RedBlackTree<T>::Node<T>*& input)
{
    if (input == NULL)
        return;
    delTree(input->left);
    delTree(input->right);
    delete input;
    input = NULL;
}

template<typename T>
void RedBlackTree<T>::printInOrder(RedBlackTree<T>::Node<T>* input)
{
    if (input == NULL)
        return;
    printInOrder(input->left);
    cout << input->data << '\t';
    printInOrder(input->right);
}

template<typename T>
string RedBlackTree<T>::getColor(RedBlackTree<T>::Node<T>* input)
{
    return (input->color == Color::BLACK) ? "Black" : "Red";
}

template<typename T>
void RedBlackTree<T>::printStructure(RedBlackTree<T>::Node<T>* input, int space)
{
    if (input == NULL)
        return;
    space += 12;
    printStructure(input->right, space);
    cout << '\n';
    for (int i = this->count; i < space; i++)
        cout << ' ';
    cout << input->data << " (" << getColor(input) << ") " << '\n';
    printStructure(input->left, space);
}

template<typename T>
void RedBlackTree<T>::printInOrder()
{
    printInOrder(this->root);
}

template<typename T>
void RedBlackTree<T>::printStructure()
{
    printStructure(this->root, 0);
}

template<typename T>
RedBlackTree<T>::~RedBlackTree()
{
    if (this->root != NULL)
        delTree(this->root);
}