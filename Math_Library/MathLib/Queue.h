#pragma once
#include <vector>
#include <assert.h>

template <typename T>
class Queue
{
public:
	// adds an item to the queue
	void push(T item)
	{
		m_queue.push_back(item);
	}
	// removes an item from the queue
	void pop()
	{
		// checks if the container is empty
		if (m_queue.empty())
		{
			// exits the function without removing anything
			return;
		}

		// holds the items in reverse order
		std::vector<T> temp;
		// iterates through the queue in reverse
		for (int i = (int)m_queue.size() - 1; i >= 0; i--)
		{
			// adds the item into the temporary container
			temp.push_back(m_queue[i]);
		}
		// removes the last item from the temp which is the first item from the queue
		temp.pop_back();

		// removes all items from the queue
		m_queue.clear();
		// adds the items back into the queue in correct order
		// checks if there are any items to transfer back
		if (!temp.empty())
		{
			// iterates through the temp in reverse
			for (int i = (int)temp.size() - 1; i >= 0; i--)
			{
				// adds the item into the queue
				m_queue.push_back(temp[i]);
			}
		}
	}

	// returns the size of the queue
	unsigned int size()
	{
		return (unsigned int)m_queue.size();
	}
	// checks if the queue is empty
	bool empty()
	{
		return m_queue.empty();
	}
	// returns the item at the index
	T& operator [] (const int& index)
	{
		// checks if the index is valid
		assert((unsigned int)index < size());

		return m_queue[index];
	}
	// returns the first item
	T& front()
	{
		// checks if the queue is empty
		assert(!m_queue.empty());
		
		return m_queue.front();
	}
	// returns the last item
	T& back()
	{
		// checks if the queue is empty
		assert(!m_queue.empty());
		
		return m_queue.back();
	}
	// checks if the item is in the queue
	bool search(T item)
	{
		// iterates through every item in the queue
		for (auto i : m_queue)
		{
			// checks if the item is equal to any of the items in the queue
			if (i == item)
			{
				return true;
			}
		}
		return false;
	}
	// clears the queue
	void clear()
	{
		m_queue.clear();
	}

private:
	// contains the items
	std::vector<T> m_queue;
};