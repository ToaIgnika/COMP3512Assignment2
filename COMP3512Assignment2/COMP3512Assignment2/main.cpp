#include <iostream>
#include "controller.hpp"
#include "database.hpp"
#include "patient.hpp"
#include <string>
using namespace std;


int main() {

	Database d;
	Database d2;
	Patient p = Patient();
	Patient p2 = Patient();


	p.set_first("Alexander");
	p.set_middle("Amadeus");
	p.set_last("Abdulla");
	
	p.set_dob(Date(1994, 20, 13));
	p.set_seriousness(12);
	p.set_healthcare_num("12345678");
	time t;
	t.hh = 1;
	t.mm = 40;
	p.set_register_time(t);

	p2.set_first("Ryan");
	p2.set_middle("C");
	p2.set_last("Chau");
	p2.set_dob(Date(1997, 29, 1));
	p2.set_seriousness(8);
	p2.set_healthcare_num("12345679");
	time t2;
	t2.hh = 13;
	t2.mm = 40;
	p2.set_register_time(t2);

	d.add_patient(p);
	d.add_patient(p2);

	Patient p3;
	p3 = p;
	//p3.print_patient();

	//p3.set_seriousness(333);
	//p3.print_patient();
	//p.print_patient();
	//d.set_by_healthnum("12345678", 10);

	run_menu(d);

	return 0;
}