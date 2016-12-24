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

	/*

	const int set1[] = { 4,5,3,8,2,4,1,9,3 };
	const int set1_len = sizeof(set1) / sizeof(int);
	const int larger[] = { 5,8,9 };
	const int larger_len = sizeof(larger) / sizeof(int);

	OrderedSet s1(set1, set1_len); // 1,2,3,4,5,8,9 // len = 7
	OrderedSet sLg(larger, larger_len); // 5,8,9

	OrderedSet temp = s1.getLarger(4);

	cout << "LARGER: " << temp << endl;

	cout << boolalpha << (temp == sLg) << endl;

	*/

	// test move intersection
	const int set1[] = { 1,2,3 };
	Set s1(set1, sizeof(set1) / sizeof(int));
	const int set2[] = { 3,2,4 };
	Set s2(set2, sizeof(set2) / sizeof(int));
	const int set3[] = { 2,3 };
	Set s3(set3, sizeof(set3) / sizeof(int));

	cout << boolalpha << (Set::intersection(s1, std::move(s2)) == s3) << endl;
	cout << s2 << endl;
	cout << s3 << endl;
	cout << boolalpha << (s2 == s3) << endl;
	cout << boolalpha << (s2.size() == s3.size()) << endl;

	// test move difference
	// s1 und s3 sollten nicht veraendert worden sein, lediglich s2
	const int set4[] = { 1 };
	Set s4(set4, sizeof(set4) / sizeof(int));
	
	cout << boolalpha << (Set::difference(std::move(s1), std::move(s3)) == s4) << endl;
	cout << boolalpha << (s1 == s4) << endl;
	cout << boolalpha << (s1.size() == s4.size()) << endl;

}

