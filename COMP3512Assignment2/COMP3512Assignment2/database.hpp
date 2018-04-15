#pragma once
#include "patient.hpp"
#include <queue>
#include <exception>
#include <stdexcept>
#include <stdio.h>
#include "exceptions.hpp"
using namespace std;



typedef bool(*comp)(Patient, Patient);

bool compare(Patient p1, Patient p2) {
	return p1 > p2;
}
auto cmp = [](Patient left, Patient right) {
	return left > right;
};

class Database {
private:
	std::priority_queue<Patient, std::vector<Patient>, comp> queue{ compare };
	int count;
	time current_time;
public:
	Database() {
		current_time = time{ 0,0 };
		count = 0;
		std::priority_queue<Patient, std::vector<Patient>, comp> queue{ compare };
	}

	Patient get_patient() {
		try {
			if (count == 0) {
				throw ex;
			}
			--count;
			Patient temp = queue.top();
			queue.pop();
			update_queue();
			temp.print_patient();
			return temp;
		}
		catch (exception& e) {
			std::cout << e.what() << std::endl;
		} 
	}

	void add_patient(Patient p) {
		count++;
		current_time = p.get_reg_time();
		queue.push(p);
		update_queue();
	}

	void print_queue() {
		try {
			if (count == 0) {
				throw ex;
			}

			std::priority_queue<Patient, std::vector<Patient>, comp> temp{ compare };
			Patient temp_pat;
			std::cout << "================================" << std::endl;
			for (int i = 0; i < count; ++i) {
				temp_pat = queue.top();
				queue.pop();
				temp.push(temp_pat);
				temp_pat.print_patient();
				std::cout << "================================" << std::endl;
			}
			for (int i = 0; i < count; ++i) {
				temp_pat = temp.top();
				temp.pop();
				queue.push(temp_pat);
			}
		}
		catch (exception& e) {
			std::cout << e.what() << std::endl;
		}
		
	}

	void update_queue() {
	
		std::priority_queue<Patient, std::vector<Patient>, comp> temp{ compare };
		Patient temp_pat;
		
		for (int i = 0; i < count; ++i) {
			temp_pat = queue.top();
			update_patient_status(temp_pat);
			queue.pop();
			temp.push(temp_pat);
		}
		for (int i = 0; i < count; ++i) {
			temp_pat = temp.top();
			temp.pop();
			queue.push(temp_pat);
		}
	}

	bool get_by_healthnum(std::string n) {
		try {
			if (count == 0) {
				return false;
				throw ex;
			}
			std::priority_queue<Patient, std::vector<Patient>, comp> temp{ compare };
			Patient temp_pat;
			Patient match;
			bool found = false;
			for (int i = 0; i < count; ++i) {
				temp_pat = queue.top();
				queue.pop();
				temp.push(temp_pat);
				if (temp_pat.get_healthcare_num().compare(n) == 0) {
					match = temp_pat;
					found = true;
				}
			}
			for (int i = 0; i < count; ++i) {
				temp_pat = temp.top();
				temp.pop();
				queue.push(temp_pat);
			}
			return found;
		}
		catch (exception& e) {
			std::cout << e.what() << std::endl;
		} 
	}

	void update_patient_status(Patient& p) {
		time t = p.get_reg_time();
		int m1 = t.hh * 60 + t.mm;
		int m2 = current_time.hh * 60 + current_time.mm;
		int shift = (m2 - m1) / 60;
		//std:cout << shift << "|" << current_time.hh << "|" << current_time.mm <<std::endl;
		p.set_seriousness(p.get_cat_for_seriousness() + shift);
	}

	void set_by_healthnum(std::string patient_num, int new_status) {
		try {
			if (count == 0) {
				throw ex;
			}
			std::priority_queue<Patient, std::vector<Patient>, comp> temp{ compare };

			Patient temp_pat;
			Patient match;
		
			for (int i = 0; i < count; ++i) {
				temp_pat = queue.top();
				queue.pop();
				if (temp_pat.get_healthcare_num().compare(patient_num) == 0) {
					temp_pat.set_seriousness(new_status);
				}
				temp.push(temp_pat);
			}
			
			for (int i = 0; i < count; ++i) {
				temp_pat = temp.top();
				temp.pop();
				queue.push(temp_pat);
			}
		}
		catch (exception& e) {
			std::cout << e.what() << std::endl;
		}
	};
};