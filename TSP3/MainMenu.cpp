#include "MainMenu.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include "MyInOut.h"

void MainMenu::mainMenu()
{
    int userChoiceInput;
    // menu glowne
    system("cls");
    std::cout << "Witaj w programie. Aby wybrac opcje wpisz odpowiadajaca cyfre i zatwierdz enter:" << std::endl;
    std::cout << "0 - Wyjscie z programu" << std::endl;
    std::cout << "1 - Wczytanie danych z pliku i wyswietlenie" << std::endl;
    std::cout << "2 - Kryterium stopu" << std::endl;
    std::cout << "3 - Wspolczynnik mutacji" << std::endl;
    std::cout << "4 - Wspolczynnik krzyzowania" << std::endl;
    std::cout << "5 - Wybor metody krzyzowania" << std::endl;
    std::cout << "6 - Wybor metody mutacji" << std::endl;
    std::cout << "7 - Wielkosc populacji" << std::endl;
    std::cout << "8 - Algorytm genetyczny" << std::endl;
    std::cout << "9 - Testy" << std::endl;


    std::string fileNamePath;
    std::string fileNameSource;
    std::string tempText;
    std::string fileName;
    while (true) {
        std::cin >> userChoiceInput;
        system("cls");


        switch (userChoiceInput) {
        case 0:
            exit(3);
            break;
        case 1:
            std::cin >> fileName;
            geneticAlgorithm.createFromFile(fileName);
            geneticAlgorithm.printMatrix();
            _getch();
            mainMenu();
            break;
        case 2:
            std::cout << "Podaj kryterium stopu:" << std::endl;
            int tempTime;
            std::cin >> tempTime;
            geneticAlgorithm.stopTime = tempTime;
            _getch();
            mainMenu();
            break;
        case 3:
            std::cout << "Podaj wspolczynnik mutacji" << std::endl;
            float tempMutation;
            std::cin >> tempMutation;
            geneticAlgorithm.mutationProb = tempMutation;
            _getch();
            mainMenu();
            break;
        case 4:
            std::cout << "Podaj wspolczynnik krzyzowania" << std::endl;
            float tempCross;
            std::cin >> tempCross;
            geneticAlgorithm.crossoverProb = tempCross;
            _getch();
            mainMenu();
            break;
        case 5:
            std::cout << "Wybierz metode krzyzowania:" << std::endl;
            std::cout << "0 - order crossover" << std::endl;
            std::cout << "1 - drugi sposob" << std::endl;
            int pickedCross;
            std::cin >> pickedCross;
            geneticAlgorithm.crossoverType = pickedCross;
            _getch();
            mainMenu();
            break;

        case 6:
            std::cout << "Wybierz metode mutacji:" << std::endl;
            std::cout << "0 - swap" << std::endl;
            std::cout << "1 - drugi sposob" << std::endl;
            int pickedMutation;
            std::cin >> pickedMutation;
            geneticAlgorithm.mutationType = pickedMutation;
            _getch();
            mainMenu();
            break;

        case 7:
            std::cout << "Podaj wielkosc populacji:" << std::endl;
            int size; 
            std::cin >> size;
            geneticAlgorithm.populationSize = size;
            _getch();
            mainMenu();
            break;
        case 8:
            geneticAlgorithm.geneticAlgorithm();
            std::cout << "Wynik: " << geneticAlgorithm.bestPathCost << std::endl;
            std::cout << "Sciezka:" << std::endl;
            for (int i = 0; i < geneticAlgorithm.bestPath.size(); i++)
            {
                std::cout << geneticAlgorithm.bestPath[i] << " ";
            }

            _getch();

            mainMenu();
            break;
        case 9:
            testy();
            _getch();
            mainMenu();

        default:
            std::cout << "Nieprawidlowy zakres, sprobuj jeszcze raz:" << std::endl;
            break;
        }
    }
}

