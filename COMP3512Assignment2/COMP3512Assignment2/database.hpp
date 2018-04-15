#pragma once
#include "patient.hpp"
#include <queue>
#include <exception>
#include <stdexcept>
#include <stdio.h>
#include <istream>
#include <fstream>
#include "exceptions.hpp"

typedef bool(*comp)(Patient, Patient);

static bool compare(Patient p1, Patient p2) {
	return p1 > p2;
}

class Database {
private:
	std::priority_queue<Patient, std::vector<Patient>, comp> queue{ compare };
	int count;
	time current_time;
public:
	Database();

	Patient get_patient();

	void add_patient(Patient p);

	void print_queue();

	int get_min_from_time(time t);

	void update_queue();

	bool get_by_healthnum(std::string n);

	void update_patient_status(Patient& p);

	void set_by_healthnum(std::string patient_num, int new_status);

	void print_current_time();

	void set_max_time();

	int get_current_time();

	void load_queue();

	void save_queue();
};