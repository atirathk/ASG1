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
   DEBUGF ('~', this << " -> " << ubig_value)
}

ubigint::ubigint (const string& that): ubig_value(0) {
   DEBUGF ('~', "that = \"" << that << "\"");
   for (char digit: that) {
      if (not isdigit (digit)) {
         throw invalid_argument ("ubigint::ubigint(" + that + ")");
      }
      ubig_value = ubig_value * 10 + digit - '0';
   }
}

ubigint ubigint::operator+ (const ubigint& that) const {
   return ubigint (ubig_value + that.ubig_value);
}

ubigint ubigint::operator- (const ubigint& that) const {
   if (*this < that) throw domain_error ("ubigint::operator-(a<b)");
   return ubigint (ubig_value - that.ubig_value);
}

ubigint ubigint::operator* (const ubigint& that) const {
   const int prodSize = this->ubig_value.size() + that.ubig_value.size();
   unsigned char* product = new unsigned char[prodSize];
   return ubigint (ubig_value * that.ubig_value);
}

void ubigint::multiply_by_2() {
   ubig_value *= 2;
}

void ubigint::divide_by_2() {
   ubig_value /= 2;
}


struct quo_rem { ubigint quotient; ubigint remainder; };
quo_rem udivide (const ubigint& dividend, const ubigint& divisor_) {
   // NOTE: udivide is a non-member function.
   ubigint divisor {divisor_};
   ubigint zero {0};
   if (divisor == zero) throw domain_error ("udivide by zero");
   ubigint power_of_2 {1};
   ubigint quotient {0};
   ubigint remainder {dividend}; // left operand, dividend
   while (divisor < remainder) {
      divisor.multiply_by_2();
      power_of_2.multiply_by_2();
   }
   while (power_of_2 > zero) {
      if (divisor <= remainder) {
         remainder = remainder - divisor;
         quotient = quotient + power_of_2;
      }
      divisor.divide_by_2();
      power_of_2.divide_by_2();
   }
   return {.quotient = quotient, .remainder = remainder};
}

ubigint ubigint::operator/ (const ubigint& that) const {
   return udivide (*this, that).quotient;
}

ubigint ubigint::operator% (const ubigint& that) const {
   return udivide (*this, that).remainder;
}

bool ubigint::operator== (const ubigint& that) const {
   return ubig_value == that.ubig_value;
}

bool ubigint::operator< (const ubigint& that) const {
   return ubig_value < that.ubig_value;
}

ostream& operator<< (ostream& out, const ubigint& that) {
   out << "ubigint(" << that.ubig_value << ")";
   return out;
}

