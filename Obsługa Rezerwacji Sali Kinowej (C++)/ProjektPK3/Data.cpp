#include "Data.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

vector<unique_ptr<Ticket>> fill_vec() {
	vector<unique_ptr<Ticket>> vec;
	for (int i = 0; i < 10; ++i) {
		vec.push_back(make_unique<Ticket>());
	}
	return vec;
}

Data::Data() { 
	for (int i = 0; i < 8; ++i) {
		this->all_tickets.push_back(fill_vec());
	}
}

Data::~Data() { }

void Data::display_cinema() {
	cout << " \n			 [Sala Kinowa]\n";
	cout << "\n			     Ekran";
	cout << "\n  [---------------------------------------------------------]\n" << "\n";
	cout << "    ";
	for (int i = 1; i < 11; ++i) {
		cout << i << "     ";
	}
	cout << "\n";

	for (int i = 0; i < this->all_tickets.size(); ++i) {
		cout << i + 1 << " ";
		for (int j = 0; j < this->all_tickets.at(0).size(); ++j) {
			this->all_tickets.at(i).at(j)->display_sit();
		}
		cout << "\n";
	}
}

void Data::display_sits_info() {
	cout << "Liczba wolnych miejsc : " << this->all_tickets.size() * this->all_tickets.at(0).size() - this->reservation.size()
		<< "	Liczba zajetych miejsc : " << this->reservation.size() << "\n";
}

void Data::add_new_reservation(const string& name, const string& surname, const int& verse, const int& column, const int& type) {
	unique_ptr<Ticket> new_ticket_ptr_N = make_unique<Ticket>();
	unique_ptr<Ticket> new_ticket_ptr_S = make_unique<Ticket_S>();
	unique_ptr<Ticket> new_ticket_ptr_D = make_unique<Ticket_D>();
	unique_ptr<Ticket> new_ticket_ptr_F = make_unique<Ticket_F>();
	if (type == Normal) {
		this->all_tickets.at(verse - 1).at(column - 1) = move(new_ticket_ptr_N);
		this->all_tickets.at(verse - 1).at(column - 1)->reserve();
		this->all_tickets.at(verse - 1).at(column - 1)->set_name(name);
		this->all_tickets.at(verse - 1).at(column - 1)->set_surname(surname);
		this->reservation.push_back(make_unique<Ticket>(name, surname, this->all_tickets.at(verse - 1).at(column - 1)->get_price(), verse, column));
	}
	else if (type == Student) {
		this->all_tickets.at(verse - 1).at(column - 1) = move(new_ticket_ptr_S);
		this->all_tickets.at(verse - 1).at(column - 1)->reserve();
		this->all_tickets.at(verse - 1).at(column - 1)->set_name(name);
		this->all_tickets.at(verse - 1).at(column - 1)->set_surname(surname);
		this->reservation.push_back(make_unique<Ticket_S>(name, surname, this->all_tickets.at(verse - 1).at(column - 1)->get_price(), verse, column));
	}
	else if (type == Discount) {
		this->all_tickets.at(verse - 1).at(column - 1) = move(new_ticket_ptr_D);
		this->all_tickets.at(verse - 1).at(column - 1)->reserve();
		this->all_tickets.at(verse - 1).at(column - 1)->set_name(name);
		this->all_tickets.at(verse - 1).at(column - 1)->set_surname(surname);
		this->reservation.push_back(make_unique<Ticket_D>(name, surname, this->all_tickets.at(verse - 1).at(column - 1)->get_price(), verse, column));
	}
	else if (type == Family) {
		this->all_tickets.at(verse - 1).at(column - 1) = move(new_ticket_ptr_F);
		this->all_tickets.at(verse - 1).at(column - 1)->reserve();
		this->all_tickets.at(verse - 1).at(column - 1)->set_name(name);
		this->all_tickets.at(verse - 1).at(column - 1)->set_surname(surname);
		this->reservation.push_back(make_unique<Ticket_F>(name, surname, this->all_tickets.at(verse - 1).at(column - 1)->get_price(), verse, column));
	}
}

