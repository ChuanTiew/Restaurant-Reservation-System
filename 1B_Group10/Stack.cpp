#include "Stack.h"  // header file

Stack::Stack()
{
    topPtr = nullptr;
}

Stack::Stack(const Stack& S)
{
    topPtr = S.topPtr;
}  

Stack::~Stack()
{
    while (!isEmpty())
        pop();
}  // end destructor

bool Stack::isEmpty() const
{
    return bool(topPtr == nullptr);
} 

void Stack::push(const StackItemType& newItem)
{
    StackNode* newPtr = new StackNode;

    // set data portion  of new node
    newPtr->item = newItem;

    // insert the new node
    newPtr->next = topPtr;
    topPtr = newPtr;
}  

void Stack::pop() 
{
    if(!isEmpty())
    {  // stack is not empty; delete top
        StackNode* temp = topPtr;
        topPtr = topPtr->next;
        // return deleted node to system
        temp->next = nullptr;  // safeguard
        delete temp;
    }  // end if
}  

StackItemType Stack::getTop() const
{
    if (!isEmpty())
    {
        // stack is not empty; retrieve top
        return topPtr->item;
    }
    return -1;
}  

