#include <assert.h>
#include "Sudoku9.hpp"

static void testIsSafe() {
    Sudoku9 sudoku;

    // Testiranje sa praznom tablom
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            assert(sudoku.isSafe(i, j, 1) == true);
        }
    }

    // Testiranje sa popunjenom tablom
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku.set(i, j, 1);
        }
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            assert(sudoku.isSafe(i, j, 1) == false);
        }
    }

    // Testiranje sa nevazecim indeksima
    assert(sudoku.isSafe(-1, 0, 1) == false);
    assert(sudoku.isSafe(0, -1, 1) == false);
    assert(sudoku.isSafe(9, 0, 1) == false);
    assert(sudoku.isSafe(0, 9, 1) == false);

    // Testiranje sa nevazecim brojevima
    assert(sudoku.isSafe(0, 0, 0) == false);
    assert(sudoku.isSafe(0, 0, 10) == false);

    // Testiranje sa razlicitim brojevima na istom mestu
    for (int num = 1; num <= 9; num++) {
        sudoku.set(0, 0, num);
        assert(sudoku.isSafe(0, 0, num) == false);
    }
}

static void testSolve() {
    Sudoku9 sudoku;

    // Testiranje sa praznom tablom
    // Ocekujemo da će solve metoda da vrati true, jer je to pocetno stanje table
    assert(sudoku.solve() == true);

    // Testiranje sa tablom koja ima moze da se resi
    // Ocekujemo da ce solve metoda da vrati true
    sudoku.loadFromFile("solve_valid.txt");
    assert(sudoku.solve() == true);

    // Testiranje sa tablom koja ne moze biti resena
    // Postavljamo sve brojeve na 1
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku.set(i, j, 1);
        }
    }
    // Ocekujemo da ce solve metoda da vrati false, jer tabela ne moze biti resena
    assert(sudoku.solve() == false);
}


static void testLoadFromFile() {
    Sudoku9 sudoku;

    // Testiranje sa validnom datotekom
    std::string filename = "valid.txt";
    sudoku.loadFromFile(filename);
    // Provera da li je prva linija izgleda ovako: 003000000
    for (int j = 0; j < 9; j++) {
        if (j == 2) {
            assert(sudoku.get(0, j) == 3);
        }
        else {
            assert(sudoku.get(0, j) == 0);
        }
    }

    // Testiranje sa nevazecom datotekom
    // Pretpostavimo da imate nevazecu Sudoku datoteku pod nazivom "invalid.txt"
    sudoku.loadFromFile("invalid.txt");
    // Ocekujemo da ce ovaj poziv da ispiše poruku o gresci i da neće promeniti stanje table

    // Testiranje sa nepostojecom datotekom
    sudoku.loadFromFile("nepostojeca.txt");
    // Ocekujemo da će ovaj poziv da ispise poruku o gresci i da nece promeniti stanje table
}

static void testPrintToFile() {
    Sudoku9 sudoku;

    // Testiranje sa validnom datotekom
    std::string filename = "test.txt";
    sudoku.printToFile(filename);
    // Provera da li je datoteka uspešno kreirana
    std::ifstream file(filename);
    assert(file.good());
    file.close();

    // Testiranje sa nevažećom putanjom do datoteke
    // Pretpostavimo da nemate pristup direktorijumu "nevalid"
    filename = "nevalid/test.txt";
    sudoku.printToFile(filename);
    // Ocekujemo da će ovaj poziv da ispiše poruku o gresci
}


static void testIsSolutionValid() {
    Sudoku9 sudoku;

    // Testiranje sa validnom rešenom tablom
    sudoku.loadFromFile("valid_resenje.txt");
    // Ocekujemo da će isSolutionValid metoda da vrati true
    assert(sudoku.isSolutionValid() == true);

    // Testiranje sa nevalidnom rešenom tablom
    sudoku.loadFromFile("invalid_resenje.txt");
    // Ocekujemo da će isSolutionValid metoda da vrati false
    assert(sudoku.isSolutionValid() == false);
}


static void testGeneratePuzzle() {
    Sudoku9 sudoku;

    // Generisemo zagonetku
    sudoku.generatePuzzle();

    // Proveravamo da li je broj popunjenih polja po podmatrici manji ili jednak 6
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            int filled = 0;
            for (int k = 0; k < 3; k++) {
                for (int l = 0; l < 3; l++) {
                    if (sudoku.get(i + k, j + l) != 0)
                        filled++;
                }
            }
            assert(filled <= 6);
        }
    }

    // Proveravamo da li je svako polje validno
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int num = sudoku.get(i, j);
            if (num != 0) {
                // Postavljamo polje na 0
                sudoku.set(i, j, 0);
                // Proveravamo da li je broj siguran
                assert(sudoku.isSafe(i, j, num));
                // Vracamo polje na originalnu vrednost
                sudoku.set(i, j, num);
            }
        }
    }
}