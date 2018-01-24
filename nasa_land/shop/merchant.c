#include "nasa.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check_new_list(char *program_name) {
    char *old_list = expand_from_executable_dir(program_name, "list");
    FILE *old_fp = fopen(old_list, "r");
    char old_buf[32], new_buf[32];

    while (fgets(old_buf, sizeof(old_buf)/ sizeof(old_buf[0]), old_fp)) {
        old_buf[strlen(old_buf) - 1] = '\0';
        if (!fgets(new_buf, sizeof(new_buf) / sizeof(new_buf[0]), stdin)) {
            printf("there are something missing.\n");
            return;
        }

        int len = strlen(new_buf);
        if (len > 0 && new_buf[len-1] == '\n') {
            new_buf[len-1] = '\0';
        }

        if (strcmp(old_buf, "poison") != 0) {
            if (strcmp(old_buf, new_buf) != 0) {
                printf("You should not replace %s with %s.\n", old_buf, new_buf);
                return;
            }
        } else {
            if (strcmp("potion", new_buf) != 0) {
                printf("You should replace %s with %s, not with %s.\n", old_buf, "potion", new_buf);
                return;
            }
        }

    }

    printf("Well done! The secret is %s\n", seed_to_string(get_seed(program_name)));

    fclose(old_fp);
}

int main(int argc, char *argv[]) {

    printf("The file \"list\" contains all the goods I have.\n");
    char *goods[] = { "arrow", "sword", "poison", "armor" };
    printf("They are %s", goods[0]);
    for (int i = 1; i < sizeof(goods) / sizeof(goods[0]); ++i) {
        printf(", %s", goods[i]);
    }
    printf("\n");
    printf("Wait... I accidently misspelled the word \"potion\" as \"poison\".\n");
    printf("Please fix it for me, and tell me the correct list line by line.\n");
    printf("If you do it right, I will tell you the secret.\n");

    check_new_list(argv[0]);
    return 0;
}
