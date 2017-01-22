#include "stdafx.h"
#include "CppUnitTest.h"
#include "../MySet/MySet.h"
#include "../MySet/OrderedSet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(TestMySet)
	{
	public:

		TEST_METHOD(Creation)
		{
			Set s1;
			Set s11(s1);
			const int set2[] = { 1,2,3 };
			Set s2(set2, sizeof(set2) / sizeof(int));
			Set s21(s2);
			Set s22 = s2;
			const int set3[] = { 4,5,5,6 };
			Set s3(set3, sizeof(set3) / sizeof(int));
		}

		TEST_METHOD(CreationOrdered)
		{
			const int set1[] = { 4,5,3,8,2,4,1,9,3 };
			const int set1len = sizeof(set1) / sizeof(int);
			OrderedSet s1(set1, set1len); // 1,2,3,4,5,8,9 // len = 7

			Assert::IsTrue(s1.size() == 7);
			Assert::IsTrue(s1.begin()[0] == 1);
			Assert::IsTrue(s1.begin()[s1.size() - 1] == 9);
		}

		TEST_METHOD(Contains)
		{
			const int set1[] = { 1,2,3 };
			Set s1(set1, sizeof(set1) / sizeof(int));
			Assert::IsTrue(s1.contains(2));
			Assert::IsFalse(s1.contains(0));
			Assert::IsFalse(Set().contains(1));

			const int set2[] = { 2,1 };
			Set s2(set2, sizeof(set2) / sizeof(int));
			Assert::IsTrue(s1.containsAll(s2));
			Assert::IsFalse(s2.containsAll(s1));
			Assert::IsFalse(Set().containsAll(s1));
			Assert::IsTrue(s1.containsAll(Set()));
		}

		TEST_METHOD(GetSmaller)
		{
			const int set1[] = { 4,5,3,8,2,4,9,3 };
			const int set1_len = sizeof(set1) / sizeof(int);
			
			const int smaller[] = { 2,3 };
			const int smaller_len = sizeof(smaller) / sizeof(int);

			OrderedSet s1(set1, set1_len); // 2,3,4,5,8,9 // len = 6
			OrderedSet sSm(smaller, smaller_len); // 2,3
			OrderedSet sEmpty = OrderedSet();

			Assert::IsTrue(s1.getSmaller(4) == sSm);
			Assert::IsTrue(sEmpty.getSmaller(10) == sEmpty);
			Assert::IsTrue(s1.getSmaller(2) == sEmpty);
		}

		TEST_METHOD(GetLarger)
		{
			const int set1[] = { 4,5,3,8,2,4,1,9,3 };
			const int set1_len = sizeof(set1) / sizeof(int);

			const int larger[] = { 5,8,9 };
			const int larger_len = sizeof(larger) / sizeof(int);

			OrderedSet s1(set1, set1_len); // 1,2,3,4,5,8,9 // len = 7
			OrderedSet sLg(larger, larger_len); // 5,8,9
			OrderedSet sEmpty = OrderedSet();

			Assert::IsTrue(s1.getLarger(4) == sLg);
			//Assert::IsTrue(sEmpty.getLarger(10) == sEmpty);
			//Assert::IsTrue(s1.getLarger(20) == sEmpty);
		}

		TEST_METHOD(Empty)
		{
			Assert::IsTrue(Set().isEmpty());

			const int set1[] = { 1,2,3 };
			Set s1(set1, sizeof(set1) / sizeof(int));
			Assert::IsFalse(s1.isEmpty());
		}

		TEST_METHOD(Size)
		{
			Assert::IsTrue(Set().size() == 0);

			const int set1[] = { 1,2,3 };
			Set s1(set1, sizeof(set1) / sizeof(int));
			Assert::IsTrue(s1.size() == 3);
		}

		TEST_METHOD(Merge)
		{
			const int set1[] = { 1,2,3 };
			Set s1(set1, sizeof(set1) / sizeof(int));
			const int set2[] = { 3,2,4 };
			Set s2(set2, sizeof(set2) / sizeof(int));
			const int set3[] = { 1,2,3,4 };
			Set s3(set3, sizeof(set3) / sizeof(int));

			Assert::IsTrue(Set::merge(s1, s2) == s3);
			Assert::IsTrue(Set::merge(s1, Set()) == s1);
			Assert::IsTrue(Set::merge(Set(), s1) == s1);
		}

		TEST_METHOD(MergeOrdered)
		{
			const int set1[] = { 1,2,3,8,5,2,4,7,8 };
			OrderedSet s1(set1, sizeof(set1) / sizeof(int));
			const int set2[] = { 3,2,4 };
			OrderedSet s2(set2, sizeof(set2) / sizeof(int));
			const int set3[] = { 1,2,3,4,5,7,8 };
			OrderedSet s3(set3, sizeof(set3) / sizeof(int));

			Assert::IsTrue(OrderedSet::merge(s1, s2) == s3);
			Assert::IsTrue(OrderedSet::merge(s1, OrderedSet()) == s1);
			Assert::IsTrue(OrderedSet::merge(OrderedSet(), s1) == s1);
		}

		// Differenzmenge A ohne B
		TEST_METHOD(Difference)
		{
			const int set1[] = { 1,2,3 };
			Set s1(set1, sizeof(set1) / sizeof(int));
			const int set2[] = { 3,2,4 };
			Set s2(set2, sizeof(set2) / sizeof(int));
			const int set3[] = { 1 };
			Set s3(set3, sizeof(set3) / sizeof(int));
			const int set4[] = { 4 };
			Set s4(set4, sizeof(set4) / sizeof(int));

			Assert::IsTrue(Set::difference(s1, s2) == s3);
			Assert::IsTrue(Set::difference(s2, s1) == s4);
			Assert::IsTrue(Set::difference(Set(), s1) == Set());
			Assert::IsTrue(Set::difference(s1, Set()) == s1);
		}

		// Schnittmenge
		TEST_METHOD(Intersect)
		{
			const int set1[] = { 1,2,3 };
			Set s1(set1, sizeof(set1) / sizeof(int));
			const int set2[] = { 3,2,4 };
			Set s2(set2, sizeof(set2) / sizeof(int));

			auto s1s2t = Set::intersection(s1, s2) == Set::intersection(s2, s1);
			Assert::IsTrue(Set::intersection(s1, s2) == Set::intersection(s2, s1));
			
			auto sets1t = Set::intersection(Set(), s1) == Set();
			Assert::IsTrue(Set::intersection(Set(), s1) == Set());
			
			auto s1sett = Set::intersection(s1, Set()) == Set();
			Assert::IsTrue(Set::intersection(s1, Set()) == Set());
		}

		TEST_METHOD(MoveSemantics)
		{
			// test move intersection
			const int set1[] = { 1,2,3 };
			Set s1(set1, sizeof(set1) / sizeof(int));
			const int set2[] = { 3,2,4 };
			Set s2(set2, sizeof(set2) / sizeof(int));
			const int set3[] = { 2,3 };
			Set s3(set3, sizeof(set3) / sizeof(int));
			Assert::IsTrue(Set::intersection(s1, std::move(s2)) == s3);
			Assert::IsTrue(s2 == s3);
			Assert::IsTrue(s2.size() == s3.size());

			// test move difference
			// s1 und s3 sollten nicht veraendert worden sein, lediglich s2
			const int set4[] = { 1 };
			Set s4(set4, sizeof(set4) / sizeof(int));
			Assert::IsTrue(Set::difference(std::move(s1), std::move(s3)) == s4);
			Assert::IsTrue(s1 == s4);
			Assert::IsTrue(s1.size() == s4.size());
		}
	};
}