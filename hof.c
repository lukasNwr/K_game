#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hof.h"

int count = 0;

void sort(struct player *list, int n);


void sort(struct player *list, int n) {
    int j,i;

    for(i = 1; i < n; i++) {
        for(j = 0; j < n-i; j++) {
            if(list[j].score > list[j+1].score) {
                struct player tmp = list[j];
                list[j] = list[j+1];
                list[j+1] = tmp;
            }
        }
    }
}

bool save(const struct player list[], const int size) {
    FILE* fp = fopen("HOF_FILE", "a+");
    if(fp == NULL) return false;

    for(size_t i = 0; i < size; i++){
        fwrite(&list[i], sizeof(struct player), 1, fp);
    }

    fclose(fp);
    return true;
}

int load(struct player list[]) {
    FILE* fp = fopen("HOF_FILE", "a+");
    if(fp == NULL) return -1;

    while(fscanf(fp, "%s %d", list[count].name, &list[count].score) != EOF) {
        fscanf(fp, "%s %d", list[count].name, &list[count].score);
        count++;
        if(count == 10) break;
    }
    
    sort(list, count);
    fclose(fp);

    return count;
}

bool add_player(struct player list[], int* size, const struct player player) {
    if(size == 0) {
        strcpy(list[0].name, player.name);
        list[0].score = player.score;  
    }
    for(int i = 1; i <= *size; i++) {
        if(player.score > list[i].score) {
            strcpy(list[i].name, player.name);
            list[i].score = player.score;
            return true;
        }
    }
    return false;
}
