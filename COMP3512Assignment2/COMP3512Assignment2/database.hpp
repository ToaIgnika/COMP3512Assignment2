#pragma once
#include "patient.h"
#include <queue>
#include <exception>
#include <stdexcept>
using namespace std;

class EmptyQueueException : public std::exception
{
	virtual const char* what() const throw()
	{
		return "The queue is empty. Please, add users before performing actions";
	}
} ex ;

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
			return left > right;
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
				return left > right;
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
			return left > right;
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
};