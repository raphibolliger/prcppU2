// Console.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include "../MySet/MySet.h"
#include "../MySet/OrderedSet.h"

int main()
{
	OrderedSet sEmpty1 = OrderedSet();

	const int allL[] = { 10,11,12,13 };
	const int allL_len = sizeof(allL) / sizeof(int);

	OrderedSet sOrg(allL, allL_len);
	
	OrderedSet s1O(allL, allL_len);
	OrderedSet s2O(allL, allL_len);
	OrderedSet s3O(allL, allL_len);
	OrderedSet s4O(allL, allL_len);
	
	OrderedSet s1 = s1O.getSmaller(4);
	OrderedSet s2 = s1O.getSmaller(12);

	OrderedSet s3 = s1O.getLarger(20);
	OrderedSet s4 = s1O.getLarger(11);

	cout << endl << sOrg << endl << endl;

	cout << "1: " << s1 << endl;
	cout << "2: " << s2 << endl << endl;
	
	cout << "3: " << s3 << endl;
	cout << "4: " << s4 << endl << endl;

}