void Data::make_reservation() {
	if (this->reservation.size() == 80) {
		cout << "\nNie mozna dokonac rezerwacji - brak wolnych miejsc.\n";
	}
	else {
		bool quit{ false };
		string name, surname;
		int verse{}, column{};
		string choose{};
		cout << "\nWprowadz imie : ";
		cin >> name;
		cout << "\nWprowadz nazwisko : ";
		cin >> surname;
		while (!quit) {
			cout << "===========================================================\n";
			cout << "\n1. Bilet normalny - 25 PLN." << "\n2. Bilet studencki - 12.50 PLN."
				<< "\n3. Bilet ulgowy - 15 PLN." << "\n4. Bilet rodzinny (4 rezerwacje) - 18.50 PLN.\n";
			cout << "\nWybierz rodzaj rezerwacji : ";
			cin >> choose;
			switch ([choose]()->int {
				if (choose == "1") {
					return 1;
				}
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
				else {
					return 0;
				}}()) {
			case 1:
				choose_sits(verse, column);
				add_new_reservation(name, surname, verse, column, Normal);
				add_to_his(name, surname, Normal_Price, verse, column, Normal, Add);
				quit = true;
				break;
			case 2:
				choose_sits(verse, column);
				add_new_reservation(name, surname, verse, column, Student);
				add_to_his(name, surname, Student_Price, verse, column, Student, Add);
				quit = true;
				break;
			case 3:
				choose_sits(verse, column);
				add_new_reservation(name, surname, verse, column, Discount);
				add_to_his(name, surname, Discount_Price, verse, column, Discount, Add);
				quit = true;
				break;
			case 4:
				cout << "\nMiejsce 1 :\n";
				choose_sits(verse, column);
				add_new_reservation(name, surname, verse, column, Family);
				add_to_his(name, surname, Family_Price, verse, column, Family, Add);
				cout << "\nMiejsce 2 :\n";
				choose_sits(verse, column);
				add_new_reservation(name, surname, verse, column, Family);
				add_to_his(name, surname, Family_Price, verse, column, Family, Add);
				cout << "\nMiejsce 3 :\n";
				choose_sits(verse, column);
				add_new_reservation(name, surname, verse, column, Family);
				add_to_his(name, surname, Family_Price, verse, column, Family, Add);
				cout << "\nMiejsce 4 :\n";
				choose_sits(verse, column);
				add_new_reservation(name, surname, verse, column, Family);
				add_to_his(name, surname, Family_Price, verse, column, Family, Add);
				quit = true;
				break;
			default:
				cout << "===========================================================\n";
				cout << "Niepoprawny wybor - sprobuj ponownie.\n";
				break;
			}
		}
		cout << "===========================================================";
		cout << "\nRezerwcja dokonana pomyslnie.\n";
		cout << "===========================================================\n";
	}
}

void Data::choose_sits(int& verse, int& column) {
	while (true) {
		while (true)
		{
			cout << "\nWybierz numer rzedu : ";
			cin >> verse;
			if (verse < 0 || verse > 8) {
				cout << "===========================================================\n";
				cout << "Niepoprawny wybor - sprobuj ponownie.\n";
				cout << "===========================================================\n";
			}
			else {
				break;
			}
		}
		while (true)
		{
			cout << "\nWybierz numer miejsca : ";
			cin >> column;
			if (column < 0 || column > 10) {
				cout << "===========================================================\n";
				cout << "Niepoprawny wybor - sprobuj ponownie.\n";
				cout << "===========================================================\n";
			}
			else {
				break;
			}
		}
		if (!this->all_tickets.at(verse-1).at(column-1)->get_is_free()) {
			cout << "===========================================================\n";
			cout << "To miejsce jest juz zajete - sprobuj ponownie.\n";
			cout << "===========================================================\n";
		}
		else {
			break;
		}
	}
}

