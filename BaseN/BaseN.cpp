// BaseN.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
using  namespace std;

//forward declaration
string convert_to_base(string _num, string _base, string _newbase);
bool is_valid_for_base(string _num, int _base);
string to_upper(string _str);
template <typename T>
T clip(const T& n, const T& lower, const T& upper);
template <typename T>
string NumberToString(T Number);
template <typename T>
T StringToNumber(const string &Text);

//constants
const string charset = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";


int _tmain(int argc, _TCHAR* argv[])
{
	string input = "";
	string base = "";
	string newbase = "";

	cout << "type: \"quit\" to close\n\n";

	do
	{
		cout << "Enter a number and its base: ";
		cin >> input;
			if (input == "quit") break;
		cout << "\tBase: ";
		cin >> base;
			if (base == "quit") break;
		cout << "Convert to base: ";
		cin >> newbase;
			if (newbase == "quit") break;
		cout << "\n";

		cout << convert_to_base(input, base, newbase) << "\n-----------------------------" << endl;
	} while (input != "quit" && base != "quit" && newbase != "quit");
	

	return 0;
}

//convert a number from base: _base to: _newbase
//base values are clamped between 2 and 36
string convert_to_base(string _num, string _base, string _newbase)
{
	string retval = "";
	_num = to_upper(_num);

	//convert input strings to integers
	int inum = StringToNumber<int>(_num);
	int ibase = clip<int>(StringToNumber<int>(_base), 2, 36);
	int inewbase = clip<int>(StringToNumber<int>(_newbase), 2, 36);

	if (!is_valid_for_base(_num, ibase))
		return "Invalid number \"" + _num + "\" for base " + _base;

	//convert to base 10 if it isn't already
	if (ibase != 10)
	{
		inum = 0;
		for (int i = 0; i < _num.length(); i++)
		{
			int pwr = _num.length() - (i+1);
			//get the numerical value of _num[i] (e.g. "A" == 10)
			int val = charset.find(_num[i]);
			inum += val * static_cast<int>(pow(ibase, pwr));
		}
	}

	//if converting to base 10, our work is already done
	if (inewbase == 10)
	{
		retval = NumberToString<int>(inum);
	}
	//otherwise, convert from base 10 to _newbase
	else
	{
		string values = "";
		int remainder = inum;

		do
		{
			values += charset[remainder % inewbase];
			remainder /= inewbase;
		} while (remainder != 0);
		//invert the string
		for (int i = values.length(); i >= 0; i--)
		{
			retval += values[i];
		}
	}
	
	return retval;
}

bool is_valid_for_base(string _num, int _base)
{
	for (int i = 0; i < _num.length(); i++)
	{
		if (charset.find(_num[i]) >= _base)
			return false;
	}
	return true;
}


//Utility functions

//convert all characters to uppercase
string to_upper(string _str)
{
	for (string::size_type i = 0; i < _str.length(); i++)
	{
		_str[i] = toupper(_str[i]);
	}
	return _str;
}

//clamp a numerical value between two points
template <typename T>
T clip(const T& n, const T& lower, const T& upper)
{
	return std::max(lower, std::min(n, upper));
}

//convert a number to a string value
template <typename T>
string NumberToString(T Number)
{
	stringstream ss;
	ss << Number;
	return ss.str();
}

//convert a string to a numerical value
template <typename T>
T StringToNumber(const string &Text)//Text not by const reference so that the function can be used with a 
{									//character array as argument
	stringstream ss(Text);
	T result;
	return ss >> result ? result : 0;
}