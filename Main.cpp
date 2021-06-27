#include <bits/stdc++.h>
using namespace std;

class Sudoku
{
private:
    vector<vector<char>> board;
    bool rowCache[10][10], colCache[10][10], gridCache[10][10][10];

public:
    void solve()
    {
        if (isValidSudoku() == false)
        {
            cout << "Not a valid Sudoku!";
            return;
        }

        solveSudoku();
        print();
        return;
    }

private:
    void solveSudoku()
    {

        memset(rowCache, 0, sizeof rowCache);
        memset(colCache, 0, sizeof colCache);
        memset(gridCache, 0, sizeof gridCache);

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] != '.')
                {
                    updateCache(i, j, true);
                }
            }
        }

        backtrack(0, 0);
    }

    void updateCache(int i, int j, bool value)
    {
        int num = board[i][j] - '0';
        rowCache[i][num] = value;
        colCache[j][num] = value;
        gridCache[(i / 3) * 3][(j / 3) * 3][num] = value;
    }

    bool backtrack(int row, int col)
    {
        if (col == 9)
            return backtrack(row + 1, 0);

        if (row == 9)
            return true;

        if (board[row][col] != '.')
            return backtrack(row, col + 1);

        for (char num = '1'; num <= '9'; num++)
        {

            board[row][col] = num;

            if (isSafe(row, col))
            {
                board[row][col] = num;

                updateCache(row, col, true);

                bool isSolvable = backtrack(row, col + 1);
                if (isSolvable)
                    return true;

                updateCache(row, col, false);
            }

            board[row][col] = '.';
        }

        return false;
    }

    bool isSafe(int row, int col)
    {
        int num = board[row][col] - '0';

        if (rowCache[row][num] == true)
            return false;

        if (colCache[col][num] == true)
            return false;

        if (gridCache[(row / 3) * 3][(col / 3) * 3][num] == true)
            return false;

        return true;
    }

    bool isValidSudoku()
    {

        memset(rowCache, 0, sizeof rowCache);
        memset(colCache, 0, sizeof colCache);
        memset(gridCache, 0, sizeof gridCache);

        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (board[i][j] != '.')
                {
                    int num = board[i][j] - '0';
                    if (rowCache[i][num] or colCache[j][num] or gridCache[(i / 3) * 3][(j / 3) * 3][num])
                    {
                        return false;
                    }

                    rowCache[i][num] = true;
                    colCache[j][num] = true;
                    gridCache[(i / 3) * 3][(j / 3) * 3][num] = true;
                }
            }
        }

        return true;
    }

public:
    void read()
    {
        vector<vector<char>> board(9, vector<char>(9));
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                cin >> board[i][j];
                if (board[i][j] < '1' or board[i][j] > '9')
                    board[i][j] = '.';
            }
        }

        this->board = board;
    }

    void print()
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
                cout << board[i][j] << " ";
            cout << endl;
        }
    }
};

int main()
{
    /*
    Sample Input:
    
    8 . . . . . . . .
    . . 3 6 . . . . .
    . 7 . . 9 . 2 . .
    . 5 . . . 7 . . .
    . . . . 4 5 . . .
    . . . 1 . . . 3 .
    . . 1 . . . . 6 8
    . . 8 5 . . . 1 .
    . 9 . . . . 4 . .
    
    */

    Sudoku sudoku;
    sudoku.read();
    sudoku.solve();

    return 0;
}
