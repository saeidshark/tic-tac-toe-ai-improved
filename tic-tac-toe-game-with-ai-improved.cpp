#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

char board[3][3] = { {'1','2','3'},
                     {'4','5','6'},
                     {'7','8','9'} };

// draw the board
void drawBoard() {
    cout << "\n";
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << "\n";
    cout << "---+---+---\n";
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << "\n";
    cout << "---+---+---\n";
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << "\n";
    cout << "\n";
}

// check winner
char checkWinner() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];
    return ' ';
}

// check free cell
bool isFree(int row, int col) {
    return (board[row][col] != 'X' && board[row][col] != 'O');
}


void computerMove() {
    int row, col;

    // 1. try to win
    for (int i = 1; i <= 9; i++) {
        row = (i - 1) / 3;
        col = (i - 1) % 3;
        if (isFree(row, col)) {
            board[row][col] = 'O';
            if (checkWinner() == 'O') {
                cout << "Computer chose cell " << i << " to WIN\n";
                return;
            }
            board[row][col] = '0' + i; // undo
        }
    }

    // 2. block human
    for (int i = 1; i <= 9; i++) {
        row = (i - 1) / 3;
        col = (i - 1) % 3;
        if (isFree(row, col)) {
            board[row][col] = 'X';
            if (checkWinner() == 'X') {
                board[row][col] = 'O'; // block
                cout << "Computer chose cell " << i << " to BLOCK\n";
                return;
            }
            board[row][col] = '0' + i; // undo
        }
    }

    // 3. If no win or block, choose random
    while (true) {
        int move = rand() % 9 + 1;
        row = (move - 1) / 3;
        col = (move - 1) % 3;
        if (isFree(row, col)) {
            board[row][col] = 'O';
            cout << "Computer chose cell " << move << "\n";
            break;
        }
    }
}

int main() {
    srand(time(0));
    char player = 'X';
    int move;
    int movesCount = 0;

    while (true) {
        drawBoard();

        if (player == 'X') {
            cout << "your turn (1-9): ";
            cin >> move;

            int row = (move - 1) / 3;
            int col = (move - 1) % 3;

            if (move < 1 || move > 9 || !isFree(row, col)) {
                cout << "invalid move try again \n";
                continue;
            }

            board[row][col] = 'X';
        } else {
            computerMove();
        }

        movesCount++;

        char winner = checkWinner();
        if (winner == 'X' || winner == 'O') {
            drawBoard();
            if (winner == 'X')
                cout << "you win\n";
            else
                cout << "computer wins \n";
            break;
        }

        if (movesCount == 9) {
            drawBoard();
            cout << "draw \n";
            break;
        }

        player = (player == 'X') ? 'O' : 'X';
    }

    return 0;
}
