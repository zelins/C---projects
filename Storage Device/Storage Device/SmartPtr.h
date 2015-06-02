#pragma once

template <typename Type>
class SmartPtr
{
	Type* m_ptr;
	int* m_count;
public:
	SmartPtr();

	SmartPtr(Type* objPtr);

	SmartPtr(const SmartPtr& obj);

	SmartPtr& operator=(const SmartPtr& obj);

	Type* operator->();

	~SmartPtr();

	void Delete();

	void MoveReferences(const SmartPtr& obj);
};

#pragma region Constructors

template <typename Type>
SmartPtr<Type>::SmartPtr()
{
	m_ptr = nullptr;
	m_count = new int(1);
}

template <typename Type>
SmartPtr<Type>::SmartPtr(Type* objPtr)
{
	m_ptr = objPtr;
	m_count = new int(1);
}

template <typename Type>
SmartPtr<Type>::SmartPtr(const SmartPtr<Type>& obj)
{
	MoveReferences(obj);
}

#pragma endregion

#pragma region Destructor

template <typename Type>
SmartPtr<Type>::~SmartPtr()
{
	Delete();
}

#pragma endregion

#pragma region Operators

template <typename Type>
SmartPtr<Type>& SmartPtr<Type>::operator=(const SmartPtr<Type>& obj)
{
	if (this != &obj)
	{
		Delete();
		MoveReferences(obj);
	}
	return *this;
}

template <typename Type>
Type* SmartPtr<Type>::operator->()
{
	return m_ptr;
}

#pragma endregion

#pragma region Methods

template <typename Type>
void SmartPtr<Type>::Delete()
{
	(*m_count)--;

	if ((*m_count) == 0)
	{
		delete m_ptr;
		delete m_count;
	}
}

template <typename Type>
void SmartPtr<Type>::MoveReferences(const SmartPtr<Type>& obj)
{
	m_count = obj.m_count;
	m_ptr = obj.m_ptr;
	(*m_count)++;
}

#pragma endregion


//  Specification for array type

template <typename Type>
class SmartPtr <Type[]>
{
	Type* m_ptr;
	int* m_count;

public:
	SmartPtr();

	SmartPtr(Type* objPtr);

	SmartPtr(const SmartPtr& obj);

	SmartPtr& operator=(const SmartPtr& obj);

	Type& operator[](const int index);

	~SmartPtr();

	void Delete();

	void MoveReferences(const SmartPtr& obj);

	void Show();
};

#pragma region Constructors

template <typename Type>
SmartPtr<Type[]>::SmartPtr()
{
	m_ptr = nullptr;
	m_count = new int(1);
}

template <typename Type>
SmartPtr<Type[]>::SmartPtr(Type* objPtr)
{
	m_ptr = objPtr;
	m_count = new int(1);
}

template <typename Type>
SmartPtr<Type[]>::SmartPtr(const SmartPtr<Type[]>& obj)
{
	MoveReferences(obj);
}

#pragma endregion

#pragma region Destructor

template <typename Type>
SmartPtr<Type[]>::~SmartPtr()
{
	Delete();
}

#pragma endregion

#pragma region Operators

template <typename Type>
SmartPtr<Type[]>& SmartPtr<Type[]>::operator=(const SmartPtr<Type[]>& obj)
{
	if (this != &obj)
	{
		Delete();
		MoveReferences(obj);
	}
}

template <typename Type>
Type& SmartPtr<Type[]>::operator[](const int index)
{
	return m_ptr[index];
}

#pragma endregion

#pragma region Methods

template <typename Type>
void SmartPtr<Type[]>::Delete()
{
	(*m_count)--;

	if ((*m_count) == 0)
	{
		delete[] m_ptr;
		delete m_count;
	}
}

template <typename Type>
void SmartPtr<Type[]>::MoveReferences(const SmartPtr<Type[]>& obj)
{
	m_count = obj.m_count;
	m_ptr = obj.m_ptr;
	(*m_count)++;
}

#pragma endregion