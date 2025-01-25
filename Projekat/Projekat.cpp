#include "Sudoku9.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    Sudoku9 sudoku;
    int choice;
    bool gameStarted = false;
    std::string filename;

    while (true) {
        if (!gameStarted) {
            std::cout << "SUDOKU\n";
            std::cout << "--------------------------------------\n";
            std::cout << "1. Ucitaj Sudoku zagonetku iz datoteke\n";
            std::cout << "2. Generisi novu Sudoku zagonetku\n";
            std::cout << "Unesite svoj izbor: ";
            std::cin >> choice;

            switch (choice) {
            case 1:
                std::cout << "Unesite naziv datoteke: ";
                std::cin >> filename;
                sudoku.loadFromFile(filename);
                gameStarted = true;
                sudoku.print();
                break;
            case 2:
                sudoku.generatePuzzle();
                sudoku.printToFile("sudoku.txt");
                std::cout << "Nova zagonetka je generisana i upisana u datoteku 'sudoku.txt'.\n";
                gameStarted = true;
                sudoku.print();
                break;
            default:
                std::cout << "Nepoznat izbor. Molim vas pokusajte ponovo.\n";
            }
        }
        else {
            if (sudoku.isSolutionValid()) {
                std::cout << "Igra je zavrsena.\n";
                sudoku.printStats();
                std::cout << "1. Zapocni novu igru\n";
                std::cout << "2. Izadji iz programa\n";
                std::cout << "Unesite svoj izbor: ";
                std::cin >> choice;

                switch (choice) {
                case 1:
                    sudoku.incrementGamesPlayed();
                    gameStarted = false;
                    break;
                case 2:
                    return 0;
                default:
                    std::cout << "Nepoznat izbor. Molim vas pokusajte ponovo.\n";
                }
            }
            else {
                std::cout << "1. Unesi resenje\n";
                std::cout << "2. Resi zagonetku\n";
                std::cout << "3. Ispisi statistiku\n";
                std::cout << "4. Izadji iz programa\n";

                std::cout << "Unesite svoj izbor: ";
                std::cin >> choice;

                switch (choice) {
                case 1:
                    int row, col, num;
                    std::cout << "Unesite red (1-9): ";
                    std::cin >> row;
                    if (row > 9 || row < 1) {
                        std::cout << "Broj mora biti 1-9\n";
                        break;
                    }
                    row--;
                    std::cout << "Unesite kolonu (1-9): ";
                    std::cin >> col;
                    if (col > 9 || col < 1) {
                        std::cout << "Broj mora biti 1-9\n";
                        break;
                    }
                    col--;
                    std::cout << "Unesite broj (1-9): ";
                    std::cin >> num;
                    if (num > 9 || num < 1) {
                        std::cout << "Broj mora biti 1-9\n";
                        break;
                    }
                    if (sudoku.isSafe(row, col, num)) {
                        sudoku.set(row, col, num);
                        std::cout << "Broj je uspesno unesen!\n";
                        sudoku.incrementCorrectEntries();
                    }
                    else {
                        std::cout << "Broj ne moze biti unesen na ovo polje.\n";
                        sudoku.incrementFalseEntries();
                    }
                    sudoku.print();
                    break;
                case 2:
                    if (sudoku.solve()) {
                        std::cout << "Zagonetka je uspesno resena!\n";
                        sudoku.print();
                    }
                    else
                        std::cout << "Zagonetka ne moze biti resena.\n";

                    break;
                case 3:
                    sudoku.printStats();
                    break;
                case 4:
                    return 0;
                default:
                    std::cout << "Nepoznat izbor. Molim vas pokusajte ponovo.\n";
                }
            }
        }
    }

    return 0;
}
