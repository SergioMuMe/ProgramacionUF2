#pragma once
#include <array>

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
	int length = 0;

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

		if (position > length / 2)
		{
			actualPtr = endPtr;

			for (int i = 0; i < (length - position); i++)
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

	int GetLength()
	{
		return length;
	}
	
	Node<T>* GetStart()
	{
		return startPtr;
	}

	Node<T>* GetBack()
	{
		IterationToPosition(length);
		return actualPtr->backPtr;
	}

	
	std::vector<T> &GiveAllData() {
		//std::array<T, length> results;
		
		std::vector<T> results;
		results.resize(length);

		actualPtr = startPtr;

		for (int i = 0; i < length; i++)
		{
			results[i] = actualPtr->data;

			actualPtr = actualPtr->nextPtr;
		}

		return results;
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
		length++;
	}

	void Add(T &data, int position)
	{
		if (position >= length)
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
		length++;
	}

	void Remove(int position)
	{

		if (position >= length)
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
		length--;
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
		length = 0;
	}

	T & GetItem(const size_t id)
	{
		IterationToPosition(id);

		return actualPtr->data;
	}

	T & GetMemoryPosition(const size_t id)
	{
		IterationToPosition(id);

		return actualPtr;
	}
};