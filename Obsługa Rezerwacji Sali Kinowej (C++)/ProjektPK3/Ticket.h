#pragma once
#include <string>

/**
 * @copyright
 * Copyright 2023 Michal Wieczorek.
 */

const double Normal_Price = 25;
const double Student_Price = 12.5;
const double Discount_Price = 15;
const double Family_Price = 17.5;

/**
 * @brief Klasa reprezentujaca rezerwacje normalne dziedziczaca po klasie Ticket.
 */
class Ticket {
protected:
	std::string name;
	std::string surname;
	double price;
	bool is_free;
	int verse, column;
	Ticket(double price);
public:
	Ticket();
	Ticket(std::string name, std::string surname, double price, int verse, int column);
	Ticket(std::string name, std::string surname, int verse, int column);
	~Ticket();
	/**
	* @brief Publiczna metoda ustawiajaca informacje o imieniu na ktorym jest przypisana dana rezerwacja.
	*/
	void set_name(const std::string& name);
	/**
	* @brief Publiczna metoda ustawiajaca informacje o nazwisku na ktorym jest przypisana dana rezerwacja.
	*/
	void set_surname(const std::string& surname);
	/**
	* @brief Publiczna metoda ustawiajaca cene danego miejsca.
	*/
	void set_price(const double& price);
	/**
	* @brief Publiczna metoda zwracajaca informacje o imieniu na ktorym jest przypisana dana rezerwacja.
	*/
	std::string get_name();
	/**
	* @brief Publiczna metoda zwracajaca informacje o nazwisku na ktorym jest przypisana dana rezerwacja.
	*/
	std::string get_surname();
	/**
	* @brief Publiczna metoda zwracajaca informacje o cenie danej rezerwacji.
	*/
	double get_price();
	/**
	* @brief Publiczna metoda zwracajaca informacje czy dane miejsce jest wolne.
	*/
	bool get_is_free();
	/**
	* @brief Publiczna metoda zwracajaca informacje o kolumnie w ktorej znajduje sie dane miejsce.
	*/
	int get_verse();
	/**
	* @brief Publiczna metoda zwracajaca informacje o kolumnie w ktorej znajduje sie dane miejsce.
	*/
	int get_column();
	/**
	* @brief Publiczna metoda dokonujaca operacji rezerwacji miejsca - modyfikuje pole klasy is_free.
	*/
	void reserve();
	/**
	* @brief Publiczna metoda dokonujaca operacji anulowania rezerwacji miejsca - modyfikuje pole klasy is_free.
	*/
	void unreserve();
	/**
	* @brief Publiczna metoda wirtualna, przeslaniana przez klasy dziedziczne, wyswietlajaca odpowiednio pole w animacji wizualizujacej sale kinowa dla rezerwacji norlamnych.
	*/
	virtual void display_sit();
	/**
	* @brief Publiczna metoda wirtualna, przeslaniana przez klasy dziedziczne, wyswietlajaca informacje o typie rezerwacji.
	*/
	virtual void display_ticket_type();
	/**
	* @brief Publiczna metoda wirtualna, przeslaniana przez klasy dziedziczne, zwracajaca informacje o typie obiektu (zwraca wartosc typu int).
	*/
	virtual int type();
};