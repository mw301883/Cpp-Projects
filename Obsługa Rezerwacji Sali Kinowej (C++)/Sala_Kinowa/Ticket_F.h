#pragma once
#include "Ticket.h"

/**
 * @copyright
 * Copyright 2023 Michal Wieczorek.
 */

/**
 * @brief Klasa reprezentujaca rezerwacje rodzinne dziedziczaca po klasie Ticket.
 */
class Ticket_F : public Ticket {
public:
	Ticket_F();
	Ticket_F(std::string name, std::string surname, double price, int verse, int column);
	/**
	* @brief Publiczna metoda wirtualna wyswietlajaca odpowiednio pole w animacji wizualizujacej sale kinowa dla rezerwacji rodzinnych.
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
