#include<iostream>
#include<math.h>

using namespace std;

//prints out a sudoku table
void printTable(int **_table, int *size) {
    for (int i = 0; i < *size; i++) {
        cout << endl;
        for (int k = 0; k < *size; k++)
            cout << "[" << _table[i][k] << "] ";
        cout << endl;
    }
}

//checks that the number doesn't coincide with others on the same row, column and section of the table
bool isCorrect(int **_table, int *size, int *X, int *Y, int* n) {
    for (int i = 0; i < *size; i++)
        if ((i != *Y && _table[*X][i] == *n) || (i != *X && _table[i][*Y] == *n))
            return false;

    int sqrtsize = sqrt(*size);
    int defX = *X + sqrtsize - *X % sqrtsize - 1;
    int defY = *Y + sqrtsize - *Y % sqrtsize - 1;

    for (int x = defX; x > defX - sqrtsize; x--)
        for (int y = defY; y > defY - sqrtsize; y--)
            if (!(x == *X && y == *Y) && _table[x][y] == *n)
                return false;

    return true;
}

//solves a 3x3 sudoku puzzle using recursion,
//use (0, 0) as parameters
bool solveSudoku(int **_table, int *size, int *X, int *Y) {
    if (*Y >= *size)
        return true;

    int nextX = (*X != *size - 1)? *X + 1 : 0;
    int nextY = (*X == *size - 1)? *Y + 1 : *Y;

    if (_table[*X][*Y] != 0)
        if (isCorrect(_table, size, X, Y, &_table[*X][*Y]))
            return solveSudoku(_table, size, &nextX, &nextY);
        else
            return false;

    for (int n = 1; n <= *size; n++)
        if (isCorrect(_table, size, X, Y, &n)) {
            _table[*X][*Y] = n;
            if (solveSudoku(_table, size, &nextX, &nextY))
                return true;
            else
                _table[*X][*Y] = 0;
        }

    return false;
}

int main(int argc, char const *argv[])
{
    //initialization
    cout << endl << "This solves a Sudoku puzzle using backtracking";
    cin.get();

    int size;
    cout << "Size of one section of the puzzle [normally 3][only very small numbers (1-4)]: ";
    cin >> size;
    size = size * size;
    cin.get();

    int **table = new int*[size];
    for (int x = 0; x < size; x++) {
        table[x] = new int[size];
        for (int y = 0; y < size; y++)
            table[x][y] = 0;
    }

    //prints out starting sudoku table
    printTable(table, &size);
    cin.get();

    //elaboration and output
    cout << "Elaborating..." << endl;

    int firstX = 0, firstY = 0;
    if (solveSudoku(table, &size, &firstX, &firstY)) {
        cout << "...Solved" << endl;
        printTable(table, &size);
    }
    else
        cout << "...No valid solutions were found" << endl;
    
    cin.get();

    return 0;
}