// Binary Search Tree class
//Doxygen comments needed in the declaration

// Make sure Bst is minimal and complete.
// Code from Lab 9 can come here too.

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include "VECTOR.h"
#include <algorithm>

template <class T>
struct nodeType // answer why struct encapsulation is used - rationale
{
	// A in binary tree has 3 elements, data and two children. By introducing the nodeType
	// encapsulation, we have reduced the complexity of the code and now we only need to
	// tackle a single pointer instead of 3 for each node.
public:
	T data;
	nodeType *left, *right;
};

template <class T>
class Bst // answer why class encapsulation is used - rationale
{
// In OO languages like C++/Java, data structures are usually implements as classes.
// Encapsulation is used to place data and all the related operations at one place.


	typedef void (*f1Typ)(T &);
	// you are not restricted to a single parameter. You
    // decide on how many parameters and provide rationale

    //For this assignment, we have stick will using functions accepting only one argument
    //This reason for this is to keep our class generalized


public:
	// you write whatever else is needed. You already have some from Lab 9.
	// insert is needed.

	/**
	 * @brief inorder travelsal of bst
	 *
	 * traverses the bst in order fashion and invokes the passed function with the node's data
	 * passed as argument into it
	 *
	 * @param  f1 - function pointer or a lambda
	 * @return none
	 */
	void inOrderTraversal(f1Typ f1) const;

	/**
	 * @brief preorder travelsal of bst
	 *
	 * traverses the bst preorder fashion and invokes the passed function with the node's data
	 * passed as argument into it
	 *
	 * @param  f1 - function pointer or a lambda
	 * @return none
	 */
	void preOrderTraversal(f1Typ f1) const; // parameter f1 in here too. left as an exercise

	/**
	 * @brief post order travelsal of bst
	 *
	 * traverses the bst post order fashion and invokes the passed function with the node's data
	 * passed as argument into it
	 *
	 * @param  f1 - function pointer or a lambda
	 * @return none
	 */
	void postOrderTraversal(f1Typ f1) const; // parameter f1 in here too. left as an exercise

	/**
	 * @brief inserts the given element
	 *
	 * inserts the passed element in to the binary search tree at appropriate location
	 *
	 * @param  data - data to insert
	 * @return none
	 */
	void insertElement(const T &data);

	/**
	 * @brief deletes the subtree starting from the passed node
	 *
	 * deletes the subtree down the provided node. Deletion is performed recursively
	 *
	 * @param  t - starting node
	 * @return none
	 */
	void clear(nodeType<T> *t);

	/**
	 * @brief returns the node containing the data
	 *
	 * finds the node containing the given data and returns a pointer to it
	 *
	 * @param  data - data to look for
	 * @return pointer to the node
	 */
	nodeType<T> *getNode(const T &data);

	/**
	 * @brief check if data exist in the bst
	 *
	 * recursively searches the bst for the existing of provided data
	 *
	 * @param  data - data to look for
	 * @return boolean
	 */
	bool exist(const T &data) const;

	/**
	 * @brief constructs a binary search tree from given vector of data
	 *
	 * deletes the existing bst and create anew from given vector of data
	 *
	 * @param  data - vector containing collection of data
	 * @return reference to Bst
	 */
	Bst &createFromVector(const Vector<T> &data);

	/**
	 * @brief returns data in descending order
	 *
	 * traverses the tree inorderly and stores elements a vector.
	 * returns the revserse of the vector
	 *
	 * @param  none
	 * @return vector of data
	 */
	Vector<T> getDatainRInorder() const;

	/**
	 * @brief returns the numer of elements in the bst
	 *
	 * returns the number of elemets present in the container(Bst itself)
	 *
	 * @param  none
	 * @return none
	 */
	void printSize() const;

	~Bst();

private:
	nodeType<T> *root = nullptr;

	/**
	 * @brief auxilary function for finding data in descending order
	 *
	 * returns sorted data stored in a vector
	 *
	 * @param  data - vector containg data elements
	 * @param t - pointer to node
	 * @return none
	 */
	void getDataRInorderaux(Vector<T> &data, nodeType<T> *t) const;

	/**
	 * @brief finds the node correspnding to given data
	 *
	 * auxilary function to find the node containing the passed data
	 *
	 * @param  t - pointer to a node
	 * @param data - data to look for
	 * @return pointer to node containing the data(if found) else nullptr
	 */
	nodeType<T> *find(nodeType<T> *t, const T &x) const;

	/**
	 * @brief auxilary function for inorder traversal of graph
	 *
	 * traverses the bst inorder and passes each node data to the function pointer (invoking it)
	 *
	 * @param  f1 - pointer to a function
	 * @param p - pointer to a node
	 * @return none
	 */
	void inOrder(f1Typ f1, nodeType<T> *p) const;

