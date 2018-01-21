#include "nasa.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define NASA_PREFIX "NASA-"

char *seed_to_string(int seed) {
    int len = 5;
    int prefix_len = strlen(NASA_PREFIX);
    char *str = malloc(sizeof(*str)*(prefix_len+len+1));
    str[len] = '\0';

    strcpy(str, NASA_PREFIX);

    srand(seed);
    for (int i = 0; i < len; ++i) {
        str[prefix_len+i] = 'A' + (rand() % 26);
    }

    return str;
}

char *expand_from_executable_dir(char *program_name, char *filename) {
    int filename_len = strlen(filename);
    int len = strlen(program_name);
    int size = len + filename_len + 1;
    char *buf = malloc(size * sizeof(*buf));

    strncpy(buf, program_name, len+1);
    while (buf[len] != '/') --len;
    ++len;
    strncpy(buf + len, filename, size - len);
    buf[len + filename_len] = '\0';

    return buf;
}

int get_seed(char *program_name) {
    char *seedfile = expand_from_executable_dir(program_name, ".seed");
    int seed;

    FILE *fp = fopen(seedfile, "r");
    fscanf(fp, "%d", &seed);
    fclose(fp);

    free(seedfile);
    return seed;
}
