#include "UserMenu.h"
#include <iostream>
#include <conio.h>

void UserMenu::mainMenu()
{
    int userChoiceInput;
    // menu glowne
    std::cout << "Witaj w programie. Aby wybrac opcje wpisz odpowiadajaca cyfre i zatwierdz enter:" << std::endl;
    std::cout << "0 - Wyjscie z programu" << std::endl;
    std::cout << "1 - Algorytmy MST" << std::endl;

    while (true) {
        std::cin >> userChoiceInput;
        switch (userChoiceInput) {
        case 0:
            exit(3);
            break;
        case 1:
            mstMenu();
            break;
        default:
            std::cout << "Nieprawidlowy zakres, sprobuj jeszcze raz:" << std::endl;
            break;
        }
    }
}

void UserMenu::mstMenu()
{
    int userListMenuInput;
    system("cls");
    std::cout << "Jestes wlasnie w MST menu! Lista instrukcji:" << std::endl;
    std::cout << "0 - Powrot do glownego menu" << std::endl;
    std::cout << "1 - Wczytaj z pliku" << std::endl;
    std::cout << "2 - Wygeneruj graf losowo" << std::endl;
    std::cout << "3 - Wyswietl listowo i macierzowo" << std::endl;
    std::cout << "4 - Algorytm Kruskala" << std::endl;
    std::cout << "5 - Algorytm Prima" << std::endl;

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
            
            kruskal.createFromFile(fileName);
            kruskal.createListFromFile(fileName);
            kruskal.printMatrix();
            kruskal.printList();
            prim.createListFromFile(fileName);
            prim.createFromFile(fileName);
            _getch();
            mstMenu();
            break;
        }

        case 2:
            int numberOfVertex, density;
            std::cout << "Podaj ilosc wierzcholkow:" << std::endl;
            std::cin >> numberOfVertex;
            std::cout << "Podaj gestosc w procentach:" << std::endl;
            std::cin >> density;
            kruskal.generateGraph(numberOfVertex,density);
            kruskal.printMatrix();
            kruskal.printList();
            _getch();
            mstMenu();
            break;

        case 3:
            kruskal.printMatrix();
            kruskal.printList();
            _getch();
            mstMenu();
            break;

        case 4:
            
            kruskal.kruskalAlgorithmMatrix();
            kruskal.printResultFromMatrix();
            kruskal.kruskalAlgorithmList();
            kruskal.printResultFromList();
            _getch();
            mstMenu();
            break;
        case 5:
            prim.primAlgorithmList();
            prim.printResultFromList();
            _getch();
            mstMenu();
        default:
            std::cout << "Nieprawidlowy zakres, sprobuj jeszcze raz:" << std::endl;
            break;
        }
    }
}