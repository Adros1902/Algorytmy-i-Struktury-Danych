#include "UserMenu.h"
#include <iostream>
#include <conio.h>
#include <fstream>

void UserMenu::mainMenu()
{
    int userChoiceInput;
    // menu glowne
    system("cls");
    std::cout << "Witaj w programie. Aby wybrac opcje wpisz odpowiadajaca cyfre i zatwierdz enter:" << std::endl;
    std::cout << "0 - Wyjscie z programu" << std::endl;
    std::cout << "1 - Wczytanie danych z pliku" << std::endl;
    std::cout << "2 - Kryterium stopu" << std::endl;
    std::cout << "3 - Tabu Search" << std::endl;
    std::cout << "4 - Wspolczynnik zmiany temperatury" << std::endl;
    std::cout << "5 - Simulated Annealing" << std::endl;
    std::cout << "6 - Zapis sciezki SA do txt" << std::endl;
    std::cout << "7 - Zapis sciezki TS do txt" << std::endl;
    std::cout << "8 - Wczytanie ciezki z txt" << std::endl;
    std::cout << "9 - Testy" << std::endl;
    //std::string fileName;
    
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
            tabuSearch.createFromFile(fileName);
            simulatedAnnealing.createFromFile(fileName);
            _getch();
            mainMenu();
            break;
        case 2:
            std::cout << "Podaj kryterium stopu:" << std::endl;
            int tempTime;
            std::cin >> tempTime;
            tabuSearch.stopTime = tempTime;
            simulatedAnnealing.stopTime = tempTime;
            _getch();
            mainMenu();
            break;
        case 3:
            tabuSearch.tabuSearch();
            tabuSearch.printResult();
            _getch();
            mainMenu();
            break;
        case 4:
            std::cout << "Podaj wspolczynnik zmiany temperatury:" << std::endl;
            double tempCoefficient;
            std::cin >> tempCoefficient;
            simulatedAnnealing.temperatureCoefficient = tempCoefficient;
            _getch();
            mainMenu();
            break;
        case 5:
            simulatedAnnealing.simulatedAnnealing();
            simulatedAnnealing.printResult();
            _getch();
            mainMenu();
            break;

        case 6:
            tempText = "SA_";
            tempText += fileName;
            tempText.substr(0, tempText.size() - 4);
            tempText += ".txt";

            simulatedAnnealing.saveToFile(tempText);
            mainMenu();
            break;

        case 7:
            tempText = "TS_";
            tempText += fileName;
            tempText.substr(0, tempText.size() - 4);
            tempText += ".txt";

            tabuSearch.saveToFile(tempText);
            mainMenu();
            break;
        case 8:
            std::cout << "Wprowadz nazwe pliku ze sciezka: " << std::endl;
            std::cin >> fileNamePath;
            std::cout << "Wprowadz nazwe pliku zrodlowego";
            std::cin >> fileNameSource;
            inOut.calculateCostFromFile(fileNamePath, fileNameSource);
            _getch();
            mainMenu();
            break;
        case 9:
            tests();
            mainMenu();
            break;
        default:
            std::cout << "Nieprawidlowy zakres, sprobuj jeszcze raz:" << std::endl;
            break;
        }
    }
}

