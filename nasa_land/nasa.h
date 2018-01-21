#ifndef NASA_HEADER
#define NASA_HEADER

char *expand_from_executable_dir(char *program_name, char *filename);
int get_seed(char *program_name);
char *seed_to_string(int seed);

#endif
