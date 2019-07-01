// $Id: ubigint.cpp,v 1.16 2019-04-02 16:28:42-07 - - $
#include <cctype>
#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
#include<algorithm>
#include<vector>
using namespace std;

#include "ubigint.h"
#include "debug.h"
#ifdef _WIN32
#define not !
#endif
ubigint::ubigint(ubigvalue_t that) : ubig_value(that) {
     DEBUGF('~', this << " -> ")
          for (auto i = ubig_value.begin(); i < ubig_value.end(); i++) {
               DEBUGF('~', this << *i)
          }
}

ubigint::ubigint(const string& that) {
     DEBUGF('~', "that = \"" << that << "\"");
     for (char digit : that) {
          if (not isdigit(digit) && not '_' && not '+') {
               throw invalid_argument("ubigint::ubigint(" + that + ")");
          }
     }
     for(int i = that.length()-1; i >= 0; i--) {
          int convert = that[i] - '0';
          this->ubig_value.push(convert);
          unsigned char temp = ubig_value.top();
     }
}

ubigint ubigint::operator+ (const ubigint& that) const {
     int maxLength;
     int thisSize = this->ubig_value.size();
     int thatSize = that.ubig_value.size();
     ubigint thisCopy(this->ubig_value);
     ubigint thatCopy(that.ubig_value);
     if (thisSize <= thatSize) {
          maxLength = thatSize;
          while(thisCopy.ubig_value.size() != that.ubig_value.size()) {
               thisCopy.ubig_value.push(0);
          }
     }
     else {
          maxLength = thisSize;
          while(thatCopy.ubig_value.size() != thisCopy.ubig_value.size()) {
               thatCopy.ubig_value.push(0);
          }
     }
     ubigvalue_t num;
     ubigint sum ("");
     auto j = thatCopy.ubig_value.end() - 1;
     unsigned char carry = 0;
     for (auto i = thisCopy.ubig_value.end() - 1; thisCopy.ubig_value.begin() < i + 1; --i, --j) {
          udigit_t digit = *i + *j + carry;
          cout << "current digit: " << static_cast<int>(*i) << '\n';
          carry = 0;
          if (digit >= 10) {
               carry = 1;
               digit %= 10;
          }
          sum.ubig_value.push(digit);
     }
     if(carry > 0) {
          sum.ubig_value.push(carry);
     }
     return sum;
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
quo_rem udivide(const ubigint& dividend, const ubigint& divisor_) {
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
     if(this->ubig_value.size() != that.ubig_value.size()) {
          return false;
     }
     auto j = this->ubig_value.begin();
     for (auto i = that.ubig_value.begin(); i < that.ubig_value.end(); ++i, ++j) {
          if (*i != *j) {
               return false;
          }
     }
     return true;
}

bool ubigint::operator< (const ubigint& that) const {
     if(this->ubig_value.size() < that.ubig_value.size()) {
          return true;
     }
     if(this->ubig_value.size() > that.ubig_value.size()) {
          return false;
     }
     auto j = this->ubig_value.begin();
     for (auto i = that.ubig_value.begin(); i < that.ubig_value.end(); ++i, ++j) {
          if (*i > *j) {
               return false;
          }
          if (*i < *j) {
               return true;
          }
     }
     return false;
}

bool ubigint::operator> (const ubigint& that) const {
     if (*this == that) {
          return false;
     }

     return (*this < that);
}

ostream& operator<< (ostream& out, const ubigint& that) {
     out << "ubigint(";
     for (auto i = that.ubig_value.begin(); i < that.ubig_value.end(); ++i) {
          out << static_cast<int>(*i);
     }
     out << ")";
}