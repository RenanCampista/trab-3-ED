#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"
#include "binary_tree.h"
#include "word.h"

BinaryTree *load_index(string dir_index_file) {
    FILE *fp = fopen(dir_index_file, "r");
    if (fp == NULL)
        exit(printf("Error: load_index: could not open file %s.\n\n", dir_index_file));

    int n_words;
    fscanf(fp, "%d", &n_words);
    BinaryTree *index = binary_tree_construct();

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
        binary_tree_add(index, word_get_name(w), w);
    }
    fclose(fp);
    return index;
}

void documents_freq_analysis(BinaryTree *docs, BinaryTree *recommendations) {
    Vector *docs_vector = binary_tree_all_data(docs);
    for (int i = 0; i < vector_size(docs_vector); i++) {
        Document *d = (Document *)vector_get(docs_vector, i);
        string key = document_get_name(d);

        // Se o documento ainda não foi adicionado na arvore de recomendações
        if (!binary_tree_contains_key(recommendations, key)) {
            // fazer uma copia do documento pois será mais facil de desalocar no final
            Document *doc = document_construct(document_get_name(d), document_get_freq_word(d));
            // Adiciona o documento na arvore de recomendações
            binary_tree_add(recommendations, key, doc);
        } else {
            // Se o documento já foi adicionado, apenas aumenta a frequencia da palavra
            Document *doc = binary_tree_get(recommendations, key);
            if (doc != NULL)
                document_set_freq_word(doc, document_get_freq_word(doc) + document_get_freq_word(d));
        }
    }
    
    vector_destroy(docs_vector);
}

ForwardList *get_docs_from_binary_tree(Vector *unique, BinaryTree *index, BinaryTree *recommendations){
    ForwardList *doc_list = forward_list_construct();
    // Pega os documentos da arvore de recomendações e adiciona na lista de documentos para poder ordenar
    for (int i = 0; i < vector_size(unique); i++) {
        string word = (string)vector_get(unique, i);
        Word *w = binary_tree_get(index, word);
        if (w == NULL) continue;
        BinaryTree *docs = word_get_docs(w);
        if (binary_tree_size(docs) > 0) {
            Vector *docs_vector = binary_tree_all_data(docs);

            for (int i = 0; i < vector_size(docs_vector); i++) {
                Document *d = (Document *) vector_get(docs_vector, i);
                string key = document_get_name(d);

                if (binary_tree_contains_key(recommendations, key)) {
                    Document *doc = binary_tree_get(recommendations, key);
                    if (doc != NULL) {
                        Document *new_doc = document_construct(document_get_name(doc), document_get_freq_word(doc));
                        forward_list_push_front(doc_list, new_doc);
                    }
                }
            }
            vector_destroy(docs_vector);
        }
    }

    return doc_list;
}

ForwardList *search_docs(BinaryTree *index, string query) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    Vector *words = string_split(query);
    // Remove as palavras repetidas
    Vector *unique = vector_unique(words, string_compare);

    // Cria uma arvore binaria para armazenar os documentos recomendados e suas frequencias
    BinaryTree *recommendations = binary_tree_construct();

    for (int i = 0; i < vector_size(unique); i++) {
        string word = (string)vector_get(unique, i);

        Word *w = binary_tree_get(index, word);
        if (w == NULL) continue;
   
        // Se a palavra existe no indice, analisa os documentos que ela aparece
        BinaryTree *docs = word_get_docs(w);

        // Se a palavra não aparece em nenhum documento, não é necessário analisar
        if (binary_tree_size(docs) > 0) 
            documents_freq_analysis(docs, recommendations);
        
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de busca: %.3f segundos\n", cpu_time_used);

    ForwardList *doc_list = get_docs_from_binary_tree(unique, index, recommendations);
    free_data(words);
    vector_destroy(unique);
    binary_tree_destroy(recommendations, (data_type)document_destroy);
    forward_list_sort(doc_list, (data_type)document_compare_freqs);

    return doc_list;
}

void print_output(ForwardList *docs) {
    ForwardListIterator *it = forward_list_iterator_init(docs);
    int cont = 0;
    while(forward_list_iterator_has_next(it)) {
        Document *doc = forward_list_iterator_get_data(it);
        printf("%s: %d\n", document_get_name(doc), document_get_freq_word(doc));
        cont++;
        if (cont == 10)
            break;
        forward_list_iterator_next(it);
    }
    forward_list_iterator_destroy(it);
}

int main(int argc, char *argv[]) {
    if (argc != 2) 
        exit(printf("Usage: %s <size>\n", argv[0]));

    string dir_index_file = argv[1];
    BinaryTree *index = load_index(dir_index_file);
    char query[1000];
    printf("Query: ");
    scanf("%[^\n]", query);
    ForwardList *docs = search_docs(index, query);
    print_output(docs);

    forward_list_destroy(docs, (data_type)document_destroy);
    binary_tree_destroy(index, (data_type)word_destroy);

    return 0;
}