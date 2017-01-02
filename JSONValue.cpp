#include <string>
#include <cstdlib>
#include <vector>
#include <string>
#include <cmath>

#include "JSONValue.h"

// Macros to free an array/object
#define FREE_ARRAY(x) { Array::iterator iter; for (iter = x.begin(); iter != x.end(); iter++) { delete *iter; } }
#define FREE_OBJECT(x) { Object::iterator iter; for (iter = x.begin(); iter != x.end(); iter++) { delete (*iter).second; } }

/**
 * Basic constructor for creating a  Value of type nullL
 *
 * @access public
 */
Value::Value(/*null*/)
{
	type = Var_Null;
}

/**
 * Basic constructor for creating a  Value of type String
 *
 * @access public
 *
 * @param std::wstring m_string_value The string to use as the value
 */
Value::Value(const string value)
{
	type = Var_String;
	string_value = value;
}

/**
 * Basic constructor for creating a  Value of type Bool
 *
 * @access public
 *
 * @param bool m_bool_value The bool to use as the value
 */
Value::Value(bool value)
{
	type = Var_Bool;
	bool_value = value;
}

/**
 * Basic constructor for creating a  Value of type Number
 *
 * @access public
 *
 * @param double m_number_value The number to use as the value
 */
Value::Value(double value)
{
	type = Var_Number;
	number_value = value;
}

/**
 * Basic constructor for creating a  Value of type Number
 *
 * @access public
 *
 * @param int m_integer_value The number to use as the value
 */
Value::Value(int m_integer_value)
{
	type = Var_Number;
	number_value = (double) m_integer_value;
}

/**
 * Basic constructor for creating a  Value of type Array
 *
 * @access public
 *
 * @param Array m_array_value The Array to use as the value
 */
Value::Value(const Array &value)
{
	type = Var_Array;
	array_value = new Array(value);
}

/**
 * Basic constructor for creating a  Value of type Object
 *
 * @access public
 *
 * @param Object m_object_value The Object to use as the value
 */
Value::Value(const Object &value)
{
	type = Var_Object;
	object_value = new Object(value);
}

/**
 * Copy constructor to perform a deep copy of array / object values
 *
 * @access public
 *
 * @param Value m_source The source Value that is being copied
 */
Value::Value(const Value &m_source)
{
	type = m_source.type;

	switch (type)
	{
		case Var_String:
			string_value = m_source.string_value;
			break;

		case Var_Bool:
			bool_value = m_source.bool_value;
			break;

		case Var_Number:
			number_value = m_source.number_value;
			break;

		case Var_Array:
		{
			Array source_array = *m_source.array_value;
			Array::iterator iter;
			array_value = new Array();
			for (iter = source_array.begin(); iter != source_array.end(); iter++)
				array_value->push_back(new Value(**iter));
			break;
		}

		case Var_Object:
		{
			Object source_object = *m_source.object_value;
			object_value = new Object();
			Object::iterator iter;
			for (iter = source_object.begin(); iter != source_object.end(); iter++)
			{
				string name = (*iter).first;
				(*object_value)[name] = new Value(*((*iter).second));
			}
			break;
		}

		case Var_Null:
			// Nothing to do.
			break;
	}
}

/**
 * The destructor for the  Value object
 * Handles deleting the objects in the array or the object value
 *
 * @access public
 */
Value::~Value()
{
	if (type == Var_Array)
	{
		Array::iterator iter;
		for (iter = array_value->begin(); iter != array_value->end(); iter++)
			delete *iter;
		delete array_value;
	}
	else if (type == Var_Object)
	{
		Object::iterator iter;
		for (iter = object_value->begin(); iter != object_value->end(); iter++)
		{
			delete (*iter).second;
		}
		delete object_value;
	}
}

/**
 * Checks if the value is a nullL
 *
 * @access public
 *
 * @return bool Returns true if it is a nullL value, false otherwise
 */
bool Value::IsNull() const
{
	return type == Var_Null;
}

/**
 * Checks if the value is a String
 *
 * @access public
 *
 * @return bool Returns true if it is a String value, false otherwise
 */
bool Value::IsString() const
{
	return type == Var_String;
}

/**
 * Checks if the value is a Bool
 *
 * @access public
 *
 * @return bool Returns true if it is a Bool value, false otherwise
 */