void Data::search_reservation() {
	bool is_searched{ false };
	string name, surname;
	string choose{};
	cout << "\nWprowadz imie : ";
	cin >> name;
	cout << "\nWprowadz nazwisko : ";
	cin >> surname;
	for (auto& x : this->reservation) {
		if (x->get_name() == name && x->get_surname() == surname) {
			is_searched = true;
		}
	}
	if (!is_searched) {
		cout << "===========================================================\n";
		cout << "Brak rezerwacji na podane imie i nazwisko.\n";
		cout << "===========================================================\n";
	}
	else {
		cout << "===========================================================\n";
		{
			cout << " |   imie   |  nazwisko  | rzad | miejsce | rodzaj |\n";
			cout << "----------------------------------------------------\n";
			int i = 1;
			list<unique_ptr<Ticket>>::iterator it;
			for (it = this->reservation.begin(); it != this->reservation.end(); ++it) {
				if (it->get()->get_name() == name && it->get()->get_surname() == surname) {
					cout << i << "| " << setw(9) << it->get()->get_name() << "|" << setw(12) << it->get()->get_surname() << "|" << setw(6) << it->get()->get_verse() << "|" << setw(9) << it->get()->get_column() << "|" << setw(2);
					it->get()->display_ticket_type();
					cout << "|\n";
					++i;
				}
			}
		}
		cout << "===========================================================\n";
	}
}

void Data::display_reserwation() {
	if (this->reservation.size() == 0) {
		cout << "===========================================================\n";
		cout << "Brak rezerwacji.\n";
		cout << "===========================================================\n";
	}
	else {
		cout << "===========================================================\n";
		cout << " |   imie   |  nazwisko  | rzad | miejsce |  rodzaj  |\n";
		cout << "----------------------------------------------------\n";
		{
			int i = 1;
			for (auto& x : this->reservation) {
				cout << i << "| " << setw(9) << x->get_name() << "|" << setw(12) << x->get_surname() << "|" << setw(6) << x->get_verse() << "|" << setw(9) << x->get_column() << "|" << setw(10);
				x->display_ticket_type();
				cout << "|\n";
				++i;
			}
		}
	}
}

