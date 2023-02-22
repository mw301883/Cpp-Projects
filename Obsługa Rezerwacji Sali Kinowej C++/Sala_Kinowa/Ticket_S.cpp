#include "Ticket_S.h"
#include <iostream>

using namespace std;

enum {
	Normal = 1,
	Student = 2,
	Discount = 3,
	Family = 4
};

Ticket_S::Ticket_S() : Ticket(Student_Price) {}

Ticket_S::Ticket_S(std::string name, std::string surname, double price, int verse, int column) : Ticket(name, surname, Student_Price, verse, column) {}

void Ticket_S::display_sit() {
	if (this->is_free) {
		cout << "[ + ] ";
	}
	else {
		cout << "[ s-] ";
	}
}

void Ticket_S::display_ticket_type() {
	cout << "studencki";
}

int Ticket_S::type() {
	return Student;
}