#include <iostream>
#include "controller.hpp"
#include "database.hpp"
#include <string>
using namespace std;


int main() {

	Database d;
	Patient p = Patient();
	Patient p2 = Patient();


	p.set_first("Alexander");
	p.set_middle("Amadeus");
	p.set_last("Abdulla");
	DOB db;
	db.day = 10;
	db.month = 12;
	db.year = 12;
	p.set_dob(db);
	p.set_seriousness(12);
	p.set_healthcare_num("12345678");
	time t;
	t.hh = 1;
	t.mm = 40;
	p.set_register_time(t);

	p2.set_first("Ryan");
	p2.set_middle("C");
	p2.set_last("Chau");
	DOB db2;
	db2.day = 10;
	db2.month = 12;
	db2.year = 12;
	p2.set_dob(db2);
	p2.set_seriousness(8);
	p2.set_healthcare_num("12345679");
	time t2;
	t2.hh = 13;
	t2.mm = 40;
	p2.set_register_time(t2);

	d.add_patient(p);
	d.add_patient(p2);
	//d.set_by_healthnum("12345678", 10);

	run_menu(d);

	return 0;
}