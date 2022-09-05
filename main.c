#include <stdio.h>

#define mm_player 'x'
#define player 'o'
#define empty ' '

void print_board(char board[]) {
	for (int i = 0; i < 9; i += 3) {
		printf("%c", board[i]);
		printf("%c", board[i+1]);
		printf("%c\n", board[i+2]);
	}
	printf("\n");
}

void print_board_info() {
	for (int i = 0; i < 9; i += 3) {
		printf("%d", i);
		printf("%d", i+1);
		printf("%d\n", i+2);
	}
	printf("\n");
}

int moves_left(char board[]) {
	for (int i = 0; i < 9; i++) {
		if (board[i] == ' ') {
			return 1;
		}
	}
	return 0;
}

char board_eval(char board[]) {
	int i;
	for (i = 0; i < 9; i += 3) {
		if (board[i] == board[i + 1] && board[i + 1] == board[i + 2]) {
			if (board[i] != ' ') {
				return board[i];
			}
		}
	}
	for (i = 0; i < 4; i++) {
		if (board[i] == board[i + 3] && board[i + 3] == board[i + 6]) {
			if (board[i] != ' ') {
				return board[i];
			}
		}
	}
	if (board[0] == board[4] && board[4] == board[8]) {
		if (board[0] != ' ') {
			return board[i];
		}
	}
	if (board[2] == board[4] && board[4] == board[6]) {
		if (board[2] != ' ') {
			return board[i];
		}
	}
	return ' ';
}

int minimax(char board[], int depth, int max_turn, int alpha, int beta) {
	char winning = board_eval(board);
	int best, mm;
	if (winning == mm_player) {
		return 10;
	}
	if (winning == player) {
		return -10;
	}
	if (!moves_left(board)) {
		return 0;
	}
	if (max_turn) {
		best = -1000;
		for (int i = 0; i < 9; i++) {
			if (board[i] == empty) {
				board[i] = mm_player;
				mm = minimax(board, depth + 1, 0, alpha, beta);
				if (mm > best) {
					best = mm - depth;
				}
				if (best > alpha) {
					alpha = best;
				}
				board[i] = empty;
				if (beta <= alpha) {
					break;
				}
			}
		}
		return best;
	} else {
		best = 1000;
		for (int i = 0; i < 9; i++) {
			if (board[i] == empty) {
				board[i] = player;
				mm = minimax(board, depth + 1, 1, alpha, beta);
				if (mm < best) {
					best = mm + depth;
				}
				if (best < beta) {
					beta = best;
				}
				board[i] = empty;
				if (beta <= alpha) {
					break;
				}
			}
		}
		return best;
	}
}

int best_move(char board[]) {
	int best = -1000;
	int move = -1;
	int mm;
	for (int i = 0; i < 9; i++) {
		if (board[i] == empty) {
			board[i] = mm_player;
			mm = minimax(board, 0, 0, -1000, 1000);
			if (mm > best) {
				best = mm;
				move = i;
			}
			board[i] = empty;
		}
	}
	return move;
}

int main() {
	char board[] = {' ', ' ', ' ',
					' ', ' ', ' ',
					' ', ' ', ' '};
	int best;
	int playermove;
	char win;
	print_board_info();
	while (1) {
		printf("Position: ");
		scanf("\n%d", &playermove);
		if (board[playermove] == empty) {
			board[playermove] = player;
		}
		best = best_move(board);
		board[best] = mm_player;
		print_board(board);
		win = board_eval(board);
		if (win == 'x') {
			printf("X won.\n");
			return 0;
		} else if (win == 'o') {
			printf("O won.\n");
			return 0;
		}
		if (!moves_left(board)) {
			printf("Tie.\n");
			return 0;
		}
	}
	return 0;
}