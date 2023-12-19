#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int hash_function(HashTable *hash, data_type key) {
    int h, a = 31415, b = 27183;
    string s = (string) key;
    for (h = 0; *s != '\0'; s++, a = a * b % (hash_table_get_table_size(hash) - 1))
        h = (a * h + *s) % hash_table_get_table_size(hash);
    return h;
}

int word_hash_compare(data_type word, data_type key) {
    Pair *item = (Pair *) word;
    Word *w = (Word *) _hash_pair_get_item(item);
    string name = (string)key;
    return strcmp(word_get_name(w), name) == 0;
}

int document_hash_compare(data_type document, data_type key) {
    Pair *item = (Pair *) document;
    Document *doc = (Document *) _hash_pair_get_item(item);
    string name = (string)key;
    return strcmp(document_get_name(doc), name) == 0;
}

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

int document_compare(data_type d1, data_type d2) {
    Document *doc1 = (Document *) d1;
    Document *doc2 = (Document *) d2;
    return strcmp(document_get_name(doc1), document_get_name(doc2));
}

int document_compare_freqs(data_type d1, data_type d2) {
    Document *doc1 = (Document *) d1;
    Document *doc2 = (Document *) d2;
    return document_get_freq_word(doc1) - document_get_freq_word(doc2);
}

int word_compare(data_type w1, data_type w2) {
    Word *word1 = (Word *) w1;
    Word *word2 = (Word *) w2;
    return strcmp(word_get_name(word1), word_get_name(word2));
}

