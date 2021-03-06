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
		return OrderedSet();
	}


	size_t newSize = 0;
	while (newSize <= m_size && begin()[newSize] < x) newSize++;
	m_size = newSize;

	return OrderedSet(m_values, newSize, 0);
}

OrderedSet OrderedSet::getLarger(const int x)
{
	if (m_size == 0) {
		m_size = 0;
		m_start = 0;
		return OrderedSet();
	}

	size_t newStart = 0;
	size_t count = 0;

	while (count < m_size && begin()[newStart] <= x)
	{
		count++;
		newStart++;
	}

	return OrderedSet(m_values, m_size - newStart, newStart);
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
