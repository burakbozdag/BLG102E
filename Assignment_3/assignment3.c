/**
 *  Istanbul Technical University
 *  assignment3.c
 *  Purpose: Finding the best parking slot for the car.
 *  
 *  @author Burak Bozdað
 *  @version 9.9	// Lots of updates because of the uncertainty of the assignment
 */

#include <stdio.h>
#include <stdlib.h>

/**
 *  Returns the Manhattan distance between two points.
 *  
 *  @param x1 The value of the 'x' which indicates the position of the first point along the x-axis.
 *  @param y1 The value of the 'y' which indicates the position of the first point along the y-axis.
 *  @param x2 The value of the 'x' which indicates the position of the second point along the x-axis.
 *  @param y2 The value of the 'y' which indicates the position of the second point along the y-axis.
 *  @return The Manhattan distance between (x1, y1) and (x2, y2).
 */
int manhattan(int x1, int y1, int x2, int y2)
{
    int x = x1 - x2, y = y1 - y2;
    if (x < 0) {
        x *= -1;
    }
    if (y < 0) {
        y *= -1;
    }
    return x + y;
}

int main()
{
    double size, cars;
    printf("Size: ");
    scanf("%lf", &size);
    while (size > 50 || size < 1) {
        printf("Size must be between 50 and 1\n");
        printf("Size: ");
        scanf("%lf", &size);
    }
    if (size != (int)size) {
        return EXIT_FAILURE;
    }
    printf("Cars: ");
    scanf("%lf", &cars);
    if (cars < 0 || cars != (int)cars) {
        return EXIT_FAILURE;
    }
    if (cars > (size * size)) {
        return EXIT_FAILURE;
    }
    if (cars == (size * size)) { //Checks whether the parking lot is full
        printf("Best Slot Found In: 0 0\n");
        return EXIT_SUCCESS;
    }

    int grid[50][50], distances[50][50];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) { //Assigning initial values of arrays
            grid[i][j] = 0;
            distances[i][j] = size * size;
        }
    }

    for (int i = 0; i < cars; i++) { //Receiving locations of cars as an input
        double x, y;
        printf("Locations: ");
        scanf("%lf %lf", &x, &y);
        if (x != (int)x || y != (int)y) {
            return EXIT_FAILURE;
        }
        if (x > size || y > size) { //Ignoring locations that are outside of the parking lot
            continue;
        }
        if (x <= 0 || y <= 0) {
            return EXIT_FAILURE;
        }
        if (grid[(int)x - 1][(int)y - 1] == 1) { //Ignoring locations that are entered more than once
            continue;
        }
        grid[(int)x - 1][(int)y - 1] = 1; //Inserting cars into empty slots
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (grid[i][j] == 0) {
                for (int k = 0; k < size; k++) {
                    for (int m = 0; m < size; m++) {
                        if (grid[k][m] == 1) {
                            if (distances[i][j] > manhattan(i, j, k, m)) { //Finding the lowest manhattan distance for each empty slot
                                distances[i][j] = manhattan(i, j, k, m);
                            }
                        }
                    }
                }
            }
        }
    }

    int bestx = 0, besty = 0, distance = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (grid[i][j] != 1) {
                if (distances[i][j] > distance) { //Finding the best place to park the car
                    distance = distances[i][j];
                    bestx = i;
                    besty = j;
                }
            }
        }
    }
    printf("Best Slot Found In: %d %d\n", bestx + 1, besty + 1);

    return EXIT_SUCCESS;
}
