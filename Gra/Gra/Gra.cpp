#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include "funkcje.h"
using namespace std;

void menu() {
    int pos = 0; // ZMIENNA PRZECHOWUJĄCA POZYCJĘ KURSORA
    int submenu = 0; // ZMIENNA DO OTWIERANIA ODPOWIEDNIEGO MENU W MENU
    while (true) {
        system("cls");
        //cout << "\033c";
        // ========== TABLICA DO WYŚWIETLANIA 'KURSORA' ========== 
        string cursor[4];
        for (int i = 0; i < 4; i++) {
            cursor[i] = "";
        }
        if (pos > 3) pos = 0;
        if (pos < 0) pos = 3;
        cursor[pos] = "*";

        // INFO
        //cout << endl << "W gore [w] | W dol [s] | Zatwierdz [ENTER]\n";
        // ========== WCZYTANIE TYTUŁU ========== 
        title("tytul.txt", 14);

        // ==================== RESZTA MENU ==================== 
        cout << "\t" << cursor[0] << "Wczytaj gre" << endl;
        cout << "\t" << cursor[1] << "Rozpocznij nowa" << endl;
        cout << "\t" << cursor[2] << "Sterowanie" << endl;
        cout << "\t" << cursor[3] << "Wyjdz" << endl;
        cout << "====================\n";

        // RYSOWANIE SUBMENU
        // otwarcie zapisów
        fstream save1("save1.txt"); 
        fstream save2("save2.txt");
        unsigned char wybor2;
        switch (submenu) {

        case 1: // ======== WCZYTYWANIE GRY ======== 
            cout << "Dostepne zapisy: (wybierz numer w nawiasie)\n";

            // WYŚWIETL ZAPIS 1
            if (save1.good()) cout << "SAVE 1"; else cout << "[BRAK 1]";
            cout << " (1)" << endl;

            // WYŚWIETL ZAPIS 2
            if (save2.good()) cout << "SAVE 2"; else cout << "[BRAK 2]";
            cout << " (2)" << endl<<endl;
            // Opcja 3
            cout << "Powrot (3)";

            // wybor w submenu
            wybor2 = _getch();
            if (wybor2 == '1') {
                if (save1.good()) load_save("save1.txt");
                else save_save();
                return;
            } else if (wybor2 == '2') {
                if (save1.good()) load_save("save2.txt");
                else save_save();
                return;
            } else if (wybor2 == '3') {
                submenu = -1;
            }
            wybor2 = '0';
            break;
        
        case 2: // ======== WCZYTYWANIE GRY ======== 
            cout << "Dostepne zapisy: (wybierz numer w nawiasie)\n";

            // WYŚWIETL ZAPIS 1
            if (save1.good()) cout << "SAVE 1"; else cout << "[BRAK 1]";
            cout << " (1)" << endl;

            // WYŚWIETL ZAPIS 2
            if (save2.good()) cout << "SAVE 2"; else cout << "[BRAK 2]";
            cout << " (2)" << endl<<endl;
            // Opcja 3
            cout << "Powrot (3)";

            // wybor w submenu
            wybor2 = _getch();
            if (wybor2 == '1') {
                current_save = "save1.txt";
                save_save();
                load_save("save1.txt");
                return;
            } else if (wybor2 == '2') {
                current_save = "save2.txt";
                save_save();
                load_save("save2.txt");
                return;
            } else if (wybor2 == '3') {
                submenu = -1;
            }
            wybor2 = '0';
            break;

        case 3: // ======== WYŚWIETLENIE STEROWANIA ======== 
            cout << "Sterowanie:\n";
            cout << "\nGora [w]\nLewo [a]\nPrawo [d]\nDol [s]\n";
            cout << "Zapis [p]\n\n";
            cout << "Powrot (3)";
            // wybor w submenu
            wybor2 = _getch();
            if (wybor2 == '3') {
                submenu = -1;
            }
            wybor2 = '0';
            break;

        case 4:
            exit(0);
            break;
        default: break;
        }
        // ZAMKNIĘCIE ZAPISÓW
        save1.close();
        save2.close();
        // ==================== WYBÓR ==================== 
        unsigned char wybor; // ZMIENNA POBIERAJACA ZNAK
        if (submenu == 0) {
            wybor = _getch();
            int kod_wyboru = static_cast <int>(wybor); // ZMIENNA PRZECHOWUJĄCA KOD ENTERA
            switch (wybor) {
            case 'w': pos--; break;
            case 's': pos++; break;
            default:
                if (kod_wyboru == 13) submenu = pos + 1;
                break;
            }
        }
        else if (submenu == -1) submenu = 0;
    }
}

// MAIN =============================================================================

int main()
{
    srand((unsigned int)time(NULL));
    retry:
    menu();
    cout << "HP =" << hp;
    cout << "lvl =" << lvl;
    int prev = 1;

    while (true) {
        draw_level();
        ruch_gracza(current, prev);
        if (hp <= 0) goto retry;
    }
    //delete[] current;
    return 0;
}

