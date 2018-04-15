#pragma once
#include <fstream>

class Date
{
public:
	Date(int year = 2018, int month = 1, int day = 1);

	// Use compiler-generated copy constructor, destructor, and assignment
	// operator because we are just storing three primitive data members

	int get_year() const { return year; } // implicitly inline
	int get_month() const { return month; }
	int get_day() const { return day; }

	Date set_date(int year, int month, int day); // returns previous date
	bool is_leap_year() const { return is_leap_year(year); }

	// define statics in the class implementation file
	static bool is_leap_year(int year);
	static bool is_valid_date(int year, int month, int date);
	static Date today(); // no *this pointer

	friend std::ostream& operator<<(std::ostream&, const Date&);
	friend std::istream& operator>>(std::istream&, Date&);

	Date& operator++(); //prefix
	Date operator++(int); // postfix
	Date& operator--(); //prefix
	Date operator--(int); // postfix

	friend bool operator==(const Date& lhs, const Date& rhs);
	friend bool operator!=(const Date& lhs, const Date& rhs);
	friend bool operator<(const Date& lhs, const Date& rhs);
	friend bool operator>(const Date& lhs, const Date& rhs);
	friend bool operator>=(const Date& lhs, const Date& rhs);
	friend bool operator<=(const Date& lhs, const Date& rhs);

	//friend bool compare(const Date lhs, const Date rhs);

private:
	int year, month, day;
	static const int days_in_regular_year[];
	static const int days_in_leap_year[];
};
