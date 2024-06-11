#include "UserMenu.h"
#include <iostream>
#include <conio.h>

#include <Windows.h>
#include <fstream>


void UserMenu::mainMenu()
{
    int userChoiceInput;
    // menu glowne
    std::cout << "Witaj w programie. Aby wybrac opcje wpisz odpowiadajaca cyfre i zatwierdz enter:" << std::endl;
    std::cout << "0 - Wyjscie z programu" << std::endl;
    std::cout << "1 - Metoda Brute Force" << std::endl;
    std::cout << "2 - Metoda Programowania dynamicznego" << std::endl;
    std::cout << "3 - Branch and Bound" << std::endl;
    std::cout << "4 - Branch and Bound BFS" << std::endl;
    std::cout << "5 - Testy" << std::endl;

    while (true) {
        std::cin >> userChoiceInput;
        switch (userChoiceInput) {
        case 0:
            exit(3);
            break;
        case 1:
            bruteForceMenu();
            break;
        case 2:
            dynamicProgrammingMenu();
            break;

        case 3: 
            branchAndBoundMenu();
            break;
        case 4:
            branchAndBoundDFSMenu();
            break;
        case 5:
            Tests();
            break;
        default:
            std::cout << "Nieprawidlowy zakres, sprobuj jeszcze raz:" << std::endl;
            break;
        }
    }
}

void UserMenu::bruteForceMenu()
{
    int userListMenuInput;
    system("cls");
    std::cout << "Jestes wlasnie w Brute Force menu! Lista instrukcji:" << std::endl;
    std::cout << "0 - Powrot do glownego menu" << std::endl;
    std::cout << "1 - Wczytaj z pliku" << std::endl;
    std::cout << "2 - Wygeneruj losowo" << std::endl;
    std::cout << "3 - Wyswietl dane" << std::endl;
    std::cout << "4 - Brute Force" << std::endl;

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
            std::string fileName;
            std::cout << "Podaj nazwe pliku:" << std::endl;
            std::cin >> fileName;
            bruteForce.createFromFile(fileName);
            bruteForce.printMatrix();
            _getch();
            bruteForceMenu();
            break;
        }

        case 2:
            int size;
            std::cout << "Podaj rozmiar:" << std::endl;
            std::cin >> size;
            bruteForce.generateRandomMatrix(size);
            bruteForce.printMatrix();
            _getch();
            bruteForceMenu();
            break;

        case 3:
            bruteForce.printMatrix();
            _getch();
            bruteForceMenu();
            break;

        case 4:
            LARGE_INTEGER frequency;
            LARGE_INTEGER startTime;
            LARGE_INTEGER endTime;
            elapsedTime = 0;

            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&startTime);

            bruteForce.bruteForce(0);

            QueryPerformanceCounter(&endTime);
            elapsedTime += static_cast<double>(endTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;
            //elapsedTime = elapsedTime * 1000;
 
            bruteForce.printResult();
            std::cout << std::endl << "Czas: " << elapsedTime << " s";
            _getch();
            bruteForceMenu();

            break;
        default:
            std::cout << "Nieprawidlowy zakres, sprobuj jeszcze raz:" << std::endl;
            break;
        }
    }
}

void UserMenu::dynamicProgrammingMenu()
{
    int userListMenuInput;
    system("cls");
    std::cout << "Jestes wlasnie w Programowanie Dynamiczne menu! Lista instrukcji:" << std::endl;
    std::cout << "0 - Powrot do glownego menu" << std::endl;
    std::cout << "1 - Wczytaj z pliku" << std::endl;
    std::cout << "2 - Wygeneruj losowo" << std::endl;
    std::cout << "3 - Wyswietl dane" << std::endl;
    std::cout << "4 - Programowanie dynamiczne" << std::endl;

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
            std::string fileName;
            std::cout << "Podaj nazwe pliku:" << std::endl;
            std::cin >> fileName;
            dynamicProgramming.createFromFile(fileName);
            dynamicProgramming.printMatrix();
            _getch();
            dynamicProgrammingMenu();
            break;
        }

        case 2:
            int size;
            std::cout << "Podaj rozmiar:" << std::endl;
            std::cin >> size;
            dynamicProgramming.generateRandomMatrix(size);
            dynamicProgramming.printMatrix();
            _getch();
            dynamicProgrammingMenu();
            break;

        case 3:
            
            dynamicProgramming.printMatrix();
            _getch();
            dynamicProgrammingMenu();
            break;

        case 4:
            LARGE_INTEGER frequency;
            LARGE_INTEGER startTime;
            LARGE_INTEGER endTime;
            elapsedTime = 0;

            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&startTime);

            dynamicProgramming.dynamicProgramming();

            QueryPerformanceCounter(&endTime);
            elapsedTime += static_cast<double>(endTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;
            //elapsedTime = elapsedTime * 1000;
            dynamicProgramming.printResult();
            std::cout << std::endl << "Czas: " << elapsedTime << " s";
            _getch();
            dynamicProgrammingMenu();

            break;
        default:
            std::cout << "Nieprawidlowy zakres, sprobuj jeszcze raz:" << std::endl;
            break;
        }
    }
}