bool Value::IsBool() const
{
	return type == Var_Bool;
}

/**
 * Checks if the value is a Number
 *
 * @access public
 *
 * @return bool Returns true if it is a Number value, false otherwise
 */
bool Value::IsNumber() const
{
	return type == Var_Number;
}

/**
 * Checks if the value is an Array
 *
 * @access public
 *
 * @return bool Returns true if it is an Array value, false otherwise
 */
bool Value::IsArray() const
{
	return type == Var_Array;
}

/**
 * Checks if the value is an Object
 *
 * @access public
 *
 * @return bool Returns true if it is an Object value, false otherwise
 */
bool Value::IsObject() const
{
	return type == Var_Object;
}

/**
 * Retrieves the String value of this Value
 * Use IsString() before using this method.
 *
 * @access public
 *
 * @return std::wstring Returns the string value
 */
const string &Value::AsString() const
{
	return (string_value);
}

/**
 * Retrieves the Bool value of this Value
 * Use IsBool() before using this method.
 *
 * @access public
 *
 * @return bool Returns the bool value
 */
bool Value::AsBool() const
{
	return bool_value;
}

/**
 * Retrieves the Number value of this Value
 * Use IsNumber() before using this method.
 *
 * @access public
 *
 * @return double Returns the number value
 */
double Value::AsNumber() const
{
	return number_value;
}

/**
 * Retrieves the Array value of this Value
 * Use IsArray() before using this method.
 *
 * @access public
 *
 * @return Array Returns the array value
 */
const Array &Value::AsArray() const
{
	return (*array_value);
}

/**
 * Retrieves the Object value of this Value
 * Use IsObject() before using this method.
 *
 * @access public
 *
 * @return Object Returns the object value
 */
const Object &Value::AsObject() const
{
	return (*object_value);
}

/**
 * Retrieves the number of children of this Value.
 * This number will be 0 or the actual number of children
 * if IsArray() or IsObject().
 *
 * @access public
 *
 * @return The number of children.
 */
std::size_t Value::CountChildren() const
{
	switch (type)
	{
		case Var_Array:
			return array_value->size();
		case Var_Object:
			return object_value->size();
		default:
			return 0;
	}
}

/**
 * Checks if this Value has a child at the given index.
 * Use IsArray() before using this method.
 *
 * @access public
 *
 * @return bool Returns true if the array has a value at the given index.
 */
bool Value::HasChild(std::size_t index) const
{
	if (type == Var_Array)
	{
		return index < array_value->size();
	}
	else
	{
		return false;
	}
}

/**
 * Retrieves the child of this Value at the given index.
 * Use IsArray() before using this method.
 *
 * @access public
 *
 * @return Value* Returns Value at the given index or nullL
 *                    if it doesn't exist.
 */
Value *Value::Child(std::size_t index)
{
	if (index < array_value->size())
	{
		return (*array_value)[index];
	}
	else
	{
		return NULL;
	}
}

/**
 * Checks if this Value has a child at the given key.
 * Use IsObject() before using this method.
 *
 * @access public
 *
 * @return bool Returns true if the object has a value at the given key.
 */
bool Value::HasChild(const string name) const
{
	if (type == Var_Object)
	{
		return object_value->find(name) != object_value->end();
	}
	else
	{
		return false;
	}
}

/**
 * Retrieves the child of this Value at the given key.
 * Use IsObject() before using this method.
 *
 * @access public
 *
 * @return Value* Returns Value for the given key in the object
 *                    or nullL if it doesn't exist.
 */
Value* Value::Child(const string name)
{
	Object::const_iterator it = object_value->find(name);
	if (it != object_value->end())
	{
		return it->second;
	}
	else
	{
		return NULL;
	}
}

/**
 * Retrieves the keys of the  Object or an empty vector
 * if this value is not an object.
 *
 * @access public
 *
 * @return std::vector<std::wstring> A vector containing the keys.
 */
vector<string> Value::ObjectKeys() const
{
	vector<string> keys;

	if (type == Var_Object)
	{
		Object::const_iterator iter = object_value->begin();
		while (iter != object_value->end())
		{
			keys.push_back(iter->first);

			iter++;
		}
	}

	return keys;
}

/**
 * Creates a JSON encoded string for the value with all necessary characters escaped
 *
 * @access public
 *
 * @param bool prettyprint Enable prettyprint
 *
 * @return std::wstring Returns the JSON string
 */
