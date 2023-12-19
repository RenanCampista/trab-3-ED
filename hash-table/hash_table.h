#if !defined(_HASH_TABLE_H_)
#define _HASH_TABLE_H_

#include <stdio.h>
#include "vector.h"

typedef struct Pair Pair;
typedef struct HashTable HashTable;
typedef int (*HashFunction)(HashTable *h, data_type);
typedef int (*CmpFunction)(data_type k1, data_type k2);

/**
 * @brief Constrói um Pair.
 * @param key A chave do Pair.
 * @param val O valor do Pair.
 * @return Um ponteiro para o Pair construído.
 */
Pair *_hash_pair_construct(data_type key, data_type val);

/**
 * @brief Destrói um Pair.
 * @param pair O Pair a ser destruído.
 */
void _hash_pair_destroy(Pair *pair, void (*free_data)(data_type));

/**
 * @brief Obtém o item de um Pair.
 * @param item O Pair.
 * @return O item do Pair.
 */
data_type _hash_pair_get_item(Pair *item);

/**
 * @brief Constrói uma HashTable.
 * @param table_size O tamanho da tabela.
 * @param hash_fn A função hash.
 * @param cmp_fn A função de comparação.
 * @return Um ponteiro para a HashTable construída.
 */
HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn);

/**
 * @brief Destrói uma HashTable.
 * @param h A HashTable a ser destruída.
 */
void hash_table_destroy(HashTable *h, void (*free_data)(data_type));

/**
 * @brief Destrói os buckets de uma HashTable.
 * @param h A HashTable.
 */
void hash_table_destroy_buckets(HashTable *h);

/**
 * @brief Obtém o tamanho de uma HashTable.
 * @param h A HashTable.
 * @return O tamanho da HashTable.
 */
int hash_table_size(HashTable *h);

/**
 * @brief Obtém o tamanho da tabela de uma HashTable.
 * @param h A HashTable.
 * @return O tamanho da tabela da HashTable.
 */
int hash_table_get_table_size(HashTable *h);

/**
 * @brief Insere um elemento em uma HashTable.
 * @param h A HashTable.
 * @param key A chave do elemento a ser inserido.
 * @param val O valor do elemento a ser inserido.
 */
void hash_table_insert(HashTable *h, data_type key, data_type val);

/**
 * @brief Verifica se uma HashTable contém uma chave específica.
 * @param h A HashTable.
 * @param key A chave a ser verificada.
 * @return 1 se a HashTable contém a chave, 0 caso contrário.
 */
int hash_table_contains_key(HashTable *h, data_type key);

/**
 * @brief Obtém um Pair de uma HashTable.
 * @param h A HashTable.
 * @param key A chave do Pair a ser obtido.
 * @return O Pair obtido.
 */
Pair *hash_table_get(HashTable *h, data_type key);

/**
 * @brief Imprime todos os dados de uma HashTable em um arquivo.
 * @param h A HashTable.
 * @param fprint_fn A função para imprimir o tipo de dados em um arquivo.
 * @param file O arquivo.
 */
void hash_table_fprint_all_data(HashTable *h, void (*fprint_fn)(data_type, FILE *), FILE *file);

/**
 * @brief Obtém todos os pares de uma HashTable.
 * @param h A HashTable.
 * @return Um vetor com todos os pares da HashTable.
*/
Vector *hash_table_all_pairs(HashTable *h);

#endif // _HASH_TABLE_H_