void Data::cancel_reserwation() {
	bool is_searched{ false };
	string name, surname;
	int verse{}, column{};
	string choose{};
	vector<int> verses{};
	vector<int> columns{};
	cout << "\nWprowadz imie : ";
	cin >> name;
	cout << "\nWprowadz nazwisko : ";
	cin >> surname;
	for (auto& x : this->reservation) {
		if (x->get_name() == name && x->get_surname() == surname) {
			is_searched = true;
		}
	}
	if (!is_searched) {
		cout << "===========================================================\n";
		cout << "Brak rezerwacji na podane imie i nazwisko.\n";
		cout << "===========================================================\n";
	}
	else {
		cout << "===========================================================\n";
		{
			cout << " |   imie   |  nazwisko  | rzad | miejsce | rodzaj |\n";
			cout << "----------------------------------------------------\n";
			int i = 1;
			list<unique_ptr<Ticket>>::iterator it;
			for (it = this->reservation.begin(); it != this->reservation.end(); ++it) {
				if (it->get()->get_name() == name && it->get()->get_surname() == surname) {
					cout << i << "| " << setw(9) << it->get()->get_name() << "|" << setw(12) << it->get()->get_surname() << "|" << setw(6) << it->get()->get_verse() << "|" << setw(9) << it->get()->get_column() << "|" << setw(2);
					it->get()->display_ticket_type();
					cout << "|\n";
					verses.push_back(it->get()->get_verse());
					columns.push_back(it->get()->get_column());
					++i;
				}
			}
		}
		bool is_wrong_choice_ver{true};
		bool is_wrong_choice_col{true};
		bool wrong_reservation{true};
		bool lock{ true };
		int counter = 1, count = 1;
		while (counter != 0) {
			wrong_reservation = false;
			cout << "===========================================================\n";
			cout << "Rezerwacja  " << count << " :\n";
			cout << "===========================================================\n";
			cout << "Wybierz rzad usuwanej rezerwacji : ";
			cin >> verse;
			cout << "\n";
			cout << "Wybierz miejsce usuwanej rezerwacji : ";
			cin >> column;
			cout << "\n";

			for (auto& x : this->reservation) {
				if (x->get_verse() == verse && x->get_column() == column) {
					if (x->get_name() != name || x->get_surname() != surname) {
						wrong_reservation = true;
					}
				}
			}

			if (verse <= 8 && column <= 10 && !wrong_reservation) {
				if (this->all_tickets.at(verse - 1).at(column - 1)->type() == Family && lock) {
					counter = 4;
					lock = false;
				}
				for (auto x : verses) {
					if (verse == x) {
						is_wrong_choice_ver = false;
					}
				}
				for (auto x : columns) {
					if (column == x) {
						is_wrong_choice_col = false;
					}
				}
				if (!is_wrong_choice_ver && !is_wrong_choice_col && lock) {
					--counter;
					add_to_his(name, surname, this->all_tickets.at(verse - 1).at(column - 1)->get_price(), verse, column, this->all_tickets.at(verse - 1).at(column - 1)->type(), Cancel);
					this->all_tickets.at(verse - 1).at(column - 1)->unreserve();
					for (list<std::unique_ptr<Ticket>>::iterator it = this->reservation.begin(); it != this->reservation.end();) {
						if (it->get()->get_name() == name && it->get()->get_surname() == surname && it->get()->get_verse() == verse && it->get()->get_column() == column) {
							it->release();
							it = this->reservation.erase(it);
						}
						else {
							++it;
						}
					}
					cout << "==========================================================================================================\n";
					cout << "Rezerwacja : " << name << "-" << surname << "-" << verse << "-" << column << " zostala usunieta pomyslnie.\n";
					cout << "==========================================================================================================\n";
				}
				if (!is_wrong_choice_ver && !is_wrong_choice_col && !lock) {
					if (this->all_tickets.at(verse - 1).at(column - 1)->type() == Family) {
						--counter;
						this->all_tickets.at(verse - 1).at(column - 1)->unreserve();
						for (list<std::unique_ptr<Ticket>>::iterator it = this->reservation.begin(); it != this->reservation.end();) {
							if (it->get()->get_name() == name && it->get()->get_surname() == surname && it->get()->get_verse() == verse && it->get()->get_column() == column) {
								it->release();
								it = this->reservation.erase(it);
							}
							else {
								++it;
							}
						}
						cout << "==========================================================================================================\n";
						cout << "Rezerwacja : " << name << "-" << surname << "-" << verse << "-" << column << " zostala usunieta pomyslnie.\n";
						cout << "==========================================================================================================\n";
						add_to_his(name, surname, Family_Price, verse, column, Family, Cancel);
						++count;
					}
					else {
						cout << "=========================================================================================================================================\n";
						cout << "Wybrano rezerwacje z niewlasciwym typem. Usuwajac rezerwacje rodzinne nalezy usunac wszystkie 4 zarezerwowane miejsca - sprobuj ponownie.\n";
						cout << "=========================================================================================================================================\n";
					}
				}
				if (is_wrong_choice_ver || is_wrong_choice_col) {
					cout << "===========================================================\n";
					cout << "Bledna lokalizacja miejsca, sprobuj ponownie.\n";
					cout << "===========================================================\n";
				}
			}
			else {
				cout << "===========================================================\n";
				cout << "Bledna lokalizacja miejsca, sprobuj ponownie.\n";
				cout << "===========================================================\n";
			}
		}
	}
}

