#include "Ticket_D.h"
#include <iostream>

using namespace std;

enum {
	Normal = 1,
	Student = 2,
	Discount = 3,
	Family = 4
};

Ticket_D::Ticket_D() : Ticket(Discount_Price) {}

Ticket_D::Ticket_D(std::string name, std::string surname, double price, int verse, int column) : Ticket(name, surname, Discount_Price, verse, column) {}

void Ticket_D::display_sit() {
	if (this->is_free) {
		cout << "[ + ] ";
	}
	else {
		cout << "[ u-] ";
	}
}

void Ticket_D::display_ticket_type() {
	cout << "ze znizka";
}

int Ticket_D::type() {
	return Discount;
}