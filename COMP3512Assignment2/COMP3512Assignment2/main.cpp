#include <iostream>
#include "controller.hpp"
#include "database.hpp"
#include "patient.hpp"
#include <string>
#include <istream>
#include <fstream>

using namespace std;

/*
	Test cases covered, tested and implemented:
	1. All invalid inputs are handled properly. That is, the program will re-prompt user in case of invalid input.
	2. Out of Bondaries queue issues are handled properly
	3. File save/load feature tested and works without issues even in scenario of bad inputs
	4. Priority queue keeps track of time and resorts the queue every time operation happens
	5. Tests were optimized to work in the range of 00:00 - 23:59
	6. Each method was tested manually in the main when creating a patient
	7. Duplicates of the healthcare num are not allowed*
*/


int main() {
	/*
	Database d;
	Database d2;
	Patient p = Patient();
	Patient p2 = Patient();
	Controller cont;
	p.set_first("Alexander");
	p.set_middle("Amadeus");
	p.set_last("Abdulla");
	
	p.set_dob(Date(1994, 8, 8));
	p.set_seriousness(1);
	p.set_healthcare_num("12345678");
	p.set_register_time(time{ 1,20 });
	p.set_symptoms("nonbe");

	p2.set_first("Ryan");
	p2.set_middle("C");
	p2.set_last("Chau");
	p2.set_dob(Date(1997, 11, 22));
	p2.set_seriousness(3);
	p2.set_healthcare_num("12345679");
	time t2;
	t2.hh = 13;
	t2.mm = 40;
	p2.set_register_time(time{ 5,40 });
	p2.set_symptoms("nonbe");
	d.add_patient(p);
	d.add_patient(p2);

	Patient p3;
	p3 = p;
	*/

	Controller cont;
	cont.run_menu();
	return 0;
}