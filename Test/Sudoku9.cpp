#include<iostream>
#include "Sudoku9.hpp"
//using namespace std;

// N je velicina Sudoku table. 
constexpr auto N = 9;

bool Sudoku9::isSafe(int row, int col, int num) {
    // Provera argumenata
    if (row < 0 || row > 8 || col < 0 || col > 8 || num < 1 || num > 9) {
        return false;
    }

    // Provera u trenutnom redu
    for (int x = 0; x <= 8; x++)
        if (grid[row][x] == num)
            return false;

    // Provera u trenutnoj koloni
    for (int x = 0; x <= 8; x++)
        if (grid[x][col] == num)
            return false;

    // Provera u trenutnom 3x3 kvadratu
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num)
                return false;

    return true;
}

// Metoda za resavanje Sudoku zagonetke
bool Sudoku9::solve() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            // Trazimo prazno polje
            if (grid[row][col] == 0) {
                // Pokusavamo brojeve od 1 do 9
                for (int num = 1; num <= 9; num++) {
                    // Proveravamo da li je sigurno postaviti broj
                    if (isSafe(row, col, num)) {
                        // Postavljamo broj
                        grid[row][col] = num;

                        // Rekurzivni poziv
                        if (solve())
                            return true;

                        // Ako resenje nije pronađeno, vracamo polje na 0
                        grid[row][col] = 0;
                    }
                }

                return false; // Vracamo false ako nijedan broj ne moze biti postavljen na ovo polje
            }
        }
    }

    // Proveravamo da li je trenutno stanje table validno
    if (!isSolutionValid()) {
        return false;
    }

    return true; // Vracamo true ako je svako polje popunjeno
}




// Metoda za ucitavanje Sudoku zagonetke iz datoteke
void Sudoku9::loadFromFile(std::string filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        Sudoku9 temp;
        for (int i = 0; i < 9; i++) {
            std::string line;
            if (!std::getline(file, line) || line.length() != 9) {
                std::cout << "Neispravan format datoteke: " << filename << std::endl;
                return;
            }
            for (int j = 0; j < 9; j++) {
                if (!std::isdigit(line[j])) {
                    std::cout << "Neispravan karakter u datoteci: " << filename << std::endl;
                    return;
                }
                int num = line[j] - '0'; // Konvertujemo karakter u broj
                if (num != 0) {
                    if (!temp.isSafe(i, j, num)) {
                        std::cout << "Ovaj fajl se ne moze konvertovati u tabelu" << std::endl;
                        return;
                    }
                    temp.set(i, j, num);
                }
            }
        }
        file.close();
        grid = temp.grid; // Postavljamo stanje table samo ako je moguce
    }
    else {
        std::cout << "Ne mogu da otvorim datoteku: " << filename << std::endl;
    }
}




// Metoda za ispisivanje Sudoku zagonetke u datoteku
void Sudoku9::printToFile(std::string filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                // Ispisujemo vrednost polja
                file << grid[i][j];
            }
            file << '\n';
        }
        file.close();
    }
    else {
        std::cout << "Ne mogu da otvorim datoteku: " << filename << std::endl;
    }
}


// Metoda za proveru da li je resenje ispravno
bool Sudoku9::isSolutionValid() {
    // Provera svakog reda
    for (int i = 0; i < 9; i++) {
        bool row[10] = { false };
        for (int j = 0; j < 9; j++) {
            if (row[grid[i][j]])
                return false;
            row[grid[i][j]] = true;
        }
    }

    // Provera svake kolone
    for (int i = 0; i < 9; i++) {
        bool col[10] = { false };
        for (int j = 0; j < 9; j++) {
            if (col[grid[j][i]])
                return false;
            col[grid[j][i]] = true;
        }
    }

    // Provera svakog 3x3 kvadrata
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            bool box[10] = { false };
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    if (box[grid[i + k][j + l]])
                        return false;
                    box[grid[i + k][j + l]] = true;
                }
            }
        }
    }

    return true; // Vracamo true ako su sve provere prošle
}


// Metoda za generisanje postavke Sudoku zagonetke
void Sudoku9::generatePuzzle() {
    // Inicijalizacija generatora slučajnih brojeva
    std::srand(std::time(0));

    // Prvo generisemo potpuno popunjenu tablu
    if (!solve())
        return;

    // Zatim uklanjamo brojeve sa table da bismo dobili postavku zagonetke
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            // Sa svakim poljem imamo 50% sanse da ga uklonimo
            if (std::rand() % 2 == 0)
                grid[i][j] = 0;
        }
    }

    // Proveravamo da li je broj popunjenih polja po podmatrici manji od 6
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            int filled = 0;
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    if (grid[i + k][j + l] != 0)
                        filled++;
                }
            }
            // Ako je broj popunjenih polja veći od 6, uklanjamo neka polja
            while (filled > 6) {
                int k = std::rand() % 3;
                int l = std::rand() % 3;
                if (grid[i + k][j + l] != 0) {
                    grid[i + k][j + l] = 0;
                    filled--;
                }
            }
        }
    }
}


// Metoda za ispis statistickih informacija
void Sudoku9::printStats() const {
    std::cout << "Broj unetih brojeva koji su na pravom mestu: " << correctEntries << std::endl;
    std::cout << "Broj unetih brojeva koji su na pogresnom mestu: " << falseEntries << std::endl;
    std::cout << "Redni broj partije koja se igra: " << gamesPlayed + 1 << std::endl;
}

// Metoda za ispisivanje Sudoku table u konzoli
void Sudoku9::print() {
    std::cout << "  ";
    for (int i = 0; i < 9; i++) {
        std::cout << i + 1 << ' ';
    }
    std::cout << '\n';

    std::cout << "  ";
    for (int i = 0; i < 9; i++) {
        std::cout << "--";
    }
    std::cout << "-\n";

    for (int i = 0; i < 9; i++) {
        std::cout << i + 1 << '|';
        for (int j = 0; j < 9; j++) {
            std::cout << grid[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

// Metoda za postavljanje vrednosti na odredjeno polje
void Sudoku9::set(int row, int col, int num) {
    grid[row][col] = num;
}

// Metoda za dobijanje vrednosti sa odredjenog polja
int Sudoku9::get(int row, int col) {
    return grid[row][col];
}

// Metoda za povecanje broja tacnih unosa
void Sudoku9::incrementCorrectEntries() {
    correctEntries++;
}

// Metoda za dobijanje broja tacnih unosa
int Sudoku9::getCorrectEntries() const {
    return correctEntries;
}

// Metoda za povecanje broja pogresnih unosa
void Sudoku9::incrementFalseEntries() {
    falseEntries++;
}

// Metoda za dobijanje broja pogresnih unosa
int Sudoku9::getFalseEntries() const {
    return falseEntries;
}

// Metoda za povecanje broja odigranih igara
void Sudoku9::incrementGamesPlayed() {
    gamesPlayed++;
}

// Metoda za dobijanje broja odigranih igara
int Sudoku9::getGamesPlayed() const {
    return gamesPlayed;
}