void MainMenu::testy()
{
    /*
    //ftv47
    geneticAlgorithm.stopTime = 120;
    geneticAlgorithm.populationSize = 500;
    geneticAlgorithm.crossoverType = 0;
    geneticAlgorithm.mutationType = 0;
    geneticAlgorithm.createFromFile("ftv47.xml");

    std::ofstream myFile("Wyniki_PEA3.csv");
    myFile << "current file: " << ";" << "ftv55" << "\n";
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType <<"\n";
    myFile << "numer iteracji" << ";" << "czas znalezienia" << ";" << "wynik" << "\n";


    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv47_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverType = 1;
    geneticAlgorithm.mutationType = 0;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 0
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv47_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    geneticAlgorithm.crossoverType = 0;
    geneticAlgorithm.mutationType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 0, mut 1
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv47_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    geneticAlgorithm.crossoverType = 1;
    geneticAlgorithm.mutationType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 1
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv47_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    //POPULACJA 1000
    geneticAlgorithm.populationSize = 1000;
    geneticAlgorithm.crossoverType = 0;
    geneticAlgorithm.mutationType = 0;

    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv47_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverType = 1;
    geneticAlgorithm.mutationType = 0;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 0
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv47_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    geneticAlgorithm.crossoverType = 0;
    geneticAlgorithm.mutationType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 0, mut 1
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv47_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    geneticAlgorithm.crossoverType = 1;
    geneticAlgorithm.mutationType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 1
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv47_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    //populacja 2000


    geneticAlgorithm.populationSize = 2000;
    geneticAlgorithm.crossoverType = 0;
    geneticAlgorithm.mutationType = 0;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";

    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv47_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverType = 1;
    geneticAlgorithm.mutationType = 0;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 0
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv47_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    geneticAlgorithm.crossoverType = 0;
    geneticAlgorithm.mutationType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 0, mut 1
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv47_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    geneticAlgorithm.crossoverType = 1;
    geneticAlgorithm.mutationType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 1
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv47_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }












    //ftv170
    geneticAlgorithm.stopTime = 240;
    geneticAlgorithm.populationSize = 500;
    geneticAlgorithm.crossoverType = 0;
    geneticAlgorithm.mutationType = 0;
    geneticAlgorithm.createFromFile("ftv170.xml");

    myFile << "current file: " << ";" << "ftv170" << "\n";
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    myFile << "numer iteracji" << ";" << "czas znalezienia" << ";" << "wynik" << "\n";


    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv170_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverType = 1;
    geneticAlgorithm.mutationType = 0;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 0
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv170_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    geneticAlgorithm.crossoverType = 0;
    geneticAlgorithm.mutationType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 0, mut 1
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv170_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    geneticAlgorithm.crossoverType = 1;
    geneticAlgorithm.mutationType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 1
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv170_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    //POPULACJA 1000
    geneticAlgorithm.populationSize = 1000;
    geneticAlgorithm.crossoverType = 0;
    geneticAlgorithm.mutationType = 0;

    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv170_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverType = 1;
    geneticAlgorithm.mutationType = 0;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 0
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv170_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    geneticAlgorithm.crossoverType = 0;
    geneticAlgorithm.mutationType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 0, mut 1
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv170_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    geneticAlgorithm.crossoverType = 1;
    geneticAlgorithm.mutationType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 1
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv170_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    //populacja 2000


    geneticAlgorithm.populationSize = 2000;
    geneticAlgorithm.crossoverType = 0;
    geneticAlgorithm.mutationType = 0;

    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv170_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverType = 1;
    geneticAlgorithm.mutationType = 0;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 0
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv170_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    geneticAlgorithm.crossoverType = 0;
    geneticAlgorithm.mutationType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 0, mut 1
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv170_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    geneticAlgorithm.crossoverType = 1;
    geneticAlgorithm.mutationType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 1
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv170_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }






















    //rng403
    geneticAlgorithm.stopTime = 360;
    geneticAlgorithm.populationSize = 500;
    geneticAlgorithm.crossoverType = 0;
    geneticAlgorithm.mutationType = 0;
    geneticAlgorithm.createFromFile("rbg403.xml");

    myFile << "current file: " << ";" << "rbg407_" << "\n";
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    myFile << "numer iteracji" << ";" << "czas znalezienia" << ";" << "wynik" << "\n";


    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "rbg407_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverType = 1;
    geneticAlgorithm.mutationType = 0;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 0
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "rbg407_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    geneticAlgorithm.crossoverType = 0;
    geneticAlgorithm.mutationType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 0, mut 1
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "rbg407_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    geneticAlgorithm.crossoverType = 1;
    geneticAlgorithm.mutationType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 1
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "rbg407_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    //POPULACJA 1000
    geneticAlgorithm.populationSize = 1000;
    geneticAlgorithm.crossoverType = 0;
    geneticAlgorithm.mutationType = 0;

    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "rbg407_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverType = 1;
    geneticAlgorithm.mutationType = 0;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 0
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "rbg407_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    geneticAlgorithm.crossoverType = 0;
    geneticAlgorithm.mutationType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 0, mut 1
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "rbg407_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    geneticAlgorithm.crossoverType = 1;
    geneticAlgorithm.mutationType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 1
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "rbg407_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    //populacja 2000


    geneticAlgorithm.populationSize = 2000;
    geneticAlgorithm.crossoverType = 0;
    geneticAlgorithm.mutationType = 0;

    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "rbg407_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverType = 1;
    geneticAlgorithm.mutationType = 0;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 0
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "rbg407_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    geneticAlgorithm.crossoverType = 0;
    geneticAlgorithm.mutationType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 0, mut 1
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "rbg407_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    geneticAlgorithm.crossoverType = 1;
    geneticAlgorithm.mutationType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 1
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "rbg407_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }*/















    geneticAlgorithm.stopTime = 120;
    geneticAlgorithm.populationSize = 1000;
    geneticAlgorithm.crossoverType = 0;
    geneticAlgorithm.mutationType = 1;
    geneticAlgorithm.createFromFile("ftv47.xml");
    geneticAlgorithm.crossoverProb = 0.5;
    geneticAlgorithm.mutationProb = 0.01;
    std::ofstream myFile("Wyniki_PEA3_dodatkowe_wyniki_mut_test_cross0_teraztestowaniekrosa111111.csv");
    myFile << "current file: " << ";" << "ftv55" << "\n";
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    myFile << "numer iteracji" << ";" << "czas znalezienia" << ";" << "wynik" << "\n";


    for (int i = 1; i < 2; i++) {
        system("cls");
        std::string textToFile = "ftv47_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += "_______";
        textToFile += std::to_string(geneticAlgorithm.crossoverProb);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverProb = 0.7;
    geneticAlgorithm.crossoverType = 0;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 0
    for (int i = 1; i <2; i++) {
        system("cls");
        std::string textToFile = "ftv47_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += "_______";
        textToFile += std::to_string(geneticAlgorithm.crossoverProb);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverProb = 0.9;
    geneticAlgorithm.crossoverType = 0;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 0, mut 1
    for (int i = 1; i < 2; i++) {
        system("cls");
        std::string textToFile = "ftv47_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += "________";
        textToFile += std::to_string(geneticAlgorithm.crossoverProb);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverProb = 0.5;
    geneticAlgorithm.crossoverType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 1
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv47_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += "_______";
        textToFile += std::to_string(geneticAlgorithm.crossoverProb);
        textToFile += ".csv";
        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverProb = 0.7;
    geneticAlgorithm.crossoverType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 1
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv47_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += "_______";
        textToFile += std::to_string(geneticAlgorithm.crossoverProb);
        textToFile += ".csv";
        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverProb = 0.9;
    geneticAlgorithm.crossoverType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 1
    for (int i = 1; i <= 3; i++) {
        system("cls");
        std::string textToFile = "ftv47_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += "______";
        textToFile += std::to_string(geneticAlgorithm.crossoverProb);
        textToFile += ".csv";
        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }



//std::ofstream myFile("Wyniki_PEA3_dodatkowe_wyniki_mut_test_cross0_odFTV170.csv");

    geneticAlgorithm.stopTime = 240;
    geneticAlgorithm.populationSize = 1000;
    geneticAlgorithm.crossoverType = 0;
    geneticAlgorithm.mutationType = 1;
    geneticAlgorithm.createFromFile("ftv170.xml");
    geneticAlgorithm.crossoverProb = 0.5;
    geneticAlgorithm.mutationProb = 0.01;
    myFile << "current file: " << ";" << "ftv170" << "\n";
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    myFile << "numer iteracji" << ";" << "czas znalezienia" << ";" << "wynik" << "\n";


    for (int i = 1; i < 2; i++) {
        system("cls");
        std::string textToFile = "ftv170_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += "_______";
        textToFile += std::to_string(geneticAlgorithm.crossoverProb);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverProb = 0.7;
    geneticAlgorithm.crossoverType = 0;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 0
    for (int i = 1; i < 2; i++) {
        system("cls");
        std::string textToFile = "ftv170_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += "______";
        textToFile += std::to_string(geneticAlgorithm.crossoverProb);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverProb = 0.9;
    geneticAlgorithm.crossoverType = 0;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 0, mut 1
    for (int i = 1; i < 2; i++) {
        system("cls");
        std::string textToFile = "ftv170_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += "______";
        textToFile += std::to_string(geneticAlgorithm.crossoverProb);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverProb = 0.5;
    geneticAlgorithm.crossoverType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 1
    for (int i = 1; i <2; i++) {
        system("cls");
        std::string textToFile = "ftv170_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += "_______";
        textToFile += std::to_string(geneticAlgorithm.crossoverProb);
        textToFile += ".csv";
        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverProb = 0.7;
    geneticAlgorithm.crossoverType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 1
    for (int i = 1; i <2; i++) {
        system("cls");
        std::string textToFile = "ftv170_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += "_______";
        textToFile += std::to_string(geneticAlgorithm.crossoverProb);
        textToFile += ".csv";
        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverProb = 0.9;
    geneticAlgorithm.crossoverType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 1
    for (int i = 1; i <2; i++) {
        system("cls");
        std::string textToFile = "ftv170_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += "______";
        textToFile += std::to_string(geneticAlgorithm.crossoverProb);
        textToFile += ".csv";
        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }





    geneticAlgorithm.stopTime = 360;
    geneticAlgorithm.populationSize = 1000;
    geneticAlgorithm.crossoverType = 0;
    geneticAlgorithm.mutationType = 1;
    geneticAlgorithm.createFromFile("rbg403.xml");
    geneticAlgorithm.crossoverProb = 0.5;
    geneticAlgorithm.mutationProb = 0.01;
    myFile << "current file: " << ";" << "ftv170" << "\n";
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    myFile << "numer iteracji" << ";" << "czas znalezienia" << ";" << "wynik" << "\n";


    for (int i = 1; i < 2; i++) {
        system("cls");
        std::string textToFile = "rbg403_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += "_______";
        textToFile += std::to_string(geneticAlgorithm.crossoverProb);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverProb = 0.7;
    geneticAlgorithm.crossoverType = 0;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 0
    for (int i = 1; i < 2; i++) {
        system("cls");
        std::string textToFile = "rbg403_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += "______";
        textToFile += std::to_string(geneticAlgorithm.crossoverProb);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverProb = 0.9;
    geneticAlgorithm.crossoverType = 0;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 0, mut 1
    for (int i = 1; i < 2; i++) {
        system("cls");
        std::string textToFile = "rbg403_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += "_______";
        textToFile += std::to_string(geneticAlgorithm.crossoverProb);
        textToFile += ".csv";

        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverProb = 0.5;
    geneticAlgorithm.crossoverType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 1
    for (int i = 1; i <2; i++) {
        system("cls");
        std::string textToFile = "rbg403_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += "_______";
        textToFile += std::to_string(geneticAlgorithm.crossoverProb);
        textToFile += ".csv";
        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverProb = 0.7;
    geneticAlgorithm.crossoverType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 1
    for (int i = 1; i <2; i++) {
        system("cls");
        std::string textToFile = "rbg403_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += "_______";
        textToFile += std::to_string(geneticAlgorithm.crossoverProb);
        textToFile += ".csv";
        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    geneticAlgorithm.crossoverProb = 0.9;
    geneticAlgorithm.crossoverType = 1;
    myFile << "pop size" << ";" << geneticAlgorithm.populationSize << ";" << "mutType: " << geneticAlgorithm.crossoverType << ";" << "crossType" << geneticAlgorithm.crossoverType << "\n";
    //pop 500 cross 1, mut 1
    for (int i = 1; i <2; i++) {
        system("cls");
        std::string textToFile = "rbg403_";
        textToFile += std::to_string(i);
        textToFile += "pop_";
        textToFile += std::to_string(geneticAlgorithm.populationSize);
        textToFile += "_cr_";
        textToFile += std::to_string(geneticAlgorithm.crossoverType);
        textToFile += "_mut_";
        textToFile += std::to_string(geneticAlgorithm.mutationType);
        textToFile += "______";
        textToFile += std::to_string(geneticAlgorithm.crossoverProb);
        textToFile += ".csv";
        std::cout << "Current file" << textToFile;

        geneticAlgorithm.geneticAlgorithm();
        myFile << i << ";";
        myFile << geneticAlgorithm.bestPathTime << ";";
        myFile << geneticAlgorithm.bestPathCost << "\n";

        std::ofstream outputFile(textToFile);

        if (outputFile.is_open()) {
            for (int i = 0; i < geneticAlgorithm.bestFoundTimes.size(); i++)
            {
                outputFile << geneticAlgorithm.bestFoundTimes[i][0] << ";" << geneticAlgorithm.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

}




