﻿#include <fstream>
#include <string>
#include <vector>

class Sudoku9 {
private:
    std::vector<std::vector<int>> grid;
    int correctEntries;
    int falseEntries;
    int gamesPlayed;

public:
    // Konstruktor koji inicijalizuje praznu tablu
    Sudoku9() : correctEntries(0), falseEntries(0), gamesPlayed(0) {
        grid = std::vector<std::vector<int>>(9, std::vector<int>(9, 0));
    }

    // Metoda za postavljanje vrednosti na određeno polje
    void set(int row, int col, int num);

    // Metoda za dobijanje vrednosti sa određenog polja
    int get(int row, int col);

    // Metoda za povećanje broja tačnih unosa
    void incrementCorrectEntries();

    // Metoda za dobijanje broja tačnih unosa
    int getCorrectEntries() const;

    // Metoda za povećanje broja pogresnih unosa
    void incrementFalseEntries();

    // Metoda za dobijanje broja pogresnih unosa
    int getFalseEntries() const;

    // Metoda za povećanje broja odigranih igara
    void incrementGamesPlayed();

    // Metoda za dobijanje broja odigranih igara
    int getGamesPlayed() const;

    // Metoda za ispisivanje Sudoku table u konzoli
    void print();

    // Metoda za proveru da li je moguće postaviti broj na određeno polje
    bool isSafe(int row, int col, int num);

    // Metoda za rešavanje Sudoku zagonetke
    bool solve();

    // Metoda za učitavanje Sudoku zagonetke iz datoteke
    void loadFromFile(std::string filename);

    // Metoda za ispisivanje Sudoku zagonetke u datoteku
    void printToFile(std::string filename);

    // Metoda za proveru da li je rešenje ispravno
    bool isSolutionValid();

    // Metoda za generisanje postavke Sudoku zagonetke
    void generatePuzzle();

    // Metoda za ispis statističkih informacija
    void printStats() const;


};
