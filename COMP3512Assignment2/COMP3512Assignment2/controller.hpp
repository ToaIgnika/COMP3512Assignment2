#pragma once
#include <iostream>
#include <istream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include "database.hpp"
#include "date.hpp"

class Controller {
private:
	Database db;
public:
	Controller() {
	}

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

	void print_status_menu() {
		std::cout << "Please, select patients status:" << std::endl;
		std::cout << "1. Critical and life-threatening, requires immediate care" << std::endl;
		std::cout << "2. Critical, requires care `very soon'" << std::endl;
		std::cout << "3. Serious, requires care `soon'" << std::endl;
		std::cout << "4. Serious" << std::endl;
		std::cout << "5. Non-serious" << std::endl;
		std::cout << "6. Not a priority" << std::endl;
	}

	bool is_valid_healthcare_input(std::string f) {
		if (f.length() != 8) {
			return false;
		}
		else {
			for (int i = 0; i < 8; ++i) {
				if (!isdigit(f[i])) {
					return false;
				}
			}
		}
		return true;
	}

	std::string prompt_name(std::string f, bool req = false) {
		std::cin.clear();
		std::string content;
		std::string line;
		std::cout << f << std::endl;
		std::cin >> line;
		if (req) {
			while (!is_valid_healthcare_input(line)) {
				std::cout << "Invalid HealthCard Number. Please, try again." << std::endl;
				cin >> line;
			}
		}
		content += line;
		return content;
	}



	std::string prompt_sympt(std::string f) {
		std::cin.clear();
		std::cin.ignore();
		std::cout << f;
		std::string line;
		std::getline(std::cin, line);
		return line;
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
		p.set_healthcare_num(prompt_name("HealthCare #: ", true));
		p.set_register_time(prompt_time("Registration time: "));
		p.set_symptoms(prompt_sympt("Symptoms: "));
		print_status_menu();
		p.set_seriousness(prompt_num("How dead you are: "));
		std::cout << "Patient successfuly added." << std::endl;
		return p;
	}

	void change_patient() {
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

	void run_menu() {
		print_menu();
		char u_input = 'p';
		while (true) {
			std::cin >> u_input;
			switch (u_input) {
			case '1':
				system("CLS");
				db.add_patient(compile_patient());
				db.print_current_time();
				print_menu();
				break;
			case '2':
				system("CLS");
				db.get_patient();
				db.print_current_time();
				print_menu();
				break;
			case '3':
				system("CLS");
				change_patient();
				db.print_current_time();
				print_menu();
				break;
			case '4':
				system("CLS");
				std::cout << "Saving to file..." << std::endl;
				db.save_queue();
				db.print_current_time();
				print_menu();
				break;
			case '5':
				system("CLS");
				std::cout << "Loading from file..." << std::endl;
				db.load_queue();
				db.print_current_time();
				print_menu();
				break;
			case '6':
				system("CLS");
				db.print_queue();
				db.print_current_time();
				print_menu();
				break;
			case '7':
				return;
				break;
			case '*':
				system("CLS");
				db.print_current_time();
				print_menu();
				break;
			}
		}
	}
};





/*
(a) Last name / req
(b) First name / req
(c) Middle name / optional
(d) Year of birth / req
(e) Month of birth / req
(f) Day of birth / req
(g) Personal healthcare number / req, 8-digit number
(h) Time admitted in format 24:00 / req, xx:xx format
(i) Main symptom(s) (one line) / optional
(j) Category number / int between 1 and 6. 
*/

