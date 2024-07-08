#include <iostream>
#include <vector>

using namespace std;

class TicTacToe {
public:
    TicTacToe() : board(3, vector<char>(3, ' ')), currentPlayer('X') {}

    void playGame() {
        bool playAgain = true;
        while (playAgain) {
            resetBoard();
            bool gameEnded = false;
            while (!gameEnded) {
                displayBoard();
                playerMove();
                gameEnded = checkWin() || checkDraw();
                if (!gameEnded) switchPlayer();
            }
            displayBoard();
            displayResult();
            playAgain = askPlayAgain();
        }
    }

private:
    vector<vector<char>> board;
    char currentPlayer;

    void resetBoard() {
        for (auto& row : board) {
            fill(row.begin(), row.end(), ' ');
        }
    }

    void displayBoard() const {
        cout << "  0 1 2\n";
        for (int i = 0; i < 3; ++i) {
            cout << i << " ";
            for (int j = 0; j < 3; ++j) {
                cout << board[i][j];
                if (j < 2) cout << "|";
            }
            cout << "\n";
            if (i < 2) cout << "  -----\n";
        }
    }

    void playerMove() {
        int row, col;
        while (true) {
            cout << "Player " << currentPlayer << ", enter your move (row and column): ";
            cin >> row >> col;
            if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
                board[row][col] = currentPlayer;
                break;
            } else {
                cout << "Invalid move. Try again.\n";
            }
        }
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    bool checkWin() const {
        for (int i = 0; i < 3; ++i) {
            if (board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) return true;
            if (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer) return true;
        }
        if (board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) return true;
        if (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer) return true;
        return false;
    }

    bool checkDraw() const {
        for (const auto& row : board) {
            for (char cell : row) {
                if (cell == ' ') return false;
            }
        }
        return true;
    }

    void displayResult() const {
        if (checkWin()) {
            cout << "Player " << currentPlayer << " wins!\n";
        } else {
            cout << "The game is a draw.\n";
        }
    }

    bool askPlayAgain() const {
        char choice;
        cout << "Do you want to play again? (y/n): ";
        cin >> choice;
        return choice == 'y' || choice == 'Y';
    }
};

int main() {
    TicTacToe game;
    game.playGame();
    return 0;
}
