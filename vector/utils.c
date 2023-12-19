#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "word.h"

Vector *string_split(string str) {
    Vector *words = vector_construct();

    string word = strtok(str, " ");

    while (word != NULL) {
        // o strdup faz um malloc internamente! Lembre-se de remove-lo!
        vector_push_back(words, strdup(word));
        word = strtok(NULL, " ");
    }

    return words;
}

void free_data(Vector *words) {
    for (int i = 0; i < vector_size(words); i++)
        free(vector_get(words, i));

    vector_destroy(words);
}

int string_compare(data_type s1, data_type s2) {
    return strcmp((string) s1, (string) s2);
}

int document_compare(data_type doc, data_type name) {
    return strcmp(document_get_name((Document *) doc), (string) name) == 0;
}

int document_compare_sort(data_type doc1, data_type doc2) {
    return document_get_freq_word((Document *) doc1) - document_get_freq_word((Document *) doc2);
}

int word_compare(data_type w, data_type name) {
    return strcmp(word_get_name((Word *) w), (string) name) == 0;
}

int document_compare_freqs(data_type d1, data_type d2) {
    Document *doc1 = (Document *) d1;
    Document *doc2 = (Document *) d2;
    return document_get_freq_word(doc1) - document_get_freq_word(doc2);
}