string Value::Stringify(bool const prettyprint)
{
	size_t indentDepth = prettyprint ? 1 : 0;
	return StringifyImpl(indentDepth);
}


/**
 * Creates a JSON encoded string for the value with all necessary characters escaped
 *
 * @access private
 *
 * @param size_t indentDepth The prettyprint indentation depth (0 : no prettyprint)
 *
 * @return std::wstring Returns the JSON string
 */
string Value::StringifyImpl(size_t indentDepth)
{
	string ret_string;
	size_t const indentDepth1 = indentDepth ? indentDepth + 1 : 0;
	string const indentStr = Indent(indentDepth);
	string const indentStr1 = Indent(indentDepth1);

	switch (type)
	{
		case Var_Null:
			ret_string = "null";
			break;

		case Var_String:
			ret_string = StringifyString(string_value);
			break;

		case Var_Bool:
			ret_string = bool_value ? "true" : "false";
			break;

		case Var_Number:
		{
			if (isinf(number_value) || isnan(number_value))
				ret_string = "null";
			else
			{
				stringstream ss;
				ss.precision(15);
				ss << number_value;
				ret_string = ss.str();
			}
			break;
		}

		case Var_Array:
		{
			ret_string = indentDepth ? "[\n" + indentStr1 : "[";
			Array::const_iterator iter = array_value->begin();
			while (iter != array_value->end())
			{
				ret_string += (*iter)->StringifyImpl(indentDepth1);

				// Not at the end - add a separator
				if (++iter != array_value->end())
					ret_string += ",";
			}
			ret_string += indentDepth ? "\n" + indentStr + "]" : "]";
			break;
		}

		case Var_Object:
		{
			ret_string = indentDepth ? "{\n" + indentStr1 : "{";
			Object::const_iterator iter = object_value->begin();
			while (iter != object_value->end())
			{
				ret_string += StringifyString((*iter).first);
				ret_string += ":";
				ret_string += (*iter).second->StringifyImpl(indentDepth1);

				// Not at the end - add a separator
				if (++iter != object_value->end())
					ret_string += ",";
			}
			ret_string += indentDepth ? "\n" + indentStr + "}" : "}";
			break;
		}
	}

	return ret_string;
}

/**
 * Creates a JSON encoded string with all required fields escaped
 * Works from http://www.ecma-internationl.org/publications/files/ECMA-ST/ECMA-262.pdf
 * Section 15.12.3.
 *
 * @access private
 *
 * @param std::wstring str The string that needs to have the characters escaped
 *
 * @return std::wstring Returns the JSON string
 */
string Value::StringifyString(string str)
{
	string str_out = "\"";

	string::const_iterator iter = str.begin();
	while (iter != str.end())
	{
		wchar_t chr = *iter;

		if (chr == L'"' || chr == L'\\' || chr == L'/')
		{
			str_out += L'\\';
			str_out += chr;
		}
		else if (chr == L'\b')
		{
			str_out += "\\b";
		}
		else if (chr == L'\f')
		{
			str_out += "\\f";
		}
		else if (chr == L'\n')
		{
			str_out += "\\n";
		}
		else if (chr == L'\r')
		{
			str_out += "\\r";
		}
		else if (chr == L'\t')
		{
			str_out += "\\t";
		}
		else if (chr < L' ' || chr > 126)
		{
			str_out += "\\u";
			for (int i = 0; i < 4; i++)
			{
				int value = (chr >> 12) & 0xf;
				if (value >= 0 && value <= 9)
					str_out += (wchar_t)('0' + value);
				else if (value >= 10 && value <= 15)
					str_out += (wchar_t)('A' + (value - 10));
				chr <<= 4;
			}
		}
		else
		{
			str_out += chr;
		}

		iter++;
	}

	str_out += "\"";
	return str_out;
}

/**
 * Creates the indentation string for the depth given
 *
 * @access private
 *
 * @param size_t indent The prettyprint indentation depth (0 : no indentation)
 *
 * @return std::wstring Returns the string
 */
string Value::Indent(size_t depth)
{
	depth ? --depth : 0;
	string indentStr;
	for ( int i=0; i < depth * 2; i++) {
        indentStr += ' ';
	}
	return indentStr;
}
