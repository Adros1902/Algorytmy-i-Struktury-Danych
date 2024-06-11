#include "UserMenu.h"
#include "List.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>

void UserMenu::mainMenu(){
    int userChoiceInput;

    // menu glowne
    std::cout << "Witaj w programie. Aby wybrac opcje wpisz odpowiadajaca cyfre i zatwierdz enter:" << std::endl;
    std::cout << "0 - Wyjscie z programu" << std::endl;
    std::cout << "1 - Operacje na liscie" << std::endl;
    std::cout << "2 - Operacje na tablicy" << std::endl;
    std::cout << "3 - Operacje na kopcu" << std::endl;
    std::cout << "4 - Operacje na drzewie czerwono czarnym" << std::endl;
    std::cout << "5 - testy" << std::endl;

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
        case 3: 
            heapMenu();
            break;
        case 4:
            blackRedTreeMenu();
            break;
        case 5:
            tests();
            break;
        default:
            std::cout << "Nieprawidlowy zakres, sprobuj jeszcze raz:" << std::endl;
            break;
        }
    }
}

// menu listy
void UserMenu::listMenu(){
        int userListMenuInput;
        system("cls");
        std::cout << "Jestes wlasnie w list menu! Lista instrukcji:" << std::endl;
        std::cout << "0 - Powrot do glownego menu" << std::endl;
        std::cout << "1 - Zbuduj z pliku" << std::endl;
        std::cout << "2 - Usun" << std::endl;
        std::cout << "3 - Dodaj" << std::endl;
        std::cout << "4 - Znajdz" << std::endl;
        std::cout << "5 - Utworz losowo" << std::endl; 
        std::cout << "6 - Wyswietl liste" << std::endl;

        while (true) {
            std::cin >> userListMenuInput;
            system("cls");

            switch (userListMenuInput)
            {
            case 0:
                mainMenu();
                break;

            case 1:
            {
                std::cout << "Podaj sciezke pliku:" << std::endl;
                std::string fileName;
                std::cin >> fileName;
                list.createListFromFile(fileName);
                list.printAllElements();
                _getch();
                listMenu();
                break;
            }

            case 2:
                int valueToDelete;
                bool isValueInList;

                std::cout << "Podaj wartosc do usuniecia" << std::endl;
                std::cin >> valueToDelete;

                if (list.size == 0) {
                    std::cout << "Lista jest pusta." << std::endl;
                    _getch();
                    listMenu();
                    break;
                }
                isValueInList = list.deleteElementOfList(valueToDelete);

                if (isValueInList) {
                    if (list.size == 0) {
                        std::cout << "Lista jest pusta" << std::endl;
                    }
                    else {
                        list.printAllElements();
                    }
                }
                else {
                    std::cout << "Nie ma takiego elementu" << std::endl;
                }
                _getch();
                listMenu();
                break;

            case 3:
                int indexOfInsertValue;
                int insertValue;

                while (true) {
                    std::cout << "Podaj indeks wstawianej liczby:" << std::endl;
                    std::cin >> indexOfInsertValue;

                    if (list.size == 0 && indexOfInsertValue != 0) {
                        std::cout << "Lista jest pusta, mozliwe wstawienie tylko na miejsce o indeksie 0" << std::endl;
                    }
                    else if ((list.size < indexOfInsertValue || indexOfInsertValue < 0) && indexOfInsertValue != 0){
                        std::cout << "Wybrany indeks przekroczyl dostepny zakres. Najwyzszy mozliwy indeks do wstawienia to: " << list.size << ". Sprobuj jeszcze raz" << std::endl;
                    }
                    else{
                        break;
                    }
                }

                std::cout << "Podaj liczbe:" << std::endl;
                std::cin >> insertValue;
                list.addElementToList(indexOfInsertValue, insertValue);
                list.printAllElements();
                _getch();
                listMenu();
                break;

            case 4:
                int valueToFind;
                bool isValueFound;
                std::cout << "Podaj wartosc, ktora chcesz wyszukac:" << std::endl;
                std::cin >> valueToFind;
                isValueFound = list.findElement(valueToFind);
                if (isValueFound) {
                    std::cout << "Wartosc znajduje sie na liscie." << std::endl;
                }
                else {
                    std::cout << "Wartosc nie znajduje sie na liscie." << std::endl;
                }
                _getch();
                listMenu();
                break;

            case 5:
                int quantity;
                std::cout << "Podaj wielkosc struktury:" << std::endl;
                std::cin >> quantity;
                list.autoGeneration(quantity);
                list.printAllElements();
                _getch();
                listMenu();
                break;

            case 6:
                list.printAllElements();
                _getch();
                listMenu();
            default:
                std::cout << "Nieprawidlowy zakres, sprobuj jeszcze raz:" << std::endl;
                break;
            }
        }
}

