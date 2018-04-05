#include <iostream>
#include <istream>
#include <string>
#include "database.hpp"

void print_menu() {
	std::cout << "1. Add new patient" << std::endl;
	std::cout << "2. Get next patient" << std::endl;
	std::cout << "3. Change patient category" << std::endl;
	std::cout << "4. Save patient list" << std::endl;
	std::cout << "5. Load patient list" << std::endl;
	std::cout << "6. Print patient list" << std::endl;
	std::cout << "7. Exit program" << std::endl;
}



void run_menu(Database db) {
	print_menu();
	char u_input = 'p';

	while (true) {
		std::cin >> u_input;
		switch (u_input) {
		case '1':
			//db.add_patient(Patient s);
			break;
		case '2':
			db.get_patient();
			break;
		case '3':
			break;
		case '4':
			break;
		case '5':
			break;
		case '6':
			db.print_queue();
			break;
		case '7':
			return;
			break;
		}
	}
}

std::string prompt_name(std::string f) {
	std::string content;
	std::string line;
	std::cout << f;
	getline(std::cin, line);
	content += line;
	return content;
}

int prompt_num(std::string f) {
	int n;
	std::cout << f;
	std::cin >> n;
	return n;
}

DOB prompt_dob(std::string f) {
	DOB d;
	d.year = prompt_num("Year of birth: ");
	d.month = prompt_num("Month of birth: ");
	d.day = prompt_num("Day of birth: ");
	return d;
}

time prompt_time(std::string f) {
	time t;
	t.hh = 0;
	t.mm = 0;
	return t;
}



/*
(a) Last name /
(b) First name / 
(c) Middle name /
(d) Year of birth / 
(e) Month of birth /
(f) Day of birth /
(g) Personal healthcare number /
(h) Time admitted in format 24:00  
(i) Main symptom(s) (one line)
(j) Category number (this will be determined by the nurse at the desk,
not the patient of course)
*/

