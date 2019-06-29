// $Id: util.cpp,v 1.1 2016-06-14 18:19:17-07 - - $
#ifdef __unix__

#include <cstring>
#include <string.h>
#include <libgen.h>
using namespace std;

#include "util.h"
ydc_exn::ydc_exn (const string& what): runtime_error (what) {
}

string exec::execname_; // Must be initialized from main(). 
int exec::status_ = EXIT_SUCCESS;

void exec::execname (const string& argv0) {
   // char* argv0Dup = strdup(argv0.c_str());
   execname_ = basename (strdup(argv0.c_str()));
   cout << boolalpha;
   cerr << boolalpha;
   DEBUGF ('Y', "execname = " << execname_);
}

void exec::status (int new_status) {
   new_status &= 0xFF;
   if (status_ < new_status) status_ = new_status;
}

ostream& note() {
   return cerr << exec::execname() << ": ";
}

ostream& error() {
   exec::status (EXIT_FAILURE);
   return note();
}

#endif
