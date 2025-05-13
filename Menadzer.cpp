#include <iostream>
#include "menadzer.h"

void MenedzerKont::dodajUzytkownika() {
    Uzytkownik nowyUzytkownik;
    nowyUzytkownik.rejestracja();
    uzytkownicy.push_back(nowyUzytkownik);
    zapiszUzytkownikowDoPliku();
};

void MenedzerKont::usunUzytkownika() {
    int idDoUsuniecia;
    cout << "Podaj id uzytkownika do usuniecia: ";
    cin >> idDoUsuniecia;
    if (cin.fail()) {
        cout << "Blad. Wprowadzono niepoprawna wartosc." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
        bool znaleziono = false;
        for (auto it = uzytkownicy.begin(); it != uzytkownicy.end(); ++it) {
            if (it->getId() == idDoUsuniecia) {
                uzytkownicy.erase(it);
                znaleziono = true;
                break;
            }
        }
        if (znaleziono) {
            cout << "Uzytkownik zostal usuniety." << endl;
        } else {
            cout << "Nie znaleziono uzytkownika o podanym id." << endl;
        }
    }
    zapiszUzytkownikowDoPliku();
};
