#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
using namespace std;

// KLASY


class Przeciwnik {
public:

    string type;
    int health;
    int strength;

    Przeciwnik(string type = "-11", int h = 1, int s = 1) {
        if (type == "-11") {
            h = 10;
            s = 1;
        }
        else if (type == "-12") {
            h = 70;
            s = 10;
        }
        else {
            h = 1;
            s = 1;
        }
        health = h;
        strength = s;
    }
};

// GLOBALNE ZMIENNE =============================================================================

int hp = 10;
int lvl = 0;
int money = 5;
int eq = 0;
int tablica[20][20];
string current_room = "room_11.txt";
string current_save;
string npc = "";
int current[2] = { 10, 10 };

// FUNKCJE =============================================================================

void title(string name, int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    string title = "";
    fstream tytul(name);
    while (getline(tytul, title)) {
        cout << title << endl;
    }
    tytul.close();
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
    cout << "====================\n";
}
/*
void draw_enemy(string enemy) {
    string enemy_sprite, enemy_char;
    fstream sprite("enemies/enemy_" + enemy + ".txt");
    while (getline(sprite, enemy_sprite)) {
        cout << enemy_sprite << endl;
    }
    sprite.close();
}*/

void load_room(string room, int x, int y) {
    // WCZYTANIE NOWEGO POZIOMU
    string rm = "rooms/" + room;
    current_room = room;
    fstream pokoj(rm);
    if (pokoj.good()) {
        cout << endl;
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 20; j++) {
                pokoj >> tablica[i][j];
            }
        }
        tablica[x][y] = 10;
        current[0] = x;
        current[1] = y;
    }
    pokoj.close();
}

void battle(string enemy, int x, int y) {
    int turn = 1;
    string enemy_sprite;
    unsigned char input;
    fstream sprite("enemies/enemy_" + enemy + ".txt");

    // STWORZENIE PRZECIWNIKA
    Przeciwnik en(enemy);

    while (true) { // ===== PÊTLA WALKI

        // RYSOWANIE PRZECINWIKA
        system("cls");

        title("enemies/enemy_" + enemy + ".txt", 10);
        cout << "HP PRZECIWNIKA: " << en.health;
        cout << "\nSILA PRZECIWNIKA: " << en.strength;
        cout << "\n====================================\n";
        //cout << "enemy id: " << enemy << endl;
        cout << "HP: " << hp << endl;
        if (turn == 1) {
            cout << "Tura Gracza\n";
            cout << "\nAtakuj (1)\n";
            cout << "Leczenie (2) [posiadasz "<< eq << "]\n";
            cout << "Uciekaj (3)\n";
        input:
            input = _getch();
            switch (input) {
            case '1': en.health -= 5 + lvl*0.5; break;
            case '2': if (eq > 0 && hp<100) {
                eq--;
                hp += 15;
            }
            break;
            case '3': if (en.strength<lvl+5) return; break;
            default: goto input; break;
            }
        }
        else {
            cout << "Tura Wroga\n";
            cout << "\nHP - " << en.strength;
            hp -= en.strength;
            input = _getch();
        }

        turn = !turn;
        if (en.health <= 0) {
            cout << "PRZECIWNIK POKONANY!";
            input = _getch();
            // PRZYZNANIE EXPA
            if (en.strength < 4) { if ((rand() % 2 + 1) == 1) lvl += ceil(en.strength * 0.5); }
            else lvl += ceil(en.strength * 0.5);
            // PRZYZNANIE PIENIĘDZY
            money += (rand() % 5 + 1) * en.strength;
            if (tablica[x][y] < -10) tablica[x][y] = 1;
            return;
        }
        else if (hp <= 0) return;
    }
    //delete en;

}

