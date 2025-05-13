#include <iostream>
#include "zaplanowane.h"

void ZaplanowaneWydatki::dodajZaplanowanyWydatek() {
    double kwota;
    string data, opis;

    cout << "Podaj kwote: ";
    cin >> kwota;

    cout << "Podaj date w formacie RRRR-MM-DD: ";
    cin >> data;
    if (!czyPoprawnaData(data)) {
        cout << "Niepoprawny format daty!" << endl;
        return;
    }

    cout << "Podaj opis: ";
    cin.ignore();
    getline(cin, opis);

    Wydatek zaplanowanyWydatek(kwota, data, opis);
    zaplanowaneWydatki.push_back(zaplanowanyWydatek);
    cout << "Zaplanowany wydatek dodany poprawnie." << endl;
};