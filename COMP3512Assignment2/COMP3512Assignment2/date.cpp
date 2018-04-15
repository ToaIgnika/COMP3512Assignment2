#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "date.hpp"

// define static members
const int Date::days_in_regular_year[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
const int Date::days_in_leap_year[] = { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

Date::Date(int year, int month, int day)
	: year{ year }, month{ month }, day{ day } {
	if (!is_valid_date(year, month, day)) {
		throw std::invalid_argument("Date::Date(int, int, int): invalid argument");
	}

	// Catch the constructor exception
	// try {
	//    Date d(...)
	// } catch (const std::invalid_argument& e) {
	//    cerr << e.what() << endl;
}

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

Date
Date::operator++(int)
{
	Date copy(*this);
	++*this;
	return copy;
}

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

Date
Date::operator--(int)
{
	Date copy(*this);
	--*this;
	return copy;
}

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


bool
Date::is_valid_date(int year, int month, int day)
{
	const int * days = is_leap_year(year) ? days_in_leap_year : days_in_regular_year;
	return 1 <= month && month <= 12 && 1 <= day && day <= days[month];
}

Date
Date::today()
{
	std::time_t now = time(0);
	struct tm * timeinfo = localtime(&now);
	return Date(timeinfo->tm_year + 1900,
		timeinfo->tm_mon + 1,
		timeinfo->tm_mday);
}

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

bool operator==(const Date& lhs, const Date& rhs)
{
	return lhs.year == rhs.year
		&& lhs.month == rhs.month
		&& lhs.day == rhs.day;
}

bool operator!=(const Date& lhs, const Date& rhs)
{
	return !operator==(lhs, rhs);
}

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

bool operator>(const Date& lhs, const Date& rhs)
{
	return operator<(rhs, lhs);
}

bool operator>=(const Date& lhs, const Date& rhs)
{
	return !operator<(lhs, rhs);
}

bool operator<=(const Date& lhs, const Date& rhs)
{
	return !operator>(lhs, rhs);
}

