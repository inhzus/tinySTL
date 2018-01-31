#ifndef _TEST_UTIL_H_
#define _TEST_UTIL_H_
#include <iostream>
#include <sstream>
#include "rang.hpp"
namespace sz {
	namespace test {
		inline void unitpass(const char* str) {
			std::cout << str << rang::fg::green << " ok\n" << rang::style::reset;
		}
		template<class T>
		void printContainer(T& container, const char* name = "") {
			std::cout << "Container: " << name << std::endl;
			for (auto val : container)
				std::cout << val << std::endl;
		}
		template<class T>
		void printItem(T& container, const char* name = "") {
			std::cout << "Container: " << name << std::endl;
			std::cout << container << std::endl;
		}

		template<class T, class K>
		bool printEqual(T& dest, K& src) {
			std::stringstream ssd, sss;
			ssd << dest;
			sss << src;
			return !ssd.str().compare(sss.str());
		}

		template<class T, class K>
		bool containerEqual(T& dest, K&src){
			auto first1 = std::begin(dest), last1 = std::end(dest);
			auto first2 = std::begin(src), last2 = std::end(src);
			for (; first1 != last1 && first2 != last2; ++first1, ++first2)
				if (*first1 != *first2)
					return false;
			return (first1 == last1 && first2 == last2);
		}

		/*void unitPass(const char* str) {
			std::cout << str << rang::fg::green << " ok\n";
		}*/
	}
}
#endif