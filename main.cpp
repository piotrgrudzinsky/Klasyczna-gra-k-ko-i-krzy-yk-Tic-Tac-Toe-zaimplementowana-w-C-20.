#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

class newGameXO {
private:
    vector<vector<char>> plansza;
    char gracz;
    const int ROZMIAR = 3;
    const char PUSTY = '_';
public:
    enum class stanGry {
        KONTYNUACJA,
        WYGRANA_X,
        WYGRANA_O,
        REMIS
    };

    newGameXO() {
        plansza = {
            {'_', '_', '_' },
            {'_', '_', '_' },
            {'_', '_', '_' },
        };
    }

    void setChar(char gracz, int posx, int posy) {
        posx -=1;
        posy -=1;

        if (posx < 0 || posx >= ROZMIAR || posy < 0 || posy >= ROZMIAR) {
            return;
        }

        if (plansza[posx][posy] != PUSTY) {
            return;
        }

        plansza[posx][posy] = gracz;
    }

    vector<vector<char>> &getPlansza() {
        return plansza;
    }
    void rysujPlansze() {
        for (vector<char> wiersz : plansza) {
            for (char element : wiersz) {
                cout<<element;
            }
            cout<<endl;
        }
    }
    bool sprawdzWiersze(int wiersz, char gracz) {
        for (int kolumna = 0; kolumna < ROZMIAR; kolumna++) {
            if (plansza[wiersz][kolumna] != gracz) return false;
        }
        return true;
    }
    bool sprawdzKolumny(int kolumna, char gracz) {
        for (int wiersz = 0; wiersz < ROZMIAR; wiersz++) {
            if (plansza[wiersz][kolumna] != gracz) return false;
        }
        return true;
    }
    bool sprawdzPrzekatne(char gracz) {
        bool glownaPrzek = true;
        for (int i = 0; i < ROZMIAR; i++) {
            if (plansza[i][i] != gracz) {
                glownaPrzek = false;
                break;
            }
        }

        bool drugaPrzek = true;
        for (int i = 0; i < ROZMIAR; i++) {
            if (plansza[i][ROZMIAR - 1 - i] != gracz) {
                drugaPrzek = false;
                break;
            }
        }
        return (glownaPrzek || drugaPrzek);
    }

    bool sprawdzWygrana(char gracz) {
        //wiersze
        for (int wiersz = 0; wiersz < ROZMIAR; wiersz++) {
            if (sprawdzWiersze(wiersz, gracz)) return true;
        }
        //kolumny
        for (int kolumna = 0; kolumna < ROZMIAR; kolumna++) {
            if (sprawdzKolumny(kolumna, gracz)) return true;
        }
        //przekatne
        return sprawdzPrzekatne(gracz);
    }
    bool czyPlanszaPelna() {
        for (vector<char> wiersz : plansza ) {
            for (char element : wiersz) {
                if (element == PUSTY) return false;
            }
        }
        return true;
    }

};
class gracze {
public:
    map<string, char> gracz1 = {
        {"active", '0'},
        {"char", 'X'}
    };
    map<string, char> gracz2 = {
        {"active", '0'},
        {"char", 'O'}
    };

    void setActive(int gracz) {
        if (gracz == 1) {
            gracz1["active"] = '1';
            gracz2["active"] = '0';
        } else {
            gracz2["active"] = '1';
            gracz1["active"] = '0';
        }
    }

    char getActivePlayerChar() {
        if (gracz1["active"] == '1') {
            return gracz1["char"];
        } else {
            return gracz2["char"];
        }
    }

    int getActivePlayer() {
        if (gracz1["active"] == '1') {
            return 1;
        } else {
            return 2;
        }
    }

    void switchPlayer() {
        if (gracz1["active"] == '1') {
            setActive(2);
        } else {
            setActive(1);
        }
    }
};

int main() {
    newGameXO gra;
    gracze gracze;
    gracze.setActive(1);

    cout << "=== GRA KÓŁKO I KRZYŻYK ===" << endl;
    gra.rysujPlansze();

    while (true) {
        int x, y;
        char aktywnyGracz = gracze.getActivePlayerChar();

        cout << "\nGracz " << gracze.getActivePlayer() << " (" << aktywnyGracz << ") - Podaj pozycje (x y): ";
        cin >> x >> y;

        // Poprawnos ruchu
        if (x < 1 || x > 3 || y < 1 || y > 3) {
            cout << "Niepoprawne współrzędne! Podaj liczby od 1 do 3." << endl;
            continue;
        }


        vector<vector<char>>& plansza = gra.getPlansza();
        if (plansza[x-1][y-1] != '_') {
            cout << "To pole jest już zajete! Wybierz inne." << endl;
            continue;
        }

        gra.setChar(aktywnyGracz, x, y);
        gra.rysujPlansze();

        // Sprawdza wygrana
        if (gra.sprawdzWygrana(aktywnyGracz)) {
            cout << "\nGracz " << gracze.getActivePlayer() << " (" << aktywnyGracz << ") wygrywa!" << endl;
            break;
        }

        // Sprawdza remmus
        if (gra.czyPlanszaPelna()) {
            cout << "\n REMIS" << endl;
            break;
        }


        gracze.switchPlayer();
    }
}