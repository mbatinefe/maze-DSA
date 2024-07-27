// Mustafa Batin EFE - 29272
// CS300 - Data Structures - Homework 1

#include "stack.h"

// Cell struct definitions
template <typename Object>
Cell<Object>::Cell() : x(0), y(0), row(0), col(0), L(true), R(true), U(true), D(true), visited(false) {}

template <typename Object>
Cell<Object>::Cell(Object x, Object y) : x(x), y(y), row(0), col(0), L(true), R(true), U(true), D(true), visited(false) {}

template <typename Object>
bool Cell<Object>::operator!=(const Cell &rhs) const {
    return row != rhs.row || col != rhs.col;
}

template <typename Object>
bool Cell<Object>::operator==(const Cell &rhs) const {
    return row == rhs.row && col == rhs.col;
}

template <typename Object>
Cell<Object>& Cell<Object>::operator=(const Cell &rhs) {
    if (this != &rhs) {
        x = rhs.x;
        y = rhs.y;
        row = rhs.row;
        col = rhs.col;
        L = rhs.L;
        R = rhs.R;
        U = rhs.U;
        D = rhs.D;
        visited = rhs.visited;
    }
    return *this;
}

// Stack class definitons

// Consturcter
template <class Object>
Stack<Object>::Stack()
{
    topOfStack = NULL;
}

// Is Full function
template <class Object>
bool Stack<Object>::isFull() const
{
    return false;
}

// Is Empty function
template <class Object>
bool Stack<Object>::isEmpty() const
{
    return topOfStack == NULL;
}

// Get the top element and report exception if stack is empty
template <class Object>
const Object & Stack<Object>::top() const
{
    if (isEmpty())
        throw Underflow();
    return topOfStack->element;
}

// Pop/Remove the top element and report exception if stack is empty
template <class Object>
void Stack<Object>::pop()
{
    if (isEmpty())
        throw Underflow();
    ListNode *oldTop = topOfStack;
    topOfStack = topOfStack->next;
    delete oldTop;
}

// Insert value to stack
template <class Object>
void Stack<Object>::push(const Object &x)
{   
    if (isFull()) {
        cout << "Warning: Stack is full. Cannot push new element." << endl;
        return;
    }
    topOfStack = new ListNode(x, topOfStack);
}

// Remove last added item and return it
template <class Object>
Object Stack<Object>::topAndPop()
{
    Object topItem = top();
    pop();
    return topItem;
}

// Make stack empty
template <class Object>
void Stack<Object>::makeEmpty()
{
    while (!isEmpty())
        pop();
}

// Deep-Copy
template <class Object>
const Stack<Object> & Stack<Object>::
operator=(const Stack<Object> & rhs)
{
    if (this != &rhs)
    {
        makeEmpty();
        if (rhs.isEmpty())
            return *this;

        ListNode *rptr = rhs.topOfStack;
        ListNode *ptr  = new ListNode(rptr->element);
        topOfStack = ptr;

        for (rptr = rptr->next; rptr != NULL; rptr = rptr->next) ptr = ptr->next = new ListNode(rptr->element);
    }
    return *this;
}

// Copy Consturctor
template <class Object>
Stack<Object>::Stack(const Stack<Object> & rhs)
{
    topOfStack = NULL;
    *this = rhs; // Deep-Copy === Operator Overloading
}

// Destructor
template <class Object>
Stack<Object>::~Stack()
{
    makeEmpty();
}

// List of stack defintions
template <class Object>
ListOfStacks<Object>::ListOfStacks(int numStacks) : head(nullptr) {
    for (int i = 0; i < numStacks; i++) {
        addStacktoEnd();
    }
}

// Destructor
template <class Object>
ListOfStacks<Object>::~ListOfStacks() {
    while (head != nullptr) {
        StackNode *temp = head;
        head = head->next;
        delete temp;
    }
}

// Get stack at index from list
template <class Object>
Stack<Object>* ListOfStacks<Object>::getStackAtIndex(int index) {
    StackNode *current = head;
    int count = 0;
    while (current != nullptr && count < index) {
        current = current->next;
        count++;
    }
    if (current == nullptr) {
        cout<< "Stack at index " << index << " DNE." << endl;
        return nullptr;
    }
    return current->stack;
}

// Constructor
template <class Object>
ListOfStacks<Object>::StackNode::StackNode(StackNode *n) {
    stack = new Stack<Object>();
    next = n;
}

// Destructor
template <class Object>
ListOfStacks<Object>::StackNode::~StackNode() {
    delete stack;
}

// Add stack to the end of list
template <class Object>
void ListOfStacks<Object>::addStacktoEnd() {
    StackNode *newNode = new StackNode();
    if (head == nullptr) {
        head = newNode;
    } else {
        StackNode *current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}
