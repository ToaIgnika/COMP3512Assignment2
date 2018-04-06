#pragma once
#include "patient.h"
#include <queue>
#include <exception>
#include <stdexcept>
#include <stdio.h>
using namespace std;

class EmptyQueueException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "The queue is empty or the element was not found. Please, add users before performing actions";
	}
} ex ;

class ElementNotFound : public std::exception
{
	virtual const char* what() const throw()
	{
		return "The requested patient was not found.";
	}
} nf;

typedef bool(*comp)(Patient, Patient);

bool compare(Patient p1, Patient p2) {
	return (p1 > p2);
}

class Database {
private:
	std::priority_queue<Patient, std::vector<Patient>, comp> queue{ compare };
	int count;
public:
	Database() {
		auto cmp = [](Patient left, Patient right) { 
			if (left > right) {
				return true;
			}
			if (right > left) {
				return false;
			}
			return false;
		};
		count = 0;
		std::priority_queue<Patient, std::vector<Patient>, decltype(cmp)>queue(cmp);
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
		queue.push(p);
		update_queue();
	}

	void print_queue() {
		try {
			if (count == 0) {
				throw ex;
			}
			auto cmp = [](Patient left, Patient right) {
				if (left > right) {
					return true;
				}
				if (right > left) {
					return false;
				}
				return false;
			};
			std::priority_queue<Patient, std::vector<Patient>, decltype(cmp)>temp(cmp);
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
		auto cmp = [](Patient left, Patient right) {
			if (left > right) {
				return true;
			}
			if (right > left) {
				return false;
			}
			return false;
		};
		std::priority_queue<Patient, std::vector<Patient>, decltype(cmp)>temp(cmp);
		Patient temp_pat;
		
		for (int i = 0; i < count; ++i) {
			temp_pat = queue.top();
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
				throw ex;
			}
			auto cmp = [](Patient left, Patient right) {
				if (left > right) {
					return true;
				}
				if (right > left) {
					return false;
				}
				return false;
			};
			std::priority_queue<Patient, std::vector<Patient>, decltype(cmp)>temp(cmp);
			Patient temp_pat;
			Patient match;
			bool found = false;
			for (int i = 0; i < count; ++i) {
				temp_pat = queue.top();
				queue.pop();
				temp.push(temp_pat);
				if (temp_pat.get_healthcare_num().compare(n) == 0) {
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

	void set_by_healthnum(std::string patient_num, int new_status) {
		try {
			if (count == 0) {
				throw ex;
			}
			auto cmp = [](Patient left, Patient right) {
				if (left > right) {
					return true;
				}
				if (right > left) {
					return false;
				}
				return false;
			};
			std::priority_queue<Patient, std::vector<Patient>, decltype(cmp)>temp(cmp);
			Patient temp_pat;
			Patient match;

			for (int i = 0; i < count; ++i) {
				temp_pat = queue.top();
				queue.pop();
				
				if (temp_pat.get_healthcare_num().compare(patient_num) == 0) {
					temp_pat.set_seriousness(new_status);
					std::cout << "checked";
				}
				//temp_pat.print_patient();
				
				temp.push(temp_pat);

			}
			//std::cout << count;
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