void UserMenu::tests()
{
    //testy dla ftv55 0.99
    simulatedAnnealing.stopTime = 120;
    simulatedAnnealing.temperatureCoefficient = 0.99;
    simulatedAnnealing.createFromFile("ftv55.xml");

   // 
    std::ofstream myFile("Wyniki_PEA2_SA_POP2termin.csv");
    myFile << "current file: " << ";" << "ftv55" << "\n";
    myFile << "temp coeficient" << ";" << simulatedAnnealing.temperatureCoefficient << "\n";
    myFile << "numer iteracji" << ";" << "czas znalezienia" << ";" << "wynik" << "\n";

    for (int i = 0; i < 10; i++) {
        system("cls");
        std::string textToFile = "ftv55_";
        textToFile += std::to_string(i);
        textToFile += "_tempCoe_";
        textToFile += std::to_string(simulatedAnnealing.temperatureCoefficient);
        textToFile += ".txt";

        std::cout << "Current file" << textToFile;

        simulatedAnnealing.simulatedAnnealing();
        myFile << i << ";";
        myFile << simulatedAnnealing.bestPathTime << ";";
        myFile << simulatedAnnealing.bestPathCost << ";";
        myFile << simulatedAnnealing.currentTemp << "\n";
        simulatedAnnealing.saveToFile(textToFile);

        std::string fileName = "SA_ftv55_";
        fileName += std::to_string(i);
        fileName += "_tempCoe_";
        fileName += std::to_string(simulatedAnnealing.temperatureCoefficient);
        fileName += ".csv";

        std::ofstream outputFile(fileName);

        if (outputFile.is_open()) {
            for (int i = 0; i < tabuSearch.bestFoundTimes.size(); i++)
            {
                outputFile << tabuSearch.bestFoundTimes[i][0] << ";" << tabuSearch.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }


    simulatedAnnealing.temperatureCoefficient = 0.999;
    myFile << "current file: " << ";" << "ftv55" << "\n";
    myFile << "temp coeficient" << ";" << simulatedAnnealing.temperatureCoefficient << "\n";
    for (int i = 0; i < 10; i++) {
        system("cls");
        std::string textToFile = "ftv55_";
        textToFile += std::to_string(i);
        textToFile += "_tempCoe_";
        textToFile += std::to_string(simulatedAnnealing.temperatureCoefficient);
        textToFile += ".txt";

        std::cout << "Current file" << textToFile;

        simulatedAnnealing.simulatedAnnealing();
        myFile << i << ";";
        myFile << simulatedAnnealing.bestPathTime << ";";
        myFile << simulatedAnnealing.bestPathCost << ";";
        myFile << simulatedAnnealing.currentTemp << "\n";

        simulatedAnnealing.saveToFile(textToFile);

        std::string fileName = "SA_ftv55_";
        fileName += std::to_string(i);
        fileName += "_tempCoe_";
        fileName += std::to_string(simulatedAnnealing.temperatureCoefficient);
        fileName += ".csv";

        std::ofstream outputFile(fileName);

        if (outputFile.is_open()) {
            for (int i = 0; i < tabuSearch.bestFoundTimes.size(); i++)
            {
                outputFile << tabuSearch.bestFoundTimes[i][0] << ";" << tabuSearch.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }


    simulatedAnnealing.temperatureCoefficient = 0.9995;
    myFile << "current file: " << ";" << "ftv55" << "\n";
    myFile << "temp coeficient" << ";" << simulatedAnnealing.temperatureCoefficient << "\n";
    for (int i = 0; i < 10; i++) {
        system("cls");
        std::string textToFile = "ftv55_";
        textToFile += std::to_string(i);
        textToFile += "_tempCoe_";
        textToFile += std::to_string(simulatedAnnealing.temperatureCoefficient);
        textToFile += ".txt";

        std::cout << "Current file" << textToFile;

        simulatedAnnealing.simulatedAnnealing();
        myFile << i << ";";
        myFile << simulatedAnnealing.bestPathTime << ";";
        myFile << simulatedAnnealing.bestPathCost << ";";
        myFile << simulatedAnnealing.currentTemp << "\n";
        simulatedAnnealing.saveToFile(textToFile);

        std::string fileName = "SA_ftv55_";
        fileName += std::to_string(i);
        fileName += "_tempCoe_";
        fileName += std::to_string(simulatedAnnealing.temperatureCoefficient);
        fileName += ".csv";

        std::ofstream outputFile(fileName);

        if (outputFile.is_open()) {
            for (int i = 0; i < tabuSearch.bestFoundTimes.size(); i++)
            {
                outputFile << tabuSearch.bestFoundTimes[i][0] << ";" << tabuSearch.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    
    //ftv170
    simulatedAnnealing.createFromFile("ftv170.xml");
    simulatedAnnealing.stopTime = 240;
    simulatedAnnealing.temperatureCoefficient = 0.99;
    myFile << "current file: " << ";" << "ftv170" << "\n";
    myFile << "temp coeficient" << ";" << simulatedAnnealing.temperatureCoefficient << "\n";
    for (int i = 0; i < 10; i++) {
        system("cls");
        std::string textToFile = "1111ftv170_";
        textToFile += std::to_string(i);
        textToFile += "_tempCoe_";
        textToFile += std::to_string(simulatedAnnealing.temperatureCoefficient);
        textToFile += ".txt";

        std::cout << "Current file" << textToFile;

        simulatedAnnealing.simulatedAnnealing();
        myFile << i << ";";
        myFile << simulatedAnnealing.bestPathTime << ";";
        myFile << simulatedAnnealing.bestPathCost << ";";
        myFile << simulatedAnnealing.currentTemp << "\n";
        simulatedAnnealing.saveToFile(textToFile);

        std::string fileName = "SA_ftv170_";
        fileName += std::to_string(i);
        fileName += "_tempCoe_";
        fileName += std::to_string(simulatedAnnealing.temperatureCoefficient);
        fileName += ".csv";

        std::ofstream outputFile(fileName);

        if (outputFile.is_open()) {
            for (int i = 0; i < tabuSearch.bestFoundTimes.size(); i++)
            {
                outputFile << tabuSearch.bestFoundTimes[i][0] << ";" << tabuSearch.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }
    
    simulatedAnnealing.temperatureCoefficient = 0.999;
    myFile << "current file: " << ";" << "ftv170" << "\n";
    myFile << "temp coeficient" << ";" << simulatedAnnealing.temperatureCoefficient << "\n";
    for (int i = 0; i < 3; i++) {
        system("cls");
        std::string textToFile = "ftv170_";
        textToFile += std::to_string(i);
        textToFile += "_tempCoe_";
        textToFile += std::to_string(simulatedAnnealing.temperatureCoefficient);
        textToFile += ".txt";

        std::cout << "Current file" << textToFile;

        simulatedAnnealing.simulatedAnnealing();
        myFile << i << ";";
        myFile << simulatedAnnealing.bestPathTime << ";";
        myFile << simulatedAnnealing.bestPathCost << ";";
        myFile << simulatedAnnealing.currentTemp << "\n";
        simulatedAnnealing.saveToFile(textToFile);

        std::string fileName = "SA_ftv170_";
        fileName += std::to_string(i);
        fileName += "_tempCoe_";
        fileName += std::to_string(simulatedAnnealing.temperatureCoefficient);
        fileName += ".csv";

        std::ofstream outputFile(fileName);

        if (outputFile.is_open()) {
            for (int i = 0; i < tabuSearch.bestFoundTimes.size(); i++)
            {
                outputFile << tabuSearch.bestFoundTimes[i][0] << ";" << tabuSearch.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }


    simulatedAnnealing.temperatureCoefficient = 0.9995;
    myFile << "current file: " << ";" << "ftv170" << "\n";
    myFile << "temp coeficient" << ";" << simulatedAnnealing.temperatureCoefficient << "\n";
    for (int i = 0; i < 3; i++) {
        system("cls");
        std::string textToFile = "ftv170_";
        textToFile += std::to_string(i);
        textToFile += "_tempCoe_";
        textToFile += std::to_string(simulatedAnnealing.temperatureCoefficient);
        textToFile += ".txt";

        std::cout << "Current file" << textToFile;

        simulatedAnnealing.simulatedAnnealing();
        myFile << i << ";";
        myFile << simulatedAnnealing.bestPathTime << ";";
        myFile << simulatedAnnealing.bestPathCost << ";";
        myFile << simulatedAnnealing.currentTemp << "\n";
        simulatedAnnealing.saveToFile(textToFile);

        std::string fileName = "SA_ftv170_";
        fileName += std::to_string(i);
        fileName += "_tempCoe_";
        fileName += std::to_string(simulatedAnnealing.temperatureCoefficient);
        fileName += ".csv";

        std::ofstream outputFile(fileName);

        if (outputFile.is_open()) {
            for (int i = 0; i < tabuSearch.bestFoundTimes.size(); i++)
            {
                outputFile << tabuSearch.bestFoundTimes[i][0] << ";" << tabuSearch.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    // TRZECI PLIK
    simulatedAnnealing.createFromFile("rbg358.xml");
    simulatedAnnealing.stopTime = 360;
    simulatedAnnealing.temperatureCoefficient = 0.99;
    myFile << "current file: " << ";" << "rbg358" << "\n";
    myFile << "temp coeficient" << ";" << simulatedAnnealing.temperatureCoefficient << "\n";
    for (int i = 0; i < 3; i++) {
        system("cls");
        std::string textToFile = "rbg358_";
        textToFile += std::to_string(i);
        textToFile += "_tempCoe_";
        textToFile += std::to_string(simulatedAnnealing.temperatureCoefficient);
        textToFile += ".txt";

        std::cout << "Current file" << textToFile;

        simulatedAnnealing.simulatedAnnealing();
        myFile << i << ";";
        myFile << simulatedAnnealing.bestPathTime << ";";
        myFile << simulatedAnnealing.bestPathCost << ";";
        myFile << simulatedAnnealing.currentTemp << "\n";
        simulatedAnnealing.saveToFile(textToFile);

        std::string fileName = "SA_rbg358_";
        fileName += std::to_string(i);
        fileName += "_tempCoe_";
        fileName += std::to_string(simulatedAnnealing.temperatureCoefficient);
        fileName += ".csv";

        std::ofstream outputFile(fileName);

        if (outputFile.is_open()) {
            for (int i = 0; i < tabuSearch.bestFoundTimes.size(); i++)
            {
                outputFile << tabuSearch.bestFoundTimes[i][0] << ";" << tabuSearch.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }


    simulatedAnnealing.temperatureCoefficient = 0.999;
    myFile << "current file: " << ";" << "rbg358" << "\n";
    myFile << "temp coeficient" << ";" << simulatedAnnealing.temperatureCoefficient << "\n";
    for (int i = 0; i < 3; i++) {
        system("cls");
        std::string textToFile = "rbg358_";
        textToFile += std::to_string(i);
        textToFile += "_tempCoe_";
        textToFile += std::to_string(simulatedAnnealing.temperatureCoefficient);
        textToFile += ".txt";

        std::cout << "Current file" << textToFile;

        simulatedAnnealing.simulatedAnnealing();
        myFile << i << ";";
        myFile << simulatedAnnealing.bestPathTime << ";";
        myFile << simulatedAnnealing.bestPathCost << ";";
        myFile << simulatedAnnealing.currentTemp << "\n";
        simulatedAnnealing.saveToFile(textToFile);

        std::string fileName = "SA_rbg358_";
        fileName += std::to_string(i);
        fileName += "_tempCoe_";
        fileName += std::to_string(simulatedAnnealing.temperatureCoefficient);
        fileName += ".csv";

        std::ofstream outputFile(fileName);

        if (outputFile.is_open()) {
            for (int i = 0; i < tabuSearch.bestFoundTimes.size(); i++)
            {
                outputFile << tabuSearch.bestFoundTimes[i][0] << ";" << tabuSearch.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }
    }

    simulatedAnnealing.temperatureCoefficient = 0.9995;
    myFile << "current file: " << ";" << "rbg358" << "\n";
    myFile << "temp coeficient" << ";" << simulatedAnnealing.temperatureCoefficient << "\n";
    for (int i = 0; i < 3; i++) {
        system("cls");
        std::string textToFile = "rbg358_";
        textToFile += std::to_string(i);
        textToFile += "_tempCoe_";
        textToFile += std::to_string(simulatedAnnealing.temperatureCoefficient);
        textToFile += ".txt";

        std::cout << "Current file" << textToFile;

        simulatedAnnealing.simulatedAnnealing();
        myFile << i << ";";
        myFile << simulatedAnnealing.bestPathTime << ";";
        myFile << simulatedAnnealing.bestPathCost << ";";
        myFile << simulatedAnnealing.currentTemp << "\n";
        simulatedAnnealing.saveToFile(textToFile);

        std::string fileName = "SA_rbg358_";
        fileName += std::to_string(i);
        fileName += "_tempCoe_";
        fileName += std::to_string(simulatedAnnealing.temperatureCoefficient);
        fileName += ".csv";

        std::ofstream outputFile(fileName);

        if (outputFile.is_open()) {
            for (int i = 0; i < tabuSearch.bestFoundTimes.size(); i++)
            {
                outputFile << tabuSearch.bestFoundTimes[i][0] << ";" << tabuSearch.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }

    }
    //std::ofstream myFile("Wyniki_PEA2_TS.csv");
    myFile << "TABU SEARCH" << "\n";
    myFile << "current file: " << ";" << "ftv55" << "\n";
    myFile << "temp coeficient" << ";" << simulatedAnnealing.temperatureCoefficient << "\n";
    myFile << "numer iteracji" << ";" << "czas znalezienia" << ";" << "wynik" << "\n";


    tabuSearch.createFromFile("ftv55.xml");
    tabuSearch.stopTime = 120;
    for (int i = 0; i < 10; i++) {
        system("cls");
        std::string textToFile = "TS_ftv55_";
        textToFile += std::to_string(i);
        textToFile += ".txt";

        std::cout << "Current file" << textToFile;

        tabuSearch.tabuSearch();
        myFile << i << ";";
        myFile << tabuSearch.bestPathTime << ";";
        myFile << tabuSearch.bestPathCost << "\n";
        tabuSearch.saveToFile(textToFile);
    
        std::string fileName = "TS_ftv55_";
        fileName += std::to_string(i);
        fileName += ".csv";

        std::ofstream outputFile(fileName);

        if (outputFile.is_open()) {
            for (int i = 0; i < tabuSearch.bestFoundTimes.size(); i++)
            {
                outputFile << tabuSearch.bestFoundTimes[i][0] << ";" << tabuSearch.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }

    
    }

    tabuSearch.stopTime = 240;
    myFile << "current file: " << ";" << "ftv170" << "\n";
    tabuSearch.createFromFile("ftv170.xml");
    for (int i = 0; i < 10; i++) {
        system("cls");
        std::string textToFile = "TS_ftv170_";
        textToFile += std::to_string(i);
        textToFile += ".txt";

        std::cout << "Current file" << textToFile;

        tabuSearch.tabuSearch();
        myFile << i << ";";
        myFile << tabuSearch.bestPathTime << ";";
        myFile << tabuSearch.bestPathCost << "\n";
        tabuSearch.saveToFile(textToFile);

        std::string fileName = "TS_ftv170_";
        fileName += std::to_string(i);
        fileName += ".csv";

        std::ofstream outputFile(fileName);

        if (outputFile.is_open()) {
            for (int i = 0; i < tabuSearch.bestFoundTimes.size(); i++)
            {
                outputFile << tabuSearch.bestFoundTimes[i][0] << ";" << tabuSearch.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }

    }

    tabuSearch.stopTime = 360;
    myFile << "current file: " << ";" << "rbg358" << "\n";
    tabuSearch.createFromFile("rbg358.xml");
    for (int i = 0; i < 10; i++) {
        system("cls");
        std::string textToFile = "TS_rbg358_";
        textToFile += std::to_string(i);
        textToFile += ".txt";

        std::cout << "Current file" << textToFile;

        tabuSearch.tabuSearch();
        myFile << i << ";";
        myFile << tabuSearch.bestPathTime << ";";
        myFile << tabuSearch.bestPathCost << "\n";
        tabuSearch.saveToFile(textToFile);

        std::string fileName = "TS_rbg358_";
        fileName += std::to_string(i);
        fileName += ".csv";

        std::ofstream outputFile(fileName);

        if (outputFile.is_open()) {
            for (int i = 0; i < tabuSearch.bestFoundTimes.size(); i++)
            {
                outputFile << tabuSearch.bestFoundTimes[i][0] << ";" << tabuSearch.bestFoundTimes[i][1] << "\n";
            }
            outputFile.close();
        }

    }

        myFile.close();


        std::cout << "KONIEEEEEEEEEEEEEEEEEEEEEEEEEEEEEC";
        std::cout << "end";
        _getch();
}
