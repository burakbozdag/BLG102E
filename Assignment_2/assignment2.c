/** 
 *  Istanbul Technical University
 *  assignment2.c
 *  Purpose: Simulates a dart game by tracking the point value along the game.
 *  
 *  @author Burak Bozdað
 *  @version 1.0
 */

#include <stdio.h>
#include <stdlib.h>

/**
 *  Returns the point value for the throw.
 *
 *  @param segment The value of the segment that the dart is thrown.
 *  @param ring Specifies the radial position of the dart.
 *  @return The point value of the throw.
 */
int points(int segment, char ring)
{
    int score = 1;
    switch (ring) {
    case 'S':
        score *= segment;
        break;
    case 'D':
        score *= 2 * segment;
        break;
    case 'T':
        score *= 3 * segment;
        break;
    case 'O':
        score = 25;
        break;
    case 'I':
        score = 50;
        break;
    }
    return score;
}

/**
 *  Returns the remaining target score.
 *
 *  @param target Represents the starting target
 *  @param current Represents current points
 *  @param segment The value of the segment that the dart is thrown.
 *  @param ring Specifies the radial position of the dart.
 *  @return The remaining points after the throw.
 */
int remaining_current(int target, int current, int segment, char ring)
{
    if (target == current) {
        if (ring != 'D') {
            return current;
        } else {
            current -= points(segment, ring);
            if (current <= 1) {
                return target;
            }
            return current;
        }
    }
    int key = current;
    current -= points(segment, ring);
    if (current == 0) {
        if (ring == 'D') {
            return 0;
        } else {
            current = key;
            return current;
        }
    } else if (current < 0 || current == 1) {
        current = key;
        return current;
    } else {
        return current;
    }
}

int main()
{
    int target, segment;
    char ring;
    printf("Target: ");
    scanf("%d", &target);
    int current = target;
    printf("\n");

    while (current != 0) {
        printf("Throw: ");
        scanf("%d %c", &segment, &ring);
        current = remaining_current(target, current, segment, ring);
        printf("Points: %d\n", current);
    }
    return EXIT_SUCCESS;
}
