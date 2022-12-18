#include "AVLtree.h"

template<typename T>
AVLTree<T>::AVLTree()
{
	this->root = NULL;
	this->count = 0;
}

template<typename T>
int AVLTree<T>::size()
{
	return this->count;
}

template<typename T>
int AVLTree<T>::getHeight(Node<T>* input)
{
	if (input == NULL)
		return 0;
	return input->height;
}

template<typename T>
int AVLTree<T>::getBalance(Node<T>* input)
{
	if (input == NULL)
		return 0;
	return input->bl;
}

template<typename T>
void AVLTree<T>::calHeightAndBalance(Node<T>* input)
{
	int leftH = getHeight(input->left);
	int rightH = getHeight(input->right);
	input->bl = leftH - rightH;
	if (leftH > rightH)
		input->height = leftH + 1;
	else
		input->height = rightH + 1;
}

template<typename T>
void AVLTree<T>::leftRotate(Node<T>*& input)
{
	Node<T>* rightHand = input->right;
	input->right = rightHand->left;
	rightHand->left = input;
	calHeightAndBalance(input);
	calHeightAndBalance(rightHand);
	input = rightHand;
}

template<typename T>
void AVLTree<T>::rightRotate(Node<T>*& input)
{
	Node<T>* leftHand = input->left;
	input->left = leftHand->right;
	leftHand->right = input;
	calHeightAndBalance(input);
	calHeightAndBalance(leftHand);
	input = leftHand;
}

template<typename T>
void AVLTree<T>::insertRec(Node<T>*& input, T data)
{
    if (input == NULL)
    {
        input = new Node<T>;
        input->data = data;
        input->bl = 0;
        input->height = 1;
        input->left = NULL;
        input->right = NULL;
    }
    else
    {
        if (data < input->data)
            insertRec(input->left, data);
        else
            insertRec(input->right, data);
        calHeightAndBalance(input);
        if (input->bl > 1 && input->left->bl == 1)
            rightRotate(input);
        else if (input->bl < -1 && input->right->bl == -1)
            leftRotate(input);
        else if (input->bl > 1 && input->left->bl == -1)
        {
            leftRotate(input->left);
            rightRotate(input);
        }
        else if (input->bl < -1 && input->right->bl == 1)
        {
            rightRotate(input->right);
            leftRotate(input);
        }
    }
}

template<typename T>
void AVLTree<T>::insert(T data)
{
    insertRec(this->root, data);
    this->count++;
}

template<typename T>
void AVLTree<T>::removeRec(Node<T>*& input, T data)
{
    if (input == NULL)
        return;
    if (data < input->data)
        removeRec(input->left, data);
    else if (data > input->data)
        removeRec(input->right, data);
    else
    {
        if (input->left == NULL && input->right == NULL)
        {
            Node<T>* temp = input;
            input = NULL;
            delete temp;
            this->count--;
            return;
        }
        else if (input->left == NULL)
        {
            Node<T>* temp = input;
            input = input->right;
            delete temp;
            this->count--;
        }
        else if (input->right == NULL)
        {
            Node<T>* temp = input;
            input = input->left;
            delete temp;
            this->count--;
        }
        else
        {
            Node<T>* temp = input->right;
            while (temp->left != NULL)
                temp = temp->left;
            input->data = temp->data;
            removeRec(input->right, input->data);
        }
    }
    calHeightAndBalance(input);
    if (getBalance(input) > 1 && getBalance(input->left) >= 0)
        rightRotate(input);
    else if (getBalance(input) < -1 && getBalance(input->right) <= 0)
        leftRotate(input);
    else if (getBalance(input) > 1 && getBalance(input->left) < 0)
    {
        leftRotate(input->left);
        rightRotate(input);
    }
    else if (getBalance(input) < -1 && getBalance(input->right) > 0)
    {
        rightRotate(input->right);
        leftRotate(input);
    }
}

template<typename T>
void AVLTree<T>::remove(T data)
{
    removeRec(this->root, data);
}

template<typename T>
bool AVLTree<T>::isContain(Node<T>* input, T val)
{
    if (input == NULL)
        return false;
    else if (val < input->data)
        return isContain(input->left, val);
    else if (val > input->data)
        return isContain(input->right, val);
    else
        return true;
}

template<typename T>
bool AVLTree<T>::isContain(T val)
{
    return isContain(this->root, val);
}

template<typename T>
void AVLTree<T>::delTree(Node<T>*& input)
{
    if (input == NULL)
        return;
    delTree(input->left);
    delTree(input->right);
    delete input;
    input = NULL;
}

template<typename T>
void AVLTree<T>::printInOrder(Node<T>* input)
{
    if (input == NULL)
        return;
    printInOrder(input->left);
    cout << input->data << '\t';
    printInOrder(input->right);
}

template<typename T>
string AVLTree<T>::heightToStr(Node<T>* input)
{
    return to_string(input->height);
}

template<typename T>
void AVLTree<T>::printStructure(Node<T>* input, int space)
{
    if (input == NULL)
        return;
    space += 12;
    printStructure(input->right, space);
    cout << '\n';
    for (int i = this->count; i < space; i++)
        cout << ' ';
    cout << input->data << " (" << heightToStr(input) << ") " << '\n';
    printStructure(input->left, space);
}

template<typename T>
void AVLTree<T>::printInOrder()
{
    printInOrder(this->root);
}

template<typename T>
void AVLTree<T>::printStructure()
{
    printStructure(this->root, 0);
}

template<typename T>
AVLTree<T>::~AVLTree()
{
    if (this->root != NULL)
        delTree(this->root);
}