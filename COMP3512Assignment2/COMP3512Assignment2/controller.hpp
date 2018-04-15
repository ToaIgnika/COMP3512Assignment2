#include <iostream>
#include <istream>
#include <string>
#include "database.hpp"
#include "date.hpp"

void print_menu() {
	std::cout << "1. Add new patient" << std::endl;
	std::cout << "2. Get next patient" << std::endl;
	std::cout << "3. Change patient category" << std::endl;
	std::cout << "4. Save patient list" << std::endl;
	std::cout << "5. Load patient list" << std::endl;
	std::cout << "6. Print patient list" << std::endl;
	std::cout << "7. Exit program" << std::endl;
	std::cout << "*. Clear screen" << std::endl;
}

std::string prompt_name(std::string f) {
	std::cin.clear();
	std::string content;
	std::string line;
	std::cout << f << std::endl;
	std::cin >> line;
	content += line;
	return content;
}

int prompt_num(std::string f) {
	int n;
	std::cout << f;
	std::cin >> n;
	return n;
}

Date prompt_dob(std::string f) {
	
	int year = prompt_num("Year of birth: ");
	int month = prompt_num("Month of birth: ");
	int day = prompt_num("Day of birth: ");
	Date d = Date(year, month, day);
	return d;
}

time prompt_time(std::string f) {
	time t;
	int conv1, conv2;
	std::cout << f << std::endl;
	std::string z;
	std::cin >> z;	
	std::string hh = z.substr(0, 2);
	std::string mm = z.substr(3, 2);
	t.hh = std::atoi(hh.c_str());
	t.mm = std::atoi(mm.c_str());
	return t;
}

Patient compile_patient() {
	Patient p;
	p.set_last(prompt_name("Last name: "));
	p.set_first(prompt_name("First name: "));
	p.set_middle(prompt_name("Middle name: "));
	p.set_dob(prompt_dob(""));
	p.set_healthcare_num(prompt_name("HealthCare #: "));
	p.set_register_time(prompt_time("Registration time: "));
	p.set_symptoms(prompt_name("Symptoms: "));
	p.set_seriousness(prompt_num("How dead you are: "));
	std::cout << "Patient successfuly added." << std::endl;

	return p;
}

void change_patient(Database& db) {
	std::string num;
	std::cout << "Enter the patient to change: " << std::endl;
	std::cin >> num;
	if (db.get_by_healthnum(num)) {
		std::cout << "User found. Current condition: " << std::endl;
		std::cout << "Enter new item:  " << std::endl;
		int new_num;
		std::cin >> new_num;
		db.set_by_healthnum(num, new_num);
	}
	else {
		std::cout << "Patient was not found. Please, try again." << std::endl;
	}

}

void run_menu(Database db) {
	print_menu();
	char u_input = 'p';

	while (true) {
		std::cin >> u_input;
		switch (u_input) {
		case '1':
			system("CLS");
			db.add_patient(compile_patient());
			print_menu();
			break;
		case '2':
			system("CLS");
			db.get_patient();
			print_menu();
			break;
		case '3':
			system("CLS");
			change_patient(db);
			print_menu();
			break;
		case '4':
			system("CLS");
			std::cout << "Saving to file..." << std::endl;
			print_menu();
			break;
		case '5':
			system("CLS");
			std::cout << "Loading from file..." << std::endl;
			print_menu();
			break;
		case '6':
			system("CLS");
			db.print_queue();
			print_menu();
			break;
		case '7':
			return;
			break;
		case '*':
			system("CLS");
			print_menu();
			break;
		}
		
	}
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

