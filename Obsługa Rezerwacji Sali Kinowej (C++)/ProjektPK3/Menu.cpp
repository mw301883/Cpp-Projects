#include "Menu.h"
#include <iostream>
#include <string>

using namespace std;

Menu::Menu(){ }

Menu::~Menu(){}

void Menu::display_opt() {
	
	this->reservation_info.display_cinema();
	cout << "\nn - rezerwacja normalna\n" << "s - rezerwacja studencka\n" << "u - rezerwacja ulgowa\n" << "r - rezerwacja rodzinna\n"
		<< "+ - miejsce wolne\n" << "- - miejsce zajete\n";
	cout << "===========================================================\n"; 
	this->reservation_info.display_sits_info();
	cout << "===========================================================\n" << "1. Dokonanie rezerwacji.\n" << "2. Anulowanie rezerwacji.\n" 
		<< "3. Szukaj rezerwacji.\n" << "4. Wyswietl wszystkie rezerwacje.\n" << "5. Sortuj wszystkie rezerwacje.\n" << "6. Drukuj raport.\n" << "7. Zamknij." << "\n===========================================================\n";
	cout << "Wybor : ";
}

void Menu::start_prog() {
	bool quit{false};
	string choose{};
	while (!quit) {
		display_opt();
		cin >> choose;
		switch ([choose]()->int {
			if (choose == "1") { return 1; }
			else if (choose == "2") {
				return 2;
			}
			else if (choose == "3") {
				return 3;
			}
			else if (choose == "4") {
				return 4;
			}
			else if (choose == "5") {
				return 5;
			}
			else if (choose == "6") {
				return 6;
			}
			else if (choose == "7") {
				return 7;
			}
			else {
				return 0;
			}}())
		{
		case 1:
			this->reservation_info.make_reservation();
			break;
		case 2:
			this->reservation_info.cancel_reserwation();
			break;
		case 3:
			this->reservation_info.search_reservation();
			break;
		case 4:
			this->reservation_info.display_reserwation();
			break;
		case 5:
			this->reservation_info.sort_reservation();
			break;
		case 6:
			this->reservation_info.print_raport();
			break;
		case 7:
			quit = true;
			break;
		default:
			cout << "===========================================================\n";
			cout << "\nNiepoprawny wybor - sprobuj ponownie.\n";
			cout << "===========================================================\n";
			break;
		}
	}
}