#pragma once
#include <vector>
#include <assert.h>

template <typename T>
class Stack
{
public:
	// adds an item to the queue
	void push(T item)
	{
		m_stack.push_back(item);
	}
	// removes an item from the queue
	void pop()
	{
		m_stack.pop_back();
	}

	// returns the size of the queue
	unsigned int size()
	{
		return m_stack.size();
	}
	// checks if the queue is empty
	bool empty()
	{
		return m_stack.empty();
	}
	// returns the item at the index
	T& operator [] (const int& index)
	{
		// checks if the index is valid
		assert(index < size());
		
		return m_stack[index];
	}
	// returns the first item
	T& front()
	{
		// checks if the queue is empty
		assert(!m_stack.empty());
		
		return m_stack.front();
	}
	// returns the last item
	T& back()
	{
		// checks if the queue is empty
		assert(!m_stack.empty());
		
		return m_stack.back();
	}
	// checks if the item is in the stack
	bool search(T item)
	{
		// iterates through every item in the stack
		for (auto i : m_stack)
		{
			// checks if the item is equal to any of the items in the stack
			if (i == item)
			{
				return true;
			}
		}
		return false;
	}
	// clears the stack
	void clear()
	{
		m_stack.clear();
	}

private:
	// contains the items
	std::vector<T> m_stack;
};