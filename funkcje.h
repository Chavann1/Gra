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

    Przeciwnik(string type="-11", int h = 10, int s = 1) {
        health = h;
        strength = s;
    }
};

// GLOBALNE ZMIENNE =============================================================================

int hp = 10;
int lvl = 0;
int tablica[20][20];
string current_room = "room_11.txt";
string current_save;
string npc ="";
int current[2] = { 10, 10 };

// FUNKCJE =============================================================================

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
    short first_loop = 0;
    int turn = 1;
    string enemy_sprite;
    unsigned char input;
    fstream sprite("enemies/enemy_"+enemy+".txt");

    // STWORZENIE PRZECIWNIKA
    Przeciwnik en(enemy);

    while (true) { // ===== PÊTLA WALKI

        // RYSOWANIE PRZECINWIKA
        sprite.open("enemies/enemy_" + enemy + ".txt", ios::in);
        system("cls");
        while (getline(sprite, enemy_sprite)) {
            cout << enemy_sprite << endl;
        }
        if (first_loop == 0) {
            cout <<"\n\n\n\n\n\tPRZECIWNIK NADCHODZI...\n\n\n\n\n";
            first_loop++;
        }
        cout << "HP PRZECIWNIKA: " << en.health;
        cout << "\n====================================\n";
        //cout << "enemy id: " << enemy << endl;
        cout << "HP: " << hp << endl;
        if (turn == 1) {
            cout << "Tura Gracza\n";
            cout << "\nAtakuj (1)\n";
            cout << "Uciekaj (2)\n";
            input:
            input = _getch();
            switch (input) {
            case '1': en.health -= 5 + lvl; break;
            case '2': return; break;
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
        sprite.close();
        if (en.health <= 0) {
            cout << "PRZECIWNIK POKONANY!";
            input = _getch();
            lvl += en.strength;
            if(tablica[x][y] < -10) tablica[x][y] = 1;
            return;
        }
        else if (hp <= 0) return;
    }
    //delete en;

}

int check_field(int x, int y) {
    int num = tablica[x][y];
    if (tablica[x][y] == 3) return false;
    else if (tablica[x][y] > 10 && tablica[x][y] < 100) {
        
        if (y < 7) load_room("room_" + to_string(num) + ".txt", 10, 17);
        else if (y >= 7 && y < 15) load_room("room_" + to_string(num) + ".txt", 10, 10);
        else if (y > 15) load_room("room_" + to_string(num) + ".txt", 10, 2);
        
        return false;
    } else if (tablica[x][y] > 100) {
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
            case 3: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 64); cout << "# "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); break;
            case 10: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 221); cout << "@ "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); break;
            default: 
                if (tablica[i][j] > 10 && tablica[i][j] < 100) { 
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 21); cout << "* "; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); break;
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
    cout << "HP: " << hp << endl << "LVL: " << lvl;
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

void title() {
    string title = "";
    fstream tytul("tytul.txt");
    while (getline(tytul, title)) {
        cout << title << endl;
    }
    tytul.close();
    cout << "====================\n";
}