int check_field(int x, int y) {
    int num = tablica[x][y];
    if (tablica[x][y] == 3) return false;
    else if (tablica[x][y] == 2) {
        if((rand() % 5 + 1) == 2) battle("-11", x, y);
    }
    else if (tablica[x][y] == 4) {
        hp -= 3;
        return true;
    }
    else if (tablica[x][y] == 5) {
        if (money >= 5) {
            npc = "Kupiles leczenie za 5 pieniedzy";
            eq += 1;
            money -= 5;
        }
        else {
            npc = "Nie stac cie na zakup leczenia";
        }
        return false;
    }
    else if (tablica[x][y] > 10 && tablica[x][y] < 100) {

        if (y < 7) load_room("room_" + to_string(num) + ".txt", 10, 17);
        else if (y >= 7 && y < 15) load_room("room_" + to_string(num) + ".txt", 10, 10);
        else if (y > 15) load_room("room_" + to_string(num) + ".txt", 10, 2);

        return false;
    }
    else if (tablica[x][y] > 100) {
        npc = "Witaj, to jest NPC";
        return false;
    }
    else if (tablica[x][y] < -10) {
        battle(to_string(num), x, y);
        return false;
    }
}

void load_save(string save) {
    // WCZYTANIE DANYCH GRACZA
    current_save = save;
    fstream zapis(save);
    int count = 0;
    string data;
    while (zapis >> data) {
        switch (count) {
        case 0:
            hp = atoi(data.c_str());
            break;
        case 1:
            lvl = atoi(data.c_str());
            break;
        case 2:
            current_room = data;
            break;
        }
        count++;
    }
    zapis.close();
    load_room(current_room, 10, 10);
}

void save_save() {
    // ZAPISANIE DANYCH DO OBECNEGO SAVE
    ofstream zapis(current_save);
    zapis.open(current_save, ios::trunc);
    zapis.close();
    zapis.open(current_save, ios::out);
    zapis << hp << endl << lvl << endl << current_room;
    zapis.close();
}

void draw_level() {
    system("cls");

    // RYSOWANIE PODANEJ TABLICY
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            switch (tablica[i][j]) {
            case 0: cout << "  "; break;
            case 1: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8); cout << "[ "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); break;
            case 2: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);  cout << "W "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); break;
            case 3: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 76); cout << "# "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); break;
            case 4: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); cout << "X "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); break;
            case 5: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 102); cout << "@ "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); break;
            case 10: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 221); cout << "@ "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); break;
            default:
                if (tablica[i][j] > 10 && tablica[i][j] < 100) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 147); cout << "* "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); break;
                }
                else if (tablica[i][j] > 100) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 238); cout << "@ "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); break;
                }
                else if (tablica[i][j] < -10) {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 204); cout << "@ "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); break;
                }
                else break;
            }
        }
        cout << endl;
    }
    // STATYSTYKI
    cout << "HP: " << hp << endl << "LVL: " << lvl << endl << "MONEY: " << money;
    // DIALOG
    cout << "\n==========\n";
    cout << npc;
    npc = "";
}

void ruch_gracza(int* cur, int& p) {
    char ruch;
    ruch = _getch();
    switch (ruch) {
    case 'w':
        if (check_field(cur[0] - 1, cur[1]) != false) {
            tablica[cur[0]][cur[1]] = p;
            cur[0] -= 1;
            p = tablica[cur[0]][cur[1]];
        }
        break;
    case 's':
        if (check_field(cur[0] + 1, cur[1]) != false) {
            tablica[cur[0]][cur[1]] = p;
            cur[0] += 1;
            p = tablica[cur[0]][cur[1]];
        }
        break;
    case 'a':
        if (check_field(cur[0], cur[1] - 1) != false) {
            tablica[cur[0]][cur[1]] = p;
            cur[1] -= 1;
            p = tablica[cur[0]][cur[1]];
        }
        break;
    case 'd':
        if (check_field(cur[0], cur[1] + 1) != false) {
            tablica[cur[0]][cur[1]] = p;
            cur[1] += 1;
            p = tablica[cur[0]][cur[1]];
        }
        break;
    case 'p':
        save_save();
        break;
    default: break;

    }
    tablica[cur[0]][cur[1]] = 10;
    Sleep(50);
}
