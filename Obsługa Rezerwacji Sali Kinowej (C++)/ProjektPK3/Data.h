#pragma once
#include "Ticket.h"
#include "Ticket_S.h"
#include "Ticket_D.h"
#include "Ticket_F.h"
#include "Ticket.h"
#include <vector>
#include <memory>
#include <list>
#include <algorithm>
#include <fstream>

/**
 * @copyright
 * Copyright 2023 Michal Wieczorek.
 */

enum {
	Normal = 1,
	Student = 2,
	Discount = 3,
	Family = 4
};

enum {
	Add = 1,
	Cancel = 2
};

/**
 * @brief Struktura pomocnicza reprezentujaca liczbe danych rezerwacji na dane nazwisko - wykorzystanie w funkcjach sortujacych programu.
 */
struct Ranking {
	std::string name;
	std::string surname;
	int count;
};

/**
 * @brief Struktura pomocnicza przechowujaca dane rezerwacji, ktore zostana zapisane w raporcie.
 */
struct His_obj {
	std::string name;
	std::string surname;
	double price;
	int verse, column, type, mode;
};

/**
 * @brief Funkcja porownujaca obiekty typu ranking i zwracajaca te z wieksza liczba rezerwacji - wykorzystanie w funkcjach sortujacych programu.
 */
bool comp_ranking_count(Ranking obj1, Ranking obj2);
std::string give_type(His_obj obj);
std::string give_mode(His_obj obj);

/**
 * @brief Glowna klasa Data przechowujaca i obslugujaca wszystkie dane w bazie.
 */
class Data {
private:
	/**
	* @brief Struktura danych odpowiedzialna za wyswietlanie animacji wizualizujaca sale kinowa.
	*/
	std::vector<std::vector<std::unique_ptr<Ticket>>> all_tickets;
	/**
	* @brief Struktura danych odpowiedzialna za obluge aktualnych danych dotyczacych rezerwacji.
	*/
	std::list<std::unique_ptr<Ticket>> reservation;
	/**
	* @brief Struktura danych odpowiedzialna za historie rezerwacji zapisywana w raporcie.
	*/
	std::vector<His_obj> history;
	/**
	* @brief Prywatna metoda dodajaca nowa rezerwacje - dokonuje zmian w strukturach danych przechowujacych dane o rezerwacjach.
	*/
	void add_new_reservation(const std::string& name, const std::string& surname, const int& verse, const int& column, const int& type);
public:
	Data();
	~Data();
	/**
	* @brief Publiczna metoda wyswietlajaca animacje wizualizujaca sale kinowa.
	*/
	void display_cinema();
	/**
	* @brief Publiczna metoda wyswietlajaca informacje dodycznaca dostepnosci miejsc (wolne/zajete) w  sali kinowej.
	*/
	void display_sits_info();
	/**
	* @brief Publiczna metoda umozliwiajaca dokonanie nowej rezerwacji.
	*/
	void make_reservation();
	/**
	* @brief Publiczna metoda sprawdzajaca czy wprowadzone dane (wybor rzedu i miejsca w sali) sa dostepne do rezerwacji.
	*/
	void choose_sits(int& verse, int& column);
	/**
	* @brief Publiczna metoda umozliwiajaca wyszukanie danej rezerwacji.
	*/
	void search_reservation();
	/**
	* @brief Publiczna metoda umozliwiajaca wyswietlenie wszystkich rezerwacji znajdujacych sie w bazie.
	*/
	void display_reserwation();
	/**
	* @brief Publiczna metoda umozliwiajaca anulowanie konkretnej rezerwacji.
	*/
	void cancel_reserwation();
	/**
	* @brief Publiczna metoda umozliwiajaca wyswietlenie roznego rodzaju sortowania zgromadzonych danych (sortowanie wedlug ilosci rezeracji lub wyswietlenie tylko rezerwacji o konkretnym typie tj. Normalny, Studencki, Ulgowy, Rodzinny).
	*/
	void sort_reservation();
	/**
	* @brief Publiczna metoda sortujaca i wyswietlajaca rezerwacje pod katem ilosci dodokanych rezerwacji.
	*/
	void display_reservation_ranking();
	/**
	* @brief Publiczna metoda zapisujaca dane dzialanie w bazie danych (dodanie/anulowanie rezerwacji) w historii, ktora moze zostac wydrukowana w raporcie tj. zewnetrznym pliku tekstowym.
	*/
	void add_to_his(const std::string& name, const std::string& surname, const double& price, const int& verse, const int& column, const int& type, const int& mode);
	/**
	* @brief Publiczna metoda zapisujaca historie rezerwacji oraz aktualne zyski w zewnetrznym pliku tekstowym.
	*/
	void print_raport();
};
