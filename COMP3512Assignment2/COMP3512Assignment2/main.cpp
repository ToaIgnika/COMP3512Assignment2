#include <iostream>
#include "controller.hpp"
#include "database.hpp"
#include <string>
using namespace std;


int main() {

	Database d;
	Patient p(0);
	string zzz = "michael";
	p.set_first(zzz);
	p.set_middle("Amadeus");
	p.set_last("Abdulla");
	DOB db;
	db.day = 10;
	db.month = 12;
	db.year = 12;
	p.set_dob(db);
	p.set_healthcare_num("12345678");
	p.set_register_time("12:12:12");

	d.add_patient(p);
	d.add_patient(Patient(2));

	//d.get_patient();
	d.print_queue();
	run_menu();
	return 0;
}