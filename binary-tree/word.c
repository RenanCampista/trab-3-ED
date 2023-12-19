#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word.h"

struct Word {
    char name[100];
    BinaryTree *docs;
};

Word *word_construct(string name) {
    Word *word = calloc(1, sizeof(Word));
    if (word == NULL)
        exit(printf("Error: word_construct: could not allocate memory.\n\n"));

    strcpy(word->name, name);
    word->docs = binary_tree_construct();
    return word;
}

void word_destroy(Word *word) {
    if (word == NULL) return;
    binary_tree_destroy(word->docs, (data_type)document_destroy);
    free(word);
}

void word_add_doc(Word *word, Document *doc) {
    binary_tree_add(word->docs, document_get_name(doc), doc);
}

BinaryTree *word_get_docs(Word *word) {
    return word->docs;
}

string word_get_name(Word *word) {
    return word->name;
}

Document *word_get_doc_from_file_name(Word *word, string file_name) {
    return binary_tree_get(word->docs, file_name);
}

void word_print(Word *word, FILE *file) {
    fprintf(file, "%s\n", word->name);
    fprintf(file, "%d\n", binary_tree_size(word->docs));
    binary_tree_fprint_all_data(word->docs, (data_type)document_print, file);
}

int word_contains_doc(Word *word, string file_name) {
    return binary_tree_contains_key(word->docs, file_name);
}