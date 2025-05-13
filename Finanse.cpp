#include <iostream>
#include "finanse.h"

void Finanse::przychod() {
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

    Przychod nowyPrzychod(kwota, data, opis);
    przychody.push_back(nowyPrzychod);
    cout << "Przychod dodany poprawnie." << endl;
};

void Finanse::biezaceWydatki() {
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

    Wydatek nowyWydatek(kwota, data, opis);
    wydatki.push_back(nowyWydatek);
    cout << "Wydatek dodany poprawnie." << endl;
};