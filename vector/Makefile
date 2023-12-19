build_index:
	gcc -Wall -Wextra -Werror -g -o build_index forward_list.c vector.c document.c utils.c word.c build_index.c -lm
search_engine:
	gcc -Wall -Wextra -Werror -g -o search_engine forward_list.c vector.c document.c utils.c word.c search_engine.c -lm
clean_build_index:
	rm -f build_index
clean_search_engine:
	rm -f search_engine
run_build_index:
	./build_index
run_search_engine:
	./search_engine
valgrind_build_index:
	valgrind --track-origins=yes --leak-check=full ./build_index
valgrind_search_engine:
	valgrind --track-origins=yes --leak-check=full ./search_engine
