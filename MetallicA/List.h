#pragma once

template <class T>
struct List
{
private:
	template <class T>
	struct Node
	{
		T data;
		Node<T>* nextPtr = nullptr;
		Node<T>* backPtr = nullptr;
	};

	Node<T>* startPtr = nullptr;
	Node<T>* endPtr = nullptr;
	Node<T>* actualPtr = nullptr;
	int lenght = 0;

	void InsterNode(T &data)
	{
		Node<T> *auxNode = actualPtr;

		actualPtr = new Node<T>{ data, nullptr, nullptr };

		actualPtr->backPtr = auxNode->backPtr;
		actualPtr->nextPtr = auxNode->nextPtr;
		auxNode->backPtr->nextPtr = actualPtr;
		auxNode->nextPtr->backPtr = actualPtr;
	}

	void DeleteNode()
	{
		actualPtr->backPtr->nextPtr = actualPtr->nextPtr;
		actualPtr->nextPtr->backPtr = actualPtr->backPtr;

		delete(actualPtr);
	}

	void IterationToPosition(int position)
	{

		if (position > lenght / 2)
		{
			actualPtr = endPtr;

			for (int i = 0; i < (lenght - position); i++)
			{
				actualPtr = actualPtr->backPtr;
			}
		}
		else
		{
			actualPtr = startPtr;

			for (int i = 0; i < position; i++)
			{
				actualPtr = actualPtr->nextPtr;
			}
		}
	}

public:
	
	Node<T>* GetStart()
	{
		return startPtr;
	}

	Node<T>* GetBack()
	{
		//IterationToPosition(position);
		return &actualPtr->backPtr;
	}

	
	void SetDataDoors(int tempRoom)
	{
		

	}


	void Add(T &data)
	{
		if (startPtr == nullptr)
		{
			startPtr = new Node<T>{ data, nullptr, nullptr };
			endPtr = startPtr;
		}
		else
		{
			actualPtr = new  Node<T>{ data, nullptr, nullptr };
			endPtr->nextPtr = actualPtr;
			actualPtr->backPtr = endPtr;
			endPtr = actualPtr;
		}
		lenght++;
	}

	void Add(T &data, int position)
	{
		if (position >= lenght)
		{
			Add(data);
			return;
		}
		else if (position <= 0)
		{
			actualPtr = new Node<T>{ data, nullptr, nullptr };
			actualPtr->nextPtr = startPtr;
			startPtr->backPtr = actualPtr;
			startPtr = actualPtr;
		}
		else
		{
			IterationToPosition(position);
			InsterNode(data);
		}
		lenght++;
	}

	void Remove(int position)
	{

		if (position >= lenght)
		{
			actualPtr = endPtr;
			endPtr = endPtr->backPtr;
			endPtr->nextPtr = nullptr;
			delete(actualPtr);
		}
		else if (position <= 0)
		{
			actualPtr = startPtr;
			startPtr = startPtr->nextPtr;
			startPtr->backPtr = nullptr;
			delete(actualPtr);
		}
		else
		{
			IterationToPosition(position);
			DeleteNode();
		}
		lenght--;
	}

	void Clear()
	{
		actualPtr = endPtr;
		endPtr = nullptr;

		while (startPtr != nullptr)
		{
			if (actualPtr->backPtr != nullptr)
			{
				actualPtr = actualPtr->backPtr;
				delete(actualPtr->nextPtr);
				actualPtr->nextPtr = nullptr;
			}
			else
			{
				delete(actualPtr);
				startPtr = nullptr;
			}
		}
		lenght = 0;
	}
};