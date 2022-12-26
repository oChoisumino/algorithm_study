#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#define MAX_BUFFER 1024

#define START 'S'
#define GOAL 'G'
#define WAY ' '
#define WALL '#'
#define MARKED '+'

typedef struct _MazeInfo {
    int width;
    int height;

    char **data;
} MazeInfo;

typedef struct _Position {
    int x;
    int y;
} Position;

typedef enum {
    DIRECTION_NORTH = 0,
    DIRECTION_SOUTH,
    DIRECTION_EAST,
    DIRECTION_WEST,
    DIRECTION_MAX,
} DIRECTION;

typedef enum {
    FAIL = 0,
    SUCCESS = 1,
} RESULT;

int get_next_step(MazeInfo *maze, Position *current, int direction, Position *next);
int move_to(MazeInfo *maze, Position *current, int direction);
int solve(MazeInfo *maze);
int get_maze(char *file_path, MazeInfo *maze);

#endif // MAZE_SOLVER_H