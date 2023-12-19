#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word.h"
#include "utils.h"

struct Word {
    char name[100];
    Vector *docs;
};

Word *word_construct(string name) {
    Word *word = calloc(1, sizeof(Word));
    if (word == NULL)
        exit(printf("Error: word_construct: could not allocate memory.\n\n"));

    strcpy(word->name, name);
    word->docs = vector_construct();
    return word;
}

void word_destroy(Word *word) {
    if (word == NULL) return;
    for (int i = 0; i < vector_size(word->docs); i++)
        document_destroy(vector_get(word->docs, i));
    vector_destroy(word->docs);
    free(word);
}

void word_add_doc(Word *word, Document *doc) {
    vector_push_back(word->docs, doc);
}

Vector *word_get_docs(Word *word) {
    return word->docs;
}

string word_get_name(Word *word) {
    return word->name;
}

Document *word_get_doc_from_file_name(Word *word, string file_name) {
    return vector_search(word->docs, file_name, document_compare);
}

void word_print(Word *word, FILE *file) {
    fprintf(file, "%s\n", word->name);
    fprintf(file, "%d\n", vector_size(word->docs));
    for (int i = 0; i < vector_size(word->docs); i++)
        document_print(vector_get(word->docs, i), file);
}

int word_contains_doc(Word *word, string file_name) {
    return vector_search(word->docs, file_name, document_compare) != NULL;
}