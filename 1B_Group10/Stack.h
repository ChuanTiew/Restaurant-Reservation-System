#pragma once
typedef int StackItemType;

class Stack
{
private:
    struct StackNode
    {
        StackItemType item;
        StackNode* next;
    }; 

    StackNode* topPtr;

public:

    Stack();
    Stack(const Stack& S);
    ~Stack();

    bool isEmpty() const;
    void push(const StackItemType& newItem);
    void pop();
    StackItemType getTop() const;
};