void UserMenu::branchAndBoundMenu()
{
    int userListMenuInput;
    system("cls");
    std::cout << "Jestes wlasnie w Branch and Bound menu! Lista instrukcji:" << std::endl;
    std::cout << "0 - Powrot do glownego menu" << std::endl;
    std::cout << "1 - Wczytaj z pliku" << std::endl;
    std::cout << "2 - Wygeneruj losowo" << std::endl;
    std::cout << "3 - Wyswietl dane" << std::endl;
    std::cout << "4 - Branch and Bound" << std::endl;

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
            std::string fileName;
            std::cout << "Podaj nazwe pliku:" << std::endl;
            std::cin >> fileName;
            branchAndBound.createFromFile(fileName);
            branchAndBound.printMatrix();
            _getch();
            branchAndBoundMenu();
            break;
        }

        case 2:
            int size;
            std::cout << "Podaj rozmiar:" << std::endl;
            std::cin >> size;
            branchAndBound.generateRandomMatrix(size);
            branchAndBound.printMatrix();
            _getch();
            branchAndBoundMenu();
            break;

        case 3:
            branchAndBound.printMatrix();
            _getch();
            branchAndBoundMenu();
            break;

        case 4:
            LARGE_INTEGER frequency;
            LARGE_INTEGER startTime;
            LARGE_INTEGER endTime;
            elapsedTime = 0;

            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&startTime);

            int cost;

            cost = branchAndBound.branchAndBoundAlgorithm();

            QueryPerformanceCounter(&endTime);
            elapsedTime += static_cast<double>(endTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;
            //elapsedTime = elapsedTime * 1000;

            branchAndBound.printResult();
            std::cout << std::endl << "Czas: " << elapsedTime << " s";
            _getch();
            branchAndBoundMenu();

            break;

        default:
            std::cout << "Nieprawidlowy zakres, sprobuj jeszcze raz:" << std::endl;
            break;
        }
    }
}

void UserMenu::branchAndBoundDFSMenu()
{
    int userListMenuInput;
    system("cls");
    std::cout << "Jestes wlasnie w Branch and Bound DFS menu! Lista instrukcji:" << std::endl;
    std::cout << "0 - Powrot do glownego menu" << std::endl;
    std::cout << "1 - Wczytaj z pliku" << std::endl;
    std::cout << "2 - Wygeneruj losowo" << std::endl;
    std::cout << "3 - Wyswietl dane" << std::endl;
    std::cout << "4 - Branch and Bound DFS" << std::endl;

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
            std::string fileName;
            std::cout << "Podaj nazwe pliku:" << std::endl;
            std::cin >> fileName;
            branchAndBoundDFS.createFromFile(fileName);
            branchAndBoundDFS.printMatrix();
            _getch();
            branchAndBoundDFSMenu();
            break;
        }

        case 2:
            int size;
            std::cout << "Podaj rozmiar:" << std::endl;
            std::cin >> size;
            branchAndBoundDFS.generateRandomMatrix(size);
            branchAndBoundDFS.printMatrix();
            _getch();
            branchAndBoundDFSMenu();
            break;

        case 3:
            branchAndBoundDFS.printMatrix();
            _getch();
            branchAndBoundDFSMenu();
            break;

        case 4:
            LARGE_INTEGER frequency;
            LARGE_INTEGER startTime;
            LARGE_INTEGER endTime;
            elapsedTime = 0;

            QueryPerformanceFrequency(&frequency);
            QueryPerformanceCounter(&startTime);

            int cost;

            cost = branchAndBoundDFS.branchAndBoundAlgorithm();

            QueryPerformanceCounter(&endTime);
            elapsedTime += static_cast<double>(endTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;
            //elapsedTime = elapsedTime * 1000;

            //std::cout << std::endl << "Najkrotsza sciezka: " << cost;
            branchAndBoundDFS.printResult();
            std::cout << std::endl << "Czas: " << elapsedTime << " s";
            _getch();
            branchAndBoundDFSMenu();

            break;

        default:
            std::cout << "Nieprawidlowy zakres, sprobuj jeszcze raz:" << std::endl;
            break;
        }
    }
}

