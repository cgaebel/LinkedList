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
		_T tData;
		Node* pnNext;

		Node() { }

		Node(const _T& tpNewData)
		{
			tData = tpNewData;
		}
	};

	Node* pnSentinel;

public:
	class iterator
	{
	private:
		Node* pnChild;

	public:
		iterator(Node* npNode)
		{
			pnChild = npNode;
		}

		bool operator==(const iterator& ipOther) const
		{
			return pnChild->pnNext == ipOther.pnChild->pnNext;
		}

		bool operator!=(const iterator& ipOther) const
		{
			return !(*this == ipOther);
		}

		iterator& operator++()
		{
			pnChild = pnChild->pnNext;
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
			return pnChild->tData;
		}

		_T* operator->() const
		{
			return &(pnChild->tData);
		}
	};

private:
	void Link(Node* npLeft, Node* npNewValue, Node* npRight)
	{
		npLeft->pnNext = npNewValue;
		npNewValue->pnNext = npRight;
	}

	void RemoveFromParentList(Node* npPreviousElement, Node* npToRemove)
	{
		npPreviousElement->pnNext = npToRemove->pnNext;
		delete npToRemove;
	}

public:
	LinkedList()
	{
		pnSentinel = new Node;
		pnSentinel->pnNext = pnSentinel;
	}

	LinkedList(LinkedList& llpOther)
	{
		pnSentinel = new Node;
		pnSentinel->pnNext = pnSentinel;

		for(iterator i = llpOther.begin(); i != llpOther.end(); ++i)
			Push(*i);
	}

	void Push(const _T& tpToAdd)
	{
		Link(pnSentinel, new Node(tpToAdd), pnSentinel->pnNext);
	}

	_T Pop()
	{
		_T removed = pnSentinel->pnNext->tData;
		RemoveFromParentList(pnSentinel, pnSentinel->pnNext);

		return removed;
	}

	iterator begin()
	{
		return iterator(pnSentinel->pnNext);
	}

	iterator end()
	{
		return iterator(pnSentinel);
	}

	bool empty()
	{
		return pnSentinel == pnSentinel->pnNext;
	}

	// Return if the element was found.
	bool remove(const _T& tpToRemove)
	{
		// A little hack was used here to prevent deletion
		// of an element we need the next pointer of.
		// Instead of using "current" as an iterator, we
		// use the element directly before it.
		for(
			Node* previous = pnSentinel;
			previous->pnNext != pnSentinel;
			previous = previous->pnNext
		)
		{
			Node* current = previous->pnNext;

			if(current->tData == tpToRemove)
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

		delete pnSentinel;
	}
};
