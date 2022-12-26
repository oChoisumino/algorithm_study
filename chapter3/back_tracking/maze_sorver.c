#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze_solver.h"

int get_next_step(MazeInfo *maze, Position *current, int direction, Position *next)
{
    switch (direction)
    {
    case DIRECTION_NORTH:
        next->x = current->x;
        next->y = current->y - 1;
        if (next->y == -1) {
            return FAIL;
        }
        break;
    case DIRECTION_SOUTH:
        next->x = current->x;
        next->y = current->y + 1;
        if (next->y == maze->height) {
            return FAIL;
        }
        break;
    case DIRECTION_EAST:
        next->x = current->x + 1;
        next->y = current->y;
        if (next->y == maze->width) {
            return FAIL;
        }
        break;
    case DIRECTION_WEST:
        next->x = current->x - 1;
        next->y = current->y;
        if (next->x == -1) {
            return FAIL;
        }
        break;
    default:
        break;
    }

    if (maze->data[next->y][next->x] == WALL) {
        return FAIL;
    }

    if (maze->data[next->y][next->x] == MARKED) {
        return FAIL;
    }
    return SUCCESS;
}

int move_to(MazeInfo *maze, Position *current, int direction)
{
    Position next;

    if (maze->data[current->y][current->x] == GOAL) {
        return SUCCESS;
    }
    
    maze->data[current->y][current->x] = MARKED;

    for (int i = DIRECTION_NORTH; i < DIRECTION_MAX; i++) {
        if (get_next_step(maze, current, i, &next) == FAIL) {
            continue;
        }

        if (move_to(maze, &next, DIRECTION_NORTH) == SUCCESS) {
            return SUCCESS;
        }
    }
    maze->data[current->y][current->x] = WAY;
    return FAIL;
}

int solve(MazeInfo *maze)
{
    int start_found = FAIL;
    int result = FAIL;

    Position start;

    for (int i = 0; i < maze->height; i++) {
        for (int j = 0; j < maze->width; j++) {
            if (maze->data[i][j] == START) {
                start.x = j;
                start.y = i;
                start_found = SUCCESS;
                break;
            }
        }
    }

    if (start_found == FAIL) {
        return FAIL;
    }

    if (move_to(maze, &start, DIRECTION_NORTH) == SUCCESS) {
        result = SUCCESS;
    } else if (move_to(maze, &start, DIRECTION_SOUTH) == SUCCESS) {
        result = SUCCESS;
    } else if (move_to(maze, &start, DIRECTION_EAST) == SUCCESS) {
        result = SUCCESS;
    } else if (move_to(maze, &start, DIRECTION_WEST) == SUCCESS) {
        result = SUCCESS;
    }

    maze->data[start.y][start.x] = START;

    return result;
}

int get_maze(char *file_path, MazeInfo *maze) {
    int width = -1, height = 0;

    FILE *fp;
    char buffer[MAX_BUFFER];

    if ((fp = fopen(file_path, "r")) == NULL ) {
        printf("cannot open file %s\n", file_path);
        return FAIL;
    }

    while (fgets(buffer, MAX_BUFFER, fp) != NULL) {
        height++;
        if (width == -1) {
            width = strlen(buffer) - 1;
        } else if (width != (strlen(buffer) - 1)) {
            printf("maze data in file %s is not valid %d\n", file_path, (int) (strlen(buffer) - 1));
            fclose(fp);
            return FAIL;
        }
    }
    maze->height = height;
    maze->width = width;
    maze->data = (char **) malloc(sizeof(char*) * height);
    
    for (int i = 0; i < height; i++) {
        maze->data[i] = (char *) malloc(sizeof(char) * width);
    }
    rewind(fp);

    for (int i = 0; i < height; i++) {
        fgets(buffer, MAX_BUFFER, fp);

        for (int j = 0; j < width; j++) {
            maze->data[i][j] = buffer[j];
        }
    }

    fclose(fp);
    return SUCCESS;

}

int main(void)
{
    char file_path[64];
    MazeInfo maze;

    scanf("%s", file_path);
    if (get_maze(file_path, &maze) == FAIL) {
        return 0;
    }
    if (solve(&maze) == FAIL) {
        return 0;
    }

    for (int i = 0; i < maze.height; i++) {
        for (int j = 0; j < maze.width; j++) {
            printf("%c", maze.data[i][j]);
        }
        printf("\n");
    }
    return 0;

}