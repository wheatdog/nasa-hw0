#include "nasa.h"
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

void set_seed(char *filename) {
    FILE *fp = fopen(filename, "w");
    fprintf(fp, "%d", rand());
    fclose(fp);
}
void cleanup(char *program_name, char *dirname) {
    DIR *dir;
    struct dirent *entry;
    char *name = expand_from_executable_dir(program_name, dirname);

    if (!(dir = opendir(name))) {
        return;
    }

    char buffer[128];
    while ((entry = readdir(dir))) {
        if (entry->d_type == DT_REG) {
            sprintf(buffer, "%s/%s", name, entry->d_name);
            remove(buffer);
        }
    }

    free(name);
}

void create_list(char *program_name) {
    char *listfile = expand_from_executable_dir(program_name, "shop/list");
    FILE *fp = fopen(listfile, "w");
    free(listfile);

    char *goods[] = { "arrow", "sword", "poison", "armor" };

    int goods_count = rand() % 10000;
    int goods_kind = sizeof(goods) / sizeof(goods[0]);
    
    for (int i = 0; i < goods_count; ++i) {
        fprintf(fp, "%s\n", goods[rand() % goods_kind]);
    }

    fclose(fp);
}

int main(int argc, char *argv[]) {
    char *program_name = argv[0];
    srand(time(NULL));
    char *filenames[] = { "castle/.seed", "shop/.seed" };

    printf("You jump into the worm hole, the world has changed a little bit.\n");
    for (int i = 0; i < sizeof(filenames) / sizeof(filenames[0]); ++i) {
        char *seedfile = expand_from_executable_dir(program_name, filenames[i]);
        set_seed(seedfile);
        free(seedfile);
    }

    char *chestfile = expand_from_executable_dir(program_name, "cave/chest");
    FILE *chest = fopen(chestfile, "w");
    char *chest_content = seed_to_string(rand());
    fprintf(chest, "%s", chest_content);
    fclose(chest);
    free(chestfile);
    free(chest_content);

    create_list(program_name);

    char buffer[32];
    strcpy(buffer, "village/bookshelf/");

    cleanup(program_name, buffer);

    int len = strlen(buffer);
    
    int file_cnt = rand() % 1000;
    if (file_cnt < 10) {
        file_cnt = 10;
    }

    int *cnt_arr = malloc(sizeof(*cnt_arr)*file_cnt);
    for (int i = 0; i < file_cnt; ++i) {
        cnt_arr[i] = i;
    }

    for (int i = file_cnt-1; i > 0; --i) {
        int j = rand() % (i+1);
        int tmp = cnt_arr[i];
        cnt_arr[i] = cnt_arr[j];
        cnt_arr[j] = tmp;
    }

    for (int i = 0; i < file_cnt; ++i) {
        char *s = seed_to_string(rand());
        strcpy(buffer + len, s);
        free(s);
        char *file = expand_from_executable_dir(program_name, buffer);
        FILE *fp = fopen(file, "w");
        free(file);

        for (int j = 0; j < 40+cnt_arr[i]; ++j) {
            for (int k = 0; k < 80; ++k) {
                fprintf(fp, "%c", 'A' + (rand() % 26));
            }
            fprintf(fp, "\n");
        }

        fclose(fp);
    }

    return 0;
}
