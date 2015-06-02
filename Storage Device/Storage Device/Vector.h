#pragma once
#include <iostream>
using namespace std;

#define CAPACITY 10

typedef unsigned uint;

template <class T>
class Vector
{
	T *vect;								// Вектор
	uint size;								// размерность вектора
	uint capacity;
public:

	Vector() : size(0),
		capacity(size + CAPACITY)
	{
		vect = new T[capacity] {};
	}

	explicit Vector(uint _size) : size(_size),
		capacity(size + CAPACITY)
	{
		vect = new T[capacity] {};
	}

	Vector(T *ar, uint _size) : size(_size),
		capacity(size + CAPACITY)
	{
		vect = new T[capacity] {};

		for (int i = 0; i < size; ++i)
		{
			vect[i] = ar[i];
		}
	}

	Vector(const Vector& copy)
	{
		size = copy.size;
		capacity = copy.capacity;

		vect = new T[capacity] {};

		for (int i = 0; i < size; ++i)
		{
			vect[i] = copy.vect[i];
		}
	}

	~Vector()
	{
		delete[]vect;
	}

	Vector& operator ++()
	{
		for (int i = 0; i < size; ++i)
		{
			++vect[i];
		}

		return *this;
	}

	Vector operator ++(int)
	{
		Vector temp = *this;

		for (int i = 0; i < size; ++i)
		{
			++vect[i];
		}

		return temp;
	}

	Vector& operator --()
	{
		for (int i = 0; i < size; ++i)
		{
			--vect[i];
		}

		return *this;
	}

	Vector operator --(int)
	{
		Vector temp = *this;

		for (int i = 0; i < size; ++i)
		{
			--vect[i];
		}

		return temp;
	}

	Vector& operator =(const Vector& v)
	{
		if (this != &v)
		{
			delete[] vect;
			size = v.size;
			capacity = v.capacity;
			vect = new T[capacity] {};
			for (int i = 0; i < size; ++i)
			{
				vect[i] = v.vect[i];
			}
		}

		return *this;
	}

	T& operator [](int index) const
	{
		if (index >= 0 && index < size)
		{
			return vect[index];
		}

		static T trash;
		return trash;
	}

	Vector operator +(T value)
	{
		Vector temp = *this;
		for (int i = 0; i < size; ++i)
		{
			temp[i] += value;
		}

		return temp;
	}

	Vector& operator +=(T value)
	{
		for (int i = 0; i < size; ++i)
		{
			vect[i] += value;
		}

		return *this;
	}

	Vector operator -(T value)
	{
		Vector temp = *this;

		for (int i = 0; i < size; ++i)
		{
			temp[i] += value;
		}

		return temp;
	}

	Vector& operator -=(T value)
	{
		for (int i = 0; i < size; ++i)
		{
			vect[i] -= value;
		}

		return *this;
	}

	uint GetSize() const
	{
		return size;
	}

	friend ostream& operator <<(ostream& os, const Vector& v)
	{
		for (int i = 0; i < v.GetSize(); ++i)
		{
			os << v[i] << ' ';
		}

		return os;
	}

	Vector operator +(const Vector& v);

	Vector operator -(const Vector& v);

	Vector& operator +=(const Vector& v);

	Vector& operator -=(const Vector& v);

	Vector operator *(T value);

	Vector operator *(const Vector& v);

	Vector& operator *=(T value);

	Vector& operator *=(const Vector& v);

	void Clear();

	bool IsEmpty() const;

	void Add(const T& value);

	void Insert(uint index, const T value);

	void Remove(uint index);
};

template <class T>
Vector<T> Vector<T>::operator +(const Vector& v)
{
	int min_size = this->size > v.size ? v.size : this->size;

	Vector temp;
	temp = this->size > v.size ? *this : v;

	for (int i = 0; i < min_size; ++i)
	{
		temp[i] = vect[i] + v[i];
	}

	return temp;
}

template <class T>
Vector<T>& Vector<T>::operator +=(const Vector& v)
{
	*this = *this + v;

	return *this;
}

template <class T>
Vector<T> Vector<T>::operator -(const Vector& v)
{
	int min_size = this->size > v.size ? v.size : this->size;
	int max_size = this->size > v.size ? this->size : v.size;

	Vector temp;
	temp = this->size > v.size ? *this : v;

	for (int i = 0; i < max_size; ++i)
	{
		if (i < min_size)
		{
			temp[i] = vect[i] - v[i];
		}
		else if (this->size > min_size)
		{
			break;
		}
		else
		{
			temp[i] = 0 - v[i];
		}
	}

	return temp;
}

template <class T>
Vector<T>& Vector<T>::operator -=(const Vector& v)
{
	*this = *this - v;

	return *this;
}

template <class T>
Vector<T> Vector<T>::operator *(T value)
{
	Vector temp = *this;
	for (int i = 0; i < size; ++i)
	{
		temp[i] *= value;
	}

	return temp;
}

template <class T>
Vector<T> Vector<T>::operator *(const Vector& v)
{
	int min_size = this->size > v.size ? v.size : this->size;
	Vector temp = this->size > v.size ? *this : v;

	for (int i = 0; i < min_size; ++i)
	{
		temp[i] = vect[i] * v[i];
	}

	return temp;
}

template <class T>
Vector<T>& Vector<T>::operator *=(T value)
{
	*this = *this * value;

	return *this;
}

template <class T>
Vector<T>& Vector<T>::operator *=(const Vector& v)
{
	*this = *this * v;

	return *this;
}

template <class T>
void Vector<T>::Clear()
{
	delete[] vect;
	size = 0;
	capacity = CAPACITY;
	vect = new T[capacity];
}

template <class T>
bool Vector<T>::IsEmpty() const
{
	return !GetSize;
}

template <class T>
void Vector<T>::Add(const T& value)
{
	if (size == capacity)
	{
		T *temp = new T[size + CAPACITY];
		for (int i = 0; i < size; ++i)
		{
			temp[i] = vect[i];
		}
		delete[] vect;
		vect = temp;
		capacity = size + CAPACITY;
	}
	vect[size] = value;
	++size;
}

template <class T>
void Vector<T>::Insert(uint index, const T value)
{
	if (index < size)
	{
		Add(0);
		for (int i = size - 1; i > index; --i)
		{
			vect[i] = vect[i - 1];
		}
		vect[index] = value;
	}
	else if (index == size)
	{
		Add(value);
	}
}

template <class T>
void Vector<T>::Remove(uint index)
{
	if (index < size - 1)
	{
		for (int i = index; i < size - 1; ++i)
		{
			vect[i] = vect[i + 1];
		}
		vect[size - 1] = 0;
		size--;
	}
	else if (index == size - 1)
	{
		vect[size - 1] = 0;
		size--;
	}
}