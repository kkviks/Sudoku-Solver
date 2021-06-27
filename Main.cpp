#include <bits/stdc++.h>
using namespace std;

struct Sudoko
{
    bool rowCache[10][10], colCache[10][10], gridCache[10][10][10];

    bool solve(vector<vector<char>> &board)
    {
        if (isValidSudoku(board) == false)
        {
            return false;
        }

        solveSudoku(board);
        return true;
    }

    void solveSudoku(vector<vector<char>> &board)
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
                    updateCache(i, j, board, true);
                }
            }
        }

        backtrack(0, 0, board);
    }

    void updateCache(int i, int j, vector<vector<char>> &board, bool value)
    {
        int num = board[i][j] - '0';
        rowCache[i][num] = value;
        colCache[j][num] = value;
        gridCache[(i / 3) * 3][(j / 3) * 3][num] = value;
    }

    bool backtrack(int row, int col, vector<vector<char>> &board)
    {
        if (col == 9)
            return backtrack(row + 1, 0, board);

        if (row == 9)
            return true;

        if (board[row][col] != '.')
            return backtrack(row, col + 1, board);

        for (char num = '1'; num <= '9'; num++)
        {

            board[row][col] = num;

            if (isSafe(row, col, board))
            {
                board[row][col] = num;

                updateCache(row, col, board, true);

                bool isSolvable = backtrack(row, col + 1, board);
                if (isSolvable)
                    return true;

                updateCache(row, col, board, false);
            }

            board[row][col] = '.';
        }

        return false;
    }

    bool isSafe(int row, int col, vector<vector<char>> const &board)
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

    bool isValidSudoku(vector<vector<char>> const &board)
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
};

int main()
{
    vector<vector<char>> board(9, vector<char>(9));

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

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cin >> board[i][j];
            if (board[i][j] < '1' or board[i][j] > '9')
                board[i][j] = '.';
        }
    }

    Sudoko sudoko;
    bool solved = sudoko.solve(board);

    if (solved)
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
                cout << board[i][j] << " ";
            cout << endl;
        }
    }
    else
    {
        cout << "Invalid Sudoku!";
    }

    return 0;
}
