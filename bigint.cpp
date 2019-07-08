// $Id: bigint.cpp,v 1.78 2019-04-03 16:44:33-07 - - $

#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;
#include "bigint.h"
#include "debug.h"
#include "relops.h"
#ifdef _WIN32
#define and &&
#define not !
#endif

bigint::bigint (long that): is_negative (that < 0) {
    if (is_negative) {
        that *= -1;
    }
    iterstack<unsigned char> val;
    /*Got this loop from stack overflow at : 
    https://stackoverflow.com/questions/3118490
    /getting-each-individual-digit-from-a-whole-integer
    from Martin B */
    while(that)
    {
        val.push(that % 10);
        that /= 10;
    }
    uvalue = ubigint(val);
    DEBUGF ('~', this << " -> " << uvalue)
}

bigint::bigint (const ubigint& uvalue_, bool is_negative_):
                uvalue(uvalue_), is_negative(is_negative_) {
                    if(uvalue == ubigint("")) {is_negative = false;}
}

bigint::bigint (const string& that) {
    is_negative = that.size() > 0 and that[0] == '_';
    uvalue = ubigint (that.substr (is_negative ? 1 : 0));
}

bigint bigint::operator+ () const {
   return *this;
}

bigint bigint::operator- () const {
   return {uvalue, not is_negative};
}

bigint bigint::operator+ (const bigint& that) const {
    ubigint result;
    bool negative = false;
    if(is_negative == that.is_negative) {
        result = uvalue + that.uvalue;
        negative = is_negative;
    }
    else {
        if(*this < that && uvalue < that.uvalue) {
            result = that.uvalue - uvalue;
            negative = that.is_negative;
        }
        else if(*this < that && uvalue > that.uvalue) {
            result = uvalue - that.uvalue;
            negative = is_negative;
        }
        else if(*this > that && uvalue < that.uvalue) {
            result = that.uvalue - uvalue;
            negative = that.is_negative;
        }
        else {
            result = uvalue - that.uvalue;
            negative = is_negative;
        }
    }
    return bigint(result, negative);
}

bigint bigint::operator- (const bigint& that) const {
    ubigint result;
    bool negative = false;
    if(is_negative == that.is_negative) {
        if(uvalue < that.uvalue) {
            result = that.uvalue - uvalue;
            negative = not is_negative;
        }
        else {
            result = uvalue - that.uvalue;
            negative = is_negative;
        }
    }
    else {
        if(*this < that) {
            result = that.uvalue + uvalue;
            negative = true;
        }
        else {
            result = uvalue + that.uvalue;
            negative = false;
        }
    }
    return bigint(result, negative);
}


bigint bigint::operator* (const bigint& that) const {
    bigint result = uvalue * that.uvalue;
    result.is_negative = (is_negative != that.is_negative);
    return result;
}

bigint bigint::operator/ (const bigint& that) const {
    return bigint((uvalue / that.uvalue), 
    (is_negative != that.is_negative));
}

bigint bigint::operator% (const bigint& that) const {
    return bigint((uvalue % that.uvalue), 
    (is_negative != that.is_negative));
}

bool bigint::operator== (const bigint& that) const {
   return is_negative == that.is_negative and uvalue == that.uvalue;
}

bool bigint::operator< (const bigint& that) const {
   if (is_negative != that.is_negative) return is_negative;
   return is_negative ? uvalue > that.uvalue
                      : uvalue < that.uvalue;
}
bool bigint::operator> (const bigint& that) const {
        if(*this == that || *this < that) {
            return false;
        }
        return true;
}
bool bigint::operator<= (const bigint& that) const {
        if(*this == that || *this < that) {
            return true;
        }
        return false;
}
bool bigint::operator>= (const bigint& that) const {
        if(*this == that || *this > that) {
            return true;
        }
        return false;
}
ostream& operator<< (ostream& out, const bigint& that) {
    return out << (that.is_negative ? "-" : "")
                << that.uvalue;
}

