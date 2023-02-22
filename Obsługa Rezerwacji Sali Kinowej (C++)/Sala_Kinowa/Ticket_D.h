#pragma once
#include "Ticket.h"

/**
 * @copyright
 * Copyright 2023 Michal Wieczorek.
 */


/**
 * @brief Klasa reprezentujaca rezerwacje ulgowe dziedziczaca po klasie Ticket.
 */
class Ticket_D : public Ticket {
public:
	Ticket_D();
	Ticket_D(std::string name, std::string surname, double price, int verse, int column);
	/**
	* @brief Publiczna metoda wirtualna wyswietlajaca odpowiednio pole w animacji wizualizujacej sale kinowa dla rezerwacji ulgowych.
	*/
	virtual void display_sit();
	/**
	* @brief Publiczna metoda wirtualna wyswietlajaca informacje o typie rezerwacji.
	*/
	virtual void display_ticket_type();
	/**
	* @brief Publiczna metoda wirtualna zwracajaca informacje o typie obiektu (zwraca wartosc typu int).
	*/
	virtual int type();
};
