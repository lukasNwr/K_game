#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "k.h"

int find_letter(struct game *game,const int row, const int col);
void sort_right_row(struct game *game, const int row);
void merge_right_row(struct game *game, const int );



void add_random_tile(struct game *game){
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}

bool is_game_won(const struct game game) {
    for (size_t row = 0; row <  SIZE; row++) {
        for(size_t col = 0; col < SIZE; col++) {
            if(game.board[row][col] == 'K') return true;
        }
    }

    return false;
}

bool is_move_possible(const struct game game) {

    /*for(size_t row = 0; row < SIZE; row++) {
        for(size_t col = 0; col < SIZE; col++) {
            if(game.board[row][col] == ' ') return true;
        }
    }*/

    for(size_t row = 0; row < (SIZE-1); row++) {
        for(size_t col = 0; col < SIZE; col++) {
            if(game.board[row+1][col] == game.board[row][col]) return true;
        } 
    }

    for(size_t row = 0; row < SIZE; row++) {
        for(size_t col = 0; col < (SIZE-1); col++) {
            if(game.board[row][col+1] == game.board[row][col]) return true;
        }
    }

    return false;
}


void rotate_board(struct game **game) {
    char tmp;
	for (int i = 0; i < SIZE/2; i++)
	{
		for (int j = i; j < SIZE-i-1; j++)
		{
			tmp= (*game)->board[i][j];
			(*game)->board[i][j] = (*game)->board[j][SIZE-i-1];
			(*game)->board[j][SIZE-i-1] = (*game)->board[SIZE-i-1][SIZE-j-1];
			(*game)->board[SIZE-i-1][SIZE-j-1] = (*game)->board[SIZE-j-1][i];
			(*game)->board[SIZE-j-1][i] = tmp;

		}
	}
 }

int find_letter(struct game *game, int row, int col) {  
    for(int idx = col; idx >= 0; idx--) {
        if(game->board[row][idx] != ' ') return idx;
    }
    return -1;
}

void sort_right_row(struct game *game, int row) {
    int idx = 0;
    for(int col = SIZE-1; col > 0; col--) {
        if(game->board[row][col] == ' ') {
            //printf("ROW: %d\n", row+1);
            idx = find_letter(game, row, col);
            if(idx == -1) continue;
            //printf("INDEX: %d\n", idx);
            game->board[row][col] = game->board[row][idx];
            game->board[row][idx] = ' ';
        }   
    }
}

void merge_right_row(struct game *game, int row) {
    for(int col = 0; col < SIZE-1; col++) {
        if(game->board[row][col] != ' ') {
            if(game->board[row][col+1] == game->board[row][col]) {
               game->board[row][col] = game->board[row][col]+1;
               game->board[row][col+1] = ' ';
               game->score = game->score + (pow(2,(game->board[row][col]-65))) * 2;
            }
        }
    }
}


bool update(struct game *game, int dy, int dx) {
    if(is_move_possible(*game) == false) return false;
    if(dx == 1 && dy == 0) {
        //moving elements right
        for(int row = 0; row < SIZE; row++) {
            sort_right_row(game, row);
            merge_right_row(game, row);
            sort_right_row(game, row);
        }
    } else if(dx == 0 && dy == 1) {
        //moving elements down
        rotate_board(&game);

        for(int row = 0; row < SIZE; row++) {
            sort_right_row(game, row);
            merge_right_row(game, row);
            sort_right_row(game, row);
        }

        rotate_board(&game);
        rotate_board(&game);
        rotate_board(&game);
    } else if(dx == -1 && dy == 0) {
        //moving elements left
        rotate_board(&game);
        rotate_board(&game);

        for(int row = 0; row < SIZE; row++) {
            sort_right_row(game, row);
            merge_right_row(game, row);
            sort_right_row(game, row);
        }

        rotate_board(&game);
        rotate_board(&game);
    } else if(dx == 0 && dy == -1) {
        //moving elements up
        rotate_board(&game);
        rotate_board(&game);
        rotate_board(&game);

        for(int row = 0; row < SIZE; row++) {
            sort_right_row(game, row);
            merge_right_row(game, row);
            sort_right_row(game, row);
        }

        rotate_board(&game);
    } else return false;
  
    return true;
}
