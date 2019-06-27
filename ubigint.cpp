// $Id: ubigint.cpp,v 1.16 2019-04-02 16:28:42-07 - - $
#include <cctype>
#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "ubigint.h"
#include "debug.h"

ubigint::ubigint (ubigvalue_t that): ubig_value (that) {
   DEBUGF ('~', this << " -> ")
   for(auto i = ubig_value.begin(); i != ubig_value.end(); i++) {
	DEBUGF ('~', this << *i)
   }
}

ubigint::ubigint (const string& that): ubig_value(0) {
   //DEBUGF ('~', "that = \"" << that << "\"");
   //for (char digit: that) {
   //   if (not isdigit (digit)) {
   //      throw invalid_argument ("ubigint::ubigint(" + that + ")");
   //   }
   //   ubig_value = ubig_value * 10 + digit - '0';
   //}
}

ubigint ubigint::operator+ (const ubigint& that) const {
   //return ubigint (ubig_value + that.ubig_value);
	cerr << "fix ubigint ubigint::operator+!";
	return that;
}

ubigint ubigint::operator- (const ubigint& that) const {
   //if (*this < that) throw domain_error ("ubigint::operator-(a<b)");
   //return ubigint (ubig_value - that.ubig_value);
   cerr << "fix ubigint ubigint::operator-!";
   return that;
}

ubigint ubigint::operator* (const ubigint& that) const {
   //const int prodSize = this->ubig_value.size() + that.ubig_value.size();
   //unsigned char* product = new unsigned char[prodSize];
   //return ubigint (ubig_value * that.ubig_value);
	cerr << "fix ubigint ubigint::operator*!";
	return that;
}

void ubigint::multiply_by_2() {
   //ubig_value *= 2;
	cerr << "fix void ubigint::multiply_by_2()!";
}

void ubigint::divide_by_2() {
   //ubig_value /= 2;	
   cerr << "fix void ubigint::divide_by_2()!";
}


struct quo_rem { ubigint quotient; ubigint remainder; };
quo_rem udivide (const ubigint& dividend, const ubigint& divisor_) {
   // NOTE: udivide is a non-member function.
   //ubigint divisor {divisor_};
   //ubigint zero {0};
   //if (divisor == zero) throw domain_error ("udivide by zero");
   //ubigint power_of_2 {1};
   //ubigint quotient {0};
   //ubigint remainder {dividend}; // left operand, dividend
   //while (divisor < remainder) {
   //   divisor.multiply_by_2();
   //   power_of_2.multiply_by_2();
   //}
   //while (power_of_2 > zero) {
   //   if (divisor <= remainder) {
   //      remainder = remainder - divisor;
   //      quotient = quotient + power_of_2;
   //   }
   //   divisor.divide_by_2();
   //   power_of_2.divide_by_2();
   //}
   //return {.quotient = quotient, .remainder = remainder};
	cerr << "fix void ubigint::quo_rem udivide()!";
	return {};
}

ubigint ubigint::operator/ (const ubigint& that) const {
   //return udivide (*this, that).quotient;
   return ubigint("0");
}

ubigint ubigint::operator% (const ubigint& that) const {
   //return udivide (*this, that).remainder;
	return ubigint("0");
}

bool ubigint::operator== (const ubigint& that) const {
   //return ubig_value == that.ubig_value;
	return 1;
}

bool ubigint::operator< (const ubigint& that) const {
   //return ubig_value < that.ubig_value;
	return 1;

}

ostream& operator<< (ostream& out, const ubigint& that) {
   out << "ubigint(" << that.ubig_value << ")";
   return out;
}