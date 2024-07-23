// We will implement a stack and struct using a linked list data structure

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

template <typename Object>
struct Cell {
    Object x, y;
    Object row, col;
    bool L, R, U, D;
    bool visited;
    
    Cell() : x(0), y(0), L(true), R(true), U(true), D(true), visited(false), row(0), col(0) {}
    Cell(Object x, Object y) : x(x), y(y), L(true), R(true), U(true), D(true), visited(false), row(row), col(col) {}

    // Write operator overload for comparison != and ==
    bool operator!=(const Cell &rhs) const {
        return x != rhs.x || y != rhs.y;
    }

    bool operator==(const Cell &rhs) const {
        return x == rhs.x && y == rhs.y;
    }

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

            void pop(); // Double check if its constant or not
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


// Lets implement list of stacks
// We will use linked list to store the stacks
template <class Object>
class ListOfStacks
{
    public:
        // We need consturct with given number of stacks
        ListOfStacks(int numStacks) : head(nullptr) {
            for (int i = 0; i < numStacks; i++) {
                addStacktoEnd();
            }
        }

        ~ListOfStacks() {
            while (head != nullptr) {
                StackNode *temp = head;
                head = head->next;
                delete temp;
            }
        }

        Stack<Object>* getStackAtIndex(int index) {
            StackNode *current = head;
            int count = 0;
            // Traverse the list until the desired index is reached or the end of the list
            while (current != nullptr && count < index) {
                current = current->next;
                count++;
            }
            // Check if we found the stack at the given index
            if (current == nullptr) {
                cout<< "Stack at index " << index << " DNE." << endl;
                return nullptr;
            }
            return current->stack;
        }

    private:
        struct StackNode {
            Stack<Object> *stack;
            StackNode *next;
            StackNode(StackNode *n = nullptr) {
                stack = new Stack<Object>();
                next = n;
            }
            ~StackNode() {
                delete stack;
            }
        };
        StackNode *head;

        void addStacktoEnd() {
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
};

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







