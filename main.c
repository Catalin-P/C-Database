// Picior Catalin 312CB
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structures.h"
#include "fun_decl.h"

int main() {
    t_db *database;
    char cmd[MAX_CMD_LEN], *token, *command;
    for (;;) {
        // preluam comanda de la stdin
        fgets(cmd, MAX_CMD_LEN, stdin);
        // eliminam caract newline de la sfarsit
        cmd[strlen(cmd) - 1] = '\0';
        // tokenizam pentru a obtine numele comenzii date
        token = strtok(cmd, " ");
        command = token;
        // caz initializare db
        if (strcmp(command, "INIT_DB") == 0) {
            // tokenizam numele db
            token = strtok(NULL, " ");
            database = INIT_DB(token);
            continue;
        }
        // caz stergere db
        if (strcmp(command, "DELETE_DB") == 0) {
            DELETE_DB(&database);
            // iesim din for; ultima comanda data
            break;
        }
        // caz afisare db
        if (strcmp(token, "PRINT_DB") == 0) {
            PRINT_DB(database);
            continue;
        }
        // caz creare tabel
        if (strcmp(command, "CREATE") == 0) {
            // tokenizam numele tabelului
            token = strtok(NULL, " ");
            char *table_name = token;
            // tokenizam tipul de date al tabelului
            token = strtok(NULL, " ");
            char *data_type = token;
            // iteram pana ajungem la lista cu numele coloanelor
            while ((*token) != 0) {
                token++;
            }
            token++;
            // cream tabelul dupa tipul de date aferent
            char *columns_names_start = token;
            if (strcmp(data_type, "INT") == 0) {
                CREATE_TABLE(database, table_name, 0, columns_names_start);
                continue;
            }
            if (strcmp(data_type, "FLOAT") == 0) {
                CREATE_TABLE(database, table_name, 1, columns_names_start);
                continue;
            }
            if (strcmp(data_type, "STRING") == 0) {
                CREATE_TABLE(database, table_name, 2, columns_names_start);
                continue;
            } else {
                printf("Unknown data type: \"%s\".\n", data_type);
            }
        }
        // caz printare tabel
        if (strcmp(command, "PRINT") == 0) {
            // tokenizam numele tabelului
            token = strtok(NULL, " ");
            int is_table = PRINT_TABLE(database, token);
            if (!is_table) {
                printf("Table \"%s\" not found in database.\n", token);
            }
            continue;
        }
        // caz stergere tabel
        if (strcmp(command, "DELETE") == 0) {
            // tokenizam numele tabelului
            token = strtok(NULL, " ");
            char *table_name = token;
            token = strtok(NULL, " ");
            // subcaz stergere tabel 
            if (!token) {
                int is_table = DELETE_TABLE(database, table_name);
                if (!is_table) {
                    printf("Table \"%s\" not found in database.\n", table_name);
                }
                continue;
            } else {
                // subcaz stergere linie
                // tokenizam parametri dati
                char *column_name = token;
                token = strtok(NULL, " ");
                char *condition = token;
                token = strtok(NULL, " ");
                char *value = token;
                int found =
                DELETE_LINE(database, table_name,
                    column_name, condition, value);
                if (!found) {
                    printf("Table \"%s\" not found in database.\n",
                        table_name);
                }
                continue;
            }
        }
        // caz cautare linie
        if (strcmp(command, "SEARCH") == 0) {
            // tokenizam parametri dati
            token = strtok(NULL, " ");
            char *table_name = token;
            token = strtok(NULL, " ");
            char *column_name = token;
            token = strtok(NULL, " ");
            char *condition = token;
            token = strtok(NULL, " ");
            char *value = token;
            int found =
            SEARCH(database, table_name, column_name, condition, value);
            if (!found) {
                printf("Table \"%s\" not found in database.\n", table_name);
            }
            continue;
        }
        // caz add linie
        if (strcmp(command, "ADD") == 0) {
            // tokenizam numele tabelului
            token = strtok(NULL, " ");
            char *table_name = token;
            // tokenizam lista de argumente
            while ((*token) != 0) {
                token++;
            }
            token++;
            char *values_list = token;
            int found = ADD(database, table_name, values_list);
            if (!found) {
                printf("Table \"%s\" not found in database.\n", table_name);
            }
            continue;
        }
        // caz stergere linii tabel
        if (strcmp(command, "CLEAR") == 0) {
            // tokenizam numele tabelului
            token = strtok(NULL, " ");
            char *table_name = token;
            // apelam functia de stergere
            int found = CLEAR(database, table_name);
            if (!found) {
                printf("Table \"%s\" not found in database.\n", table_name);
            }
            continue;
        }
        printf("Unknown command: \"%s\".\n", command);
    }
}
