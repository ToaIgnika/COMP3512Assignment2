#pragma once
#include "dob.hpp"
#include <string>
#include <vector>
#include <iostream>

class Patient {
private:
	std::string first;
	std::string middle;
	std::string last;
	DOB dob;
	std::string healthcare_num;
	std::string register_time;
	std::vector<std::string> symptoms;
	//std::string cat_for_seriosness;
	int cat_for_seriousness;
public:
	Patient(int cat) {
		cat_for_seriousness = cat;
	}

	void set_first(std::string f) {
		first = f;
	}

	void set_middle(std::string m) {
		middle = m;
	}

	void set_last(std::string l) {
		last = l;
	}

	void set_dob(DOB n) {
		dob = n;
	}

	void set_healthcare_num(std::string n) {
		healthcare_num = n;
	}

	void set_register_time(std::string s) {
		register_time = s;
	}

	friend bool operator> (const Patient &m1, const Patient &m2) {
		if (m1.cat_for_seriousness > m2.cat_for_seriousness) {
			return true;
		}
		return false;
	}

	int get_cat_for_seriousness() {
		return cat_for_seriousness;
	}

	void print_patient() {
		std::cout << first << " " << middle << " " << last << std::endl;
		std::cout << "HealthCare #: " << healthcare_num << std::endl;
		std::cout << "Cathegory: " << cat_for_seriousness << std::endl;
		std::cout << "Admission time: " << register_time << std::endl;
	}
};

/*
cat_for_seriosness conditions:
(a) Critical and life-threatening, requires immediate care
(b) Critical, requires care `very soon'
(c) Serious, requires care `soon'
(d) Serious
(e) Non-serious
(f) Not a priority
*/

/*
order of input:
(a) Last name
(b) First name
(c) Middle name
(d) Year of birth
(e) Month of birth
(f) Day of birth
(g) Personal healthcare number
(h) Time admitted in format 24:00
(i) Main symptom(s) (one line)
(j) Category number (this will be determined by the nurse at the desk,
not the patient of course)
*/