#ifndef UZYTKOWNIK_H
#define UZYTKOWNIK_H

#include <iostream>
#include <string>

class Uzytkownik {
private:
    std::string login;
    std::string haslo;
    std::string imie;
    std::string nazwisko;
    std::string numerIndeksu;
    std::string dataUrodzenia;
    char plec;
    std::string kierunekStudiow;

public:
    Uzytkownik();
    Uzytkownik(const std::string& login, const std::string& haslo, const std::string& imie, const std::string& nazwisko,
        const std::string& numerIndeksu, const std::string& dataUrodzenia, char plec, const std::string& kierunekStudiow);

    std::string pobierzLogin() const;
    std::string pobierzHaslo() const;
    void ustawHaslo(const std::string& noweHaslo);
    std::string pobierzImie() const;
    std::string pobierzNazwisko() const;
    std::string pobierzNumerIndeksu() const;
    std::string pobierzDataUrodzenia() const;
    char pobierzPlec() const;
    std::string pobierzKierunekStudiow() const;
    void wyswietlInformacjeProfilu() const;
};

#endif // UZYTKOWNIK_H