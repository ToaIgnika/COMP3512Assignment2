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
	time register_time;
	std::string reg_time;
	std::vector<std::string> symptoms;

	int cat_for_seriousness;
public:
	Patient() {
		//cat_for_seriousness = cat;
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

	void set_register_time(time s) {
		register_time = s;
	}

	void set_reg(std::string s) {
		reg_time = s;
	}

	void set_seriousness(int s) {
		cat_for_seriousness = s;
	}

	std::string get_healthcare_num() {
		return healthcare_num;
	}

	friend void swap(Patient& p1, Patient& p2) {
		std::swap(p1.first, p2.first);
		std::swap(p1.middle, p2.middle);
		std::swap(p1.last, p2.last);
		std::swap(p1.cat_for_seriousness, p2.cat_for_seriousness);
		std::swap(p1.healthcare_num, p2.healthcare_num);
		std::swap(p1.register_time, p2.register_time);
		std::swap(p1.dob, p2.dob);
		std::swap(p1.symptoms, p2.symptoms);
		//std::swap(p1.first, p2.first);

	};

	Patient& operator=(Patient p) {
		swap(*this, p);
		return *this;
	}

	/*
	(a) Patients in the same category are sorted by their arrival time: `rst-
	come, rst-served.'
	(b) Patients who are waiting will be promoted to the `next' level after
	a certain length of time has elapsed, however, patients who are in
	critical condition will always take priority over patients who were
	admitted and assigned a less serious category:
		i. patients in category two will be promoted to level one after one
		hour
		ii. patients who are in serious condition will be promoted one level
		after two hours
		iii. patients who are in non-serious condition will be promoted one
		level after three hours
		iv. `non-priority' patients will be promoted one level after four hours
	(c) In some cases, a patient's category will change while they are waiting,
	i.e., their condition will worsen or, in rare cases, improve. The nurses
	can change a patient's priority by selecting the third menu item. The
	program must ask the nurse for the patient's personal health number,
	print out the current priority category, and then ask the nurse for the
	new category number.
	*/
	friend bool operator> (const Patient &m1, const Patient &m2) {
		

		if (m1.cat_for_seriousness > m2.cat_for_seriousness) {
			return true;
		} 
		std::cout << "xx1";
		/*
		if (m1.reg_time > m2.reg_time) {
			return true;
		}
		*/
		std::cout << m1.register_time.hh << "|" << m2.register_time.hh;
		if (m1.register_time.hh > m2.register_time.hh) {
			return true;
		}
		std::cout << "xx2";
		if (m1.register_time.hh == m2.register_time.hh) {
			if (m1.register_time.mm > m2.register_time.mm) {
				return true;
			}
		}
		std::cout << "xx3";
		return false;
	}

	int get_cat_for_seriousness() {
		return cat_for_seriousness;
	}

	void print_patient() {
		std::cout << first << " " << middle << " " << last << std::endl;
		std::cout << "HealthCare #: " << healthcare_num << std::endl;
		std::cout << "Cathegory: " << cat_for_seriousness << std::endl;
		std::cout << "Admission time: " << register_time.hh << ":" << register_time.mm << std::endl;
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

