#include<iostream>

using namespace std;

int table[9][9] {
    {0, 2, 0, 1, 0, 5, 0, 3, 0},
    {0, 0, 0, 0, 2, 0, 1, 5, 0},
    {9, 5, 0, 8, 0, 0, 6, 0, 0},
    {1, 7, 0, 0, 3, 8, 0, 0, 0},
    {0, 0, 9, 0, 0, 0, 4, 0, 1},
    {8, 0, 0, 0, 5, 0, 0, 6, 0},
    {4, 0, 0, 0, 6, 2, 0, 0, 0},
    {0, 0, 8, 5, 0, 0, 7, 0, 3},
    {0, 1, 5, 0, 0, 0, 0, 9, 6}
    };

//prints out a 9x9 sudoku table
void printTable(int table[9][9]) {
    for (int i = 0; i < 9; i++) {
        cout << "\n";
        for (int k = 0; k < 9; k++)
            cout << "[" << table[i][k] << "] ";
        cout << "\n";
    }
    cout << "\n";
}

//checks if the number doesn't coincide with others on the same row, column and 3x3 section
bool isCorrect(int X, int Y, int n) {
    for (int i = 0; i < 9; i++)
        if (table[X][i] == n || table[i][Y] == n)
            return false;

    int defX, defY;
    if (X > 5)
        defX = 8;
    else if (X > 2)
        defX = 5;
    else
        defX = 2;
    if (Y > 5)
        defY = 8;
    else if (Y > 2)
        defY = 5;
    else
        defY = 2;

    for (int x = defX; x > defX - 3; x--)
        for (int y = defY; y > defY - 3; y--)
            if (table[x][y] == n)
                return false;
    return true;
}

bool solveSudoku(int X, int Y) {
    if (Y >= 9)
        return true;

    int nextX, nextY;
    if (X >= 8) {
        nextX = 0;
        nextY = Y + 1;
    }
    else {
        nextX = X + 1;
        nextY = Y;
    }

    if (table[X][Y] != 0)
        return solveSudoku(nextX, nextY);

    for (int n = 1; n <= 9; n++)
        if (isCorrect(X, Y, n)) {
            table[X][Y] = n;
            if (solveSudoku(nextX, nextY))
                return true;
            else
                table[X][Y] = 0;
        }

    return false;
}

int main(int argc, char const *argv[])
{
    //initialization
    cout << "\n\tSUDOKU ALGORITHM\n";
    cout << "This solves a Sudoku puzzle using backtracking\n\n";
    getchar();

    //prints out default sudoku table
    printTable(table);
    getchar();

    //elaboration
    cout << "\nElaborating...\n";

    if (solveSudoku(0, 0)) {
        cout << "...Solved\n";
        printTable(table);
    }
    else
        cout << "...No valid solutions found\n";

    /*for (int x = 0; x < 9; x++)
        for (int y = 0; y < 9; y++) {
            if (table[x][y] == 0) {
                for (int n = 1; n < 10; n++)
                    if (isCorrect(x, y, n)) {
                        table[x][y] = n;
                        //printTable(table);
                        break;
                    }
            }
        }*/
    
    getchar();

    return 0;
}