void Data::sort_reservation() {
	bool quit{ false };
	string choose{};
	if (this->reservation.size() != 0) {
		while (!quit) {
			cout << "===========================================================\n";
			cout << "1. Sortowanie wedlug liczby liczby rezerwacji na dane nazwisko.\n" << "2. Wyswietl tylko rezerwacje normalne.\n"
				<< "3. Wyswietl tylko rezerwacje studenckie.\n" << "4. Wyswietl tylko rezerwacje ulgowe.\n" << "5. Wyswietl tylko rezerwacje rodzinne.\n" << "6. Wyjdz.\n";
			cout << "===========================================================\n";
			cout << "\nWybierz rodzaj sortowania : ";
			cin >> choose;
			switch ([choose]()->int {
				if (choose == "1") {
					return 1;
				}
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
				else {
					return 0;
				}}())
			{
			case 1:
				display_reservation_ranking();
				break;
			case 2:
			{
				bool is_empty = true;
				for (auto& x : this->reservation) {
					if (x->type() == Normal) {
						is_empty = false;
					}
				}
				if (!is_empty) {
					int i = 1;
					cout << " |   imie   |  nazwisko  | rzad | miejsce | rodzaj |\n";
					cout << "----------------------------------------------------\n";
					for (auto& x : this->reservation) {
						if (x->type() == Normal) {
							cout << i << "| " << setw(9) << x->get_name() << "|" << setw(12) << x->get_surname() << "|" << setw(6) << x->get_verse() << "|" << setw(9) << x->get_column() << "|" << setw(2);
							x->display_ticket_type();
							cout << "|\n";
							++i;
						}
					}
				}
				else {
					cout << "===========================================================\n";
					cout << "Brak rezerwacji normalnych.\n";
				}
			}
			break;
			case 3:
			{
				bool is_empty = true;
				for (auto& x : this->reservation) {
					if (x->type() == Student) {
						is_empty = false;
					}
				}
				if (!is_empty) {
					int i = 1;
					cout << " |   imie   |  nazwisko  | rzad | miejsce | rodzaj |\n";
					cout << "----------------------------------------------------\n";
					for (auto& x : this->reservation) {
						if (x->type() == Student) {
							cout << i << "| " << setw(9) << x->get_name() << "|" << setw(12) << x->get_surname() << "|" << setw(6) << x->get_verse() << "|" << setw(9) << x->get_column() << "|" << setw(2);
							x->display_ticket_type();
							cout << "|\n";
							++i;
						}
					}
				}
				else {
					cout << "===========================================================\n";
					cout << "Brak rezerwacji studenckich.\n";
				}
			}
			break;
			case 4:
			{
				bool is_empty = true;
				for (auto& x : this->reservation) {
					if (x->type() == Discount) {
						is_empty = false;
					}
				}
				if (!is_empty) {
					int i = 1;
					cout << " |   imie   |  nazwisko  | rzad | miejsce | rodzaj |\n";
					cout << "----------------------------------------------------\n";
					for (auto& x : this->reservation) {
						if (x->type() == Discount) {
							cout << i << "| " << setw(9) << x->get_name() << "|" << setw(12) << x->get_surname() << "|" << setw(6) << x->get_verse() << "|" << setw(9) << x->get_column() << "|" << setw(2);
							x->display_ticket_type();
							cout << "|\n";
							++i;
						}
					}
				}
				else {
					cout << "===========================================================\n";
					cout << "Brak rezerwacji ulgowych.\n";
				}
			}
			break;
			case 5:
			{
				bool is_empty = true;
				for (auto& x : this->reservation) {
					if (x->type() == Family) {
						is_empty = false;
					}
				}
				if (!is_empty) {
					int i = 1;
					cout << " |   imie   |  nazwisko  | rzad | miejsce | rodzaj |\n";
					cout << "----------------------------------------------------\n";
					for (auto& x : this->reservation) {
						if (x->type() == Family) {
							cout << i << "| " << setw(9) << x->get_name() << "|" << setw(12) << x->get_surname() << "|" << setw(6) << x->get_verse() << "|" << setw(9) << x->get_column() << "|" << setw(2);
							x->display_ticket_type();
							cout << "|\n";
							++i;
						}
					}
				}
				else {
					cout << "===========================================================\n";
					cout << "Brak rezerwacji rodzinnych.\n";
				}
			}
			break;
			case 6:
				quit = true;
				break;
			default:
				cout << "===========================================================\n";
				cout << "Niepoprawny wybor - sprobuj ponownie.\n";
				cout << "===========================================================\n";
				break;
			}
		}
	}
	else {
	cout << "===========================================================\n";
	cout << "Brak rezerwacji.\n";
	cout << "===========================================================\n";
	}
}