// menu tablicy
void UserMenu::tableMenu() {
    int userTableMenuInput;
    system("cls");
    std::cout << "Jestes wlasnie w table menu! Lista instrukcji:" << std::endl;
    std::cout << "0 - Powrot do glownego menu" << std::endl;
    std::cout << "1 - Zbuduj z pliku" << std::endl;
    std::cout << "2 - Usun" << std::endl;
    std::cout << "3 - Dodaj" << std::endl;
    std::cout << "4 - Znajdz" << std::endl;
    std::cout << "5 - Utworz losowo" << std::endl;
    std::cout << "6 - Wyswietl" << std::endl;

    while (true) {

        std::cin >> userTableMenuInput;
        system("cls");

        switch (userTableMenuInput) {
        case 0:
            mainMenu();
            break;
        case 1: 
        {
            std::string fileName;
            std::cout << "Podaj sciezke pliku" << std::endl;
            std::cin >> fileName;
            table.createTableFromFile(fileName);
            table.printAllElements();
            _getch();
            tableMenu();
            break;
        }

        case 2:
            int tableInputDeleteIndex;
            while (true) {
                std::cout << "Podaj indeks usuwanej liczby:" << std::endl;
                std::cin >> tableInputDeleteIndex;

                if (table.size == 0) {
                    std::cout << "Tablica jest pusta, usuniecie jest niemozliwe" << std::endl;
                    break;
                }
                else if (table.size <= tableInputDeleteIndex) {
                    std::cout << "Wybrany indeks wykracza poza zakres tablicy o rozmiarze: " << table.size << " Sprobuj jeszcze raz:" << std::endl;
                }
                else {
                    table.deleteElementFromTable(tableInputDeleteIndex);
                    table.printAllElements();
                    _getch();
                    break;
                }
            }
            tableMenu();
            break;

        case 3: 
            int tableInputIndex;
            int tableInputValue;
            while (true) {
                std::cout << "Podaj indeks wstawianej liczby:" << std::endl;
                std::cin >> tableInputIndex;
                if (table.size == 0 && tableInputIndex != 0) {
                    std::cout << "Tablica jest pusta, wstaw liczbe na pierwsze miejsce tablicy:" << std::endl;
                }
                else if (table.size < tableInputIndex) {
                    std::cout << "Indeks wyszedl poza zakres tablicy o rozmiarze: " << table.size << " Sprobuj jeszcze raz:" << std::endl;
                }
                else break;
            }
            std::cout << "Podaj wartosc, ktora chcesz wstawic:" << std::endl;
            std::cin >> tableInputValue;
            table.addElementToTable(tableInputIndex, tableInputValue);
            table.printAllElements();
            _getch();
            tableMenu();
            break;

        case 4:
            int valueToFind;
            bool isValueInTable;
            std::cout << "Podaj wartosc, ktorej szukasz:" << std::endl;
            std::cin >> valueToFind;
            isValueInTable =  table.findingNumber(valueToFind);

            if (isValueInTable) {
                std::cout << "Wartosc znajduje sie w tablicy" << std::endl;
            }
            else {
                std::cout << "Wartosc nie znajduje sie w tablicy" << std::endl;
            }
            _getch();
            tableMenu();
            break;

        case 5:
            int quantity;
            std::cout << "Podaj wielkosc struktury:" << std::endl;
            std::cin >> quantity;
            table.autoGeneration(quantity);
            table.printAllElements();
            _getch();
            tableMenu();
            break;

        case 6:
            table.printAllElements();
            _getch();
            tableMenu();
            break;

        default:
            std::cout << "Nieprawidlowy zakres, sprobuj jeszcze raz" << std::endl;
            _getch();
            tableMenu();
            break;
        }

        

    }
}

