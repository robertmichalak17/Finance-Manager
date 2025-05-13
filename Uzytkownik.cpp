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
