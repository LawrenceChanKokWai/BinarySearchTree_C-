// Demonstrates use of function callback to retrieve and store data from BST
// smr v2.4 10/4/2017
// smr v2.3 15/5/2016
// smr v2.2 smr v2 16/5/2015
//smr v2.1 12/4/2014
//smr v2 16/4/2013
// assumes that you have a working binary search tree.
// change the name of the template tree class and file name to suit your circumstance
// for this exercise, assumes that the tree has the following:
// void inOrderTraversal(f1Typ f1 ) const;
// f1Typ is:
// typedef void (*f1Typ)(elemType&);
// and the tree is declared as:
// template <class elemType>
//class BinarySearchTree {.... your code ...}; .. more of your code

#include <iostream>
#include <cstdlib>
#include "BinarySearchTree.h"

template <typename T>
using BinarySearchTree = Bst<T>;

using namespace std;

// this is the test object to be stored in the tree
// not the same unit used in the lab/assignment but has enough to show the concepts.
class unit
{
public:
    unit()
    {
        //a = ++c;   // static c is used to generate unique values for each unit object's member int a
        a = (rand() % 10000) + (rand() % 10000);
    }
    // normally done using a setter, but this is to demo a concept unrelated
    // to setters. Just saves time not having to write a setter for this demo only.

    int getA() const
    {
        return a; // needs to be const for use where the object is declared const
    }
    //int getA()  {return a;}  // not needed in this example - if a non const version is needed as well

private:
    int a;        // this is for the individual objects. not shared
    string st;    // not really used, in this demo
    static int c; // all objects will have this shared - just used to generate internal values for a.
                  // a trick to enable each object to have a unique value the private member a.
};

int unit::c = 5; // every object will share this value, needed for VS 2010

// The above could be in a separate file unit.h and unit.cpp. #include the .h

//The operators below can be in main program file.

// bst needs this for the insert. Normally you will have each
// of the comparators == and < operators
// not a friend or a member
bool operator>(const unit &L, const unit &R)
{

    int a = L.getA(); // naturally will use the const getA as R and L are const
    int b = R.getA();

    return a > b;
}

bool operator<(const unit &L, const unit &R)
{

    int a = L.getA(); // naturally will use the const getA as R and L are const
    int b = R.getA();

    return a > b;
}
// not a friend or a member
ostream &operator<<(ostream &os, const unit &R)
{

    os << R.getA() << " : Data Printed in operator <<" << endl;

    return os;
}

// similar to the approach used in the textbook but the problem is that
// it doesn't collect the data. Just prints it out.
void f1t(int &data)
{
    cout << data << "  ";
}

// Need a better approach than the one in the textbook. The print
// routine when used as a callback just prints, so...
// This class is used to collect the data coming back from the BST
// CollectU can be in a separate file. #include into the main program file
// Contains the callback method f1u. Class is used to collect unit objects as the callback occurs.
// The tree calls static method f1u and puts the data into f1u as a parameter.
// f1u gets the data and stores the data into an array in this case.
// This is a client side program.
class CollectU // collects the unit data from the callback
{

public:
    static void f1u(unit &data) // quick and dirty - inlined this is the callback called by the tree
    {
        cout << "in CollectU static callback f1u(..), i = " << i << "\t"
             << "data = " << data << endl; // to trace what is going on

        A[i] = data; // keeps the data that is returned. static method needs static data
        i++;         // no bounds check - just quick and dirty - improve on this.
    }

    int size()
    {
        return i;
    }
    unit &operator[](int k)
    {
        return A[k]; // used to return the data that has been collected.
    }

private:
    static int i;       // this does not create memory
    static unit A[100]; // use a vector instead, if you prefer
};

int CollectU::i = 0;   // this creates memory and initialise it to 0
unit CollectU::A[100]; // 100 objects get created here and unit's value of c would track obj creations.

int test1()
{
    BinarySearchTree<int> intTree; // change the name as appropriate for your bst

    for (int i = 0; i < 20; i++)
    {
        intTree.insertElement(rand()%55); // yes, it is inserted pre-sorted. not a good thing, but we are just looking at mechanics
    }

    intTree.inOrderTraversal(f1t); // similar to the approach used in the text - just prints, so not very useful    
    
    intTree.exist(22);
    intTree.getNode(33);
    return 0;
}

int test2() // extends the approach used in the textbook to use the approach shown in the QandA
{
    BinarySearchTree<unit> ut; // the tree for storing units - // change the name as appropriate for your bst
    unit u[20];                // 20 unit objects for storing in the tree. unit constructor generates unique values for each object

    CollectU C; // for returning the data that is returned in the callback
    // the callback is a static method of this Class

    for (int i = 0; i < 20; i++)
    {
        ut.insertElement(u[i]); // insert the 20 unit objs into the tree. don't care if pre-sorted or not. just demo
    }

    ut.inOrderTraversal(CollectU::f1u); // pass the func ptr of the static method of CollectU - collects sorted units

    // ut.inOrderTraversal(C.f1u);  // alternative use through the object. f1u is public static method
    // do not put () on f1u, otherwise the meaning changes. We want a function pointer
    // not a method call.

    cout << endl;
    cout << "checking the values collected from the tree" << endl;
    for (int i = 0; i < C.size(); i++)
    {                 // check if the data has been collected.
        cout << C[i]; // uses the overloaded [] for CollectU. can't use CollectU::A[i] as A is private
    }

    return 0;
}

// int main()
// {
//     //test1(); // textbook approach
    
//     test1(); // extended to that shown in the QandA

//     int c;
//     //cin >> c; // pause the screen in visual studio. not needed in codeblocks

//     std::cout << "Job Completed" << std::endl;
//     return 0;
// }
