// VariadicTemplates.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <tuple>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <algorithm>
#include <functional>
#include <type_traits>
#include <memory>


using namespace std;

template<typename Stream, typename... Columns>
class CSVPrinter
{
private:
	Stream& _stream;
	array<string, sizeof...(Columns)> _headers;
	const string _sep = ",";

	template<typename Value, typename... Values>
	void write_line(const Value& val, const Values&... values) const
	{
		write_column(val, _sep);
		write_line(values...);
	}

	template<typename Value>
	void write_line(const Value& val) const
	{
		write_column(val, "\n");
	}

	template<typename T>
	void write_column(const T& val, const string& terminator) const
	{
		if (is_same<typename remove_const<T>::type, string>::value)
		{
			_stream << "\"" << val << "\"";
		}
		else
		{
			_stream << val;
		}
		_stream << terminator;
	}


public:
	// variadic template function
	template<typename... Headers>
	CSVPrinter(Stream& stream, const Headers&... headers)
		: _stream(stream), _headers({ string(headers)... })
	{
		static_assert(
			sizeof...(Headers) == sizeof...(Columns),
			"Number of headers must match number of columns"
			);
	}

	void output_headers() const
	{
		for_each(begin(_headers), 
			     end(_headers) - 1,
				 [=](const string& header){write_column(header, _sep); }
		);
		write_column(_headers.back(), "\n");
	}

	void output_line(const Columns&... columns)
	{
		// validate(columns) expression followed by ellipses
		// tells the compiler to expand the parameter pack
		// given to output_line into its elements
		write_line(validate(columns)...);
	}

	template<typename T>
	const T& validate(const T& val)
	{
		return val;
	}


};

int _tmain(int argc, _TCHAR* argv[])
{
	tuple<int, string, double> entry{ 1, "David", 100.0 };
	tuple<int, string, double> entry2{};
	//tuple<int, string, double> entry3{ 2 }; // error, type safe
	//tuple<int, string, double> entry4{ "Jane", 2, 98.0 };// error, type safe

	vector<tuple<int, string, double>> people
	{
		make_tuple(2, "Brian", 101.2),
		make_tuple(3, "Beth", 202.2),
		make_tuple(4, "Kevin", 303.3)
	};

	// update the second value in the tuple called entry
	get<2>(entry) = 404.4;
	// error: type safety is checked
	// int a = get<1>(people[1]);

	// stick entry at the beginning of the vector
	people.insert(begin(people), entry);
	// run through the entire vector and pump out the tuples
	// using a simple format
	for (const auto& element : people)
	{
		cout << get<0>(element)
			<< " : "
			<< get<1>(element)
			<< " : "
			<< get<2>(element)
			<< endl;
	}

	tuple<string, string> student
	{ "firstname", "lastname" };

	// allows user defined variadic templates
	ofstream stream("out.csv");
	CSVPrinter<decltype(stream),
		int,
		string,
		string,
		int,
		double> printer(stream, "ID", "Prduct ID",
		"Product Description", "quantity", "Price");

	printer.output_headers();
	printer.output_line(10, "12012013", "B737", 2, 125000000);


	return 0;
}

