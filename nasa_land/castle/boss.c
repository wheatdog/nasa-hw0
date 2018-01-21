#include "nasa.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int health = 10000;
    char buffer[32];

    printf("I am a harmless boss.\n");
    printf("You can type \"hit\" to hit me.\n");
    printf("I will tell you the secret if you defeat me.\n");

    char *keyword = "hit\n";
    int keyword_len = strlen(keyword);
    while (health) {
        if (!fgets(buffer, sizeof(buffer) / sizeof(buffer[0]), stdin)) {
            return 1;
        }

        if (strcmp(buffer, keyword) == 0) {
            printf("I got hit! ");
            --health;
        } else {
            printf("That does nothing to me. ");
        }

        printf("My health point is %d.\n", health);
    }

    printf("The secret is %s\n", seed_to_string(get_seed(argv[0])));

    return 0;
}
