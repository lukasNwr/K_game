#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "k.h"
#include "hof.h"
#include "ui.h"

int main() {

    struct game game;
    struct player player;
    int dy, dx, size;
    char key;
    char name[30];
    struct player list[10];
    bool trigger = true;

    game.score = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            game.board[i][j] = ' ';
        }
    }

    while(is_move_possible(game) != false && trigger != false) {
        
        for(size_t row = 0; row < SIZE; row++) {
            for(size_t col = 0; col < SIZE; col++) {
                if(game.board[row][col] == ' ') trigger = true; else trigger = false;
            } 
        }

        add_random_tile(&game);
        render(game);
        scanf("%c", &key);

        if (key == 'w')
        {
            dx = 0;
            dy = -1;
        }
        if (key == 's')
        {
            dx = 0;
            dy = 1;
        }
        if (key == 'a')
        {
            dx = -1;
            dy = 0;
        }
        if (key == 'd')
        {
            dx = 1;
            dy = 0;
        }

        update(&game, dy, dx);

        if(is_game_won(game) == true) {
            printf("YOU WON!");
            break;
        }
        //printf("DX: %d, DY: %d\n", dx, dy);
    }

    printf("YOU LOST! Your score: %d\n", game.score);

    printf("Enter your name: ");
    scanf("%s", name);

    strcpy(player.name, name);
    player.score = game.score;

    size = load(list);
    add_player(list, &size, player);
    save(list, sizeof(list));


    return 0;
}
