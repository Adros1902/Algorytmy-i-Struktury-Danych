#include "UserMenu.h"
#include "List.h"
#include <iostream>
#include <conio.h>


void UserMenu::mainMenu(){
    int userChoiceInput;

    std::cout << " Witaj w programie. Aby wybrac opcje wpisz odpowiadajaca cyfre i zatwierdz enter:" << std::endl;
    std::cout << " 0 - Wyjscie z programu" << std::endl;
    std::cout << " 1 - Operacje na liscie" << std::endl;
    std::cout << " 2 - Operacje na tablicy" << std::endl;

    while (true) {
        std::cin >> userChoiceInput;

        switch (userChoiceInput) {
        case 0:
            exit(3);
            break;
        case 1:
            listMenu();
            break;
        case 2:
            tableMenu();
            break;
        default:
            std::cout << "Nieprawidlowy zakres, sprobuj jeszcze raz:" << std::endl;
            break;
        }
    }
}

void UserMenu::listMenu(){
        int userListMenuInput;
        system("cls");
        std::cout << " Jestes wlasnie w list menu! Lista instrukcji:" << std::endl;
        std::cout << " 0 - Powrot do glownego menu" << std::endl;
        std::cout << " 1 - Dodawnie wartosci do listy" << std::endl;
        std::cout << " 2 - Usuniecie wartosci z listy" << std::endl;
        std::cout << " 3 - usuniecie listy" << std::endl;
        std::cout << " 4 - przeszukiwanie listy" << std::endl;
        std::cout << " 5 - wczytaj liste z pliku" << std::endl;

        while (true) {
            std::cin >> userListMenuInput;
            system("cls");

            switch (userListMenuInput)
            {
            case 0:
                mainMenu();
                break;
            case 1:
                int indexOfInsertValue;
                int insertValue;

                while (true) {
                    std::cout << "Podaj indeks wstawianej liczby:" << std::endl;
                    std::cin >> indexOfInsertValue;

                    if (list.size == 0 && indexOfInsertValue != 0) {
                        std::cout << "Lista jest pusta, mozliwe wstawienie tylko na miejsce o indeksie 0" << std::endl;
                    }
                    else{
                        break;
                    }
                }

                std::cout << "Podaj liczbê:" << std::endl;
                std::cin >> insertValue;
                list.addElementToList(indexOfInsertValue, insertValue);
                listMenu();
                break;
            case 2:
                int valueToDelete;
                std::cout << "Podaj wartosc do usuniecia" << std::endl;
                std::cin >> valueToDelete;
                if (list.size == 0) {
                    std::cout << "Lista jest pusta." << std::endl;
                    _getch();
                    listMenu();
                }
                list.deleteElementOfList(valueToDelete);
                listMenu();
                break;
// test wewnetrzny, niepotrzebny w oficjalnej wersji
            case 3:
                list.test();
                break;
            case 4:
                int valueToFind;
                bool isValueFound;
                std::cout << "Podaj wartosc, ktora chcesz wyszukac:" << std::endl;
                std::cin >> valueToFind;
                isValueFound = list.findElement(valueToFind);
                if (isValueFound){
                    std::cout << "Wartosc znajduje sie na liscie." << std::endl;
                }
                else{
                    std::cout << "Wartosc nie znajduje sie na liscie." << std::endl;
                }
                _getch();
                listMenu();
                break;
            case 5: 
            {
                std::cout << "Podaj nazwe pliku:" << std::endl;
                std::string fileName;
                std::cin >> fileName;
                list.createListFromFile(fileName);
                _getch();
                listMenu();
                break;
            }
            default:
                std::cout << "Nieprawidlowy zakres, sprobuj jeszcze raz:" << std::endl;
                break;
            }
        }
}

void UserMenu::tableMenu() {
    int userTableMenuInput;
    system("cls");
    std::cout << " Jestes wlasnie w table menu! Lista instrukcji:" << std::endl;
    std::cout << " 0 - Powrot do glownego menu" << std::endl;
    std::cout << " 1 - Dodawnie wartosci do tablicy" << std::endl;
    std::cout << " 2 - Usuwanie wartosci z tablicy" << std::endl;

    while (true) {

        std::cin >> userTableMenuInput;
        system("cls");

        switch (userTableMenuInput) {
        case 0:
            mainMenu();
            break;
        case 1: 
            int tableInputIndex;
            int tableInputValue;
            while (true) {
                std::cout << "Podaj indeks wstawianej liczby:" << std::endl;
                std::cin >> tableInputIndex;
                if (table.size == 0 && tableInputIndex != 0) {
                    std::cout << "Tablica jest pusta, wstaw liczbe na pierwsze miejsce tablicy:" << std::endl;
                }
                else if (table.size < tableInputIndex) {
                    std::cout << "Indeks wyszedl poza zakres tablicy o rozmiarze: " << table.size << " Sproboj jeszcze raz:" << std::endl;
                }
                else break;
            }
            std::cout << "Podaj wartosc, ktora chcesz wstawic:" << std::endl;
            std::cin >> tableInputValue;
            table.addElementToTable(tableInputIndex, tableInputValue);
            _getch();
            tableMenu();
            break;
        case 2: 
            int tableInputDeleteIndex;
            while (true) {
                std::cout << "Podaj indeks usuwanej liczby:" << std::endl;
                std::wcin >> tableInputDeleteIndex;
                if (table.size == 0) {
                    std::cout << "Tablica jest pusta, usuniecie jest niemozliwe" << std::endl;
                    break;
                }
                else if (table.size < tableInputDeleteIndex) {
                    std::cout << "Wybrany indeks wykracza poza zakres tablicy o rozmiarze: " << table.size << "Sproboj jeszcze raz:" << std::endl;
                }
                else {
                    table.deleteElementFromTable(tableInputDeleteIndex);
                    std::cout << "Elementy tablicy:" << std::endl;
                    table.printAllElements();
                    _getch;
                    break;
                }
            }
            tableMenu();
            break;
        default:
            std::cout << "Nieprawidlowy zakres, sprobuj jeszcze raz:" << std::endl;
            tableMenu();
            break;
        }

        

    }
}


