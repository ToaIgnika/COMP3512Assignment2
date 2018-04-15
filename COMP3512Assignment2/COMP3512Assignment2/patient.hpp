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

	void set_dob(Date n) {
		dob = n;
	}

	void set_healthcare_num(std::string n) {
		healthcare_num = n;
	}

	void set_register_time(time s) {
		register_time.hh = s.hh;
		register_time.mm = s.mm;
	}

	void set_seriousness(int s) {
		if (s < 1) {
			cat_for_seriousness = 0;
		}
		else if (s > 6) {
			cat_for_seriousness = 6;
		}
		else {
			cat_for_seriousness = s;
		}
	}

	std::string get_healthcare_num() {
		return healthcare_num;
	}

	void set_symptoms(std::string s) {
		symptoms = s;
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
	};

	Patient& operator=(Patient p) {
		swap(*this, p);
		return *this;
	}

	void copy(Patient p) {
		first = p.first;
		middle = p.middle;
		last = p.last;
		cat_for_seriousness = p.cat_for_seriousness;
		healthcare_num = p.healthcare_num;
		register_time = p.register_time;
		dob = p.dob;
		symptoms = p.symptoms;
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
	friend bool operator > (const Patient &m1, const Patient &m2) {
		
		if (m1.cat_for_seriousness > m2.cat_for_seriousness) {
			return true;
		} 
		
		if (m1.cat_for_seriousness == m2.cat_for_seriousness) {
			if (m1.register_time.hh > m2.register_time.hh) {
				return true;
			}
			if (m1.register_time.hh == m2.register_time.hh) {
				if (m1.register_time.mm > m2.register_time.mm) {
					return true;
				}
			}
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
		if (register_time.hh < 10) {
			std::cout << "Admission time: 0" << register_time.hh << ":" << register_time.mm << std::endl;
		}
		else if (register_time.hh < 10 && register_time.mm) {
			std::cout << "Admission time: 0" << register_time.hh << ":0" << register_time.mm << std::endl;
		}
		else if (register_time.mm < 10) {
			std::cout << "Admission time: " << register_time.hh << ":0" << register_time.mm << std::endl;
		}
		else {
			std::cout << "Admission time: " << register_time.hh << ":" << register_time.mm << std::endl;
		}
	}

	time get_reg_time() {
		return register_time;
	}


	friend std::istream&
		operator>>(std::istream& is, Patient& pat)
	{
			int cat;
			std::string l_n, f_n, m_n, sympt, hc_num;
			time t;
			int yy, mm, dd, hh_, mm_, stat;
			if (is >> l_n >> f_n >> m_n >> yy >> mm >> dd >> hc_num >> hh_ >> mm_ >> sympt >> stat) {
				pat.set_last(l_n);
				pat.set_first(f_n);
				pat.set_middle(f_n);
				pat.set_dob(Date(yy, mm, dd));
				pat.set_healthcare_num(hc_num);
				pat.set_register_time(time{ hh_, mm_ });
				pat.set_symptoms(sympt);
				pat.set_seriousness(stat);
			}
		return is;
	}

	friend std::ostream&
		operator<<(std::ostream& os, const Patient& pat)
	{
		std::ostringstream oss;
		oss << pat.last << " " << pat.first << " " << pat.middle
			<< " " << pat.dob.get_year() << " " << pat.dob.get_month() << " " << pat.dob.get_day()
			<< " " << pat.healthcare_num
			<< " " << pat.register_time.hh << " " << pat.register_time.mm
			<< " " << pat.symptoms << " " << pat.cat_for_seriousness << "\n" ;
		os << oss.str();
		return os;
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

