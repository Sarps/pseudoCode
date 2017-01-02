#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <string>
#include <map>

#include "JSONValue.h"

using namespace std;

class Memory {
	public:
	Memory();
	~Memory();
	static Value* get(string var_name);
	static Value*& set(string var_name);
	static void print();

	static Object root;
};

#endif
