#if !defined(_BINARY_TREE_H_)
#define _BINARY_TREE_H_
#include <stdio.h>
#include "vector.h"

typedef void * data_type;
typedef char * key_type;
typedef struct Node Node;
typedef struct BinaryTree BinaryTree;

/**
 * @brief Constrói uma BinaryTree.
 * @return Um ponteiro para a BinaryTree construída.
 */
BinaryTree* binary_tree_construct();

/**
 * @brief Destrói uma BinaryTree.
 * @param tree A BinaryTree a ser destruída.
 * @param free_data A função para destruir o tipo de dados.
 */
void binary_tree_destroy(BinaryTree *tree, void (*free_data)(data_type));

/**
 * @brief Destrói os nós de uma BinaryTree.
 * @param tree A BinaryTree.
 */
void binary_tree_destroy_nodes(BinaryTree *tree);

/**
 * @brief Adiciona um elemento a uma BinaryTree.
 * @param tree A BinaryTree.
 * @param key A chave do elemento a ser adicionado.
 * @param value O valor do elemento a ser adicionado.
 */
void binary_tree_add(BinaryTree *tree, key_type key, data_type value);

/**
 * @brief Busca um elemento em uma BinaryTree.
 * @param tree A BinaryTree.
 * @param key A chave do elemento a ser buscado.
 * @return O valor do elemento buscado.
 */
data_type binary_tree_search(BinaryTree *tree, key_type key);

/**
 * @brief Remove um elemento de uma BinaryTree.
 * @param tree A BinaryTree.
 * @param key A chave do elemento a ser removido.
 */
void binary_tree_remove(BinaryTree *tree, key_type key);

/**
 * @brief Obtém o tamanho de uma BinaryTree.
 * @param tree A BinaryTree.
 * @return O tamanho da BinaryTree.
 */
int binary_tree_size(BinaryTree *tree);

/**
 * @brief Obtém um elemento de uma BinaryTree.
 * @param tree A BinaryTree.
 * @param key A chave do elemento a ser obtido.
 * @return O valor do elemento obtido.
 */
data_type binary_tree_get(BinaryTree *tree, key_type key);

/**
 * @brief Verifica se uma BinaryTree contém uma chave específica.
 * @param tree A BinaryTree.
 * @param key A chave a ser verificada.
 * @return 1 se a BinaryTree contém a chave, 0 caso contrário.
 */
int binary_tree_contains_key(BinaryTree *tree, key_type key);

/**
 * @brief Imprime todos os elementos de uma BinaryTree em um arquivo.
 * @param tree A BinaryTree.
 * @param fprint A função para imprimir o tipo de dados em um arquivo.
 * @param file O arquivo.
 */
void binary_tree_fprint_all_data(BinaryTree *tree, void (*fprint)(data_type, FILE *), FILE *file);

/**
 * @brief Obtém todos os elementos de uma BinaryTree.
 * @param tree A BinaryTree.
 * @return Um vetor com todos os elementos da BinaryTree.
*/
Vector *binary_tree_all_data(BinaryTree *tree);

#endif // _BINARY_TREE_H_