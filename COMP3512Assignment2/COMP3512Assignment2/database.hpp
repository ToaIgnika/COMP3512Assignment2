#pragma once
#include "patient.hpp"
#include <queue>
#include <exception>
#include <stdexcept>
#include <stdio.h>
#include <istream>
#include <fstream>
#include "exceptions.hpp"
using namespace std;

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

	int get_min_from_time(time t) {
		return t.hh * 60 + t.mm;
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
		p.set_seriousness(p.get_cat_for_seriousness() - shift);
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

	void print_current_time() {
		if (current_time.hh < 10) {
			cout << "Time: 0" << current_time.hh << ":" << current_time.mm << std::endl;
		} else if (current_time.hh < 10 && current_time.mm) {
			cout << "Time: 0" << current_time.hh << ":0" << current_time.mm << std::endl;
		} else if (current_time.mm < 10) {
			cout << "Time: " << current_time.hh << ":0" << current_time.mm << std::endl;
		} else {
			cout << "Time: " << current_time.hh << ":" << current_time.mm << std::endl;
		}
	}

	void set_max_time() {
		std::priority_queue<Patient, std::vector<Patient>, comp> temp{ compare };
		Patient temp_pat;
		time temp_time = { 0,0 };
		for (int i = 0; i < count; ++i) {
			temp_pat = queue.top();
			queue.pop();
			temp.push(temp_pat);
			if (get_min_from_time(temp_time) < get_min_from_time(temp_pat.get_reg_time())) {
				temp_time = temp_pat.get_reg_time();
			}
		}
		for (int i = 0; i < count; ++i) {
			temp_pat = temp.top();
			temp.pop();
			queue.push(temp_pat);
		}
		current_time = temp_time;
	}

	int get_current_time() {
		return get_min_from_time(current_time);
	}

	void load_queue() {
		try {
			for (int i = 0; i < count; ++i) {
				queue.top();
			}
			count = 0;
			ifstream in("patients.txt");
			if (in) {
				in >> count;
				for (int i = 0; i < count; ++i) {
					Patient temp_pat;
					in >> temp_pat;
					queue.push(temp_pat);
				}
				in.close();
			}
			else {
				std::cout << "File is not found." << std::endl;
			}
			in.close();
			set_max_time();
		}
		catch (exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

	void save_queue() {
		ofstream out("patients.txt");
		try {
			if (count == 0) {
				throw ex;
			}
			ifstream in("patients.txt");

			std::priority_queue<Patient, std::vector<Patient>, comp> temp{ compare };
			Patient temp_pat;
			out << count << "\n";
			for (int i = 0; i < count; ++i) {
				temp_pat = queue.top();
				queue.pop();
				temp.push(temp_pat);
				out << temp_pat;
			}
			for (int i = 0; i < count; ++i) {
				temp_pat = temp.top();
				temp.pop();
				queue.push(temp_pat);
			}
			in.close();
		}
		catch (exception& e) {
			std::cout << e.what() << std::endl;
		}
		out.close();
	}
};