#if !defined(_DOCUMENT_H_)
#define _DOCUMENT_H_

#include <stdio.h>

typedef struct Document Document;
typedef char * string;

/**
 * @brief Constrói um Document.
 * @param name O nome do Document.
 * @param freq_word A frequência da palavra no Document.
 * @return Um ponteiro para o Document construído.
 */
Document *document_construct(string name, int freq_word);

/**
 * @brief Destrói um Document.
 * @param doc O Document a ser destruído.
 */
void document_destroy(Document *doc);

/**
 * @brief Obtém a frequência da palavra em um Document.
 * @param doc O Document.
 * @return A frequência da palavra no Document.
 */
int document_get_freq_word(Document *doc);

/**
 * @brief Aumenta a frequência da palavra em um Document.
 * @param doc O Document.
 */
void document_increease_freq_word(Document *doc);

/**
 * @brief Obtém o nome de um Document.
 * @param doc O Document.
 * @return O nome do Document.
 */
string document_get_name(Document *doc);

/**
 * @brief Define a frequência da palavra em um Document.
 * @param doc O Document.
 * @param freq_word A frequência da palavra a ser definida.
 */
void document_set_freq_word(Document *doc, int freq_word);

/**
 * @brief Imprime um Document.
 * @param doc O Document a ser impresso.
 * @param file O arquivo para imprimir o Document.
 */
void document_print(Document *doc, FILE *file);

#endif // _DOCUMENT_H_