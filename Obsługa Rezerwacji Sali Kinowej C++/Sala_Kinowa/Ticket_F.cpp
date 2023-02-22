#include "Ticket_F.h"
#include <iostream>

using namespace std;

enum {
	Normal = 1,
	Student = 2,
	Discount = 3,
	Family = 4
};

Ticket_F::Ticket_F() : Ticket(Family_Price) {}

Ticket_F::Ticket_F(std::string name, std::string surname, double price, int verse, int column) : Ticket(name, surname, Family_Price, verse, column) {}

void Ticket_F::display_sit() {
	if (this->is_free) {
		cout << "[ + ] ";
	}
	else {
		cout << "[ r-] ";
	}
}

void Ticket_F::display_ticket_type() {
	cout << "rodzinny";
}

int Ticket_F::type() {
	return Family;
}