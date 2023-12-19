#if !defined(_UTILS_H_)
#define _UTILS_H_

#include "hash_table.h"
#include "vector.h"
#include "document.h"
#include "word.h"
#include "forward_list.h"

/**
 * @brief Função de hash para strings.
 * @param hash A HashTable.
 * @param key A chave.
 * @return O índice da chave na HashTable.
 */
int hash_function(HashTable *hash, data_type key);

/**
 * @brief Compara uma palavra com uma chave.
 * @param word A palavra.
 * @param key A chave.
 * @return 1 se o documento tem o nome especificado, 0 caso contrário.
 */
int word_hash_compare(data_type word, data_type key);

/**
 * @brief Compara um documento com uma chave.
 * @param document O documento.
 * @param key A chave.
 * @return 1 se o documento tem o nome especificado, 0 caso contrário.
 */
int document_hash_compare(data_type document, data_type key);

/**
 * @brief Imprime um documento.
 * @param document O documento.
 * @param file O arquivo para imprimir o documento.
 */
void fprint_document(data_type document, FILE *file);

/**
 * @brief Divide uma string em um vetor de strings.
 * @param str A string a ser dividida.
 * @return Um vetor de strings.
 */
Vector *string_split(string str);

/**
 * @brief Libera a memória alocada por um vetor de strings.
 * @param words O vetor de strings.
 */
void free_data(Vector *words);

/**
 * @brief Compara duas strings.
 * @param s1 A primeira string.
 * @param s2 A segunda string.
 * @return Um número negativo se s1 < s2, 0 se s1 == s2 e um número positivo se s1 > s2.
 */
int string_compare(data_type s1, data_type s2);

/**
 * @brief Compara dois documentos.
 * @param d1 O primeiro documento.
 * @param d2 O segundo documento.
 * @return 1 se d1 == d2, 0 caso contrário
 */
int document_compare(data_type d1, data_type d2);

/**
 * @brief Compara a frequência de dois documentos.
 * @param d1 O primeiro documento.
 * @param d2 O segundo documento.
 * @return 1 se d1 > d2, 0 se forem iguais e -1 se d1 < d2.
*/
int document_compare_freqs(data_type d1, data_type d2);

#endif // _UTILS_H_
