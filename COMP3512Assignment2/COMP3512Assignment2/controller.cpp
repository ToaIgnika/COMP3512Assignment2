#include "controller.hpp"
#include <iostream>
#include <istream>
#include <string>
#include <ctype.h>
#include <stdio.h>
#include "database.hpp"
#include "date.hpp"

/*
Desc: The default constructor fro the controller 
Pre: Nothing
Post: A default controller is created
Return: Nothing
*/
Controller::Controller() {
}

/*
Desc: Prints the controller's menu
Pre: A controller
Post: A printed menu
Return: Nothing
*/
void Controller::print_menu() {
	std::cout << "1. Add new patient" << std::endl;
	std::cout << "2. Get next patient" << std::endl;
	std::cout << "3. Change patient category" << std::endl;
	std::cout << "4. Save patient list" << std::endl;
	std::cout << "5. Load patient list" << std::endl;
	std::cout << "6. Print patient list" << std::endl;
	std::cout << "7. Exit program" << std::endl;
	std::cout << "*. Clear screen" << std::endl;
}

/*
Desc: Prints a status menu
Pre: A controller
Post: A printed status menu
Return: Nothing
*/
void Controller::print_status_menu() {
	std::cout << "Please, select patients status:" << std::endl;
	std::cout << "1. Critical and life-threatening, requires immediate care" << std::endl;
	std::cout << "2. Critical, requires care `very soon'" << std::endl;
	std::cout << "3. Serious, requires care `soon'" << std::endl;
	std::cout << "4. Serious" << std::endl;
	std::cout << "5. Non-serious" << std::endl;
	std::cout << "6. Not a priority" << std::endl;
}

/*
Desc: Determines whether the healthcare input is valid
Pre: A controller and an input 
Post: A boolean representing whether it is valid or not
Return: A boolean value 
*/
bool Controller::is_valid_healthcare_input(std::string f) {
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
	if (db.get_by_healthnum(f)) {
		std::cout << "User already exist. ";
		return false;
	}
	return true;
}

/*
Desc: Determines whether the time input is valid
Pre: A controller and an input
Post: A boolean representing whether it is valid or not
Return: A boolean value
*/
bool Controller::is_valid_time(std::string f) {
	if (f.length() != 5) {
		return false;
	}
	std::string hhs = f.substr(0, 2);
	std::string mms = f.substr(3, 2);
	int hh = std::atoi(hhs.c_str());
	int mm = std::atoi(mms.c_str());
	if (hh < 0 || hh > 23 || mm < 0 || mm > 59) {
		return false;
	}
	int min = hh * 60 + mm;
	if (min < db.get_current_time()) {
		return false;
	}
	return true;
}

/*
Desc:Prompts the user for another healthcare number
Pre: A controller
Post: Prompt is displayed and content is returned 
Return: Content
*/
std::string Controller::prompt_name(std::string f, bool req = false) {
	std::cin.clear();
	std::string content;
	std::string line;
	std::cout << f << std::endl;
	std::cin >> line;
	if (req) {
		while (!is_valid_healthcare_input(line)) {
			std::cout << "Invalid healthcare number. Please, try again." << std::endl;
			std::cin >> line;
		}
	}
	content += line;
	return content;
}

/*
Desc: The input is cleared and ignored and a prompt is generated 
Pre: A prompt string
Post: A prompt is generated
Return: Line 
*/
std::string Controller::prompt_sympt(std::string f) {
	std::cin.clear();
	std::cin.ignore();
	std::cout << f;
	std::string line;
	std::getline(std::cin, line);
	return line;
}

/*
Desc: Prompts for a number
Pre: A controller
Post: A number prompt is created
Return: An int n_out
*/
int Controller::prompt_num(std::string f) {
	std::string n;
	std::cout << f;
	std::cin >> n;
	int n_out = std::atoi(n.c_str());
	return n_out;
}

/*
Desc: Prompts for date of birth 
Pre: A prompt string f and controller
Post: Prompts are generated and displayed
Return: A date d with the prompts 
*/
Date Controller::prompt_dob(std::string f) {
	Date d;
	int year = prompt_num("Year of birth: ");
	int month = prompt_num("Month of birth: ");
	int day = prompt_num("Day of birth: ");
	while (!d.is_valid_date(year, month, day)) {
		std::cout << "Invalid date. Try again" << std::endl;
		year = prompt_num("Year of birth: ");
		month = prompt_num("Month of birth: ");
		day = prompt_num("Day of birth: ");
	}
	d = Date(year, month, day);
	return d;
}

/*
Desc: A prompt time is generated 
Pre: A controller and prompt string f
Post: A prompt time is generated
Return: Time t 
*/
time Controller::prompt_time(std::string f) {
	time t;
	int conv1, conv2;
	std::cout << f << std::endl;
	std::string z;
	std::cin >> z;
	while (!is_valid_time(z)) {
		std::cout << "Time is invalid. Please, use 24-hour format. hh:mm" << std::endl;
		std::cin >> z;
	}
	std::string hh = z.substr(0, 2);
	std::string mm = z.substr(3, 2);
	t.hh = std::atoi(hh.c_str());
	t.mm = std::atoi(mm.c_str());
	return t;
}

/*
Desc: The patient is compiled and values are set
Pre: A patient and a controller 
Post: The patient info is compiled
Return: The freshly compiled patient p 
*/
Patient Controller::compile_patient() {
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

/*
Desc: Changes the patient 
Pre: A patient and a controller
Post: The patient is changed
Return: Nothing
*/
void Controller::change_patient() {
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

/*
Desc: Runs the controller menu
Pre: A controller 
Post: A menu actually run as a program
Return: Nothing 
*/
void Controller::run_menu() {
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