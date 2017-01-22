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

	OrderedSet sAllL(allL, allL_len);

	OrderedSet sOrg = sAllL;
	
	OrderedSet s1 = sAllL.getSmaller(4);
	OrderedSet s2 = sAllL.getSmaller(12);

	OrderedSet s3 = sAllL.getLarger(20);
	OrderedSet s4 = sAllL.getLarger(11);

	cout << sOrg << endl;

	cout << s1 << endl;
	cout << s2  << endl;
	
	cout << s3 << endl;
	cout << s4 << endl;

}

