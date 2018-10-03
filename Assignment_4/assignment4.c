/**
 *  Istanbul Technical University
 *  assignment4.c
 *  Purpose: Find a hidden sentence in a book.
 *  
 *  @author Burak Bozdað
 *  @version 1.2 //Memory management optimizations according to the restrictions and some bugfixes
 */

#include <ctype.h> //ispunct, isdigit
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 10005
#define MAX_LINE_LENGTH 205

/**
 *  @struct instruction_s
 *  @brief A struct that will store instructions which will be taken from the file instructions.txt.
 *
 *  @var step Indicates the line that will be processed.
 *  @var index Indicates the word that will be processed.
 */
struct instruction_s {
    int step;
    int index;
};

/**
 *  @fn get_word
 *  @brief Returns the word which is requested by instructions.
 *
 *  @param s A pointer which tracks the line that is requested.
 *  @param n The value of the index that will be taken from instructions.
 *  @param word A variable that will carry the requested word.
 *  @return The word which is requested.
 */
char* get_word(char* s, int n, char* word)
{
    int word_counter = 0;
    int word_index = 0;
    for (int i = 0; i < strlen(s); i++) {
        if (s[i] == ' ') {
            continue;
        } else if (s[i] != ' ') {
            word_index = i;
            word_counter++;
            while (s[i] != ' ') {
                i++;
            }
            if (word_counter == n) { //Checking whether the counter reached to the index of the requested word
                break;
            }
        }
    }
    int k = word_index;
    int a;
    for (a = 0; s[k] != ' '; a++, k++) { //Extracting the requested word from the line
        word[a] = s[k];
    }
    return word;
}

/**
 *  @fn get_sentence
 *  @brief Processes instructions and finds the hidden sentence.
 *
 *  @param lines A pointer that keeps the book's lines.
 *  @param instructions A struct that keeps instructions which are taken from the file instructions.txt.
 *  @param n_instructions The number of instructions that are given.
 *  @param sentence A variable that will carry the hidden sentence.
 */
void get_sentence(char** lines, struct instruction_s* instructions, int n_instructions, char* sentence)
{
    int line = -1;
    char* word = (char*)malloc(sizeof(char) * MAX_LINE_LENGTH);
    for (int i = 0; i < n_instructions; i++) {
        for (int a = 0; a < MAX_LINE_LENGTH; a++) { //Resetting the variable in order to use it again
            word[a] = '\0';
        }
        line += instructions[i].step;
        if (get_word(lines[line], instructions[i].index, word)[0] != '\0') { //Ignoring lines that don't contain any letter
            strcat(sentence, get_word(lines[line], instructions[i].index, word)); //Appending the requested word to the sentence
            strcat(sentence, " ");
        }
    }
    free(word);
}

/**
 *  @fn string_fixer
 *  @brief Removes all of punctuation marks and converts upper-case letter to lower-case letters in a string.
 *
 *  @param string A string that will be processed.
 */
void string_fixer(char* string)
{
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] >= 97 && string[i] <= 122) {
            continue;
        } else if (string[i] >= 65 && string[i] <= 90) { //Converting upper-case letters to lower-case letters
            string[i] += 32;
            continue;
        } else if (ispunct(string[i])) { //Determining punctuation characters
            string[i] = 'P';
        } else if (isdigit(string[i])) {
            continue;
        } else {
            string[i] = ' ';
        }
    }
    int j = 0;
    for (int i = 0; string[i] != '\0'; i++) { //Removing determined characters from the line
        if (string[i] != 'P') {
            string[j] = string[i];
            j++;
        }
    }
    string[j] = '\0';
}

int main(int argc, char** argv)
{
    char** book = (char**)malloc(sizeof(char*) * MAX_LINES);
    for (int i = 0; i < MAX_LINES; i++) {
        book[i] = (char*)malloc(sizeof(char) * MAX_LINE_LENGTH); //Allocating memory for the book's lines
    }

    FILE* read_book = fopen(argv[1], "r");
    if (read_book == NULL) {
        return EXIT_FAILURE;
    }
    int i = 0;
    while (fgets(book[i], MAX_LINE_LENGTH, read_book) != NULL) { //Saving the book to the allocated memory
        string_fixer(book[i]);
        i++;
    }

    FILE* read_instructions = fopen(argv[2], "r");
    if (read_instructions == NULL) {
        return EXIT_FAILURE;
    }
    struct instruction_s* instructions = (struct instruction_s*)malloc(2 * sizeof(int) * MAX_LINES);
    int counter = 0;
    for (int i = 0; fscanf(read_instructions, "%d %d", &instructions[i].step, &instructions[i].index) == 2; i++) { //Taking instructions from the file
        counter++;
    }

    char* sentence = (char*)malloc(sizeof(char) * MAX_LINE_LENGTH);
    for (int i = 0; i < MAX_LINE_LENGTH; i++) { //Initializing variable that will be filled with requested words
        sentence[i] = '\0';
    }
    get_sentence(book, instructions, counter, sentence);
    printf("%s\n", sentence); //Printing the hidden sentence

    for (int i = 0; i < MAX_LINES; i++) { //Freeing allocated memories
        free(book[i]);
    }
    free(book);
    free(instructions);
    free(sentence);
    fclose(read_book);
    fclose(read_instructions);
    return EXIT_SUCCESS;
}