void UserMenu::Tests()
{
    LARGE_INTEGER frequency;
    LARGE_INTEGER startTime;
    LARGE_INTEGER endTime;
    double elapsedTime = 0;
    double elapsedTimeWhole = 0;
    LARGE_INTEGER startTimeWhole;
    LARGE_INTEGER endTimeWhole;

    std::setlocale(LC_ALL, "");

    std::ofstream myFile("wyniki-pomiary-PEA-5.csv");

    QueryPerformanceFrequency(&frequency);
    int currentNumberOfVertex, currentDensity;

    QueryPerformanceCounter(&startTimeWhole);
    int tabOfVertexNumber[7] = {5,6,7,8,9,10,11};
    myFile << "Wyniki Brute Force" << "\n";
    //bruteforce
    /*
    for (int k = 0; k < 7; k++) {
        currentNumberOfVertex = tabOfVertexNumber[k];

        myFile << currentNumberOfVertex << ";";
        elapsedTime = 0;
        system("cls");
        std::cout << "brute force - " << "Aktualny rozmiar: " << currentNumberOfVertex;
        for (int i = 0; i < 100; i++) {

            bruteForce.generateRandomMatrix(currentNumberOfVertex);

            QueryPerformanceCounter(&startTime);

            bruteForce.bruteForceAlgorithmRecursion(0);

            QueryPerformanceCounter(&endTime);
            elapsedTime += static_cast<double>(endTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;

        }
        elapsedTime = elapsedTime / 50;
        elapsedTime = elapsedTime * 1000;
        myFile << replaceDotWithComma(elapsedTime) << ";";

        myFile << "\n";
    }
    elapsedTime = 0;
    int tabOfVertexNumber2[7] = {8,10, 12,15,18,20,22};
    myFile << "Wyniki dyna" << "\n";
    for (int k = 0; k < 7; k++) {
        currentNumberOfVertex = tabOfVertexNumber2[k];

        myFile << currentNumberOfVertex << ";";
        elapsedTime = 0;
        system("cls");
        std::cout << "dynamiczne " << "Aktualny rozmiar: " << currentNumberOfVertex;
        for (int i = 0; i < 100; i++) {

            dynamicProgramming.generateRandomMatrix(currentNumberOfVertex);

            QueryPerformanceCounter(&startTime);

            dynamicProgramming.dynamicProgramming();

            QueryPerformanceCounter(&endTime);
            elapsedTime += static_cast<double>(endTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;

        }
        elapsedTime = elapsedTime / 50;
        elapsedTime = elapsedTime * 1000;
        myFile << replaceDotWithComma(elapsedTime) << ";";

        myFile << "\n";
    }
    
    elapsedTime = 0;
    int tabOfVertexNumber3[7] = { 8,10, 15,18,21,25,27 };
    myFile << "Wyniki bandb" << "\n";
    for (int k = 0; k < 7; k++) {
        currentNumberOfVertex = tabOfVertexNumber3[k];

        myFile << currentNumberOfVertex << ";";
        elapsedTime = 0;
        system("cls");
        std::cout << " B&B " << "Aktualny rozmiar: " << currentNumberOfVertex;
        for (int i = 0; i < 100; i++) {

            branchAndBound.generateRandomMatrix(currentNumberOfVertex);

            QueryPerformanceCounter(&startTime);

            branchAndBound.branchAndBoundAlgorithm();

            QueryPerformanceCounter(&endTime);
            elapsedTime += static_cast<double>(endTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;

        }
        elapsedTime = elapsedTime / 50;
        elapsedTime = elapsedTime * 1000;
        myFile << replaceDotWithComma(elapsedTime) << ";";

        myFile << "\n";
    }
    */
    elapsedTime = 0;
    int tabOfVertexNumber4[7] = { 8,10, 12,15,18,20,23 };
    myFile << "Wyniki bb dfs" << "\n";
    for (int k = 0; k < 1; k++) {
        currentNumberOfVertex = 25;

        myFile << currentNumberOfVertex << ";";
        elapsedTime = 0;
        system("cls");
        std::cout << " B&B DFS " << "Aktualny rozmiar: " << currentNumberOfVertex;
        for (int i = 0; i < 100; i++) {

            branchAndBoundDFS.generateRandomMatrix(currentNumberOfVertex);

            QueryPerformanceCounter(&startTime);

            branchAndBoundDFS.branchAndBoundAlgorithm();

            QueryPerformanceCounter(&endTime);
            elapsedTime += static_cast<double>(endTime.QuadPart - startTime.QuadPart) / frequency.QuadPart;

        }
        elapsedTime = elapsedTime / 50;
        elapsedTime = elapsedTime * 1000;
        myFile << replaceDotWithComma(elapsedTime) << ";";

        myFile << "\n";
    }
}

std::string UserMenu::replaceDotWithComma(double value)
{
    std::string valueStr = std::to_string(value);
    for (char& c : valueStr) {
        if (c == '.') {
            c = ',';
        }
    }
    return valueStr;
}