void UserMenu::heapMenu()
{
    int userListMenuInput;
    system("cls");
    std::cout << "Jestes wlasnie w heap menu! Lista instrukcji:" << std::endl;
    std::cout << "0 - Powrot do glownego menu" << std::endl;
    std::cout << "1 - Zbuduj z pliku" << std::endl;
    std::cout << "2 - Usun - aktywne" << std::endl;
    std::cout << "3 - Dodaj - aktywne" << std::endl;
    std::cout << "4 - Znajdz" << std::endl;
    std::cout << "5 - Utworz losowo" << std::endl;
    std::cout << "6 - Wyswietl kopiec - aktywne" << std::endl;

    while (true) {
        std::cin >> userListMenuInput;
        system("cls");

        switch (userListMenuInput)
        {
        case 0:
            mainMenu();
            break;

        case 1:
        {
            std::cout << "Podaj sciezke pliku:" << std::endl;
            std::string fileName;
            std::cin >> fileName;
            heap.createHeapFromFile(fileName);
            heap.printElementsOfHeapIntable();
            heap.printHeap();
            _getch();
            heapMenu();
            break;
        }

        case 2:
            int indexToDelete;
            std::cout << "Podaj indeks do usuniecia:" << std::endl;
            std::cin >> indexToDelete;
            if (indexToDelete >= heap.size) {
                std::cout << "Indeks wykracza poza rozmiar kopca" << std::endl;
                _getch();
                heapMenu();
                break;
            }
            else {
                heap.printHeap();
                heap.deletePickedIndexValue(indexToDelete);
            }
            heap.printElementsOfHeapIntable();
            heap.printHeap();
            _getch();
            heapMenu();
            break;

        case 3:
            int insertValue;
            std::cout << "Podaj liczbe:" << std::endl;
            std::cin >> insertValue;
            heap.insertValueToHeap(insertValue);
            heap.printElementsOfHeapIntable();
            heap.printHeap();
            _getch();
            heapMenu();
            break;

        case 4:
            int valueToFindHeap;
            bool isValueFoundHeap;
            std::cout << "Podaj wartosc, ktora chcesz wyszukac:" << std::endl;
            std::cin >> valueToFindHeap;
            isValueFoundHeap = heap.findingElement(valueToFindHeap);
            if (isValueFoundHeap) {
                std::cout << "Wartosc znajduje sie w kopcu." << std::endl;
            }
            else {
                std::cout << "Wartosc nie znajduje sie w kopcu." << std::endl;
            }
            _getch();
            heapMenu();
            break;

        case 5:
            int quantity;
            std::cout << "Podaj wielkosc struktury:" << std::endl;
            std::cin >> quantity;
            heap.autoGeneration(quantity);
            heap.printHeap();
            _getch();
            heapMenu();
            break;

        case 6:
            std::cout << "Kopiec w formie tablicy:" << std::endl;
            heap.printElementsOfHeapIntable();
            std::cout << "Kopiec w formie drzewa:" << std::endl;
            heap.printHeap();
            _getch();
            heapMenu();
        default:
            std::cout << "Nieprawidlowy zakres, sprobuj jeszcze raz:" << std::endl;
            break;
        }
    }
}

