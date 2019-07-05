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
     auto j = that.ubig_value.end() - 1;
     auto i = this->ubig_value.end() - 1;
     unsigned char carry = 0;
     for (i = this->ubig_value.end() - 1; this->ubig_value.begin() < i + 1 && that.ubig_value.begin() < j + 1; --i, --j) {
          udigit_t digit = *i + *j + carry;
          // cout << "current digit: " << static_cast<int>(*j) << '\n';
          carry = 0;
          if (digit >= 10) {
               carry = 1;
               digit %= 10;
          }
          sum.ubig_value.push(digit);
     }
     for (i = i; this->ubig_value.begin() < i + 1; --i) {
          sum.ubig_value.push(*i);
     }
     for (j = j; that.ubig_value.begin() < j + 1; --j) {
          sum.ubig_value.push(*j);
     }
     if(carry > 0) {
          sum.ubig_value.push(carry);
     }
     return sum;
}

ubigint ubigint::operator+= (const ubigint& that) const {
     return (*this + that);
}

ubigint ubigint::operator- (const ubigint& that) const {
     if (*this < that) { 
          // cout << *this << " " << that;
          throw domain_error ("ubigint::operator-(a<b)");
     }
     int maxLength;
     ubigvalue_t num;
     ubigint diff ("");
     auto j = that.ubig_value.end() - 1;
     auto i = this->ubig_value.end() - 1;
     unsigned char carry = 0;
     for (j = that.ubig_value.end() - 1; that.ubig_value.begin() < j + 1; --i, --j) {
          udigit_t digit = *i;
          digit = digit - *j - carry;
          carry = 0;
          if (*i < *j) {
               digit += 10;
               carry = 1;
          }
          diff.ubig_value.push(digit);
     }
     for (i = i; this->ubig_value.begin() < i + 1; --i) {
          diff.ubig_value.push(*i - carry);
     }
     return diff;
}
ubigint ubigint::operator-= (const ubigint& that) const {
     return (*this - that);
}
//NEED TO FINISH THE / OPERATOR, THEN THE % OPERATOR
ubigint ubigint::operator* (const ubigint& that) const {
	ubigint product("");
	ubigint intermed("");
	udigit_t carry = 0;
	for (auto i = this->ubig_value.end() - 1; this->ubig_value.begin() < i + 1; --i) {
		carry = 0;
		for (auto j = that.ubig_value.end() - 1; that.ubig_value.begin() < j + 1; --j) {
			intermed.ubig_value.push(*i * *j + carry);
			if (intermed.ubig_value.top() >= 10) {
				carry = intermed.ubig_value.top() / 10;
				// intermed.ubig_value.push(intermed.ubig_value % 10);
			}
		}
		product += intermed;
	}
	// product = cut_zeroes(product);
	return product;
}

void ubigint::multiply_by_2() {
     *this = *this + *this;
}

void ubigint::divide_by_2() {
     ubigint one("1");
     ubigint zero("0");
     if(*this == one) {
          *this = zero;
          return;
     }
     ubigint quotient("");
     udigit_t remainder = 0;
     for (auto i = this->ubig_value.end() - 1; this->ubig_value.begin() < i + 1; --i) {
          udigit_t digit = *i;
          remainder = digit % 2;
          if(remainder > 0) {
               udigit_t prev = quotient.ubig_value.top();
               quotient.ubig_value.pop();
               prev += 5;
               quotient.ubig_value.push(prev);
          }
          digit = digit/2;
          quotient.ubig_value.push(digit);
     }
     quotient.cut_zeroes();
     *this = quotient;
}


struct quo_rem { ubigint quotient; ubigint remainder; };
quo_rem udivide(const ubigint& dividend, const ubigint& divisor) {
     // NOTE: udivide is a non-member function.
     quo_rem calculation;
     ubigint divisor_ = divisor;
     ubigint zero ("0");
     if (divisor == zero) throw domain_error ("udivide by zero");
     ubigint power_of_2 ("1");
     ubigint quotient ("");
     ubigint remainder {dividend}; // left operand, dividend
     while (divisor_ < remainder) {
          divisor_.multiply_by_2();
          power_of_2.multiply_by_2();
     }
     while (power_of_2 > zero && divisor_ > zero) {
          if (divisor_ <= remainder) {           
               remainder -= divisor_;
               quotient = quotient + power_of_2;
               // cout << "quotient: " << quotient << '\n';
          }
          divisor_.divide_by_2();
          power_of_2.divide_by_2();
     }
     return {quotient, remainder};
}

ubigint ubigint::operator/ (const ubigint& that) const {
     quo_rem calculation = udivide(*this, that);  
     return calculation.quotient;
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
bool ubigint::operator!= (const ubigint& that) const {
     return !(*this == that);
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
          int thatVal = static_cast<int>(*i);
          int thisVal = static_cast<int>(*j);
          if (thisVal < thatVal) {
               return true;
          }
          if (thisVal > thatVal) {
               return false;
          }
     }
     return false;
}
bool ubigint::operator<= (const ubigint& that) const {
     if(*this > that) {
          return false;
     }
     return true;
}
bool ubigint::operator> (const ubigint& that) const {
     if (*this == that || *this < that) {
          return false;
     }

     return true;
}
bool ubigint::operator>= (const ubigint& that) const {
     if(*this < that) {
          return false;
     }
     return true;
}
ostream& operator<< (ostream& out, const ubigint& that) {
     out << "ubigint(";
     for (auto i = that.ubig_value.begin(); i < that.ubig_value.end(); ++i) {
          out << static_cast<int>(*i);
     }
     out << ")";
}
void ubigint::cut_zeroes () {
     while(this->ubig_value.top() <= 0) {
          this->ubig_value.pop();
     }
}