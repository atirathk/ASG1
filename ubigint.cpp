// $Id: ubigint.cpp,v 1.16 2019-04-02 16:28:42-07 - - $
#include <cctype>
#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "ubigint.h"
#include "debug.h"


ubigint::ubigint(ubigvalue_t that) : ubig_value(that) {
	DEBUGF('~', this << " -> ")
		for (auto i = ubig_value.begin(); i < ubig_value.end(); i++) {
			DEBUGF('~', this << *i)
		}
}

ubigint::ubigint(const string& that) {
	DEBUGF('~', "that = \"" << that << "\"");
	for (char digit : that) {
		if (not isdigit(digit) && not '_' && not) {
			throw invalid_argument("ubigint::ubigint(" + that + ")");
		}
	}
	for (char const c : that) {
		int convert = c - '0';
		this->ubig_value.push(convert);
	}
}

ubigint ubigint::operator+ (const ubigint& that) const {
	//return ubigint (ubig_value + that.ubig_value);
	  //int carry = 0;
	  //int maxLength;
	  //int thisSize = this->ubig_value.size();
	  //int thatSize = that.ubig_value.size();
	  //if (thisSize <= thatSize) {
	  //	maxLength = thatSize;
	  //	this->ubig_value.push("0");
	  //	ubigint temp(this->ubig_value);
	  //	*this = that;
	  //	that = temp;
	  //}
	  /*else {
		  maxLength = input1->size;
		  input2->num = realloc(input2->num, maxLength * sizeof(int));
	  }
	  apint sum;
	  sum = new_apint_default();
	  sum->size = maxLength + 1;
	  sum->num = malloc((sum->size + 1) * sizeof(int));
	  sum->num[sum->size - 1] = 0;
	  bool bothNeg = false;
	  if (input1->num[input1->size - 1] < 0 && input2->num[input2->size - 1] >= 0) {
		  input2->num[input2->size - 1] *= -1;
		  sum = subtract_apint(input2, input1);
		  return sum;
	  }
	  else if (input1->num[input1->size - 1] >= 0 && input2->num[input2->size - 1] < 0) {
		  input2->num[input2->size - 1] *= -1;
		  sum = subtract_apint(input1, input2);
		  return sum;
	  }
	  else if (input1->num[input1->size - 1] < 0 && input2->num[input2->size - 1] < 0) {
		  bothNeg = true;
		  input1->num[input1->size - 1] *= -1;
		  input2->num[input2->size - 1] *= -1;
	  }

	  input2->num[maxLength - 1] = 0;

	  for (int i = 0; i < sum->size - 1; i++) {
		  sum->num[i] = input1->num[i] + input2->num[i] + carry;
		  carry = 0;
		  if (sum->num[i] >= 10) {
			  carry = 1;
			  sum->num[i] = sum->num[i] % 10;
		  }
	  }
	  sum->num[sum->size - 1] = carry;
	  if (bothNeg == true) {
		  sum->num[sum->size - 1] *= -1;
	  }
	  return sum;
	  cerr << "fix ubigint ubigint::operator+!";*/
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