// We will implement a stack and struct using a linked list data structure

#include <iostream>

using namespace std;

template <typename Object>
struct Cell {
    Object x, y;
    bool L, R, U, D;
    bool visited;
    
    Cell() : x(0), y(0), L(true), R(true), U(true), D(true), visited(false) {}
    Cell(T x, T y) : x(x), y(y), L(true), R(true), U(true), D(true), visited(false) {}
};

template <class Object>
class List;

template <class Object>
class ListItr;

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

            void pop() const; // Double check if its constant or not
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
            
            friend class List<Object>;
            friend class ListItr<Object>;
            ListNode *topOfStack;
    };

// Consturct the stack
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
void Stack<Object>::pop() const
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







