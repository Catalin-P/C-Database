// Picior Catalin 312CB
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "fun_decl.h"

// functie de adaugare a unei linii cu elemente de tip int
// intr-un tabel
int add_int_line(t_table *table, char *values_list) {
    // pointam catre prima linie din tabel
    t_intLine *crt_line = (t_intLine *)(table -> lines), *last;
    // alocam o linie 
    t_intLine *aux_line = (t_intLine *) malloc(sizeof(t_intLine));
    // verificam alocarea
    if (!aux_line) {
        return 1;
    }
    // setam campurile celulei de tip linie la NULL
    aux_line -> next = NULL;
    aux_line -> cells = NULL;
    // cautam ultima linie din tabel
    for (last = NULL; crt_line != NULL;
        last = crt_line, crt_line = crt_line -> next) {}
    // verificam daca adaugam linia la inceput
    if (!last) {
        // modificam capul de lista
        table -> lines = aux_line;
    } else {
        // adugam linia la sfarsit
        last -> next = aux_line;
    }
    // pointam catre prima celula a liniei alocate
    t_intCell *last_cell = aux_line -> cells;
    // alocam o celula de tip int
    t_intCell *aux_cell = (t_intCell*) malloc(sizeof(t_intCell));
    // verificam alocarea
    if (!aux_cell) {
        // eliberam linia auxiliara
        free(aux_line);
        return 1;
    }
    // setam urm element al lui aux la NULL
    aux_cell -> next = NULL;
    // setam capul listei de celule
    t_intCell *head_cell = aux_cell;
    aux_line -> cells = aux_cell;
    // tokenizam valoarea ce trebuie pusa in prima celula
    char *crt_value = strtok(values_list, " ");
    // transformam val celului la int
    int crt_int_value = atoi(crt_value);

    aux_cell -> value = crt_int_value;
    // actualizam ultima celula din lista
    last_cell = aux_cell;
    // tokenizam lista de valori in continuare
    crt_value = strtok(NULL, " ");
    // cat timp lista de valori e nevida
    while (crt_value) {
        // transformam valoarea la int
        crt_int_value = atoi(crt_value);
        // alocam o celula de tip int
        aux_cell = (t_intCell*) malloc(sizeof(t_intCell));
        // verificam alocarea
        // daca nu a reusit, eliberam tot ce a fost
        // alocat precedent
        if (!aux_cell) {
            while (head_cell) {
                aux_cell = head_cell;
                head_cell = head_cell -> next;
                free(aux_cell);
            }
            free(aux_line);
            return 1;
        }
        // setam urm el al lui aux la NULL
        aux_cell -> next = NULL;
        // atribuim valoarea celului
        aux_cell -> value = crt_int_value;
        // inseram la sfarsit in lista
        last_cell -> next = aux_cell;
        // actualizam ultima celula
        last_cell = aux_cell;
        // continuam tokenizarea
        crt_value = strtok(NULL, " ");
    }
    // cod alocare cu succes
    return 0;
}
// functie de adaugare a unei linii cu elemente de tip float
// intr-un tabel
// aceeasi functionalite cu functia precedenta si scris aproape identic
// voi comenta doar diferentele
int add_float_line(t_table *table, char *values_list) {
    t_floatLine *crt_line = (t_floatLine*)(table -> lines), *last;
    t_floatLine *aux_line = (t_floatLine*) malloc(sizeof(t_floatLine));
    if (!aux_line) {
        return 1;
    }
    aux_line -> next = NULL;
    aux_line -> cells = NULL;
    for (last = NULL; crt_line != NULL;
        last = crt_line, crt_line = crt_line -> next) {}
    if (!last) {
        table -> lines = aux_line;
    } else {
        last -> next = aux_line;
    }
    t_floatCell *last_cell = aux_line -> cells;
    t_floatCell *aux_cell = (t_floatCell*) malloc(sizeof(t_floatCell));
    if (!aux_cell) {
        free(aux_line);
        return 1;
    }
    aux_cell -> next = NULL;
    t_floatCell *head_cell = aux_cell;
    aux_line -> cells = aux_cell;
    char *crt_value = strtok(values_list, " ");
    // transformam val celulei la float
    float crt_float_value = atof(crt_value);
    aux_cell -> value = crt_float_value;
    last_cell = aux_cell;
    crt_value = strtok(NULL, " ");
    while (crt_value) {
        // transformam val celulei la float
        crt_float_value = atof(crt_value);
        aux_cell = (t_floatCell*) malloc(sizeof(t_floatCell));
        if (!aux_cell) {
            while (head_cell) {
                aux_cell = head_cell;
                head_cell = head_cell -> next;
                free(aux_cell);
            }
            free(aux_line);
            return 1;
        }
        aux_cell -> next = NULL;
        aux_cell -> value = crt_float_value;
        last_cell -> next = aux_cell;
        last_cell = aux_cell;
        crt_value = strtok(NULL, " ");
    }
    return 0;
}
// functie de adaugare a unei linii cu elemente de tip string
// intr-un tabel
// aceeasi functionalite cu functia precedenta si scris aproape identic
// voi comenta doar diferentele
int add_string_line(t_table *table, char *values_list) {
    t_stringLine *crt_line = (t_stringLine*)(table -> lines), *last;
    t_stringLine *aux_line = (t_stringLine*) malloc(sizeof(t_stringLine));
    if (!aux_line) {
        return 1;
    }
    aux_line -> next = NULL;
    aux_line -> cells = NULL;
    for (last = NULL; crt_line != NULL;
        last = crt_line, crt_line = crt_line -> next) {}
    if (!last) {
        table -> lines = aux_line;
    } else {
        last -> next = aux_line;
    }
    t_stringCell *aux_cell;
    t_stringCell *last_cell = NULL;
    t_stringCell *head_cell = (t_stringCell*) malloc(sizeof(t_stringCell));
    if (!head_cell) {
        free(aux_line);
        return 1;
    }
    head_cell -> next = NULL;
    aux_line -> cells = head_cell;
    char *crt_value = strtok(values_list, " ");
    head_cell -> value = (char*) malloc(strlen(crt_value) + 1);
    // valoarea se copieza cu strcpy direct, fara nicio transformare
    strcpy(head_cell -> value, crt_value);
    last_cell = head_cell;
    crt_value = strtok(NULL, " ");
    while (crt_value) {
        aux_cell = (t_stringCell*) malloc(sizeof(t_stringCell));
        aux_cell -> value = (char*) malloc(strlen(crt_value) + 1);
        if (!aux_cell) {
            while (head_cell) {
                aux_cell = head_cell;
                head_cell = head_cell -> next;
                free(aux_cell);
            }
            free(aux_line);
            return 1;
        }
        aux_cell -> next = NULL;
        // valoarea se copieza cu strcpy direct, fara nicio transformare
        strcpy(aux_cell -> value, crt_value);
        last_cell -> next = aux_cell;
        last_cell = aux_cell;
        crt_value = strtok(NULL, " ");
    }
    return 0;
}
int ADD(t_db *database, char *table_name, char *values_list) {
    t_table *p = database -> tables;
    int table_data_type;
    for (; p != NULL; p = p -> next) {
        if (strcmp(p -> name, table_name) == 0) {
            table_data_type = p -> type;
            switch (table_data_type) {
            case 0:
                add_int_line(p, values_list);
                break;
            case 1:
                add_float_line(p, values_list);
                break;
            case 2:
                add_string_line(p, values_list);
                break;
            }
            return 1;
        }
    }
    return 0;
}
// functie de eliberare a liniilor unui tabel
int CLEAR(t_db *database, char *table_name) {
    // pointam catre primul tabel
    t_table *p = database -> tables;
    int table_data_type;
    // parcurgem lista de tabele
    for (; p != NULL; p = p -> next) {
        // cautam tabelul cu numele transmis ca parametru
        if (strcmp(p -> name, table_name) == 0) {
            table_data_type = p -> type;
            // eliberam liniile in functie de tipul de date
            switch (table_data_type) {
            case 0:
                free_int_lines(p -> lines);
                break;
            case 1:
                free_float_lines(p -> lines);
                break;
            case 2:
                free_string_lines(p -> lines);
                break;
            }
            // subliniam ca tabelul nu mai are linii
            p -> lines = NULL;
            // cod pentru stergere cu succes
            return 1;
        }
    }
    // cod tabel inexistent in baza de date
    return 0;
}
// functie de cautare a unei linii de tip int cu o conditie
// transmisa ca parametru
void searchDeleteIntLines(t_table *table,
    int col_number, char *value, char *condition) {
    // pointam catre prima linie din tabel
    t_intLine *crt_line = (t_intLine*)(table -> lines), *aux;
    t_intCell *crt_cell;
    // convertim valoarea parametrului la int
    int i, cond_int = atoi(value);
    // parcurgem liniile tabelului
    while (crt_line) {
        // pointam catre prima celula din linie
        crt_cell = crt_line -> cells;
        // ajungem la celula dorita
        for (i = 0; i < col_number - 1; i++) {
            crt_cell = crt_cell -> next;
        }
        // folosim aux pt a pastra legaturile in lista
        aux = crt_line;
        // avansam in lista de linii
        crt_line = crt_line -> next;
        // verificam cele 6 conditii posibile ce pot
        // fi primite ca parametru si le tranformam
        // in instructiuni "if".
        // daca o conditie e indeplinita, se sterge linia
        // respectiva cu functia aferenta tipului de date
        if (strcmp(condition, "<") == 0) {
            if (crt_cell -> value < cond_int) {
                free_int_line(table, aux);
            }
        }
        if (strcmp(condition, "<=") == 0) {
            if (crt_cell -> value <= cond_int) {
                free_int_line(table, aux);
            }
        }
        if (strcmp(condition, "==") == 0) {
            if (crt_cell -> value == cond_int) {
                free_int_line(table, aux);
            }
        }
        if (strcmp(condition, "!=") == 0) {
            if (crt_cell -> value != cond_int) {
                free_int_line(table, aux);
            }
        }
        if (strcmp(condition, ">=") == 0) {
            if (crt_cell -> value >= cond_int) {
                free_int_line(table, aux);
            }
        }
        if (strcmp(condition, ">") == 0) {
            if (crt_cell -> value > cond_int) {
                free_int_line(table, aux);
            }
        }
    }
}
// functie de cautare a unei linii de tip float cu o conditie
// transmisa ca parametru
// functioneaza identic cu functia predecenta si e scrisa similar
// voi comenta doar diferentele fata de functia precedenta
void searchDeleteFLoatLines(t_table *table, int col_number,
    char *value, char *condition) {
    t_floatLine *crt_line = (t_floatLine*)(table -> lines), *aux;
    t_floatCell *crt_cell;
    int i;
    // convertim valoarea param la float
    float cond_float = atof(value);
    while (crt_line) {
        crt_cell = crt_line -> cells;
        for (i = 0; i < col_number - 1; i++) {
            crt_cell = crt_cell -> next;
        }
        aux = crt_line;
        crt_line = crt_line -> next;
        // verificarea conditiilor se face comparand
        // cu cond_float, iar functiile sunt cele de
        // stergere a liniilor de tip float
        if (strcmp(condition, "<") == 0) {
            if (crt_cell -> value < cond_float) {
                free_float_line(table, aux);
            }
        }
        if (strcmp(condition, "<=") == 0) {
            if (crt_cell -> value <= cond_float) {
                free_float_line(table, aux);
            }
        }
        if (strcmp(condition, "==") == 0) {
            if (crt_cell -> value == cond_float) {
                free_float_line(table, aux);
            }
        }
        if (strcmp(condition, "!=") == 0) {
            if (crt_cell -> value != cond_float) {
                free_float_line(table, aux);
            }
        }
        if (strcmp(condition, ">=") == 0) {
            if (crt_cell -> value >= cond_float) {
                free_float_line(table, aux);
            }
        }
        if (strcmp(condition, ">") == 0) {
            if (crt_cell -> value > cond_float) {
                free_float_line(table, aux);
            }
        }
    }
}
// functie de cautare a unei linii de tip string cu o conditie
// transmisa ca parametru
// functioneaza identic cu functia predecenta si e scrisa similar
// voi comenta doar diferentele fata de functia precedenta
void searchDeleteSstringLines(t_table *table, int col_number,
    char *value, char *condition) {
    t_stringLine *crt_line = (t_stringLine*)(table -> lines), *aux;
    t_stringCell *crt_cell;
    int i;
    while (crt_line) {
        crt_cell = crt_line -> cells;
        for (i = 0; i < col_number - 1; i++) {
            crt_cell = crt_cell -> next;
        }
        aux = crt_line;
        crt_line = crt_line -> next;
        // nu mai apare niciun cond_int sau cond_float
        // conditiile se verifica cu strcmp imbricate
        if (strcmp(condition, "<") == 0) {
            if (strcmp(crt_cell -> value, value) < 0) {
                free_string_line(table, aux);
            }
        }
        if (strcmp(condition, "<=") == 0) {
            if (strcmp(crt_cell -> value, value) <= 0) {
                free_string_line(table, aux);
            }
        }
        if (strcmp(condition, "==") == 0) {
            if (strcmp(crt_cell -> value, value) == 0) {
                free_string_line(table, aux);
            }
        }
        if (strcmp(condition, "!=") == 0) {
            if (strcmp(crt_cell -> value, value) != 0) {
                free_string_line(table, aux);
            }
        }
        if (strcmp(condition, ">=") == 0) {
            if (strcmp(crt_cell -> value, value) >= 0) {
                free_string_line(table, aux);
            }
        }
        if (strcmp(condition, ">") == 0) {
            if (strcmp(crt_cell -> value, value) > 0) {
                free_string_line(table, aux);
            }
        }
    }
}
// functie pt a sterge o linie dintr-un tabel cu conditii
// trimise ca parametri
int DELETE_LINE(t_db *database, char *table_name,
    char *column_name, char *condition, char *value) {
    // pointam catre primul tabel
    t_table *p = database -> tables;
    int table_data_type;
    int col_number, col_nr = 0;
    // parcurgem lista de tabele
    while (p) {
        // identificam tabelul cautat
        if (strcmp(p -> name, table_name) == 0) {
            // gasim la ce coloana cautam datele din conditie
            col_number = find_column_number(p, column_name);
            // daca functia returneaza 0, tabelul nu contine nicio
            // linie ce trebuie stearsa
            if (!col_number) {
                printf("Table \"%s\" does not contain column \"%s\".\n",
                    p -> name, column_name);
                // cod pentru nicio linie care satisface conditiile
                return 2;
            } else {
                table_data_type = p -> type;
                // pointam catre prima coloana din tabelul curent
                t_column *crt_col = p -> columns;
                // stergem liniile in functie de tipul de date
                switch (table_data_type) {
                case 0:
                    searchDeleteIntLines(p, col_number, value, condition);
                    break;
                case 1:
                    searchDeleteFLoatLines(p, col_number, value, condition);
                    break;
                case 2:
                    searchDeleteSstringLines(p, col_number, value, condition);
                    break;
                }
                // cod stergere linii cu succes
                return 1;
            }
        }
        // avansam in lista de tabele
        p = p -> next;
    }
    // cod tabel inexistent
    return 0;
}
