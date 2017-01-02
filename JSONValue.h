#ifndef _VALUE_H_
#define _VALUE_H_

#include <vector>
#include <string>
#include <sstream>
#include <map>

using namespace std;

class Value;

typedef vector<Value*> Array;
typedef map<string, Value*> Object;

enum VarType { Var_Null, Var_String, Var_Bool, Var_Number, Var_Array, Var_Object };

class Value
{
	public:
		Value();
		Value(const string value);
		Value(bool value);
		Value(double value);
		Value(int value);
		Value(const Array &value);
		Value(const Object &value);
		Value(const Value &source);
		~Value();

		bool IsNull() const;
		bool IsString() const;
		bool IsBool() const;
		bool IsNumber() const;
		bool IsArray() const;
		bool IsObject() const;

		const string &AsString() const;
		bool AsBool() const;
		double AsNumber() const;
		const Array &AsArray() const;
		const Object &AsObject() const;

		size_t CountChildren() const;
		bool HasChild(std::size_t index) const;
		Value *Child(std::size_t index);
		bool HasChild(const string name) const;
		Value *Child(const string name);
		vector<string> ObjectKeys() const;
		string Stringify(bool const prettyprint = false);

		VarType type;

	private:
		string StringifyString(string str);
		string StringifyImpl(size_t indentDepth);
		string Indent(size_t depth);

		union
		{
			bool bool_value;
			double number_value;
			string string_value;
			Array *array_value;
			Object *object_value;
		};

};

#endif
