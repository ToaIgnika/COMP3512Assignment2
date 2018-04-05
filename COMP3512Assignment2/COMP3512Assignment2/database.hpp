#pragma once
#include "patient.h"
#include <queue>

typedef bool(*comp)(Patient, Patient);

bool compare(Patient p1, Patient p2) {
	return (p1 > p2);
}

class Database {
private:
	// Using lambda to compare elements.
	std::priority_queue<Patient, std::vector<Patient>, comp> queue{ compare };

	//std::priority_queue<Patient, std::vector<Patient>, decltype(cmp)>queue(cmp);

	
	//std::priority_queue<int, std::vector<int>, decltype(cmp)> q3(cmp);
public:
	Database() {
		auto cmp = [](Patient left, Patient right) { 
			return true; 
		};
		std::priority_queue<Patient, std::vector<Patient>, decltype(cmp)>queue(cmp);
	}

	Patient get_patient() {
		Patient temp = queue.top();
		queue.pop();
		return temp;
	}

	void add_patient(Patient p) {
		queue.push(p);
	}


	void print_queue() {
		Patient temp = queue.top();
		temp.print_patient();
	}
};