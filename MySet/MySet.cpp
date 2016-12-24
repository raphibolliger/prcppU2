#include "MySet.h"

int* Set::begin() const
{
	return m_values.get();
}

int& Set::operator[](size_t i) const
{
	return begin()[i];
}

Set Set::merge(const Set& set) const
{
	// erstelle eine neue Menge mit allen Elementen von this
	Set result(m_size + set.m_size);
	std::memcpy(result.begin(), begin(), m_size * sizeof(int));
	result.m_size = m_size;
	// fuege nur jene Elemente von set dazu, die in this noch nicht enthalten sind
	for (size_t i = 0; i < set.m_size; ++i) {
		if (!contains(set[i])) result[result.m_size++] = set[i];
	}
	return result;
}


Set Set::difference(const Set& set) const
{
	Set result(set.m_size);

	for (size_t i = 0; i < set.size(); i++)
	{
		if (!contains(set[i]))
		{
			result.begin()[result.m_size++] = set[i];
		}
	}
	return result;
}

Set Set::difference(Set&& set) const
{
	if (m_size == 0) return set;

	auto temp = new int[set.size()];
	
	size_t newSize = 0;
	for (size_t i = 0; i < set.size(); i++)
	{
		if (!contains(set[i]))
		{
			temp[newSize++] = set[i];
		}
	}

	for (size_t i = 0; i < newSize; i++)
	{
		set.begin()[i] = temp[i];
	}

	set.m_size = newSize;
	delete[] temp;
	cout << "move" << endl;
	return set;
}

// Schnittmenge
Set Set::intersection(const Set& set) const
{
	if (m_size == 0 || set.m_size == 0) return Set(0);

	// check smaller size
	int count = 0;

	size_t size = m_size;
	int* begin = Set::begin();

	if (m_size > set.m_size)
	{
		size = set.size();
		begin = set.begin();
	}
	
	Set result(size);

	for (size_t i = 0; i < size; i++)
	{
		int value = begin[i];
		if (contains(value) && set.contains(value))
		{
			result.begin()[result.m_size++] = value;
		}
	}

	return result;
}

// Schnittmenge
Set Set::intersection(Set&& set) const
{
	if (m_size == 0 || set.m_size == 0)
	{
		set.m_size = 0;
		return set;
	}

	size_t newSize = 0;
	auto temp = new int[set.size()];
	for (size_t i = 0; i < set.size(); i++)
	{
		int value = set.begin()[i];
		if (contains(value) && set.contains(value))
		{
			temp[newSize++] = value;
		}
	}

	for (size_t i = 0; i < newSize; i++)
	{
		set.begin()[i] = temp[i];
	}

	set.m_size = newSize;
	delete[] temp;
	return set;
}

bool Set::contains(const int e) const
{
	for (size_t i = 0; i < m_size; i++)
	{
		int value = begin()[i];
		if (value == e)	return true;
	}
	return false;
}

bool Set::containsAll(const Set& set) const
{
	for (size_t i = 0; i < set.m_size; i++)
	{
		if (!contains(set[i]))
			return false;
	}
	return true;
}

bool Set::isEmpty() const
{
	return m_size == 0;
}

size_t Set::size() const
{
	return m_size;
}
