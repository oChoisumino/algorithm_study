#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "brute_force.h"
#include "karp_rabin.h"
#include "kmp_algorithm.h"
#include "boyer_moore.h"


#define MAX_BUFFER      512
#define FILE_PATH_LEN   64
#define PATTERN_MAX_LEN 16

int main(void)
{
    char file_path[FILE_PATH_LEN];
    FILE *file;

    char text[MAX_BUFFER] = {0};
    char pattern[PATTERN_MAX_LEN] = {0};
    int position = 0, line = 0;
    int type = 0;

    printf("file path : ");
    scanf("%s", &file_path[0]);

    printf("pattern : ");
    scanf("%s", &pattern[0]);

    printf("search type: 1. brute_force, 2. karp_rabin 3. kmp_algorithm 4. boyer_moore\n");
    scanf("%d", &type);

    file = fopen(file_path, "r");
    if (file == NULL) {
        printf("cannot open file... \n");
    }

    while(fgets(text, sizeof(char) * MAX_BUFFER, file) != NULL) {
        if (type == 1) {
            position = brute_force(text, strlen(text), 0, pattern, strlen(pattern));
        } else if (type == 2) {
            position = karp_rabin(text, strlen(text), 0, pattern, strlen(pattern));
        } else if (type == 3) {
            position = knuth_morris_pratt(text, strlen(text), 0, pattern, strlen(pattern));
        } else if (type == 4) {
            position = boyer_moore(text, strlen(text), 0, pattern, strlen(pattern));
        } else {
            break;
        }
        line++;
        
        if (position != -1) {
            printf("line : %d, column : %d : %s \n", line, position, text);
        }
        memset(text, 0, MAX_BUFFER);
    } 

    fclose(file);
    return 0;
}