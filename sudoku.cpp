#include<fstream>
#include<iostream>
#include<math.h>

using namespace std;

//prints out a sudoku table
void printTable(const int **_table, const int *size) {
    for (int i = 0; i < *size; i++) {
        cout << endl;
        for (int k = 0; k < *size; k++) {
            cout << "[" << _table[i][k];
            if (*size > 9 && _table[i][k] < 10)
                cout << " ";
            cout << "] ";
        }
        cout << endl;
    }
}

//creates a table using input from a file, size is determined by file
int** tableFromFile(const char *path, int *size) {
    int **_table = 0;
    ofstream file(path);
    file << 1;
    file.close();
    ifstream ifile(path);

    if (file.good()) {
        ifile >> *size;
        _table = new int*[*size];
        for (int x = 0; x < *size; x++) {
            _table[x] = new int[*size];
            for (int y = 0; y < *size; y++)
                ifile >> _table[x][y];
        }
    }

    file.close();
    return _table;
}

//checks that the number doesn't coincide with others on the same row, column and section of the table
bool isCorrect(const int **_table, const int *size, const int *X, const int *Y, const int *n) {
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

//solves a sudoku puzzle using recursion,
//_table is the Sudoku puzzle (int**)
//size is the length of one column of the table
//pass 0 to X and Y
bool solveSudoku(int **_table, const int *size, int *X, int *Y) {
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

    bool read;
    char resp;
    do {
        cout << "Read from file? (y/n): ";
        cin >> resp;
        if (resp == 'y')
            read = true;
        else if (resp == 'n')
            read = false;
    } while (resp != 'y' && resp != 'n');

    int **table;
    int size;
    if (!read) {
        cout << "Size of one section of the puzzle [normally 3][only very small numbers (1-4)]: ";
        cin >> size;
        size = size * size;
        table = new int*[size];
        for (int x = 0; x < size; x++) {
            table[x] = new int[size];
            for (int y = 0; y < size; y++)
                table[x][y] = 0;
        }
    } 
    else
        table = tableFromFile("input.txt", &size);
    
    cin.get();
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
    
    delete[] table;
    cin.get();

    return 0;
}