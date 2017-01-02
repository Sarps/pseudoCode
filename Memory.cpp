#include "Memory.h"

Memory::Memory(){}

Memory::~Memory() {
    if (root.empty()) return;
    for (Object::iterator it = root.begin(); it != root.end(); ++it) {
        delete it->second;
    }
    root.clear();
}

Value* Memory::get( string var_name ) {
	if ( root.find(var_name) != root.end() ) {
		throw "Variable unknown";
	}
	return root.at(var_name);
}

Value*& Memory::set( string var_name ) {
	return root[var_name];
}

void Memory::print() {
	Object::iterator it;
	cout << "{ ";
	for (it=root.begin(); it != root.end(); it++ ) {
		cout << it->first << " = " << it->second->Stringify() << "\n";
	}
	cout << "}" << endl;
}

Object Memory::root;
