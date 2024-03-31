#pragma once

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <bitset>

/*
 * The purpose of this class is to provide a custom way to print uint64_t values with google test.
 * Technically you can override UniversalPrinter and PrintTo(), but I couldn't get that to work for me.
 * It's pretty easy for custom types, you just override the << operator, but for standard types its harder.
 * Here's three links for how you're apparently supposed to do it for standard types:
 * [1]: https://github.com/google/googletest/discussions/4121
 * [2]: https://stackoverflow.com/questions/62054785/google-test-printto-for-stdsetstdstring
 * [3]: https://stackoverflow.com/questions/74007548/how-to-implement-a-custom-value-printer-for-googletest-for-std-enums
 * None of these worked for me, so I just decided to create this custom ExpectedU64 class and override the << operator.
*/
struct ExpectedU64
{
   uint64_t value;
   ExpectedU64(const uint64_t & v);
};

/* Relational operator overloading */
template<typename T>
inline bool operator == (const T & lhs, const ExpectedU64 rhs) { return lhs == rhs.value; }

template<typename T>
inline bool operator == (const ExpectedU64 lhs, const T & rhs) { return lhs.value == rhs; }

/* Stream operator overloading */
inline std::ostream & operator << (std::ostream& out, const ExpectedU64 & e) { out << std::bitset<64>(e.value); return out; }