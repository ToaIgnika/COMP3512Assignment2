#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "date.hpp"

// define static members
const int Date::days_in_regular_year[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int Date::days_in_leap_year[] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

/*
Desc: Three parameter date constructor 
Pre: Nothing
Post: Creates a date object 
Return: Nothing
*/
Date::Date(int year, int month, int day)
	: year{ year }, month{ month }, day{ day } {
	if (!is_valid_date(year, month, day)) {
		throw std::invalid_argument("Date::Date(int, int, int): invalid argument");
	}
}

/*
Desc: Overloads the ++ operator for the date class
Pre: A date object
Post: Incremements the day in a dynamic fashion
Return: A reference to the current date 
*/
Date&
Date::operator++()
{
	const int * days = is_leap_year() ? days_in_leap_year : days_in_regular_year;
	if (++day > days[month]) {
		day = 1;
		if (++month > 12) {
			month = 1;
			++year;
		}
	}
	return *this;
}

/*
Desc:Overloads the prefix ++operator 
Pre: A date object
Post: Increments the date via prefix 
Return: A copy of this date reference 
*/
Date
Date::operator++(int)
{
	Date copy(*this);
	++*this;
	return copy;
}

/*
Desc: Overloads the -- operator for the date object
Pre: A date object
Post: Dynamically decrements the date object
Return: A reference to this date object
*/
Date&
Date::operator--()
{
	const int * days = is_leap_year() ? days_in_leap_year : days_in_regular_year;
	if (--day < 1) {
		if (--month < 1) {
			month = 12;
			--year;
		}
		day = days[month];
	}
	return *this;
}

/*
Desc: Overloads the prefix -- operator for the date object
Pre: A date object
Post: Dynamically prefix decrements the date object
Return: A reference to a copy of this date object 
*/
Date
Date::operator--(int)
{
	Date copy(*this);
	--*this;
	return copy;
}

/*
Desc: Sets the date values for year month day
Pre: A date objecft
Post: Sets the values
Return: A copy of this date object 
*/
Date
Date::set_date(int year, int month, int day)
{
	if (!is_valid_date(year, month, day)) {
		throw std::invalid_argument("Date::set_date(int, int, int): invalid date");
	}
	Date copy(*this);
	this->year = year;
	this->month = month;
	this->day = day;
	return copy;
}

/*
Desc: Determines if this year is a leap year
Pre: A date object and a year
Post: A boolean representing the answer
Return: A bool 
*/
bool
Date::is_leap_year(int year)
{
	if (year % 400 == 0) {
		return true;
	}
	if (year % 100 == 0) {
		return true;
	}
	if (year % 4 == 0) {
		return true;
	}
	return false;
}


/*
Desc: Determines if this date is value
Pre: A date object a year, month, day
Post: A boolean representing the answer
*/
bool
Date::is_valid_date(int year, int month, int day)
{
	const int * days = is_leap_year(year) ? days_in_leap_year : days_in_regular_year;
	return 1 <= month && month <= 12 && 1 <= day && day <= days[month];
}

/*
Desc: Makes all the date info correspond to today
Pre: A date object
Post: All the date variables change apppropriately
Return: A date object
*/
Date
Date::today()
{
	std::time_t now = time(0);
	struct tm * timeinfo = localtime(&now);
	return Date(timeinfo->tm_year + 1900,
		timeinfo->tm_mon + 1,
		timeinfo->tm_mday);
}

/*
Desc: Overloads the << operator for the date object
Pre: A date object and an ostream
Post: Returns the os with the date info formated nicely
Return: The ostream os
*/
std::ostream&
operator<<(std::ostream& os, const Date& d)
{
	std::ostringstream oss;
	oss << std::setfill('0') << d.year << '/'
		<< std::setw(2) << d.month << '/'
		<< std::setw(2) << d.day;
	os << oss.str();
	return os;
}

/*
Desc: Overloads the >> operator for the date object
Pre: A date object and an istream
Post: Take the istream and inserts it into a date object properly
Return: The istream reference 
*/
std::istream&
operator>>(std::istream& is, Date& date)
{
	std::string s;
	if (is >> s) {
		std::istringstream iss(s);
		int y, m, d;
		char c1, c2;
		if (iss >> y >> c1 >> m >> c2 >> d && c1 == '/' && c2 == '/'
			&& Date::is_valid_date(y, m, d)) {
			date.year = y;
			date.month = m;
			date.day = d;
		}
		else {
			is.setstate(std::ios_base::failbit);
		} // thus called can use Date dl if (cin >> d) ...

	}
	return is;
}

/*
Desc: Checks the equality of the date on both sides
Pre: Two date objects
Post: Returns a boolean representing the answer
Return: A boolean
*/
bool operator==(const Date& lhs, const Date& rhs)
{
	return lhs.year == rhs.year
		&& lhs.month == rhs.month
		&& lhs.day == rhs.day;
}

/*
Desc: Checks the inequality of the date on both sides
Pre: Two date objects
Post: Returns a boolean representing the answer
Return: A boolean
*/
bool operator!=(const Date& lhs, const Date& rhs)
{
	return !operator==(lhs, rhs);
}

/*
Desc: Checks if the rhs is greater than the lhs
Pre: Two date objects
Post: Returns a boolean representing the answer
Return: A boolean
*/
bool operator<(const Date& lhs, const Date& rhs)
{
	if (lhs.year != rhs.year) {
		return lhs.year < rhs.year;
	}
	else if (lhs.month != rhs.month) {
		return lhs.month < rhs.month;
	}
	else if (lhs.day != rhs.day) {
		return lhs.day < rhs.day;
	}
	return false;
}

/*
Desc: Checks if the lhs is greater than the rhs
Pre: Two date objects
Post: Returns a boolean representing the answer
Return: A boolean
*/
bool operator>(const Date& lhs, const Date& rhs)
{
	return operator<(rhs, lhs);
}

/*
Desc: Checks if the rhs is greater than or equal to the lhs
Pre: Two date objects
Post: Returns a boolean representing the answer
Return: A boolean
*/
bool operator>=(const Date& lhs, const Date& rhs)
{
	return !operator<(lhs, rhs);
}

/*
Desc: Checks if the rhs is greater than or equal to the lhs
Pre: two date objects 
Post: Returns a boolean representing the answer
Return: A boolean 
*/
bool operator<=(const Date& lhs, const Date& rhs)
{
	return !operator>(lhs, rhs);
}

