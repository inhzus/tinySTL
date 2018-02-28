#include "algorithmtest.h"
#include <vector>
#include <string>
namespace sz {
	namespace algorithmTest {
		void func1() {
			std::vector<int> vec = { 10, 20, 30 };
			std::vector<int> res = { 11, 21, 31 }, res2 = { 22, 42, 62 };
			sz::for_each(vec.begin(), vec.end(), [&vec](int& i) {
				++i;
			});
			unitassert(containerEqual(vec, res), true, "UnaryFunction for_each(InputIterator first, InputIterator last, UnaryFunction f);");

			sz::for_each_n(vec.begin(), 3, [&vec](int& i) {
				i *= 2;
			});
			unitassert(containerEqual(vec, res2), true, "InputIterator for_each_n(InputIterator first, Size n, UnaryFunction f)");

		}

		void func2() {
			std::vector<int> vec = { 10, 20, 30, 10, 20, 17, 18, 20, 10, 40 };
			unitassert(sz::count(vec.begin(), vec.end(), 10), 3, "count(InputIterator first, InputIterator last, const T& val);");
			unitassert(sz::count_if(vec.begin(), vec.end(), [](int i) {return i % 5 == 0; }), 8, "count_if(InputIterator first, InputIterator last, UnaryPredicate p);");

			unitassert(sz::find(vec.begin(), vec.end(), 20) - vec.begin(), 1, "constexpr InputIterator find(InputIterator first, InputIterator last, const T& val);", false);
			unitassert(sz::find(vec.begin(), vec.end(), 11), vec.end(), "constexpr InputIterator find(InputIterator first, InputIterator last, const T& val);");

			unitassert(sz::find_if(vec.begin(), vec.end(), [](int i) {return i > 39; }), vec.end() - 1, "constexpr InputIterator find_if(InputIterator first, InputIterator last, UnaryPredicate p);");
			unitassert(sz::find_if_not(vec.begin(), vec.end(), [](int i) {return i < 30; }), vec.begin() + 2, "constexpr InputIterator find_if_not(InputIterator first, InputIterator last, UnaryPredicate p);");

			int myints[] = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 };
			std::vector<int> v(myints, myints + 10);
			int needle1[] = { 1, 2, 3 };
			auto it = sz::find_end(v.begin(), v.end(), needle1, needle1 + 3);
			unitassert(it, v.begin() + 5, "constexpr ForwardIterator1 find_end(ForwardIterator1 first, ForwardIterator1 last, ...);");

			int needle2[] = { 4, 5, 1 };
			it = sz::find_end(v.begin(), v.end(), needle2, needle2 + 3, [](int i, int j) {return i == j; });
			unitassert(it, v.begin() + 3, "constexpr ForwardIterator1 find_end(..., BinaryPredicate p);");

			int mychars[] = { 'a', 'b', 'c', 'A', 'B', 'C' };
			std::vector<char> v1(mychars, mychars + 6);
			int needle[] = { 'A', 'B', 'C' };
			auto it1 = sz::find_first_of(v1.begin(), v1.end(), needle, needle + 3);
			unitassert(*it1, 'A', "constexpr InputIterator find_first_of(InputIterator first, InputIterator last, ...);");

			it1 = sz::find_first_of(v1.begin(), v1.end(), needle, needle + 3,
				[](char ch1, char ch2) {return std::tolower(ch1) == std::tolower(ch2); });
			unitassert(*it1, 'a', "constexpr InputIterator find_first_of(..., BinaryPredicate p);");

			int myints1[] = { 5, 20, 5, 30, 30, 20, 10, 10, 20 };
			std::vector<int> v2(myints1, myints1 + 8);
			auto it2 = sz::adjacent_find(v2.begin(), v2.end());
			unitassert(*it2, 30, "constexpr ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last);");

			it2 = sz::adjacent_find(++it2, v2.end(), [](int i, int j) {return i == j; });
			unitassert(*it2, 10, "constexpr ForwardIterator adjacent_find(..., BinaryPredicate p);");
		}

