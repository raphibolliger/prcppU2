// Console.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "../MySet/MySet.h"
#include "../MySet/OrderedSet.h"

template<class T, int S> class Array {
	T m_array[S];
public:
	Array() { memset(m_array, 0, S * sizeof(T)); }
	const T& operator[ ](int pos) const { return m_array[pos]; }
	T& operator[ ](int pos) { return m_array[pos]; }
	void print() const {
		int l = 0; cout << '[';
		if (S > 0) cout << m_array[l++];
		while (l < S) cout << ',' << m_array[l++];
		cout << ']' << endl;
	}
};


// Rekursive template definition
template<int n> struct Zweihoch
{
	const static int Wert = 2 * Zweihoch<n - 1>::Wert;
};

// Verankerung der Rekursion
template<> struct Zweihoch<0>
{
	const static int Wert = 1;
};

int main()
{
	OrderedSet sEmpty1 = OrderedSet();
	OrderedSet sEmpty2 = OrderedSet();

	cout << boolalpha << (sEmpty1.getSmaller(10) == sEmpty2) << endl;
}

