#pragma once
typedef int QueueItemType;

class Queue
{
private:
	struct QueueNode
	{
		QueueItemType item;
		QueueNode* next;
	};

	QueueNode* backPtr;
	QueueNode* frontPtr;

public:
	Queue();
	Queue(const Queue& Q);
	~Queue();

	bool isEmpty() const;
	void enqueue(const QueueItemType& newItem);
	void dequeue();
	QueueItemType getFront() const;
};