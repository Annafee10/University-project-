#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// Tic Tac Toe Functions
char board[3][3];
char currentPlayer;

void resetBoard() {
    char start = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = start++;
        }
    }
    currentPlayer = 'X';
}

void printBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "-----------\n";
    }
    cout << "\n";
}

bool checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return true;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;
    return false;
}

bool isDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}

void makeMove() {
    int move;
    cout << "Player " << currentPlayer << ", enter your move (1-9): ";
    cin >> move;

    int row = (move - 1) / 3;
    int col = (move - 1) % 3;

    if (move < 1 || move > 9 || board[row][col] == 'X' || board[row][col] == 'O') {
        cout << "Invalid move. Try again.\n";
        makeMove();
    } else {
        board[row][col] = currentPlayer;
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

void playTicTacToe() {
    resetBoard();
    cout << "\n--- Tic Tac Toe ---\n";
    while (true) {
        printBoard();
        makeMove();
        if (checkWin()) {
            printBoard();
            cout << "Player " << ((currentPlayer == 'X') ? 'O' : 'X') << " wins!\n";
            break;
        }
        if (isDraw()) {
            printBoard();
            cout << "It's a draw!\n";
            break;
        }
    }
}

// Word Game Functions
string shuffleWord(string word) {
    random_shuffle(word.begin(), word.end());
    return word;
}

void playWordGame() {
    cout << "\n--- Word Game ---\n";
    ifstream file("wordlist.txt");
    if (!file) {
        cout << "Could not open wordlist.txt\n";
        return;
    }

    vector<string> words;
    string word;
    while (file >> word) {
        words.push_back(word);
    }
    file.close();

    if (words.empty()) {
        cout << "Word list is empty.\n";
        return;
    }

    srand(time(0));
    int score = 0;
    char playAgain;

    do {
        int index = rand() % words.size();
        string original = words[index];
        string shuffled = shuffleWord(original);

        cout << "\nUnscramble the word: " << shuffled << endl;
        cout << "Your guess: ";
        string guess;
        cin >> guess;

        if (guess == original) {
            cout << "Correct! +10 points\n";
            score += 10;
        } else {
            cout << "Wrong! The correct word was: " << original << "\n";
        }

        cout << "Play again? (y/n): ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Final Score: " << score << "\n";
}

int main() {
    int choice;
    do {
        cout << "\n========= Game Hub =========\n";
        cout << "1. Play Tic Tac Toe\n";
        cout << "2. Play Word Game\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                playTicTacToe();
                break;
            case 2:
                playWordGame();
                break;
            case 0:
                cout << "Exiting... Thank you for playing!\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
