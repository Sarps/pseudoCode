#include <iostream>
#include <string>
#include "Library.h"
#include "Parser.h"
#include "Memory.h"

using namespace std;

void alphaAndOmega() {
	try {
	    string data;
	    while(1) {
		    cout << "pseudo$Code>";
		    getline(cin, data, '$');
		    Parser calculator (data);
		    calculator.expr();
	    }
	} catch(const char* e) {
		cout << "Error: " << e << endl;
		alphaAndOmega();
	}
}

int main() {
    Memory mem;
	alphaAndOmega();
}
