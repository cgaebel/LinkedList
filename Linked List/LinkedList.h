#pragma once

/*
	So what's going on here, anyhow?

	Instead of having a "head" element, I have a sentinel.
	This is a blank iterator that contains a pointer to the
	real "head" of the list. therefore, the list will look
	like...

	lastElement -> sentinel -> realHead -> ... ---|
	    ^-----------------------------------------|

	Kindly notice how my largest function is 6 code-lines long.
	THIS is how to program. There are no redundant comments, and
	what is happening should be obvious to anyone who knows C++.
*/
template <typename _T>
class LinkedList
{
private:
	struct Node
	{
		_T data;
		Node* next;

		Node() { }

		Node(const _T& newData)
		{
			data = newData;
		}
	};

	Node* sentinel;

public:
	class iterator
	{
	private:
		Node* me;

	public:
		iterator(Node* node)
		{
			me = node;
		}

		bool operator==(const iterator& other) const
		{
			return me->next == other.me->next;
		}

		bool operator!=(const iterator& other) const
		{
			return !(*this == other);
		}

		iterator& operator++()
		{
			me = me->next;
			return *this;
		}

		iterator operator++(int)
		{
			iterator preIncrement = *this;
			++*this;
			return preIncrement;
		}

		_T operator*() const
		{
			return me->data;
		}

		_T* operator->() const
		{
			return &(me->data);
		}
	};

private:
	void Link(Node* left, Node* newValue, Node* right)
	{
		left->next = newValue;
		newValue->next = right;
	}

	void RemoveFromParentList(Node* previousElement, Node* toRemove)
	{
		previousElement->next = toRemove->next;
		delete toRemove;
	}

public:
	LinkedList()
	{
		sentinel = new Node;
		sentinel->next = sentinel;
	}

	LinkedList(LinkedList& other)
	{
		sentinel = new Node;
		sentinel->next = sentinel;

		for(iterator i = other.begin(); i != other.end(); ++i)
			Push(*i);
	}

	void Push(const _T& toAdd)
	{
		Link(sentinel, new Node(toAdd), sentinel->next);
	}

	_T Pop()
	{
		_T removed = sentinel->next->data;
		RemoveFromParentList(sentinel, sentinel->next);

		return removed;
	}

	iterator begin()
	{
		return iterator(sentinel->next);
	}

	iterator end()
	{
		return iterator(sentinel);
	}

	bool empty()
	{
		return sentinel == sentinel->next;
	}

	// Return if the element was found.
	bool remove(const _T& toRemove)
	{
		// A little hack was used here to prevent deletion
		// of an element we need the next pointer of.
		// Instead of using "current" as an iterator, we
		// use the element directly before it.
		for(
			Node* previous = sentinel;
			previous->next != sentinel;
			previous = previous->next
		)
		{
			Node* current = previous->next;

			if(current->data == toRemove)
			{
				RemoveFromParentList(previous, current);
				return true;
			}
		}

		return false;
	}

	~LinkedList()
	{
		while(!empty())
			Pop();

		delete sentinel;
	}
};
