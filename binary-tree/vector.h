#if !defined(_VECTOR_H_)
#define _VECTOR_H_

typedef void * data_type;
typedef struct Vector Vector;

/**
 * @brief Construct a new Vector object
 *  @return Ponteiro para o novo Vector.
*/
Vector *vector_construct();

/** @brief Adiciona um elemento no final do vetor.
 * @param v Ponteiro para a estrutura do Vector.
 *  @param val O valor a ser adicionado.
 */
void vector_push_back(Vector *v, data_type val);

/**
 * @brief Adiciona um elemento no início do vetor.
 * @param v Ponteiro para a estrutura do Vector.
 * @param val O valor a ser adicionado.
 * @return O elemento na posição i.
 */
data_type vector_get(Vector *v, int i);

/**
 * @brief Define o valor de um elemento do vetor.
 * @param v Ponteiro para a estrutura do Vector.
 * @param i A posição do elemento.
 * @param val O valor a ser definido.
*/
void vector_set(Vector *v, int i, data_type val);

/**
 * @brief Retorna o tamanho do vetor.
 * @param v Ponteiro para a estrutura do Vector.
 * @return O tamanho do vetor.
*/
int vector_size(Vector *v);

/**
 * @brief Remove um elemento do vetor.
 * @param v Ponteiro para a estrutura do Vector.
 * @param i A posição do elemento a ser removido.
 * @return O elemento removido.
*/
data_type vector_remove(Vector *v, int i);

/**
 * @brief Remove o primeiro elemento do vetor e ordena os demais elementos para preencher o espaço.
 * @param v Ponteiro para a estrutura do Vector.
 * @return O elemento removido.
*/
data_type vector_pop_front(Vector *v);

/**
 * @brief Remove o último elemento do vetor.
 * @param v Ponteiro para a estrutura do Vector.
 * @return O elemento removido.
*/
data_type vector_pop_back(Vector *v);

/**
 * @brief Insere um elemento em uma posição do vetor e reorganiza os demais elementos para abrir espaço.
 * @param v Ponteiro para a estrutura do Vector.
 * @param i A posição do elemento a ser inserido.
 * @param val O valor a ser inserido.
*/
void vector_insert(Vector *v, int i, data_type val);

/**
 * @brief Troca a posição de dois elementos do vetor.
 * @param v Ponteiro para a estrutura do Vector.
 * @param i A posição do primeiro elemento.
 * @param j A posição do segundo elemento.
*/
void vector_swap(Vector *v, int i, int j);

/**
 * @brief Ordena o vetor usando o algoritmo Bubble Sort.
 * @param v Ponteiro para a estrutura do Vector.
*/
void vector_sort(Vector *v);

/**
 * @brief Procura um elemento no vetor usando o algoritmo de busca binária.
 * @param v Ponteiro para a estrutura do Vector.
 * @param val O valor a ser procurado.
*/
int vector_binary_search(Vector *v, data_type val);

/**
 * @brief Inverte a ordem dos elementos do vetor.
 * @param v Ponteiro para a estrutura do Vector.
*/
void vector_reverse(Vector *v);

/**
 * @brief Copia um vetor.
 * @param v Ponteiro para a estrutura do Vector.
 * @return Ponteiro para o novo Vector.
*/
Vector *vector_copy(Vector *v);

/**
 * @brief Limpa o vetor.
 * @param v Ponteiro para a estrutura do Vector.
*/
void vector_clear(Vector *v);

/**
 * @brief Retorna o índice do primeiro elemento igual a val.
 * @param v Ponteiro para a estrutura do Vector.
 * @param val O valor a ser procurado.
 * @param cmp Função de comparação.
 * @return O índice do primeiro elemento igual a val. Caso não encontre, retorna -1.
*/
int vector_find(Vector *v, data_type val, int (*cmp)(data_type, data_type)) ;

/**
 * @brief Remove elementos duplicados do vetor.
 * @param v Ponteiro para a estrutura do Vector.
 * @param cmp Função de comparação.
 * @return Ponteiro para o novo Vector.
*/
Vector *vector_unique(Vector *v, int (*cmp)(data_type, data_type));

/**
 * @brief Desaloca o vetor.
 * @param v Ponteiro para a estrutura do Vector.
*/
void vector_destroy(Vector *v);

#endif // _VECTOR_H_