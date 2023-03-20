#include "Ticket.h"
#include <iostream>

using namespace std;

enum {
	Normal = 1,
	Student = 2,
	Discount = 3,
	Family = 4
};

Ticket::Ticket() : name(), surname(), price(Normal_Price), is_free(true), verse(), column() { }

Ticket::Ticket(double price) : name(), surname(), price(price), is_free(true), verse(), column() { }

Ticket::Ticket(std::string name, std::string surname, double price, int verse, int column) : name(name), surname(surname), price(price), is_free(false), verse(verse), column(column) {}

Ticket::Ticket(std::string name, std::string surname, int verse, int column) : name(name), surname(surname), price(25), is_free(false), verse(verse), column(column) {}

Ticket::~Ticket() { }

void Ticket::set_name(const string& name) {
	this->name = name;
}

void Ticket::set_surname(const string& surname) {
	this->surname = surname;
}

void Ticket::set_price(const double& price) {
	this->price = price;
}

string Ticket::get_name() {
	return this->name;
}

string Ticket::get_surname() {
	return this->surname;
}

double Ticket::get_price() {
	return this->price;
}

bool Ticket::get_is_free() {
	return this->is_free;
}

int Ticket::get_verse() {
	return this->verse;
}

int Ticket::get_column() {
	return this->column;
}

void Ticket::reserve() {
	this->is_free = false;
}

void Ticket::unreserve() {
	this->is_free = true;
}

void Ticket::display_sit() {
	if (this->is_free) {
		cout << "[ + ] ";
	}
	else {
		cout << "[ n-] ";
	}
}

void Ticket::display_ticket_type() {
	cout << "normalny";
}

int Ticket::type() {
	return Normal;
}