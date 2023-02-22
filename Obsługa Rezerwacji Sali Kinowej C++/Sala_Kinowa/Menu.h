#pragma once
#include "Data.h"

/**
 * @copyright
 * Copyright 2023 Michal Wieczorek.
 */

enum Options{
	Option_One,
	Option_Two,
	Option_Three,
	Option_Four,
	Option_Five,
};


/**
 * @brief Klasa glowna zarzadzajaca pozostalymi klasami programu (rdzen programu - zgodnie z wzorcem projektowym kompozyt).
 */
class Menu {
private:
	Data reservation_info;
public:
	Menu();
	~Menu();
	/**
	 * @brief Publiczna metoda wyswietlajaca opcje w glownym menu programu.
	 */
	void display_opt();
	/**
	 * @brief Publiczna metoda wlaczajaca program - glowna petla programu.
	 */
	void start_prog();
};