		void func3() {
			std::vector<int> v;
			for (int i = 1; i<10; i++) v.push_back(i * 10);
			int needle1[] = { 40, 50, 60, 70 };
			auto it = sz::search(v.begin(), v.end(), needle1, _SZ end(needle1));
			unitassert(it, v.begin() + 3, "constexpr ForwardIterator1 search(ForwardIterator1 first, ForwardIterator1 last, ...);");
			
			int needle2[] = { 20, 30, 50 };
			it = sz::search(v.begin(), v.end(), needle2, needle2 + 3, [](int i, int j) {return i == j; });
			unitassert(it, v.end(), "constexpr ForwardIterator1 search(..., BinaryPredicate p);");

			std::vector<char> ve = {1, 0, 0, 0, 1, 1, 3, 0, 0, 0, 1, 1, 1, 1};
			unitassert(true, sz::search_n(ve.begin(), ve.end(), 4, 0) == ve.end(), "constexpr ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Size n, const T& val);", false);
			unitassert(true, sz::search_n(ve.begin(), ve.end(), 3, 0) != ve.end(), "constexpr ForwardIterator search_n(ForwardIterator first, ForwardIterator last, Size n, const T& val);");

		}

		void func4() {
			std::vector<int> v1 = { 9, 6, 3, 6, 4, 10 }, v2(6);
			std::vector<int> v3 = { 9, 6, 6, 10 }, v4(4);
			std::vector<int> v5 = { 9, 6, 3, 6 }, v6(4);
			sz::copy(v1.begin(), v1.end(), v2.begin());
			unitassert(v1, v2, "constexpr OutputIterator copy(InputIterator first, InputIterator last, OutputIterator d_first);");
			sz::copy_if(v1.begin(), v1.end(), v4.begin(), [](int i) {return i > 5; });
			unitassert(v3, v4, "constexpr OutputIterator copy_if(..., UnaryPredicate pred);");
			sz::copy_n(v1.begin(), 4, v6.begin());
			unitassert(v5, v6, "constexpr OutputIterator copy_n(InputIterator first, Size n, OutputIterator result);");
			v2.clear();
			v2.resize(6, 0);
			sz::copy_backward(v1.begin(), v1.end(), v2.end());
			unitassert(v1, v2, "constexpr BidirectionalIterator2 copy_backward(BidirectionalIterator1 first, ...);");
		}

		void func5() {
			std::string s1("hello"), s2(5, 0), s3("ifmmp"), s4("aaaaa");
			sz::transform(sz::begin(s1), sz::end(s1), sz::begin(s2), [](unsigned char c) {return c + 1; });
			unitassert(s2, s3, "OutputIterator transform(..., UnaryOperation unary_op);");
			sz::transform(sz::begin(s2), sz::end(s2), sz::begin(s3), sz::begin(s1), [](unsigned char lhs, unsigned char rhs) { return lhs == rhs ? 'a' : 'b'; });
			unitassert(containerEqual(s1, s4), true, "OutputIterator transform(..., BinaryOperation binary_op);");

			std::vector<int> v1(5), v2 = { 2, 3, 4, 5, 6 }, v3 = { 10, 9, 8, 7, 6 };
			sz::generate(v1.begin(), v1.end(), [n = 2]() mutable{ return n++; });
			unitassert(containerEqual(v1, v2), true, "constexpr void generate(ForwardIterator first, ForwardIterator last, Generator g);");

			sz::generate_n(v1.begin(), 5, [n = 10]() mutable {return n--; });
			unitassert(containerEqual(v1, v3), true, "constexpr OutputIterator generate_n(OutputIterator first, Size n, Generator g);");
		}

		void func6() {
			std::string s1("h e llo , worl d"), s2("hello,world"), s3("h\tello\t \t ,\twor ld");
			s1.erase(sz::remove(s1.begin(), s1.end(), ' '), s1.end());
			unitassert(containerEqual(s1, s2), true, "constexpr ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& val);");

			s3.erase(sz::remove_if(s3.begin(), s3.end(), [](unsigned char c) {return c == ' ' || c == '\t'; }), s3.end());
			unitassert(containerEqual(s3, s2), true, "constexpr ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, UnaryPredicate p);");
		}

		void allTestcases() {
			func1();
			func2();
			func3();
			func4();
			func5();
			func6();
		}
	}
}