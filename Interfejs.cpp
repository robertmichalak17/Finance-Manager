#include <iostream>
#include "interfejs.h"

using namespace std;

void InterfejsUzytkownika::wyswietlMenuGlowne() {
    cout << "1. Zaloguj sie" << endl;
    cout << "2. Zarejestruj sie" << endl;
    cout << "3. Usun konto" << endl;
    cout << "4. Wyjdz" << endl;
    cout << "Wybierz opcje: ";
}

void InterfejsUzytkownika::wyswietlMenuUzytkownika() {
    cout << "1. Informacje o profilu" << endl;
    cout << "2. Finanse" << endl;
    cout << "3. Zmien haslo" << endl;
    cout << "4. Wyloguj sie" << endl;
    cout << "Wybierz opcje: ";
}

void InterfejsUzytkownika::wyswietlMenuFinansow() {
    cout << "1. Przychod" << endl;
    cout << "2. Biezace wydatki" << endl;
    cout << "3. Konto oszczednosciowe" << endl;
    cout << "4. Saldo" << endl;
    cout << "5. Przeglad operacji finansowych" << endl;
    cout << "6. Zaplanowane wydatki" << endl;  // Nowa opcja
    cout << "7. Podsumowanie pod wzgledem kategorii wydatkow" << endl;
    cout << "8. Cofnij" << endl;
    cout << "Wybierz opcje: ";
}

void InterfejsUzytkownika::wyswietlMenuKontaOszczednosciowego() {
    cout << "1. Przelac srodki na konto oszczednosciowe" << endl;
    cout << "2. Przelac srodki z konta oszczednosciowego" << endl;
    cout << "3. Pokaz dostepne srodki na koncie oszczednosciowym" << endl;
    cout << "4. Cofnij" << endl;
    cout << "Wybierz opcje: ";
}