	/**
	 * @brief auxilary function for pre order traversal of graph
	 *
	 * traverses the bst preoder and passes each node data to the function pointer (invoking it)
	 *
	 * @param  f1 - pointer to a function
	 * @param p - pointer to a node
	 * @return none
	 */
	void preOrder(f1Typ f1, nodeType<T> *p) const;

	/**
	 * @brief auxilary function for post order traversal of graph
	 *
	 * traverses the bst post order and passes each node data to the function pointer (invoking it)
	 *
	 * @param  f1 - pointer to a function
	 * @param p - pointer to a node
	 * @return none
	 */
	void postOrder(f1Typ f1, nodeType<T> *p) const;

	/**
	 * @brief finalizes insertion of data
	 *
	 * auxillary function to finalize the insertion of data into bst
	 *
	 * @param  data - data to insert
	 * @param t - pointer to a node
	 * @return pointer to a node
	 */
	nodeType<T> *insert(const T &data, nodeType<T> *t);

	std::size_t size{0};
};

template <typename T>
void Bst<T>::insertElement(const T &data)
{
	if (this->root == nullptr)
	{
		this->root = new nodeType<T>;
		this->root->data = data;
		this->root->left = this->root->right = nullptr;
		size += 1;
	}
	else if (this->insert(data, this->root))
	{
		size += 1;
	}
}

template <typename T>
void Bst<T>::clear(nodeType<T> *t)
{
	if (t == nullptr)
		return;
	else
	{
		clear(t->left);
		clear(t->right);
		delete t;
	}
	return;
}

template <typename T>
Bst<T>::~Bst()
{
	clear(this->root);
}

template <typename T>
void Bst<T>::inOrder(f1Typ f1, nodeType<T> *t) const
{
	if (t == nullptr)
		return;
	inOrder(f1, t->left);
	f1(t->data);
	inOrder(f1, t->right);
}

template <typename T>
void Bst<T>::preOrder(f1Typ f1, nodeType<T> *t) const
{
	if (t == nullptr)
		return;
	f1(t->data);
	preOrder(f1, t->left);
	preOrder(f1, t->right);
}

template <typename T>
void Bst<T>::postOrder(f1Typ f1, nodeType<T> *t) const
{
	if (t == nullptr)
		return;
	postOrder(f1, t->left);
	postOrder(f1, t->right);
	f1(t->data);
}

template <typename T>
void Bst<T>::inOrderTraversal(f1Typ f1) const
{
	this->inOrder(f1, this->root);
}

template <typename T>
void Bst<T>::preOrderTraversal(f1Typ f1) const
{
	this->preOrder(f1, this->root);
}

template <typename T>
void Bst<T>::postOrderTraversal(f1Typ f1) const
{
	this->postOrder(f1, this->root);
}

template <typename T>
nodeType<T> *Bst<T>::insert(const T &data, nodeType<T> *t)
{
	if (t == nullptr)
	{
		t = new nodeType<T>;
		t->data = data;
		t->left = t->right = nullptr;
		return t;
	}
	else if (data < t->data)
		t->left = insert(data, t->left);
	else if (data > t->data)
		t->right = insert(data, t->right);
	return t;
}

template <typename T>
nodeType<T> *Bst<T>::find(nodeType<T> *t, const T &x) const
{
	if (t == nullptr)
		return nullptr;
	else if (x < t->data)
		return find(t->left, x);
	else if (x > t->data)
		return find(t->right, x);
	else
		return t;
}

template <typename T>
bool Bst<T>::exist(const T &data) const
{
	return this->find(this->root, data) == nullptr ? false : true;
}

template <typename T>
nodeType<T> *Bst<T>::getNode(const T &data)
{
	return this->find(this->root, data);
}

template <typename T>
Bst<T> &Bst<T>::createFromVector(const Vector<T> &data)
{
	clear(this->root);
	for (int i = 0; i < data.size(); i++)
		this->insertElement(data[i]);
	return *this;
}

template <typename T>
Vector<T> Bst<T>::getDatainRInorder() const
{
	Vector<T> data;
	getDataRInorderaux(data, this->root);
	std::reverse(std::begin(data), std::end(data));
	//std::cout <<"Total elements found: "<<data.size()<<std::endl;
	return data;
}
template <typename T>
void Bst<T>::getDataRInorderaux(Vector<T> &data, nodeType<T> *t) const
{
	if (t == nullptr)
		return;
	getDataRInorderaux(data, t->left);
	data.push_back(t->data);
	getDataRInorderaux(data, t->right);
}

template <typename T>
void Bst<T>::printSize() const
{
	std::cout << "Bst has " << size << " elements" << std::endl;
}

#endif
