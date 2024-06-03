#include "Queue.h"

Queue::Queue() //: backPtr(nullptr), frontPtr(nullptr)
{
	backPtr = nullptr;
	frontPtr = nullptr;
}

Queue::Queue(const Queue& Q)
{
	backPtr = Q.backPtr;
	frontPtr = Q.frontPtr;
}

Queue::~Queue()
{
	while (!isEmpty())
		dequeue();
}

bool Queue::isEmpty() const
{
	return bool(backPtr == nullptr);
}

void Queue::enqueue(const QueueItemType& newItem)
{
	if (isEmpty())
	{
		frontPtr = new QueueNode;
		frontPtr->item = newItem;
		frontPtr->next = nullptr;
		backPtr = frontPtr;
	}
	else
	{
		QueueNode* newPtr = new QueueNode;
		newPtr->item = newItem;
		newPtr->next = nullptr;
		backPtr->next = newPtr;
		backPtr = newPtr;
	}
}

void Queue::dequeue()
{
	if (!isEmpty())
	{
		QueueNode* tempPtr = frontPtr;
		if (frontPtr == backPtr)
		{
			frontPtr = nullptr;
			backPtr = nullptr;
		}
		else
		{
			tempPtr = frontPtr;
			frontPtr = frontPtr->next;
			tempPtr->next = nullptr;
		}
		delete tempPtr;
	}
}

QueueItemType Queue::getFront() const
{
	if (!isEmpty())
	{
		return frontPtr->item;
	}
	return -1;
}