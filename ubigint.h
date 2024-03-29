// $Id: ubigint.h,v 1.11 2016-03-24 19:43:57-07 - - $
#ifndef __UBIGINT_H__
#define __UBIGINT_H__

#include <exception>
#include <iostream>
#include <limits>
#include <utility>
using namespace std;

#include "debug.h"
#include "relops.h"
#include "iterstack.h"

class ubigint {
   friend ostream& operator<< (ostream&, const ubigint&);
   private:
	   using udigit_t = unsigned char;
	   using ubigvalue_t = iterstack<udigit_t>;
	   ubigvalue_t ubig_value;
   public:
      void multiply_by_2();
      void divide_by_2();
      void cut_zeroes ();

      ubigint() = default; // Need default ctor as well.
      ubigint (ubigvalue_t);
      ubigint (const string&);

      ubigint operator+ (const ubigint& that) const;
      ubigint operator+= (const ubigint& that) const;
      ubigint operator- (const ubigint& that) const;
      ubigint operator-= (const ubigint& that) const;
      ubigint operator* (const ubigint& that) const;
      ubigint operator/ (const ubigint& that) const;
      ubigint operator% (const ubigint& that) const;

      bool operator== (const ubigint& that) const;
      bool operator!= (const ubigint& that) const;
      bool operator<  (const ubigint& that) const;
      bool operator<=  (const ubigint& that) const;
      bool operator>  (const ubigint& that) const;
      bool operator>=  (const ubigint& that) const;

};

#endif

