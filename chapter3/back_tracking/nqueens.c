#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_threatened(int columns[], int new_row)
{
    int current_row = 0, threatened = 0;

    while (current_row < new_row) {
        if ((columns[new_row] == columns[current_row])  // 같은 열
           || (abs(columns[new_row] - columns[current_row]) == abs(new_row-current_row))) { // 대각
            threatened = 1;
            break;
        }
        current_row++;
    }
    return threatened;
}

void print_solution(int columns[], int number_of_queens)
{
    for (int i = 0; i < number_of_queens; i++) {
        for (int j = 0; j < number_of_queens; j++) {
            if (columns[i] == j) {
                printf("Q");
            } else {
                printf(".");
            }
        }
        printf("\n");
    }
}

void find_solution_for_queen(int columns[], int row, int number_of_queen, int *solution_count)
{
    if (is_threatened(columns, row) == 1) {
        return;
    }
    if (row == number_of_queen-1) {
        printf("solution#%d : \n", ++(*solution_count));
        print_solution(columns, number_of_queen);
    } else {
        for (int i = 0; i <  number_of_queen; i++) {
            columns[row+1] = i;
            find_solution_for_queen(columns, row+1, number_of_queen, solution_count);
        }
    }
}

int main(void)
{
    int number_of_queens = 0, solution_counts = 0;
    int *columns;

    scanf("%d", &number_of_queens);
    columns = (int *) calloc(number_of_queens, sizeof(int));


    for (int i = 0; i < number_of_queens; i++) {
        columns[0] = i;
        find_solution_for_queen(columns, 0, number_of_queens, &solution_counts);
    }
    free (columns);

    return 0;
}