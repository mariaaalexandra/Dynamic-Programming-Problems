#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#define WORD_SIZE 1<<9
#define ALPHABET_LETTERS 26
#define NR_WORDS_MAX 1<<15
#define FILE_NOT_OPEN "The file is not open"
#define STRING_ALLOC_FAIL "String couldn't be allocated"
#define INT_ARRAY_ALLOC_FAIL "Int array couldn't be allocated"

#define DIE(assertion, message)                                                \
if(assertion) {                                                                \
    fprintf(stderr, "ERROR AT LINE %d IN FILE %s ", __LINE__, __FILE__);       \
    perror(message);                                                           \
    exit(errno);                                                               \
}

#define DIE_FILE(assertion, message, file)                                     \
if(assertion) {                                                                \
    fprintf(file, "ERROR AT LINE %d IN FILE %s ", __LINE__, __FILE__);         \
    perror(message);                                                           \
    exit(errno);                                                               \
}

// Function used to sort for quicksort descending
static int desc(const void *p1, const void *p2)
{   int a = * ((int*)p1);
    int  b = * ((int*)p2);

    if (a == b) return 0;
    else if ( a > b ) return -1;
    return 1;
}

int main(void) {
    // Open files
    FILE* f = fopen("statistics.in", "r");
    FILE* g = fopen("statistics.out", "w+");
    DIE_FILE(!f || !g, FILE_NOT_OPEN, g);

    // Read num of words
    int nr_words = 0;
    fscanf(f, "%d", &nr_words);

    // Variables
    int matrix[ALPHABET_LETTERS][NR_WORDS_MAX];
    char* word_reader = (char*) calloc(sizeof(char), WORD_SIZE);
    int *v = (int *) malloc(nr_words * sizeof(int));
    DIE_FILE(!word_reader, STRING_ALLOC_FAIL, g);
    DIE_FILE(!v, INT_ARRAY_ALLOC_FAIL, g);

    // Read words
    for (int i = 0; i < nr_words; i++) {
        // Read word
        fscanf(f, "%s", word_reader);

        // Calculate matrix
        int start = -strlen(word_reader);

        for (int j = 0; j < ALPHABET_LETTERS; j++) {
            matrix[j][i] = start;
        }

        for (int j = 0; j < (int) strlen(word_reader); j++) {
            matrix[word_reader[j] - 'a'][i] += 2;
        }
    }

    // Find result
    int answer = 0;
    for (int i = 0; i < ALPHABET_LETTERS; i++) {
        // Get each line
        for (int e = 0; e < nr_words; e++) {
            v[e] = matrix[i][e];
        }

        // Sort descending
        qsort(v, nr_words, sizeof(int), desc);

        if (v[0] <= 0) {
            continue;
        } else {
            int sum = v[0];
            int j;
            for (j = 1; j < nr_words && sum > 0; j++)
                sum += v[j];
            if (sum <= 0)
                --j;

            if (j > answer) {
                answer = j;
            }
        }
    }

    // Print results
    fprintf(g, "%d\n", answer);

    // Release memory
    free(word_reader);
    free(v);
    fclose(g);
    fclose(f);

	return 0;
}
