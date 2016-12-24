#pragma once

#include <iostream>
#include <memory>

using namespace std;

class Set
{
protected:

	shared_ptr<int> m_values;
	size_t m_size;

	Set(const size_t size) : m_values(new int[size], default_delete<int[]>()), m_size(0)
	{
		cout << "private-ctor" << endl;
	}

	virtual int *begin() const;

	int& operator[](size_t i) const;

	virtual Set merge(const Set& set) const;

	Set difference(const Set& set) const;
	Set difference(Set&& set) const;
	Set intersection(const Set& set) const;
	Set intersection(Set&& set) const;

public:

	Set() : m_size(0) {}

	Set(const Set& set) : m_values(set.m_values), m_size(set.m_size)
	{
		cout << "copy-ctor" << endl;
	}

	Set(const int* array, const size_t length) : Set(length)
	{		
		m_size = 0;
		for (size_t i = 0; i < length; i++)
		{
			int value = array[i];

			if (!contains(value))
			{
				begin()[m_size++] = value;
			}
		}
		cout << "typ-ctor" << endl;
	}

	virtual ~Set()
	{
		cout << "std-dtor" << endl;
	}

	bool contains(const int e) const;

	bool containsAll(const Set& set) const;

	bool isEmpty() const;

	size_t size() const;

	bool operator==(const Set& set) const
	{
		return containsAll(set) && set.containsAll((Set &) *this);
	}

	friend ostream& operator<<(ostream& os, const Set& s)
	{
		const int* const vptr = s.begin();
		os << "{";
		if (!s.isEmpty()) os << vptr[0];
		for (size_t i = 1; i < s.m_size; ++i) { os << ", " << vptr[i]; }
		os << "}";
		return os;
	}

	// Vereinigungsmenge
	static Set merge(const Set& set1, const Set& set2) { return set1.merge(set2); }

	
	// Differenzmenge A ohne B
	static Set difference(const Set& set1, const Set& set2)
	{
		return set2.difference(set1);
	}
	
	static Set difference(Set&& set1,const Set& set2)
	{
		if (set1.m_values.unique())	return set2.difference(move(set1));
		return set2.difference(set1);
	}

	static Set difference(Set&& set1, Set&& set2)
	{
		if (set1.m_values.unique()) return set2.difference(move(set1));
		return set2.difference(set1);
	}


	// Schnittmenge
	static Set intersection(const Set& set1, const Set& set2) { return set1.intersection(set2); }
	
	static Set intersection(const Set& set1, Set&& set2)
	{
		if (set2.m_values.unique())
			return set1.intersection(move(set2));
		return set1.intersection(set2);
	}

	static Set intersection(Set&& set1, const Set& set2)
	{
		if (set1.m_values.unique()) return set2.intersection(move(set1));
		return set2.intersection(set1);
	}

	static Set intersection(Set&& set1, Set&& set2)
	{
		if (set2.m_values.unique()) return set1.intersection(move(set2));
		return set1.intersection(set2);
	}

};