// We will implement stack using a linked list data structure

#include <iostream>

using namespace std;

template <class Object>
class List;

template <class Object>
class ListItr;

// Stack class
template <class Object>
    class Stack
    {
        public:
            Stack( );
            Stack( const Stack & rhs );
            ~Stack( );

            bool isEmpty( ) const;
            bool isFull( ) const;
            void makeEmpty( );

            void pop( );
            void push( const Object & x );
            Object topAndPop( );
            const Object & top( ) const;

            const Stack & operator=( const Stack & rhs );
        
        private:
            struct ListNode
            {
                Object   element;
                ListNode *next;

                ListNode( const Object & theElement, ListNode * n = NULL ) : element( theElement ), next( n ) { }
            };
            
            friend class List<Object>;
            friend class ListItr<Object>;

            ListNode *topOfStack;
    };

// Consturct the stack
template <class Object>
Stack<Object>::Stack( )
{
    topOfStack = NULL;
}






