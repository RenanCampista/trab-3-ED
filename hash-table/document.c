#include <stdlib.h>
#include <string.h>
#include "document.h"

struct Document {
    char name[100];
    int freq_word;
};

Document *document_construct(string name, int freq_word) {
    Document *doc = calloc(1, sizeof(Document));
    if (doc == NULL)
        exit(printf("Error: document_construct: could not allocate memory.\n\n"));

    strcpy(doc->name, name);  
    doc->freq_word = freq_word;
    return doc;
} 

void document_destroy(Document *doc) {
    free(doc);
}

int document_get_freq_word(Document *doc) {
    return doc->freq_word;
}

void document_increease_freq_word(Document *doc) {
    doc->freq_word += 1;
}

string document_get_name(Document *doc) {
    return doc->name;
}

void document_set_freq_word(Document *doc, int freq_word) {
    doc->freq_word = freq_word;
}

void document_print(Document *doc, FILE *file) {
    fprintf(file, "%s %d\n", doc->name, doc->freq_word);
}
