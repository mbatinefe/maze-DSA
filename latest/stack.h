// Mustafa Batin EFE - 29272
// CS300 - Data Structures - Homework 1

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <exception>

using namespace std;

// Define exception
class Underflow : public exception
{
    public:
        const char *what() const throw()
        {
            return "Underflow";
        }
};

// Define Cell struct
template <typename Object>
struct Cell {
    Object x, y;
    Object row, col;
    bool L, R, U, D;
    bool visited;
    
    Cell();
    Cell(Object x, Object y);

    bool operator!=(const Cell &rhs) const;
    bool operator==(const Cell &rhs) const;
    Cell& operator=(const Cell &rhs);
};

// Stack class
template <class Object>
class Stack
{
    public:
        Stack();
        Stack(const Stack & rhs);
        ~Stack();

        bool isEmpty() const;
        bool isFull() const;
        void makeEmpty();

        void pop();
        void push(const Object & x);
        Object topAndPop();
        const Object & top() const;

        const Stack & operator=(const Stack & rhs);
    
    private:
        struct ListNode
        {
            Object element;
            ListNode *next;

            ListNode(const Object & theElement, ListNode * n =NULL):element(theElement), next(n) {}
        };

        ListNode *topOfStack;
};

// Lets implement list of stacks. We will use linked list to store the stacks
template <class Object>
class ListOfStacks
{
    public:
        ListOfStacks(int numStacks);
        ~ListOfStacks();

        Stack<Object>* getStackAtIndex(int index);
    private:
        struct StackNode {
            Stack<Object> *stack;
            StackNode *next;
            StackNode(StackNode *n = nullptr);
            ~StackNode();
        };
        StackNode *head;

        void addStacktoEnd();
};

#include "stack.cpp"
#endif



