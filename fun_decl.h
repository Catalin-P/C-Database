//Picior Catalin 312CB
// Fsier de declarare al functiilor
#ifndef __DEFINITIONS__
#define __DEFINITIONS__

typedef void(*disp_lines)(void *);
t_db * INIT_DB(char * name);
void DELETE_DB(t_db **database);
void PRINT_DB(t_db *database);
void PRINT_KNOWN_TABLE(t_table *table, disp_lines fun);
int PRINT_TABLE(t_db *database, char *table_name);
int CREATE_TABLE(t_db *database, char *name,
	int data_type, char *columns_name);
int SEARCH(t_db *database, char *table_name,
	char *column_name, char *condition, char *value);
int DELETE_LINE(t_db *database, char *table_name,
	char *column_name, char *condition, char *value);
int ADD(t_db *database, char *table_name, char *values_list);
int DELETE_TABLE(t_db *database, char *table_name);
int CLEAR(t_db *database, char *table_name);
void free_int_lines(void *lines);
void free_float_lines(void *lines);
void free_string_lines(void *lines);
void free_int_line(t_table *table, void *line);
void free_float_line(t_table *table, void *line);
void free_string_line(t_table *table, void *line);
int find_column_number(t_table *table, char *column_name);
typedef void (*Distr_lines)(void*);
typedef void (*disp_lines)(void*);

#endif
