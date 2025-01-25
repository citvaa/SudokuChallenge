#include <fstream>
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

    // Metoda za postavljanje vrednosti na odredjeno polje
    void set(int row, int col, int num);

    // Metoda za dobijanje vrednosti sa odredjenog polja
    int get(int row, int col);

    // Metoda za povecanje broja tacnih unosa
    void incrementCorrectEntries();

    // Metoda za dobijanje broja tacnih unosa
    int getCorrectEntries() const;

    // Metoda za povecanje broja pogresnih unosa
    void incrementFalseEntries();

    // Metoda za dobijanje broja pogresnih unosa
    int getFalseEntries() const;

    // Metoda za povecanje broja odigranih igara
    void incrementGamesPlayed();

    // Metoda za dobijanje broja odigranih igara
    int getGamesPlayed() const;

    // Metoda za ispisivanje Sudoku table u konzoli
    void print();

    // Metoda za proveru da li je moguce postaviti broj na odredjeno polje
    bool isSafe(int row, int col, int num);

    // Metoda za resavanje Sudoku zagonetke
    bool solve();

    // Metoda za ucitavanje Sudoku zagonetke iz datoteke
    void loadFromFile(std::string filename);

    // Metoda za ispisivanje Sudoku zagonetke u datoteku
    void printToFile(std::string filename);

    // Metoda za proveru da li je resenje ispravno
    bool isSolutionValid();

    // Metoda za generisanje postavke Sudoku zagonetke
    void generatePuzzle();

    // Metoda za ispis statistickih informacija
    void printStats() const;


};
