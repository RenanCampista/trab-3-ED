#if !defined(_FORWARD_LIST_H_)
#define _FORWARD_LIST_H_
#include <stdio.h>

typedef void * data_type;
typedef struct Node Node;
typedef struct ForwardList ForwardList;
typedef struct ForwardListIterator ForwardListIterator;

/**
 * @brief Constrói um Node.
 * @param value O valor do Node.
 * @param next O próximo Node.
 * @return Um ponteiro para o Node construído.
 */
Node *node_construct(data_type value, Node *next);

/**
 * @brief Destrói um Node.
 * @param n O Node a ser destruído.
 * @param destroy_fn A função para destruir o tipo de dados.
 */
void node_destroy(Node *n, void (*destroy_fn)(data_type));

/**
 * @brief Constrói uma ForwardList.
 * @return Um ponteiro para a ForwardList construída.
 */
ForwardList *forward_list_construct();

/**
 * @brief Destrói uma ForwardList.
 * @param l A ForwardList a ser destruída.
 * @param destroy_fn A função para destruir o tipo de dados.
 */
void forward_list_destroy(ForwardList *l, void (*destroy_fn)(data_type));

/**
 * @brief Destrói um Node de uma ForwardList.
 * @param l A ForwardList.
 */
void forward_list_destroy_node(ForwardList *l);

/**
 * @brief Obtém o tamanho de uma ForwardList.
 * @param l A ForwardList.
 * @return O tamanho da ForwardList.
 */
int forward_list_size(ForwardList *l);

/**
 * @brief Adiciona um elemento no início de uma ForwardList.
 * @param l A ForwardList.
 * @param data O elemento a ser adicionado.
 */
void forward_list_push_front(ForwardList *l, data_type data);

/**
 * @brief Remove um elemento de uma ForwardList.
 * @param l A ForwardList.
 * @param value O valor do elemento a ser removido.
 * @param destroy_fn A função para destruir o tipo de dados.
 */
void forward_list_remove(ForwardList *l, data_type value, void (*destroy_fn)(data_type));

/**
 * @brief Imprime uma ForwardList.
 * @param l A ForwardList.
 * @param print_fn A função para imprimir o tipo de dados.
 */
void forward_list_print(ForwardList *l, void (*print_fn)(data_type));

/**
 * @brief Obtém um elemento de uma ForwardList.
 * @param l A ForwardList.
 * @param data O valor do elemento a ser obtido.
 * @param cmp_fn A função para comparar o tipo de dados.
 * @return O elemento obtido.
 */
data_type forward_list_get(ForwardList *l, data_type data, int (*cmp_fn)(data_type, data_type));

/**
 * @brief Remove e retorna o primeiro elemento de uma ForwardList.
 * @param l A ForwardList.
 * @param destroy_fn A função para destruir o tipo de dados.
 * @return O primeiro elemento da ForwardList.
 */
data_type forward_list_pop_front(ForwardList *l, void (*destroy_fn)(data_type));

/**
 * @brief Ordena uma ForwardList.
 * @param l A ForwardList.
 * @param cmp_fn A função para comparar o tipo de dados.
 */
void forward_list_sort(ForwardList *l, int (*cmp_fn)(data_type, data_type));

/**
 * @brief Obtém o primeiro elemento de uma ForwardList.
 * @param l A ForwardList.
 * @return O primeiro elemento da ForwardList.
 */
data_type forward_list_get_head_data(ForwardList *l);

/**
 * @brief Imprime uma ForwardList em um arquivo.
 * @param l A ForwardList.
 * @param fprint_fn A função para imprimir o tipo de dados em um arquivo.
 * @param file O arquivo.
 */
void forward_list_fprint(ForwardList *l, void (*fprint_fn)(data_type, FILE *), FILE *file);

/**
 * @brief Inicializa um iterador para uma ForwardList.
 * @param l A ForwardList.
 * @return Um ponteiro para o iterador inicializado.
 */
ForwardListIterator *forward_list_iterator_init(ForwardList *l);

/**
 * @brief Destrói um iterador de uma ForwardList.
 * @param iterator O iterador a ser destruído.
 */
void forward_list_iterator_destroy(ForwardListIterator *iterator);

/**
 * @brief Verifica se um iterador tem um próximo elemento.
 * @param iterator O iterador.
 * @return 1 se o iterador tem um próximo elemento, 0 caso contrário.
 */
int forward_list_iterator_has_next(ForwardListIterator *iterator);

/**
 * @brief Obtém o elemento atual de um iterador.
 * @param iterator O iterador.
 * @return O elemento atual do iterador.
 */
data_type forward_list_iterator_get_data(ForwardListIterator *iterator);

/**
 * @brief Avança o iterador para o próximo elemento.
 * @param iterator O iterador.
 */
void forward_list_iterator_next(ForwardListIterator *iterator);

#endif // _FORWARD_LIST_H_