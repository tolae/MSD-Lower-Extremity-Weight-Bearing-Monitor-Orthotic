#ifndef _QUEUE_H
#define _QUEUE_H

template<class T>
class Queue
{
	public:
		unsigned int front;
		unsigned int back;
		unsigned int count;
		unsigned int size;
		T* data;

		Queue(int maxSize);
		~Queue();

		int push(const T& item);
		T peek();
		T pop();
		void clear();

		int empty();
		int full();
};

template<class T>
Queue<T>::Queue(int maxSize) :
	size(0),
	front(0),
	back(0),
	count(0)
{
	size = maxSize;
	data = new T[maxSize + 1];
}

template<class T>
Queue<T>::~Queue()
{
	delete[] data;
}

template<class T>
int Queue<T>::push(const T& item)
{
	if (!full())
	{
		data[back++] = item;
		count++;
		if (back > size)
		{
			back -= (size + 1);
		}
		return 0;
	}
	return 1;
}

template<class T>
T Queue<T>::pop()
{
	if (!empty())
	{
		T toRet = data[front++];
		count--;
		if (front > size)
		{
			front -= (size + 1);
		}
		return toRet;
	}
	return T();
}

template<class T>
T Queue<T>::peek()
{
	if (!empty())
	{
		return data[front];
	}
	return T();
}

template<class T>
void Queue<T>::clear()
{
	front = 0;
	back = 0;
	count = 0;
}

template<class T>
int Queue<T>::empty()
{
	return count == 0;
}

template<class T>
int Queue<T>::full()
{
	return count == size;
}

#endif
