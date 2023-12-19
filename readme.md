# Informações gerais
Cada pasta contém dois programas feitos com uma estrutura de dados diferente para resolver o mesmo problema.

A struct word foi adapatada para cada versão. Ela contém uma string para salvar a palavra e uma estrutura de dados que armazena os documentos em que ela aparece.
A struct document armazena o diretório que ele se encontra e a frquência da palavra no documento.

# Instruções de compilação do Makefile
**build_index:** compila o programa que faz o papel de indexador. Deve ser usado antes do search_engine.

**search_engine:** compila o programa que faz a busca no índice. Deve ser usado depois do build_index.

**run_build_index:** executa o programa build_index sem utilizar o valgrind.

**run_search_engine:** executa o programa search_engine sem utilizar o valgrind.

**valgrind_build_index:** executa o programa build_index utilizando o valgrind.

**valgrind_search_engine:** executa o programa search_engine utilizando o valgrind.

**OBS.: Para executar as instruções run_build_index e valgrind_build_index é necessário passar o diretorio onde se encontra o arquivo files.txt e o nome do arquivo de saida**

**OBS.: Para executar as instruções run_search_engine e valgrind_search_engine é necessário passar o nome do arquivo que o programa indexador gerou.**