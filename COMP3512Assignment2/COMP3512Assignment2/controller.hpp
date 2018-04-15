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
	Controller();
	void print_menu();
	void print_status_menu();

	bool is_valid_healthcare_input(std::string f);

	bool is_valid_time(std::string f);

	std::string prompt_name(std::string f, bool req);

	std::string prompt_sympt(std::string f);

	int prompt_num(std::string f);

	Date prompt_dob(std::string f);

	time prompt_time(std::string f);

	Patient compile_patient();

	void change_patient();

	void run_menu();
};
