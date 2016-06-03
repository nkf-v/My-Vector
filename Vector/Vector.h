#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include <stddef.h>
#include <algorithm>
#include <new>

class Range;

template<typename T>
class Vector
{
	/* --------------- Private --------------- */

	/* --------------- Fields --------------- */

	T * array;
	int sizeArray = 0;
	int capacity = 0;

	/* --------------- Methods --------------- */

	void copy();

public:
	typedef T* iterator;

	/* --------------- Public --------------- */

	/* --------------- Constructors --------------- */

	Vector();
	Vector(int);
	Vector(int, const T&);

	/* --------------- Methods --------------- */

	void swap(Vector<T>&);
	unsigned int size() const;
	bool empty() const;

	iterator begin()
	{
		return array;
	}
	iterator end()
	{
		return array + sizeArray;
	}

	Vector<T> & pushBack(const T&);
	Vector<T> & popBack();
	Vector<T> & clear();
	Vector<T> & insert(iterator, T&);
	Vector<T> & erase(iterator);
	Vector<T> & erase(iterator, int);
	Vector<T> & erase(iterator, iterator);

	/* --------------- Operators --------------- */

	T& operator[] (int);

	/* --------------- Destructor --------------- */

	~Vector();

};

/* --------------- Constructors of class Vector --------------- */

template<typename T>
Vector<T>::Vector()
{
	capacity = 0;
	sizeArray = 0;
	array = (T*)(operator new (0));
	// array = new T[capacity];
}
template<typename T>
Vector<T>::Vector(int size)
{
	sizeArray = size;
	capacity = sizeArray*2;
	array = (T*)(operator new (sizeof(T) * capacity));

	for(T* i = array; i < array + size; i++){
		new (i)T();
	}
}
template<typename T>
Vector<T>::Vector(int size, const T& value)
{
	sizeArray = size;
	capacity = sizeArray*2;
	array = (T*)(operator new (sizeof(T) * capacity));
	for(int i = 0; i < sizeArray; i++){
		new (array + i)T(value);
	}
}

/* --------------- Methods of class Vector --------------- */

template<typename T>
Vector<T> & Vector<T>::pushBack(const T& value)
{
	if (sizeArray == capacity)
		copy();

	array[sizeArray++] = value;

	return *this;
}
template<typename T>
void Vector<T>::swap(Vector<T>& vector)
{
	std::swap(array, vector.array);
	std::swap(sizeArray, vector.sizeArray);
	std::swap(capacity, vector.capacity);
}
template<typename T>
unsigned int Vector<T>::size() const
{
	return (unsigned int) sizeArray;
}
template<typename T>
bool Vector<T>::empty() const
{
	return sizeArray == 0;
}
template<typename T>
Vector<T> & Vector<T>::clear()
{
	for(int i = 0; i < sizeArray; i++)
		(array+i)->~T();

	delete(array);

	array = (T*)(operator new (0));
	sizeArray = capacity = 0;
	return *this;
}
template<typename T>
Vector<T> & Vector<T>::popBack()
{
	(array + sizeArray--)->~T();
	return *this;
}
template<typename T>
void Vector<T>::copy()
{
	capacity == 0 ? capacity = 2 : capacity *= 2;
	T *newArray = (T*)(operator new (sizeof(T) * capacity));

	for(int i = 0; i < sizeArray; i++)
		new(newArray + i)T(array[i]);

	for(int i = 0; i < sizeArray; i++){
		array[i].~T();
	}
	array = newArray;
}

/* --------------- Methods with iterators --------------- */

template<typename T>
Vector<T> & Vector<T>::insert(Vector<T>::iterator iterator, T& value)
{
	if (iterator < begin() || end() <= iterator) throw;

	if (sizeArray == capacity)
		copy();

	new (end())T();

	for(Vector<T>::iterator i = end(); i != iterator; i--)
		*i = *(i-1);

	*iterator = value;
	return *this;
}

/* --------------- Operators of class Vector --------------- */

template<typename T>
T& Vector<T>::operator[] (int index)
{
	try{
		if (index >= sizeArray || index < 0) throw Range();

		return array[index];
	}
	catch (Range r) {
		std::cerr << "Erorr" << std::endl;
		return *array;
	}

}

/* --------------- Destructors of class Vector --------------- */

template<typename T>
Vector<T>::~Vector()
{
	delete (array);
}

/* --------------- Class Range --------------- */

class Range{
public:
	Range() {}
};
#endif //VECTOR_VECTOR_H
