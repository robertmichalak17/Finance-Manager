#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>
#include <ctime>
#include <sstream>
#include <cstdlib>
#include <conio.h>
using namespace std;

unsigned long simpleHash(const string& str) {
    unsigned long hash = 5381;
    int c;

    for (std::size_t i = 0; i < str.length(); i++) {
        c = static_cast<int>(str[i]);
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

string getHiddenInput() {
    string input;
    char ch;
    while ((ch = _getch()) != '\r') {
        cout << '*';
        input.push_back(ch);
    }
    cout << endl;
    return input;
}

class Konsola {
public:
    static void Czysc() {
        system("cls");
    }

    static void pause() {
        system("pause");
    }

    static void pokazWiadomoscICzekaj(const string& message) {
        cout << message << endl;
        pause();
    }
};

bool czyTylkoLitery(const string& str) {
    return str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos;
}
bool czyTylkoCyfry(const string& str) {
    return str.find_first_not_of("0123456789") == string::npos;
}
bool czyPoprawnaData(const string& data) {
    if (data.size() != 10 || data[4] != '-' || data[7] != '-') return false;

    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(data[i])) return false;
    }

    int rok = stoi(data.substr(0, 4));
    int miesiac = stoi(data.substr(5, 2));
    int dzien = stoi(data.substr(8, 2));

    if (miesiac < 1 || miesiac > 12) return false;

    // Dni w miesiącach - uwzględniając luty w roku przestępnym
    int dniWMiesiacu[12] = { 31, (rok % 4 == 0 && (rok % 100 != 0 || rok % 400 == 0)) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (dzien < 1 || dzien > dniWMiesiacu[miesiac - 1]) return false;

    return true;
}
bool czyPoprawnaPlec(char plec) {
    return plec == 'M' || plec == 'm' || plec == 'K' || plec == 'k';
}

class Uzytkownik {
private:
    string login;
    string haslo;
    string imie;
    string nazwisko;
    string numerIndeksu;
    string dataUrodzenia;
    char plec;
    string kierunekStudiow;

public:
    Uzytkownik() {}

    Uzytkownik(const string& login, const string& haslo, const string& imie, const string& nazwisko,
        const string& numerIndeksu, const string& dataUrodzenia, char plec, const string& kierunekStudiow)
        : login(login), haslo(haslo), imie(imie), nazwisko(nazwisko),
        numerIndeksu(numerIndeksu), dataUrodzenia(dataUrodzenia), plec(plec), kierunekStudiow(kierunekStudiow) {}

    string pobierzLogin() const { return login; }

    string pobierzHaslo() const { return haslo; }

    void ustawHaslo(const string& noweHaslo) { haslo = noweHaslo; }

    string pobierzImie() const { return imie; }

    string pobierzNazwisko() const { return nazwisko; }

    string pobierzNumerIndeksu() const { return numerIndeksu; }

    string pobierzDataUrodzenia() const { return dataUrodzenia; }

    char pobierzPlec() const { return plec; }

    string pobierzKierunekStudiow() const { return kierunekStudiow; }

    void wyswietlInformacjeProfilu() const {
        cout << "Imie: " << imie << endl;
        cout << "Nazwisko: " << nazwisko << endl;
        cout << "Numer indeksu: " << numerIndeksu << endl;
        cout << "Data urodzenia: " << dataUrodzenia << endl;
        cout << "Plec: ";
        if (plec == '1' || plec == 'M' || plec == 'm') {
            cout << "Mezczyzna";
        }
        else if (plec == '2' || plec == 'K' || plec == 'k') {
            cout << "Kobieta";
        }
        else {
            cout << "Nieznana";
        }
        cout << endl;
        cout << "Kierunek studiow: " << kierunekStudiow << endl;
    }
};
class InterfejsUzytkownika {
public:
    void wyswietlMenuGlowne() {
        cout << "1. Zaloguj sie" << endl;
        cout << "2. Zarejestruj sie" << endl;
        cout << "3. Usun konto" << endl;
        cout << "4. Wyjdz" << endl;
        cout << "Wybierz opcje: ";
    }

    void wyswietlMenuUzytkownika() {
        cout << "1. Informacje o profilu" << endl;
        cout << "2. Finanse" << endl;
        cout << "3. Zmien haslo" << endl;
        cout << "4. Wyloguj sie" << endl;
        cout << "Wybierz opcje: ";
    }

    void wyswietlMenuFinansow() {
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
    void wyswietlMenuKontaOszczednosciowego() {
        cout << "1. Przelac srodki na konto oszczednosciowe" << endl;
        cout << "2. Przelac srodki z konta oszczednosciowego na saldo" << endl;
        cout << "3. Cofnij" << endl;
        cout << "Wybierz opcje: ";
    }
    // Tutaj mozesz dodac inne metody, ktore beda potrzebne w interfejsie uzytkownika
};
class MenedzerKont {
public:
    bool czyUzytkownikIstnieje(const string& login) {
        ifstream plik("uzytkownicy.txt");
        if (!plik.is_open()) {
            return false;
        }

        string zapisanyLogin;
        while (getline(plik, zapisanyLogin, ',')) {
            plik.ignore(numeric_limits<streamsize>::max(), '\n');
            if (zapisanyLogin == login) {
                plik.close();
                return true;
            }
        }

        plik.close();
        return false;
    }

    void zarejestrujUzytkownika(const Uzytkownik& nowyUzytkownik) {
        ofstream plik("uzytkownicy.txt", ios::app);
        if (!plik) {
            cout << "Nie mozna otworzyc pliku uzytkownicy.txt" << endl;
            return;
        }
        plik << nowyUzytkownik.pobierzLogin() << "," << simpleHash(nowyUzytkownik.pobierzHaslo()) << ","
            << nowyUzytkownik.pobierzImie() << "," << nowyUzytkownik.pobierzNazwisko() << ","
            << nowyUzytkownik.pobierzNumerIndeksu() << "," << nowyUzytkownik.pobierzDataUrodzenia() << ","
            << nowyUzytkownik.pobierzPlec() << "," << nowyUzytkownik.pobierzKierunekStudiow() << endl;
        plik.close();

        // Tworzenie folderu uzytkownika
        string folderName = nowyUzytkownik.pobierzLogin() + "_Finanse";
        string command = "mkdir " + folderName;
        system(command.c_str());

        // Tworzenie plikow finansowych w folderze uzytkownika
        ofstream plikSaldo(folderName + "/Saldo.txt");
        ofstream plikKontoOszczednosciowe(folderName + "/KontoOszczednosciowe.txt");
        plikSaldo << "0.0" << endl;
        plikKontoOszczednosciowe << "0.0" << endl;
        plikSaldo.close();
        plikKontoOszczednosciowe.close();

        Konsola::pokazWiadomoscICzekaj("Zarejestrowano nowego uzytkownika i utworzono pliki finansowe.");
    }

    Uzytkownik zalogujUzytkownika(const string& login, const string& haslo) {
        ifstream plik("uzytkownicy.txt");
        if (!plik.is_open()) {
            return Uzytkownik();
        }

        string zapisanyLogin, zapisaneHaslo, imie, nazwisko, numerIndeksu, dataUrodzenia, kierunekStudiow;
        char plec;

        while (getline(plik, zapisanyLogin, ',')) {
            getline(plik, zapisaneHaslo, ',');
            getline(plik, imie, ',');
            getline(plik, nazwisko, ',');
            getline(plik, numerIndeksu, ',');
            getline(plik, dataUrodzenia, ',');
            plik >> plec;
            plik.ignore(numeric_limits<streamsize>::max(), ',');
            getline(plik, kierunekStudiow);

            if (zapisanyLogin == login && simpleHash(haslo) == std::stoul(zapisaneHaslo)) {
                plik.close();
                return Uzytkownik(login, haslo, imie, nazwisko, numerIndeksu, dataUrodzenia, plec, kierunekStudiow);
            }
        }

        plik.close();
        return Uzytkownik();
    }

    void zmienHaslo(Uzytkownik& uzytkownik, const string& noweHaslo) {
        string staryLogin = uzytkownik.pobierzLogin();
        uzytkownik.ustawHaslo(noweHaslo);

        ifstream plikWe("uzytkownicy.txt");
        ofstream plikWy("temp.txt");

        if (!plikWe.is_open() || !plikWy.is_open()) {
            cout << "Blad podczas zmiany hasla." << endl;
            return;
        }

        string zapisanyLogin, zapisaneHaslo, imie, nazwisko, numerIndeksu, dataUrodzenia, kierunekStudiow;
        char plec;

        while (getline(plikWe, zapisanyLogin, ',')) {
            getline(plikWe, zapisaneHaslo, ',');
            getline(plikWe, imie, ',');
            getline(plikWe, nazwisko, ',');
            getline(plikWe, numerIndeksu, ',');
            getline(plikWe, dataUrodzenia, ',');
            plikWe >> plec;
            plikWe.ignore(numeric_limits<streamsize>::max(), ',');
            getline(plikWe, kierunekStudiow);

            if (zapisanyLogin == staryLogin) {
                plikWy << zapisanyLogin << "," << simpleHash(noweHaslo) << ","
                    << imie << "," << nazwisko << ","
                    << numerIndeksu << "," << dataUrodzenia << ","
                    << plec << "," << kierunekStudiow << endl;
            }
            else {
                plikWy << zapisanyLogin << "," << zapisaneHaslo << ","
                    << imie << "," << nazwisko << ","
                    << numerIndeksu << "," << dataUrodzenia << ","
                    << plec << "," << kierunekStudiow << endl;
            }
        }

        plikWe.close();
        plikWy.close();

        remove("uzytkownicy.txt");
        rename("temp.txt", "uzytkownicy.txt");

        Konsola::pokazWiadomoscICzekaj("Haslo zostalo zmienione.");
    }

    void usunUzytkownika(const string& login) {
        ifstream plikWe("uzytkownicy.txt");
        ofstream plikWy("temp.txt");

        if (!plikWe.is_open() || !plikWy.is_open()) {
            cout << "Blad podczas usuwania uzytkownika." << endl;
            return;
        }

        cout << "Podaj haslo dla konta " << login << ": ";
        string haslo;
        cin >> haslo;
        unsigned long hashedPassword = simpleHash(haslo);

        string zapisanyLogin, zapisaneHaslo;
        bool znaleziono = false;
        bool hasloZgadzaSie = false;

        while (getline(plikWe, zapisanyLogin, ',')) {
            getline(plikWe, zapisaneHaslo, ',');
            string resztaLinii;
            getline(plikWe, resztaLinii);

            if (zapisanyLogin == login) {
                znaleziono = true;
                if (std::stoul(zapisaneHaslo) == hashedPassword) {
                    hasloZgadzaSie = true;
                    continue; // Nie zapisuj tego uzytkownika do temp.txt
                }
            }

            plikWy << zapisanyLogin << "," << zapisaneHaslo << "," << resztaLinii << endl;
        }

        plikWe.close();
        plikWy.close();

        if (!znaleziono) {
            remove("temp.txt");
            Konsola::pokazWiadomoscICzekaj("Nie znaleziono uzytkownika.");
        }
        else if (!hasloZgadzaSie) {
            remove("temp.txt");
            Konsola::pokazWiadomoscICzekaj("Nieprawidlowe haslo.");
        }
        else {
            remove("uzytkownicy.txt");
            rename("temp.txt", "uzytkownicy.txt");

            // Usuniecie folderu uzytkownika
            string folderName = login + "_Finanse";
            string command = "rmdir /s /q " + folderName;
            system(command.c_str());

            Konsola::pokazWiadomoscICzekaj("Uzytkownik zostal usuniety.");
        }
    }
};
class Finanse {
private:
    string nazwaFolderuUzytkownika;
    double sumaArtykulySpozywcze, sumaTransport, sumaOplaty, sumaRozrywka, sumaPozostale;
    double wczytajWartoscZPliku(const string& nazwaPliku) {
        ifstream plik(nazwaFolderuUzytkownika + "/" + nazwaPliku);
        double wartosc;
        if (plik >> wartosc) {
            return wartosc;
        }
        return 0.0;
    }

    void zapiszWartoscDoPliku(const string& nazwaPliku, double wartosc) {
        ofstream plik(nazwaFolderuUzytkownika + "/" + nazwaPliku);
        plik << fixed << setprecision(2) << wartosc;
    }

    void zapiszOperacjeDoPliku(const string& nazwaPliku, double kwota, const string& kategoria) {
        ofstream plik(nazwaFolderuUzytkownika + "/" + nazwaPliku, ios::app);
        if (!plik) {
            cout << "Nie mozna otworzyc pliku: " << nazwaPliku << endl;
            return;
        }

        // Pobieranie aktualnej daty i czasu
        time_t now = time(0);
        tm ltm;
        localtime_s(&ltm, &now); // Zmieniono na localtime_s

        // Formatowanie daty i czasu
        plik << fixed << setprecision(2) << kwota << " "
            << setw(2) << setfill('0') << ltm.tm_hour << ":"
            << setw(2) << ltm.tm_min << ":" << setw(2) << ltm.tm_sec << " "
            << setw(2) << ltm.tm_mday << "-"
            << setw(2) << ltm.tm_mon + 1 << "-" << ltm.tm_year + 1900
            << " " << kategoria << endl;

        plik.close();
    }

    string pobierzAktualnaGodzine() const {
        time_t now = time(0);
        tm ltm;
        localtime_s(&ltm, &now);
        stringstream ss;
        ss << setfill('0') << setw(2) << ltm.tm_hour << ":" << setw(2) << ltm.tm_min << ":" << setw(2) << ltm.tm_sec;
        return ss.str();
    }

    void wyswietlOperacjeFinansowe(const string& nazwaPliku, const string& rodzajOperacji) const {
        ifstream plikOperacji(nazwaFolderuUzytkownika + "/" + nazwaPliku);

        if (!plikOperacji.is_open()) {
            cout << "Brak operacji finansowych." << endl;
            return;
        }
        cout << "Rodzaj   Kwota   Godzina     Data    Kategoria" << endl;
        string wpis;
        while (getline(plikOperacji, wpis)) {
            cout << rodzajOperacji << " " << wpis << endl;
        }
        cout << endl;
        plikOperacji.close();
    }

public:
    Finanse() : nazwaFolderuUzytkownika(""), sumaArtykulySpozywcze(0.0), sumaTransport(0.0), sumaOplaty(0.0), sumaRozrywka(0.0), sumaPozostale(0.0) {}
    Finanse(const string& nazwaUzytkownika) : nazwaFolderuUzytkownika(nazwaUzytkownika + "_Finanse") {}

    void dodajPrzychod(double kwota) {
        double saldoKonta = wczytajWartoscZPliku("Saldo.txt");
        saldoKonta += kwota;
        zapiszWartoscDoPliku("Saldo.txt", saldoKonta);
        zapiszOperacjeDoPliku("Przychody.txt", kwota, "Brak kategorii"); // Dodano trzeci argument
        cout << "Dodano przychod" << endl;
    }

    void dodajWydatek(double kwota) {
        const string kategorie[5] = { "Artykuly spozywcze", "Transport", "Oplaty", "Rozrywka", "Pozostale" };
        string kategoria;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Podaj kategorie wydatku: ";
        getline(cin, kategoria);

        // Sprawdzenie, czy podana kategoria jest jedną z zdefiniowanych
        bool kategoriaZnaleziona = false;
        for (const string& kat : kategorie) {
            if (kat == kategoria) {
                kategoriaZnaleziona = true;
                break;
            }
        }

        if (!kategoriaZnaleziona) {
            cout << "Blad przy wprowadzaniu danych wejsciowych. Dostepne kategorie to: Artykuly spozywcze, Transport, Oplaty, Rozrywka, Pozostale" << endl;
            return;
        }

        double saldoKonta = wczytajWartoscZPliku("Saldo.txt");
        if (saldoKonta >= kwota) {
            saldoKonta -= kwota;
            zapiszWartoscDoPliku("Saldo.txt", saldoKonta);
            zapiszOperacjeDoPliku("BiezaceWydatki.txt", kwota, kategoria);
            cout << "Dodano wydatek" << endl;
        }
        else {
            cout << "Niewystarczajace srodki na koncie." << endl;
        }
    }

    void przelacNaOszczednosciowe(double kwota) {
        double saldoKonta = wczytajWartoscZPliku("Saldo.txt");
        double saldoOszczednosciowe = wczytajWartoscZPliku("KontoOszczednosciowe.txt");
        if (saldoKonta >= kwota) {
            saldoKonta -= kwota;
            saldoOszczednosciowe += kwota;
            zapiszWartoscDoPliku("Saldo.txt", saldoKonta);
            zapiszWartoscDoPliku("KontoOszczednosciowe.txt", saldoOszczednosciowe);
            cout << "Przelano srodki na konto oszczednosciowe" << endl;
        }
        else {
            cout << "Niewystarczajace srodki na koncie." << endl;
        }
    }
    void przelacZKontaOszczednosciowegoNaSaldo(double kwota) {
        double saldoKonta = wczytajWartoscZPliku("Saldo.txt");
        double saldoOszczednosciowe = wczytajWartoscZPliku("KontoOszczednosciowe.txt");

        if (saldoOszczednosciowe >= kwota) {
            saldoOszczednosciowe -= kwota;
            saldoKonta += kwota;
            zapiszWartoscDoPliku("Saldo.txt", saldoKonta);
            zapiszWartoscDoPliku("KontoOszczednosciowe.txt", saldoOszczednosciowe);
            cout << "Przelano srodki na konto biezace" << endl;
        }
        else {
            cout << "Niewystarczajace srodki na koncie oszczednosciowym." << endl;
        }
    }
    void pokazSaldo() {
        double saldoKonta = wczytajWartoscZPliku("Saldo.txt");
        double saldoOszczednosciowe = wczytajWartoscZPliku("KontoOszczednosciowe.txt");
        cout << "Saldo konta biezacego: " << saldoKonta << " zl" << endl;
        cout << "Saldo konta oszczednosciowego: " << saldoOszczednosciowe << " zl" << endl;
    }

    void przegladOperacjiFinansowych() const {
        Konsola::Czysc();
        wyswietlOperacjeFinansowe("BiezaceWydatki.txt", "Wydatek");
        wyswietlOperacjeFinansowe("Przychody.txt", "Przychod");
        Konsola::pause();
        Konsola::Czysc();
    }
    void podsumowanieWydatkowWedlugKategorii() {
        sumaArtykulySpozywcze = sumaTransport = sumaOplaty = sumaRozrywka = sumaPozostale = 0.0;

        ifstream plik(nazwaFolderuUzytkownika + "/BiezaceWydatki.txt");
        if (!plik) {
            cout << "Nie mozna otworzyc pliku z biezacymi wydatkami." << endl;
            return;
        }

        string linia, kategoria, pomijana;
        double kwota;
        while (getline(plik, linia)) {
            stringstream ss(linia);
            ss >> kwota; // Odczyt kwoty

            // Pomijanie godziny i daty
            ss >> pomijana; // Godzina
            ss >> pomijana; // Data

            ss >> kategoria; // Odczyt kategorii

            if (kategoria == "Artykuly spozywcze") sumaArtykulySpozywcze += kwota;
            else if (kategoria == "Transport") sumaTransport += kwota;
            else if (kategoria == "Oplaty") sumaOplaty += kwota;
            else if (kategoria == "Rozrywka") sumaRozrywka += kwota;
            else if (kategoria == "Pozostale") sumaPozostale += kwota;
        }
        plik.close();

        cout << "Podsumowanie wydatkow wedlug kategorii:" << endl;
        cout << "Artykuly spozywcze: " << fixed << setprecision(2) << sumaArtykulySpozywcze << " zl" << endl;
        cout << "Transport: " << sumaTransport << " zl" << endl;
        cout << "Oplaty: " << sumaOplaty << " zl" << endl;
        cout << "Rozrywka: " << sumaRozrywka << " zl" << endl;
        cout << "Pozostale: " << sumaPozostale << " zl" << endl;
    }
};
class ZaplanowaneWydatki {
private:
    string nazwaFolderuUzytkownika;

public:
    ZaplanowaneWydatki(const string& nazwaUzytkownika) : nazwaFolderuUzytkownika(nazwaUzytkownika + "_Finanse") {}

    void dodajZaplanowanyWydatek() {
        string data, kategoria, kwotaStr;
        double kwota;
        const string kategorie[5] = { "Artykuly spozywcze", "Transport", "Oplaty", "Rozrywka", "Pozostale" };

        Konsola::Czysc();

        cout << "Podaj kwote wydatku: ";
        cin >> kwotaStr;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // Sprawdzenie, czy kwota jest liczbą
        stringstream ss(kwotaStr);
        if (!(ss >> kwota) || kwota <= 0) {
            cout << "Niepoprawny format kwoty." << endl;
            Konsola::pause();
            Konsola::Czysc();
            return;
        }

        cout << "Podaj date wydatku (RRRR-MM-DD): ";
        cin >> data;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (!czyPoprawnaData(data)) {
            cout << "Niepoprawny format daty." << endl;
            Konsola::pause();
            Konsola::Czysc();
            return;
        }

        cout << "Podaj kategorie wydatku: ";
        getline(cin, kategoria);

        bool kategoriaZnaleziona = false;
        for (const string& kat : kategorie) {
            if (kat == kategoria) {
                kategoriaZnaleziona = true;
                break;
            }
        }

        if (!kategoriaZnaleziona) {
            cout << "Blad przy wprowadzaniu danych wejsciowych. Dostepne kategorie to: Artykuly spozywcze, Transport, Oplaty, Rozrywka, Pozostale" << endl;
            Konsola::pause();
            Konsola::Czysc();
            return;
        }

        ofstream plik(nazwaFolderuUzytkownika + "/zaplanowanewydatki.txt", ios::app);
        if (!plik.is_open()) {
            cout << "Nie mozna otworzyc pliku do zapisu." << endl;
            Konsola::pause();
            Konsola::Czysc();
            return;
        }

        plik << kwota << " " << data << " " << kategoria << endl;
        plik.close();

        cout << "Zaplanowany wydatek dodany." << endl;
        Konsola::pause();
        Konsola::Czysc();
    }
    void usunZaplanowanyWydatek() {
        ifstream plikOdczyt(nazwaFolderuUzytkownika + "/zaplanowanewydatki.txt");
        if (!plikOdczyt.is_open()) {
            cout << "Nie mozna otworzyc pliku." << endl;
            Konsola::pause();
            Konsola::Czysc();
            return;
        }

        string data, kategoria, kwotaStr, linia;
        cout << "Podaj date wydatku do usuniecia (RRRR-MM-DD): ";
        cin >> data;
        cout << "Podaj kwote wydatku do usuniecia: ";
        cin >> kwotaStr;
        cout << "Podaj kategorie wydatku do usuniecia: ";
        cin.ignore();
        getline(cin, kategoria);

        ofstream plikZapis(nazwaFolderuUzytkownika + "/temp.txt");
        bool usunieto = false;

        while (getline(plikOdczyt, linia)) {
            if (linia.find(data) == string::npos || linia.find(kwotaStr) == string::npos || linia.find(kategoria) == string::npos) {
                plikZapis << linia << endl;
            }
            else {
                usunieto = true;
            }
        }

        plikOdczyt.close();
        plikZapis.close();

        remove((nazwaFolderuUzytkownika + "/zaplanowanewydatki.txt").c_str());
        rename((nazwaFolderuUzytkownika + "/temp.txt").c_str(), (nazwaFolderuUzytkownika + "/zaplanowanewydatki.txt").c_str());

        if (usunieto) {
            cout << "Wydatek usuniety." << endl;
            Konsola::pause();
            Konsola::Czysc();
        }
        else {
            cout << "Nie znaleziono wydatku." << endl;
            Konsola::pause();
            Konsola::Czysc();
        }
    }

    void wyswietlZaplanowaneWydatki() {
        ifstream plik(nazwaFolderuUzytkownika + "/zaplanowanewydatki.txt");
        if (!plik.is_open()) {
            cout << "Brak danych do wyswietlania. Nalezy dodac zaplanowany wydatek." << endl;
            return;
        }

        string linia;
        cout << "Kwota   Data   Kategoria" << endl;
        while (getline(plik, linia)) {
            cout << linia << endl;
        }

        plik.close();
    }
};
int main() {
    InterfejsUzytkownika interfejs;
    MenedzerKont menedzer;
    Uzytkownik aktualnyUzytkownik;
    Finanse* finanse = nullptr;

    while (true) {
        Konsola::Czysc();
        interfejs.wyswietlMenuGlowne();
        int wybor;
        cin >> wybor;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (wybor == 1) {
            Konsola::Czysc();
            string login, haslo;
            cout << "Podaj login: ";
            getline(cin, login);
            cout << "Podaj haslo: ";
            haslo = getHiddenInput();
            aktualnyUzytkownik = menedzer.zalogujUzytkownika(login, haslo);
            if (!aktualnyUzytkownik.pobierzLogin().empty()) {
                finanse = new Finanse(login);
                Konsola::pokazWiadomoscICzekaj("Zalogowano pomyslnie.");
                Konsola::Czysc();

                bool zalogowany = true;
                while (zalogowany) {
                    Konsola::Czysc();
                    interfejs.wyswietlMenuUzytkownika();
                    int wyborUzytkownika;
                    cin >> wyborUzytkownika;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    switch (wyborUzytkownika) {
                    case 1:
                        Konsola::Czysc();
                        aktualnyUzytkownik.wyswietlInformacjeProfilu();
                        Konsola::pause();
                        Konsola::Czysc();
                        break;
                    case 2:
                        // Zarzadzanie finansami
                        Konsola::Czysc();
                        if (finanse != nullptr) {
                            bool wMenuFinansow = true;
                            while (wMenuFinansow) {
                                Konsola::Czysc();
                                interfejs.wyswietlMenuFinansow();
                                int wyborFinansow;
                                cin >> wyborFinansow;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                switch (wyborFinansow) {
                                case 1:
                                    Konsola::Czysc();
                                    double kwotaPrzychodu;
                                    do {
                                        cout << "Podaj kwote przychodu: ";
                                        cin >> kwotaPrzychodu;

                                        // Sprawdzanie poprawnosci wprowadzonej wartosci
                                        if (cin.fail() || kwotaPrzychodu <= 0 || cin.peek() != '\n') {
                                            cout << "Nieprawidlowa kwota. Wprowadz ponownie." << endl;
                                            cin.clear();  // Czyszczenie flag blędu
                                            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Usuwanie blędnych danych z bufora
                                            Konsola::pause();
                                            Konsola::Czysc();
                                        }
                                        else {
                                            break;  // Wyjscie z pętli, jesli wprowadzona wartosć jest poprawna
                                        }
                                    } while (true);

                                    finanse->dodajPrzychod(kwotaPrzychodu);
                                    Konsola::pause();
                                    Konsola::Czysc();
                                    break;
                                case 2:
                                    Konsola::Czysc();
                                    double kwotaWydatku;
                                    do {
                                        cout << "Podaj kwote wydatku: ";
                                        cin >> kwotaWydatku;

                                        // Sprawdzanie poprawnosci wprowadzonej wartosci
                                        if (cin.fail() || kwotaWydatku <= 0 || cin.peek() != '\n') {
                                            cout << "Nieprawidlowa kwota. Wprowadz ponownie." << endl;
                                            cin.clear();  // Czyszczenie flag blędu
                                            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Usuwanie blędnych danych z bufora
                                            Konsola::pause();
                                            Konsola::Czysc();
                                        }
                                        else {
                                            break;  // Wyjscie z pętli, jesli wprowadzona wartosć jest poprawna
                                        }
                                    } while (true);

                                    finanse->dodajWydatek(kwotaWydatku);
                                    Konsola::pause();
                                    Konsola::Czysc();
                                    break;
                                case 3:
                                {
                                    bool wMenuKontaOszczednosciowego = true;
                                    while (wMenuKontaOszczednosciowego) {
                                        Konsola::Czysc();
                                        interfejs.wyswietlMenuKontaOszczednosciowego();
                                        int wyborKontaOszczednosciowego;
                                        cin >> wyborKontaOszczednosciowego;
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                                        switch (wyborKontaOszczednosciowego) {
                                        case 1:
                                            // Przelanie srodkow na konto oszczednosciowe
                                            Konsola::Czysc();
                                            double kwotaTransferu;
                                            cout << "Podaj kwote do przeniesienia na konto oszczednosciowe: ";
                                            cin >> kwotaTransferu;
                                            finanse->przelacNaOszczednosciowe(kwotaTransferu);
                                            Konsola::pause();
                                            Konsola::Czysc();
                                            break;
                                        case 2:
                                            // Przelanie srodkow z konta oszczednosciowego na saldo
                                            Konsola::Czysc();
                                            double kwotaTransferuZKontaOszczednosciowego;
                                            cout << "Podaj kwote do przeniesienia na konto biezace: ";
                                            cin >> kwotaTransferuZKontaOszczednosciowego;
                                            finanse->przelacZKontaOszczednosciowegoNaSaldo(kwotaTransferuZKontaOszczednosciowego);
                                            Konsola::pause();
                                            Konsola::Czysc();
                                            break;
                                        case 3:
                                            wMenuKontaOszczednosciowego = false;
                                            break;
                                        default:
                                            Konsola::pokazWiadomoscICzekaj("Nieprawidlowy wybor. Sprobuj ponownie.");
                                            break;
                                        }
                                    }
                                    break;
                                }
                                case 4:
                                    Konsola::Czysc();
                                    finanse->pokazSaldo();
                                    Konsola::pause();
                                    Konsola::Czysc();
                                    break;
                                case 5:
                                    Konsola::Czysc();
                                    finanse->przegladOperacjiFinansowych();
                                    break;
                                case 6: { // Zaplanowane wydatki                                   
                                    Konsola::Czysc();
                                    ZaplanowaneWydatki zaplanowaneWydatki(aktualnyUzytkownik.pobierzLogin());
                                    bool wMenuZaplanowanychWydatkow = true;
                                    while (wMenuZaplanowanychWydatkow) {
                                        Konsola::Czysc();
                                        cout << "1. Wyswietl zaplanowane wydatki" << endl;
                                        cout << "2. Dodaj zaplanowany wydatek" << endl;
                                        cout << "3. Usun zaplanowany wydatek" << endl;
                                        cout << "4. Powrot do menu finansow" << endl;
                                        cout << "Wybierz opcje:";
                                        int wyborZaplanowaneWydatki;
                                        cin >> wyborZaplanowaneWydatki;

                                        switch (wyborZaplanowaneWydatki) {

                                        case 1:
                                            Konsola::Czysc();
                                            zaplanowaneWydatki.wyswietlZaplanowaneWydatki();
                                            Konsola::pause();
                                            Konsola::Czysc();
                                            break;
                                        case 2:
                                            Konsola::Czysc();
                                            zaplanowaneWydatki.dodajZaplanowanyWydatek();
                                            break;
                                        case 3:
                                            Konsola::Czysc();
                                            zaplanowaneWydatki.usunZaplanowanyWydatek();
                                            break;
                                        case 4:
                                            wMenuZaplanowanychWydatkow = false;
                                            Konsola::Czysc();
                                            break;
                                        default:
                                            Konsola::Czysc();
                                            cout << "Nieprawidlowy wybor. Sprobuj ponownie." << endl;
                                            Konsola::pause();
                                            Konsola::Czysc();
                                        }

                                    }
                                    break;
                                }
                                case 7:
                                    Konsola::Czysc();
                                    finanse->podsumowanieWydatkowWedlugKategorii();
                                    Konsola::pause();
                                    Konsola::Czysc();
                                    break;
                                case 8:
                                    Konsola::Czysc();
                                    wMenuFinansow = false;
                                    break;
                                default:

                                    Konsola::pokazWiadomoscICzekaj("Nieprawidlowy wybor. Sprobuj ponownie.");
                                    break;
                                }
                            }
                        }
                        else {
                            Konsola::pokazWiadomoscICzekaj("Musisz byc zalogowany, aby zarzadzac finansami.");
                        }
                        break;
                    case 3:
                        // Zmiana hasla
                        Konsola::Czysc();
                        if (!aktualnyUzytkownik.pobierzLogin().empty()) {
                            cout << "Podaj stare haslo: ";
                            string stareHaslo = getHiddenInput();
                            if (stareHaslo == aktualnyUzytkownik.pobierzHaslo()) {
                                cout << "Podaj nowe haslo: ";
                                string noweHaslo = getHiddenInput();
                                cout << "Potwierdz nowe haslo: ";
                                string potwierdzenieHasla = getHiddenInput();

                                if (noweHaslo == potwierdzenieHasla) {
                                    menedzer.zmienHaslo(aktualnyUzytkownik, noweHaslo);
                                }
                                else {
                                    Konsola::pokazWiadomoscICzekaj("Potwierdzenie hasla nie zgadza sie. Sprobuj ponownie.");
                                }
                            }
                            else {
                                Konsola::pokazWiadomoscICzekaj("Nieprawidlowe stare haslo.");
                            }
                        }
                        else {
                            Konsola::pokazWiadomoscICzekaj("Musisz byc zalogowany, aby zmienic haslo.");
                        }
                        break;
                    case 4:
                        // Wylogowanie uzytkownika
                        Konsola::Czysc();
                        zalogowany = false;
                        delete finanse;
                        finanse = nullptr;
                        Konsola::pokazWiadomoscICzekaj("Wylogowano.");
                        break;
                        // ... inne opcje ...
                    default:
                        // Mozesz tu dodac obsluge nieprawidlowego wyboru w menu uzytkownika
                        Konsola::pokazWiadomoscICzekaj("Nieprawidlowy wybor. Sprobuj ponownie.");
                        break;
                    }
                }
            }
            else {
                Konsola::pokazWiadomoscICzekaj("Nieprawidlowy login lub haslo.");
            }
        }
        else if (wybor == 2) { // Rejestracja uzytkownika
            Konsola::Czysc();
            string login, haslo, imie, nazwisko, numerIndeksu, dataUrodzenia, kierunekStudiow;
            char plec;

            cout << "Podaj login: ";
            getline(cin, login);
            if (menedzer.czyUzytkownikIstnieje(login)) {
                Konsola::pokazWiadomoscICzekaj("Uzytkownik o podanym loginie juz istnieje.");
                continue;
            }

            cout << "Podaj haslo: ";
            haslo = getHiddenInput();

            do {
                cout << "Podaj imie: ";
                getline(cin, imie);
                if (!czyTylkoLitery(imie)) {
                    cout << "Niepoprawny format imienia. Uzyj tylko liter." << endl;
                }
            } while (!czyTylkoLitery(imie));

            do {
                cout << "Podaj nazwisko: ";
                getline(cin, nazwisko);
                if (!czyTylkoLitery(nazwisko)) {
                    cout << "Niepoprawny format nazwiska. Uzyj tylko liter." << endl;
                }
            } while (!czyTylkoLitery(nazwisko));

            do {
                cout << "Podaj numer indeksu: ";
                getline(cin, numerIndeksu);
                if (!czyTylkoCyfry(numerIndeksu)) {
                    cout << "Niepoprawny format numeru indeksu. Uzyj tylko cyfr." << endl;
                }
            } while (!czyTylkoCyfry(numerIndeksu));

            do {
                cout << "Podaj date urodzenia (RRRR-MM-DD): ";
                getline(cin, dataUrodzenia);
                if (!czyPoprawnaData(dataUrodzenia)) {
                    cout << "Niepoprawny format daty urodzenia." << endl;
                }
            } while (!czyPoprawnaData(dataUrodzenia));

            do {
                cout << "Podaj plec (M/K): ";
                cin >> plec;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (!czyPoprawnaPlec(plec)) {
                    cout << "Niepoprawny format plci. Podaj M (mezczyzna) lub K (kobieta)." << endl;
                }
            } while (!czyPoprawnaPlec(plec));

            cout << "Podaj kierunek studiow: ";
            getline(cin, kierunekStudiow);

            Uzytkownik nowyUzytkownik(login, haslo, imie, nazwisko, numerIndeksu, dataUrodzenia, plec, kierunekStudiow);
            menedzer.zarejestrujUzytkownika(nowyUzytkownik);
        }
        else if (wybor == 3) { // Usuwanie uzytkownika
            Konsola::Czysc();
            string loginDoUsuniecia;
            cout << "Podaj login uzytkownika do usuniecia: ";
            getline(cin, loginDoUsuniecia);
            menedzer.usunUzytkownika(loginDoUsuniecia);
        }
        else if (wybor == 4) {
            Konsola::Czysc();
            delete finanse;
            finanse = nullptr;
            Konsola::pokazWiadomoscICzekaj("Koniec programu.");
            break;
        }
    }
    delete finanse;
    return 0;
}