void UserMenu::blackRedTreeMenu() {
    int userListMenuInput;
    system("cls");
    std::cout << "Jestes wlasnie w drzewo czerwono czarne menu! Lista instrukcji:" << std::endl;
    std::cout << "0 - Powrot do glownego menu" << std::endl;
    std::cout << "1 - Zbuduj z pliku" << std::endl;
    std::cout << "2 - Usun" << std::endl;
    std::cout << "3 - Dodaj" << std::endl;
    std::cout << "4 - Znajdz" << std::endl;
    std::cout << "5 - Utworz losowo" << std::endl;
    std::cout << "6 - Wyswietl liste" << std::endl;

    while (true) {
        std::cin >> userListMenuInput;
        system("cls");

        switch (userListMenuInput)
        {
        case 0:
            mainMenu();
            break;

        case 1:
        {
            std::cout << "Podaj sciezke pliku:" << std::endl;
            std::string fileName;
            std::cin >> fileName;
            blackRedTree.createBRTreeFromFile(fileName);
            blackRedTree.printBlackRedTree();
            _getch();
            blackRedTreeMenu();
            break;
        }

        case 2:
            int valueToDelete;
            bool isValueInTree;

            std::cout << "Podaj wartosc do usuniecia" << std::endl;
            std::cin >> valueToDelete;

            if (blackRedTree.root == blackRedTree.sentinel) {
                std::cout << "Drzewo jest puste." << std::endl;
                _getch();
                blackRedTreeMenu();
                break;
            }
            isValueInTree = blackRedTree.deleteElementFromBRTree(valueToDelete);

            if (isValueInTree) {
                blackRedTree.printBlackRedTree();
            }
            else {
                std::cout << "Nie ma takiego elementu" << std::endl;
            }
            _getch();
            blackRedTreeMenu();
            break;

        case 3:
            int insertValue;

            std::cout << "Podaj liczbe:" << std::endl;
            std::cin >> insertValue;
            blackRedTree.insertElementToBRTree(insertValue);
            blackRedTree.printBlackRedTree();
            _getch();
            blackRedTreeMenu();
            break;

        case 4:
            int valueToFind;
            bool isValueFound;
            std::cout << "Podaj wartosc, ktora chcesz wyszukac:" << std::endl;
            std::cin >> valueToFind;
            isValueFound = blackRedTree.findValueInRBTree(valueToFind);
            if (isValueFound) {
                std::cout << "Wartosc znajduje sie w drzewie." << std::endl;
            }
            else {
                std::cout << "Wartosc nie znajduje sie w drzewie." << std::endl;
            }
            _getch();
            blackRedTreeMenu();
            break;

        case 5:
            int quantity;
            std::cout << "Podaj wielkosc struktury:" << std::endl;
            std::cin >> quantity;
            blackRedTree.generateRandomRBTree(quantity);
            blackRedTree.printBlackRedTree();
            _getch();
            blackRedTreeMenu();
            break;

        case 6:
            blackRedTree.printBlackRedTree();
            _getch();
            blackRedTreeMenu();
        default:
            std::cout << "Nieprawidlowy zakres, sprobuj jeszcze raz:" << std::endl;
            break;
        }
    }
}

void UserMenu::tests() {
            
    LARGE_INTEGER frequency;
    LARGE_INTEGER startTime;
    LARGE_INTEGER endTime;
    LARGE_INTEGER startTime1;
    LARGE_INTEGER endTime1;
    double elapsedTime = 0;
    double fullTime = 0;

    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&startTime1);

    for (int i = 0; i < 100; i++) {
        int structureSize = 100000;
        int elements = 1000;
        
        table.createTableForTests(structureSize);

        QueryPerformanceCounter(&startTime);

        for (int i = 0; i < elements; i++) {
            table.deleteElementFromTableFirst();
        }

        QueryPerformanceCounter(&endTime);
        elapsedTime += static_cast<double>(endTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;
 
    }
    QueryPerformanceCounter(&endTime1);
    fullTime = static_cast<double>(endTime1.QuadPart - startTime1.QuadPart) / frequency.QuadPart;

   // fullTime = elapsedTime;
    elapsedTime = elapsedTime / 100;

    std::cout << "Sredni czas operacji: " << elapsedTime * 1000 << " ms " << std::endl;
    std::cout << "All czas operacji: " << fullTime << " s " << std::endl;

    _getch();

}

