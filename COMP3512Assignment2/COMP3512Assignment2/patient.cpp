#pragma once
#include "patient.hpp"
#include "dob.hpp"
#include "date.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

/*
Desc: The default constructor
Pre: None
Post: A default  patient object is created
Return: Nothing
*/
Patient::Patient() {}

/*
Desc: Sets the first string
Pre: A patient is required
Post: The first string is set to f
Return: Nothing
*/
void Patient::set_first(std::string f) {
	first = f;
}

/*
Desc: Sets the middle string
Pre: A patient is required
Post: The middle string is set to m
Return:   Nothing
*/
void Patient::set_middle(std::string m) {
	middle = m;
}

/*
Desc: Sets the last string
Pre: A patient is required
Post: The last string is set to l
Return: Nothing
*/
void Patient::set_last(std::string l) {
	last = l;
}

/*
Desc: Sets a date of birth
Pre: A patient is required
Post: Date of birth is set to n
Return: Nothing
*/
void Patient::set_dob(Date n) {
	dob = n;
}

/*
Desc:Sets the healthcare number
Pre: A patient is required
Post: Healthcare number is set to n
Return: Nothing
*/
void Patient::set_healthcare_num(std::string n) {
	healthcare_num = n;
}

/*
Desc: Sets the register time
Pre: A patient is required
Post: The register time's h and m are set to the s values
Return:  Nothing
*/
void Patient::set_register_time(time s) {
	register_time.hh = s.hh;
	register_time.mm = s.mm;
}

/*
Desc: Sets the seriousness
Pre: A patient is required
Post: The seriousness is set
Return: Nothing
*/
void Patient::set_seriousness(int s) {
	if (s < 1) {
		cat_for_seriousness = 1;
	}
	else if (s > 6) {
		cat_for_seriousness = 6;
	}
	else {
		cat_for_seriousness = s;
	}
}

/*
Desc: Gets the healthcare number
Pre: A patient is required
Post: The healthcare number is returned
Return: Healthcare number
*/
std::string Patient::get_healthcare_num() {
	return healthcare_num;
}

void Patient::set_symptoms(std::string s) {
	symptoms = s;
}


/*
Desc: Swaps patient 1 and patient 2
Pre: Two patients
Post: The patients are swapped
Return: Nothing
*/
void swap(Patient& p1, Patient& p2) {
	std::swap(p1.first, p2.first);
	std::swap(p1.middle, p2.middle);
	std::swap(p1.last, p2.last);
	std::swap(p1.cat_for_seriousness, p2.cat_for_seriousness);
	std::swap(p1.healthcare_num, p2.healthcare_num);
	std::swap(p1.register_time, p2.register_time);
	std::swap(p1.dob, p2.dob);
	std::swap(p1.symptoms, p2.symptoms);
};


/*
Desc: Overloads the = operator to swap patient objets
Pre: A patient object on rhs and lhs
Post: Returns patient object reference
Return: A patient object reference
*/
Patient& Patient::operator=(Patient p) {
	swap(*this, p);
	return *this;
}

/*
Desc: Copy patient p to the current patient
Pre: A patient p and a current patient
Post: Copies the patient
Return: Nothing
*/
void Patient::copy(Patient p) {
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
bool operator > (const Patient &m1, const Patient &m2) {

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

/*
Desc: Gets a current category for seriousness
Pre: A patient
Post: Returns the current category for seriousness
Return: Category for seriousness
*/
int Patient::get_cat_for_seriousness() {
	return cat_for_seriousness;
}

/*
Desc: Prints out details about the current patient
Pre: A patient
Post: Prints out all details
Return: Nothing
*/
void Patient::print_patient() {
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

/*
Desc: Get register time
Pre: A patient
Post: Returns a register time
Return: Register time
*/
time Patient::get_reg_time() {
	return register_time;
}

/*
Desc: Overloads the >> operator to insert a patient in a nice way
Pre: A patient and an is
Post: Inserts a new patient from input
Return: The is
*/
std::istream&
operator>>(std::istream& is, Patient& pat)
{
	int cat;
	std::string l_n, f_n, m_n, sympt, hc_num;
	time t;
	int yy, mm, dd, hh_, mm_, stat;
	is >> l_n >> f_n >> m_n >> yy >> mm >> dd >> hc_num >> hh_ >> mm_;
	std::getline(is, sympt);
	std::cin.clear();
	std::getline(is, sympt);
	is >> stat;
	pat.set_last(l_n);
	pat.set_first(f_n);
	pat.set_middle(f_n);
	pat.set_dob(Date(yy, mm, dd));
	pat.set_healthcare_num(hc_num);
	pat.set_register_time(time{ hh_, mm_ });
	pat.set_symptoms(sympt);
	pat.set_seriousness(stat);
	std::cin.clear();
	return is;
}

/*
Desc: Overloads the << operator to print things out nicely
Pre: A patient and an ostream
Post: Returns an os with the nicely formated printed stuff
Return: os 
*/
std::ostream&
operator<<(std::ostream& os, const Patient& pat)
{
	std::ostringstream oss;
	oss << pat.last << " " << pat.first << " " << pat.middle
		<< " " << pat.dob.get_year() << " " << pat.dob.get_month() << " " << pat.dob.get_day()
		<< " " << pat.healthcare_num
		<< " " << pat.register_time.hh << " " << pat.register_time.mm
		<< "\n" << pat.symptoms << "\n" << pat.cat_for_seriousness << " ";
	os << oss.str();
	return os;
}