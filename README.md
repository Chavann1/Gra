# Konsolowa gra RPG w C++

Prosta gra RPG działająca w konsoli, napisana w C++, zawierająca system eksploracji oparty na siatce, mechanikę walki oraz zapis/odczyt stanu gry do plików.
Uwaga: ten projekt powstał w trakcie nauki programowania i nie odzwierciedla mojego obecnego poziomu doświadczenia.
---

## Funkcje

* Poruszanie się po mapie (siatka 20x20)
* Turowy system walki
* Wiele pomieszczeń wczytywanych z plików
* System zapisu i odczytu gry (pliki tekstowe)
* Prosta interakcja z NPC
* Renderowanie w konsoli z użyciem kolorów

---

## Technologie

* C++
* Biblioteka standardowa (iostream, fstream, itp.)
* API Windows (`conio.h`, `windows.h`)

---

## Jak to działa

* Świat gry jest reprezentowany jako tablica 2D wczytywana z plików
* Każde pole ma przypisaną wartość określającą jego zachowanie (ściana, przeciwnik, przejście do innego pomieszczenia itp.)
* Ruch gracza aktualizuje stan mapy i wywołuje interakcje
* Walka działa w osobnej pętli w trybie turowym
* Stan gry (HP, poziom, aktualne pomieszczenie) zapisywany jest do plików

---

## Sterowanie

* W / A / S / D — ruch
* P — zapis gry
* Enter — wybór w menu

---

## Struktura projektu

* `main.cpp` — główna pętla gry i menu
* `funkcje.h` — logika gry (ruch, walka, zapis, renderowanie)
* `rooms/` — pliki z mapami pomieszczeń
* `enemies/` — dane przeciwników i ich wygląd ASCII
* `save*.txt` — pliki zapisu

---

## Uwagi

* Projekt ma prostą strukturę (np. użycie zmiennych globalnych i implementacji w pliku nagłówkowym)
* Działa tylko na systemie Windows (ze względu na `conio.h` i `windows.h`)
* Projekt powstał jako ćwiczenie podstawowych koncepcji programowania

---
