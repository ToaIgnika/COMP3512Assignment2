#pragma once
#include "dob.hpp"
#include "date.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

class Patient {
private:
	std::string first;
	std::string middle;
	std::string last;
	Date dob;
	std::string healthcare_num;
	time register_time;
	std::string symptoms;

	int cat_for_seriousness;
public:
	Patient();

	void set_first(std::string f);

	void set_middle(std::string m);

	void set_last(std::string l);

	void set_dob(Date n);

	void set_healthcare_num(std::string n);

	void set_register_time(time s);

	void set_seriousness(int s);

	std::string get_healthcare_num();

	void set_symptoms(std::string s);

	friend void swap(Patient& p1, Patient& p2);

	Patient& operator=(Patient p);

	void copy(Patient p);

	friend bool operator > (const Patient &m1, const Patient &m2);

	int get_cat_for_seriousness();

	void print_patient();

	time get_reg_time();


	friend std::istream&
		operator>>(std::istream& is, Patient& pat);

	friend std::ostream&
		operator<<(std::ostream& os, const Patient& pat);
};
