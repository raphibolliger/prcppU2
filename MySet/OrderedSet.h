#pragma once

#include <iostream>
#include <memory>
#include <algorithm>
#include "MySet.h"

using namespace std;

class OrderedSet: public Set
{
protected:

	size_t m_start;

	OrderedSet(size_t size) : Set(size), m_start(0)
	{
	}

public:

	// default ctor
	OrderedSet() : Set(), m_start(0)
	{
	}

	// copy ctor
	OrderedSet(const OrderedSet& set) : Set(set), m_start(set.m_start)
	{
	}

	// typ ctor
	OrderedSet(const int* array, size_t length) : Set(array, length), m_start(0)
	{
		int* beg = Set::begin();
		std::sort(beg, beg + m_size);
	}

	int *begin() const override;
	OrderedSet getSmaller(const int x);
	OrderedSet getLarger(const int x);

	Set merge(const Set& set) const override;

	friend ostream& operator<<(ostream& os, const OrderedSet& s)
	{
		const int* const vptr = s.begin();
		os << "{";
		if (!s.isEmpty()) os << vptr[0];
		for (size_t i = 1; i < s.m_size; ++i) { os << ", " << vptr[i]; }
		os << "}";
		return os;
	}

};