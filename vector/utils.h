#if !defined(_UTILS_H_)
#define _UTILS_H_

#include "vector.h"
#include "document.h"
#include "forward_list.h"

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
 * @brief Compara duas palavras.
 * @param w A primeira palavra.
 * @param name A segunda palavra.
 * @return Um número 1 se w == name, 0 caso contrário.
 */
int word_compare(data_type w, data_type name);

/**
 * @brief Compara dois documentos.
 * @param doc1 O primeiro documento.
 * @param doc2 O segundo documento.
 * @return Um número negativo se doc1 < doc2, 0 se doc1 == doc2 e um número positivo se doc1 > doc2.
*/
int document_compare_sort(data_type doc1, data_type doc2);

/**
 * @brief Compara a frequência de dois documentos.
 * @param d1 O primeiro documento.
 * @param d2 O segundo documento.
 * @return 1 se d1 > d2, 0 se forem iguais e -1 se d1 < d2.
*/
int document_compare_freqs(data_type d1, data_type d2);

#endif // _UTILS_H_
