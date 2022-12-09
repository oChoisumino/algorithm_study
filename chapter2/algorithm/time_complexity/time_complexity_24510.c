#include <stdio.h>
#include <string.h>


int main(void)
{
    int high_num = 0, line = 0;
    char *pos = NULL;

    scanf("%d", &line);
    if ((line < 1) || (line > 100)) {
        return 1;
    }

    for (int i = 0; i < line; i++) {
        int num = 0;
        char str[10000] = {0};

        scanf("%s", str);
        pos = str;
        while (1) {
            pos = strstr(pos, "for");
            if (pos == NULL) {
                break;
            }
            if (pos[0] == '\0') {
                break;
            }
            pos = pos + strlen("for") - 1;
            num++;
        }
        
        pos = str;
        while (1) {
            pos = strstr(pos, "while");
            if (pos == NULL) {
                break;
            }
            if (pos[0] == '\0') {
                break;
            }
            pos = pos + strlen("while") - 1;
            num++;
        }
        if (high_num < num) {
            high_num = num;
        }
    }
    
    printf("%d\n", high_num);
    return 0;
}