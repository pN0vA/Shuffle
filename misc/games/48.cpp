#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int ROWS = 4;
const int COLS = 4;

void print_board(int board[][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            cout << board[i][j] << "\t";
        }
        cout << endl;
    }
}

int generate_random() {
    srand(time(NULL));
    return rand() % 4 + 1;
}

bool check_empty(int board[][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 0) {
                return true;
            }
        }
    }
    return false;
}

void add_number(int board[][COLS]) {
    int row, col;
    do {
        row = generate_random() - 1;
        col = generate_random() - 1;
    } while (board[row][col] != 0);
    board[row][col] = 2;
}

void move_left(int board[][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS - 1; j++) {
            if (board[i][j] == board[i][j+1]) {
                board[i][j] *= 2;
                board[i][j+1] = 0;
            }
        }
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 0) {
                for (int k = j+1; k < COLS; k++) {
                    if (board[i][k] != 0) {
                        board[i][j] = board[i][k];
                        board[i][k] = 0;
                        break;
                    }
                }
            }
        }
    }
}

void move_right(int board[][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = COLS - 1; j > 0; j--) {
            if (board[i][j] == board[i][j-1]) {
                board[i][j] *= 2;
                board[i][j-1] = 0;
            }
        }
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = COLS - 1; j >= 0; j--) {
            if (board[i][j] == 0) {
                for (int k = j-1; k >= 0; k--) {
                    if (board[i][k] != 0) {
                        board[i][j] = board[i][k];
                        board[i][k] = 0;
                        break;
                    }
                }
            }
        }
    }
}

void move_up(int board[][COLS]) {
    for (int j = 0; j < COLS; j++) {
        for (int i = 0; i < ROWS - 1; i++) {
            if (board[i][j] == board[i+1][j]) {
                board[i][j] *= 2;
                board[i+1][j] = 0;
            }
        }
    }
    for (int j = 0; j < COLS; j++) {
        for (int i = 0; i < ROWS; i++) {
            if (board[i][j] == 0) {
                for (int k = i+1; k < ROWS; k++) {
                    if (board[k][j] != 0) {
                        board[i][j] = board[k][j];
                        board[k][j] = 0;
                        break;
                    }
                }
            }
        }
    }
}

void move_down(int board[][COLS]) {
    for (int j = 0; j < COLS; j++) {
        for (int i = ROWS - 1; i > 0; i--) {
            if (board[i][j] == board[i-1][j]) {
                board[i][j] *= 2;
                board[i-1][j] = 0;
            }
        }
    }
    for (int j = 0; j < COLS; j++) {
        for (int i = ROWS - 1; i >= 0; i--) {
            if (board[i][j] == 0) {
                for (int k = i-1; k >= 0; k--) {
                    if (board[k][j] != 0) {
                        board[i][j] = board[k][j];
                        board[k][j] = 0;
                        break;
                    }
                }
            }
        }
    }
}

bool game_over(int board[][COLS]) {
    if (check_empty(board)) {
        return false;
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS - 1; j++) {
            if (board[i][j] == board[i][j+1]) {
                return false;
            }
        }
    }
    for (int j = 0; j < COLS; j++) {
        for (int i = 0; i < ROWS - 1; i++) {
            if (board[i][j] == board[i+1][j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int board[ROWS][COLS] = {0};
    add_number(board);
    add_number(board);
    print_board(board);

    while (!game_over(board)) {
        char input;
        cout << "Input a Direction: ";
        cin >> input;
        switch (input) {
            case 'w':
                move_up(board);
                break;
            case 's':
                move_down(board);
                break;
            case 'a':
                move_left(board);
                break;
            case 'd':
                move_right(board);
                break;
            default:
                cout << "Invalid input." << endl;
        }
        if (!game_over(board)) {
            add_number(board);
        }
        print_board(board);
    }

    cout << "Game over!" << endl;

    return 0;
}
