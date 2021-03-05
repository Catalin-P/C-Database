build:
	gcc -g data_definition_functions.c data_query_fun.c data_man_fun.c main.c -o tema1
run: 
	./tema1
clean:
	rm tema1
