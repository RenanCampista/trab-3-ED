#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "word.h"
#include "utils.h"

struct Word {
    char name[100];
    HashTable *docs;
};

Word *word_construct(string name) {
    Word *word = calloc(1, sizeof(Word));
    if (word == NULL)
        exit(printf("Error: word_construct: could not allocate memory.\n\n"));

    strcpy(word->name, name);
    word->docs = hash_table_construct(199, hash_function, document_hash_compare);
    return word;
}

void word_destroy(Word *word) {
    if (word == NULL) return;
    hash_table_destroy(word->docs, (data_type)document_destroy);
    free(word);
}

void word_add_doc(Word *word, Document *doc) {
    hash_table_insert(word->docs, document_get_name(doc), doc);
}

HashTable *word_get_docs(Word *word) {
    return word->docs;
}

string word_get_name(Word *word) {
    return word->name;
}

Document *word_get_doc_from_file_name(Word *word, string file_name) {
    Pair *p = hash_table_get(word->docs, file_name);
    return p != NULL ? (Document *) _hash_pair_get_item(p) : NULL;
}

int doc_name_sort_compare(data_type d1, data_type d2) {
    Document *doc1 = (Document *) _hash_pair_get_item (d1);
    Document *doc2 = (Document *) _hash_pair_get_item (d2);
    return strcmp(document_get_name(doc1), document_get_name(doc2));
}

void word_print(Word *word, FILE *file) {
    fprintf(file, "%s\n", word->name);
    fprintf(file, "%d\n", hash_table_size(word->docs));

    Vector *pairs = hash_table_all_pairs(word->docs);

    for (int i = 0; i < vector_size(pairs); i++) {
        Pair *p = (Pair *)vector_get(pairs, i);
        Document *doc = (Document *)_hash_pair_get_item(p);
        document_print(doc, file);
    }
    vector_destroy(pairs);
}

int word_contains_doc(Word *word, string file_name) {
    return hash_table_contains_key(word->docs, file_name);
}