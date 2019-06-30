// $Id: main.cpp,v 1.58 2019-04-05 16:29:31-07 - - $

#include <cassert>
#include <deque>
#include <iostream>
#include <stdexcept>
#include <unordered_map>
#include <utility>
#include <string.h>
using namespace std;
#ifdef _WIN32
#include <process.h>
#include "wingetopt.h"
#else
#include <unistd.h>
#endif

#include "bigint.h"
#include "debug.h"
#include "iterstack.h"
#include "libfns.h"
#include "scanner.h"

using bigint_stack = iterstack<bigint>;



void do_clear(bigint_stack& stack, const char) {
	// DEBUGF('d', "");
	stack.clear();
}


void do_dup(bigint_stack& stack, const char) {
	bigint top = stack.top();
	// DEBUGF('d', top);
	stack.push(top);
}

//void do_printall (bigint_stack& stack, const char) {
//   for (const auto& elem: stack) cout << elem << endl;
//}

// void do_print(bigint_stack& stack, const char) {
// 	if (stack.size() < 1) throw ydc_exn("stack empty");
// 	cout << stack.top() << endl;
// }

// void do_debug(bigint_stack&, const char) {
// 	cout << "Y not implemented" << endl;
// }

// class ydc_quit : public exception {};
// void do_quit(bigint_stack&, const char) {
// 	throw ydc_quit();
// }

//void do_function (bigint_stack& stack, const char oper) {
//   switch (oper) {
//      case '+': do_arith    (stack, oper); break;
//      case '-': do_arith    (stack, oper); break;
//      case '*': do_arith    (stack, oper); break;
//      case '/': do_arith    (stack, oper); break;
//      case '%': do_arith    (stack, oper); break;
//      case '^': do_arith    (stack, oper); break;
//      case 'Y': do_debug    (stack, oper); break;
//      case 'c': do_clear    (stack, oper); break;
//      case 'd': do_dup      (stack, oper); break;
//      case 'f': do_printall (stack, oper); break;
//      case 'p': do_print    (stack, oper); break;
//      case 'q': do_quit     (stack, oper); break;
//      default : throw ydc_exn (octal (oper) + " is unimplemented");
//   }
//}


//
// scan_options
//    Options analysis:  The only option is -Dflags. 
//
#ifdef _WIN32
//#define opterr = 0
//#define optarg
//#define optopt
//#define optind
#endif
// void scan_options(int argc, char** argv) {
// 	opterr = 0;
// 	for (;;) {
// 		string temp = "@:";
// 		char* opts = new char[temp.length()];
// 		strcpy_s(opts, temp.length(), temp.c_str());
// 		int option = getopt(argc, argv, opts);
// 		if (option == EOF) break;
// 		switch (option) {
// 		case '@':
// 			debugflags::setflags(optarg);
// 			break;
// 		default:
// 			error() << "-" << static_cast<char> (optopt)
// 				<< ": invalid option" << endl;
// 			break;
// 		}
// 	}
// 	if (optind < argc) {
// 		error() << "operand not permitted" << endl;
// 	}
// }



//Main function.

int main() {
	iterstack <unsigned char> st;
	// st.push(4), st.push(5), st.push(0);
	ubigint u1("432");
	cout << u1 << "\n";
	ubigint u2("432");
	cout << u1 << " == " << u2 << ":	" << (u1 == u2) << "\n";
	ubigint u3("2342");
	cout << u1 << " == " << u3 << ":	" << (u1 == u3) << "\n";
	cout << u1 << " < " << u2 << ":	" << (u1 < u2) << "\n";
	cout << u1 << " < " << u3 << ":	" << (u1 < u3) << "\n";
	cout << u3 << " < " << u1 << ":	" << (u1 > u3) << "\n";
	return 0;
}

