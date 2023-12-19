#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"
#include "word.h"

Vector *load_index(string dir_index_file) {
    FILE *fp = fopen(dir_index_file, "r");
    if (fp == NULL)
        exit(printf("Error: load_index: could not open file %s.\n\n", dir_index_file));

    int n_words;
    fscanf(fp, "%d", &n_words);
    Vector *index = vector_construct();

    // O primeiro numero do arquivo é a quantidade de palavras distintas no indice
    for (int i = 0; i < n_words; i++) {
        char word[100];
        fscanf(fp, "%s", word);
        Word *w = word_construct(word);

        int n_docs;
        fscanf(fp, "%d", &n_docs);
        
        // O segundo numero é a quantidade de documentos que a palavra aparece
        for (int j = 0; j < n_docs; j++) {
            char name[100];
            int freq_word;
            fscanf(fp, "%s %d", name, &freq_word);

            Document *doc = document_construct(name, freq_word);
            word_add_doc(w, doc);
        }
        vector_push_back(index, w);
    }
    fclose(fp);
    return index;
}

void documents_freq_analysis(Vector *docs, Vector *recommendations) {
    for (int i = 0; i < vector_size(docs); i++) {
        Document *d = (Document *) vector_get(docs, i);
        string key = document_get_name(d);

        Document *doc = vector_search(recommendations, key, document_compare);
        // Se o documento ainda não foi adicionado no vector de recomendações
        if (doc == NULL) {
            Document *new_doc = document_construct(document_get_name(d), document_get_freq_word(d));
            // Adiciona o documento no vector de recomendações
            vector_push_back(recommendations, new_doc);
        }
        else {
            // Se o documento já foi adicionado, apenas aumenta a frequencia da palavra
            document_set_freq_word(doc, document_get_freq_word(doc) + document_get_freq_word(d));
        }
        
    }
}

Vector *search_docs(Vector *index, string query) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    Vector *words = string_split(query);
    // Remove as palavras repetidas
    Vector *unique = vector_unique(words, string_compare);
    
    // Cria um vector para armazenar os documentos recomendados
    Vector *recommendations = vector_construct();

    for (int i = 0; i < vector_size(unique); i++) {
        string word = (string)vector_get(unique, i);

        Word *w = vector_search(index, word, word_compare);
        if (w != NULL) {
            // Se a palavra existe no indice, pega os documentos que ela aparece
            Vector *docs = word_get_docs(w);
            
            // Se a palavra não aparece em nenhum documento, pula para a proxima palavra
            if (docs != NULL) 
                documents_freq_analysis(docs, recommendations);
        }
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de busca: %.3f segundos\n", cpu_time_used);

    // Nesse caso não é necessário passar para uma lista, pois já é possível ordenar o vector
    vector_sort(recommendations, (data_type)document_compare_freqs);

    free_data(words);
    vector_destroy(unique);

    return recommendations;
}

void print_output(Vector *docs) {
    int cont = 0;
    for (int i = 0; i < vector_size(docs); i++) {
        Document *doc = (Document *)vector_get(docs, i);
        printf("%s: %d\n", document_get_name(doc), document_get_freq_word(doc));
        cont++;
        if (cont == 10)
            break;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) 
        exit(printf("Usage: %s <size>\n", argv[0]));

    string dir_index_file = argv[1];
    Vector *index = load_index(dir_index_file);
    char query[1000];
    printf("Query: ");
    scanf("%[^\n]", query);
    Vector *docs = search_docs(index, query);
    print_output(docs);

    for (int i = 0; i < vector_size(index); i++) {
        word_destroy((Word *)vector_get(index, i));
    }
    vector_destroy(index);

    for (int i = 0; i < vector_size(docs); i++) {
        document_destroy((Document *)vector_get(docs, i));
    }
    vector_destroy(docs);
    return 0;
}