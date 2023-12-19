#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "binary_tree.h"
#include "word.h"
#include "document.h"
#include "forward_list.h"
#include "utils.h"

void analyze_word(Vector *words, BinaryTree *index, char full_file_name[200]) {
    // Para cada palavra do arquivo
    for (int i = 0; i < vector_size(words); i++) {
        string w = (string)vector_get(words, i);

        // Se a palavra já existe no índice
        if (binary_tree_contains_key(index, w)) {
            Word *word = (Word *)binary_tree_get(index, w);
            Document *doc = word_get_doc_from_file_name(word, full_file_name);
            // Se o documento já existe na palavra, ou seja, a palavra já apareceu no documento
            if (doc != NULL) {
                // Aumenta a frequência da palavra no documento
                document_increease_freq_word(doc);
            } else {
                // Se não, adiciona o documento na palavra
                Document *new_doc = document_construct(full_file_name, 1);
                word_add_doc(word, new_doc);
            }
        } else {
            // Se não, cria uma nova palavra, adiciona o documento e adiciona a palavra no índice
            Word *new_word = word_construct(w);
            Document *new_doc = document_construct(full_file_name, 1);
            word_add_doc(new_word, new_doc);
            binary_tree_add(index, word_get_name(new_word), new_word);
        }
    }
}

void read_file_words(char full_file_name[200], BinaryTree *index) {
    FILE *word_file = fopen(full_file_name, "r");
    if (word_file == NULL)
        exit(printf("Error: build_index: could not open file %s.\n\n", full_file_name));

    char line[10000];
    while (fgets(line, sizeof(line), word_file) != NULL) {
        // Remova o caractere de nova linha, se estiver presente
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        Vector *words = string_split(line);
        analyze_word(words, index, full_file_name);

        // Liberar a memória alocada para as palavras
        free_data(words);
    }
    fclose(word_file);
}

BinaryTree *build_index(string dir_in) {
    char full_dir[100];
    sprintf(full_dir, "%s/files.txt", dir_in);

    FILE *fp = fopen(full_dir, "r");
    if (fp == NULL)
        exit(printf("Error: build_index: could not open file %s.\n\n", full_dir));

    clock_t start, end;
    double cpu_time_used;
    start = clock();

    BinaryTree *index = binary_tree_construct();
    char file_name[100];
    while(fscanf(fp, "%s", file_name) != EOF) {
        char full_file_name[200];
        sprintf(full_file_name, "%s/%s", dir_in, file_name);

        // Abre o arquivo e lê as palavras
        read_file_words(full_file_name, index);
    }
    fclose(fp);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Index built in %.3f seconds.\n", cpu_time_used);
    
    return index;
}

void save_index(BinaryTree *index, string dir_out) {
    FILE *file = fopen(dir_out, "w");
    if (file == NULL)
        exit(printf("Error: save_index: could not open file %s.\n\n", dir_out));

    int n_words = binary_tree_size(index);
    fprintf(file, "%d\n", n_words);
    
    binary_tree_fprint_all_data(index, (data_type)word_print, file);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) 
        exit(printf("Usage: %s <size>\n", argv[0]));
    
    string dir_in = argv[1];
    BinaryTree *index = build_index(dir_in);
    save_index(index, argv[2]);

    binary_tree_destroy(index, (data_type)word_destroy);
    return 0;
}
