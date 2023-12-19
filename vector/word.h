#if !defined(_WORD_)
#define _WORD_
#include "document.h"
#include "vector.h"


typedef struct Word Word;

/**
 * @brief Constrói uma Word.
 * @param name O nome da Word.
 * @return Um ponteiro para a Word construída.
 */
Word *word_construct(string name);

/**
 * @brief Destrói uma Word.
 * @param word A Word a ser destruída.
 */
void word_destroy(Word *word);

/**
 * @brief Adiciona um Document a uma Word.
 * @param word A Word para adicionar o Document.
 * @param doc O Document a ser adicionado.
 */
void word_add_doc(Word *word, Document *doc);

/**
 * @brief Obtém os Documents de uma Word.
 * @param word A Word para obter os Documents.
 * @return Uma Vector dos Documents.
 */
Vector *word_get_docs(Word *word);

/**
 * @brief Obtém o nome de uma Word.
 * @param word A Word para obter o nome.
 * @return O nome da Word.
 */
string word_get_name(Word *word);

/**
 * @brief Obtém um Document de uma Word pelo nome do documento.
 * @param word A Word para obter o Document.
 * @param file_name O nome do arquivo do Document a ser obtido.
 * @return O Document com o nome de arquivo especificado.
 */
Document *word_get_doc_from_file_name(Word *word, string file_name);

/**
 * @brief Imprime uma Word.
 * @param word A Word a ser impressa.
 * @param file O arquivo para imprimir a Word.
 */
void word_print(Word *word, FILE *file);

/**
 * @brief Verifica se uma Word contém um Document com um nome de arquivo especificado.
 * @param word A Word para verificar.
 * @param file_name O nome do arquivo do Document a verificar.
 * @return 1 se a Word contém o Document, 0 caso contrário.
 */
int word_contains_doc(Word *word, string file_name);

#endif // _WORD_