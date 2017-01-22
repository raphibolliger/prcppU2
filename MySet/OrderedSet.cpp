#include "OrderedSet.h"

int * OrderedSet::begin() const
{
	return m_values.get() + m_start;
}

OrderedSet OrderedSet::getSmaller(const int x)
{
	if (m_size == 0) {
		m_size = 0;
		m_start = 0;
		return *this;
	}

	size_t newSize = 0;
	for (size_t i = m_start; i < m_size; ++i)
	{
		if (begin()[i] < x) newSize++;
	}
	m_size = newSize;

	return *this;
}

OrderedSet OrderedSet::getLarger(const int x)
{
	if (m_size == 0) {
		m_size = 0;
		m_start = 0;
		return *this;
	}

	size_t newSize = 0;
	size_t newStart = -1;
	for (size_t i = m_start; i < m_size; ++i)
	{
		if (begin()[i] > x)
		{
			newSize++;
			if (newStart == -1) newStart = i;
		}
	}
	m_size = newSize;
	m_start = newStart;

	return *this;
}

Set OrderedSet::merge(const Set &set) const
{
	const OrderedSet* oSet = dynamic_cast<const OrderedSet*>(&set);
	if (!oSet) return Set::merge(set);

	OrderedSet result(m_size + oSet->size());

	size_t oSetSize = oSet->size();

	size_t count = 0;
	size_t newSize = 0;

	while (count < m_size || count < oSet->size())
	{
		if (count < m_size) result.begin()[newSize++] = begin()[count];
		if (count < oSetSize && !contains(oSet->begin()[count])) result.begin()[newSize++] = oSet->begin()[count];
		count++;
	}

	result.m_size = newSize;
	return result;
}
