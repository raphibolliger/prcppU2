#include "OrderedSet.h"

int * OrderedSet::begin() const
{
	return m_values.get() + m_start;
}

OrderedSet OrderedSet::getSmaller(const int x)
{
	size_t newSize = 0;
	while (begin()[newSize] < x) newSize++;
	m_size = newSize;
	return *this;
}

OrderedSet OrderedSet::getLarger(const int x)
{
	size_t newStart = 0;

	while (begin()[newStart] <= x)
	{
		int test = begin()[newStart];
		newStart++;
	}
	
	m_size -= newStart;
	m_start = newStart;

	return *this;
}

Set OrderedSet::merge(const Set &set) const
{
	const OrderedSet* oSet = dynamic_cast<const OrderedSet*>(&set);
	if (!oSet) return Set::merge(set);

	auto temp = new int[m_size + oSet->size()];

	size_t oSetSize = oSet->size();

	size_t count = 0;
	size_t newSize = 0;
	while (count < m_size || count < oSet->size())
	{
		if (count < m_size) temp[newSize++] = begin()[count];
		if (count < oSetSize) temp[newSize++] = oSet->begin()[count];
		count++;
	}

	OrderedSet result(temp, newSize);
	delete[] temp;
	return result;
}