bool comp_ranking_count(Ranking obj1, Ranking obj2) {
	return obj1.count > obj2.count;
}

void Data::display_reservation_ranking() {
	vector<Ranking> ranking_list{};
	for (auto& x : this->reservation) {
		if (ranking_list.size() == 0) {
			Ranking obj;
			obj.name = x->get_name();
			obj.surname = x->get_surname();
			obj.count = 0;
			ranking_list.push_back(obj);
		}
		else{
			bool flag{true};
			for (auto& y : ranking_list) {
				if (x->get_name() == y.name && x->get_surname() == y.surname) {
					flag = false;
				}
			}
			if (flag) {
				Ranking obj;
				obj.name = x->get_name();
				obj.surname = x->get_surname();
				obj.count = 0;
				ranking_list.push_back(obj);
			}
		}
	}
	for (auto& x : this->reservation) {
		for (auto& y : ranking_list) {
			if (x->get_name() == y.name && x->get_surname() == y.surname) {
				++y.count;
			}
		}
	}
	sort(ranking_list.begin(), ranking_list.end(), comp_ranking_count);
	cout << " |   imie   |  nazwisko  | liczba rezwrwacji |\n";
	cout << "==============================================\n";
	int i = 1;
	for (auto& x : ranking_list) {
		cout << i << "| " << setw(9) << x.name << "|" << setw(12) << x.surname << "|" << setw(19) << x.count << "|\n";
		++i;
	}
}

void Data::add_to_his(const string& name, const string& surname, const double& price, const int& verse, const int& column, const int& type, const int& mode) {
	His_obj new_add;
	new_add.name = name;
	new_add.surname = surname;
	new_add.price = price;
	new_add.verse = verse;
	new_add.column = column;
	new_add.type = type;
	new_add.mode = mode;
	this->history.push_back(new_add);
}

std::string give_type(His_obj obj) {
	if (obj.type == Normal) {
		return "normalny";
	}
	else if (obj.type == Student) {
		return "studencki";
	}
	else if (obj.type == Discount) {
		return "ze znizka";
	}
	else {
		return "rodzinny";
	}
}
std::string give_mode(His_obj obj) {
	if (obj.mode == Add) {
		return "dodany";
	}
	else {
		return "anulowany";
	}
}

void Data::print_raport() {
	ofstream save("Raport.txt");
	double profit = 0;
	int count = 1;
	save << "==============================================================================" << endl;
	save << "				Historia rezerwacji" << endl;
	save << "==============================================================================" << endl;
	if (this->history.size() == 0) {
		save << "Nie dokonano zadnych rezerwacji." << endl;
	}
	else {
		save << "  |   imie   |  nazwisko  | rzad | miejsce |   rodzaj  |  cena   |    typ    |" << endl;
		save << "------------------------------------------------------------------------------" << endl;
		for (auto x : this->history) {
			save << count << " | " << setw(8) << x.name << " | " <<  setw(10) << x.surname << " | " << setw(4) << x.verse << " | " << setw(7) << x.column << " | " << setw(9) << give_type(x) << " | " << setw(7) << x.price << " | " << setw(9) << give_mode(x) << " | " << endl;
			save << "------------------------------------------------------------------------------" << endl;
			if (x.mode == Add) {
				profit += x.price;
			}
			else if (x.mode == Cancel) {
				profit -= x.price;
			}
			++count;
		}
	}
	save << "==============================================================================" << endl;
	save << "Calkowite zyski : " << profit << endl;
	save << "==============================================================================" << endl;
	cout << "==============================================================================" << endl;
	cout << "Raport zostal wydrukowany." << endl;
	cout << "==============================================================================" << endl;
}