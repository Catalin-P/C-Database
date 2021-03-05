// Picior Catalin 312CB
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structures.h"
#include "fun_decl.h"

// functie de printat o linie cu date de tip int
void print_int_line(t_intLine *line) {
  // pointam catre prima celula din linie
  t_intCell *crt_cell = line->cells;
  // daca linia e vida iesim din functie
  if (!crt_cell) {
    return;
  }
  // parcurgem linia
  while (crt_cell) {
    // printam valoarea din celula in formatul specificat
    // am folosim un macro pentru a evita "magic numbers" si
    // am inmultit cu -1 pentru aliniere la stanga
    printf("%*d ", MAX_COLUMN_NAME_LEN * (-1), crt_cell->value);
    // avansam in lista
    crt_cell = crt_cell->next;
  }
  // trecem la linia urmatoare in output
  printf("\n");
}
// functie de printat o linie cu date de tip float
// identica cu cea de printat o linie cu date de tip int
void print_float_line(t_floatLine *line) {
  t_floatCell *crt_cell = line->cells;
  if (!crt_cell) {
    return;
  }
  while (crt_cell) {
    printf("%*f ", MAX_COLUMN_NAME_LEN * (-1), crt_cell->value);
    crt_cell = crt_cell->next;
  }
  printf("\n");
}
// functie de printat o linie cu date de tip string
// identica cu cea de printat o linie cu date de tip int
void print_string_line(t_stringLine *line) {
  t_stringCell *crt_cell = line->cells;
  if (!crt_cell) {
    return;
  }
  while (crt_cell) {
    printf("%*s ", MAX_COLUMN_NAME_LEN * (-1), crt_cell->value);
    crt_cell = crt_cell->next;
  }
  printf("\n");
}
// functie de afisare a tuturor liniilor dintr-un tabel
// cu linii de tip int
void print_int_lines(void *lines) {
  // castam linia curenta la int
  t_intLine *crt_line = (t_intLine *)(lines);
  // parcugem liniile
  while (crt_line) {
    // afisam linia curenta
    print_int_line(crt_line);
    // avansam la urm linie
    crt_line = crt_line->next;
  }
}
// functie de afisare a tuturor liniilor dintr-un tabel
// cu linii de tip float
// identica cu functia precedenta, dar cu cast la float
void print_float_lines(void *lines) {
  t_floatLine *crt_line = (t_floatLine *)(lines);
  while (crt_line) {
    print_float_line(crt_line);
    crt_line = crt_line->next;
  }
}
// functie de afisare a tuturor liniilor dintr-un tabel
// cu linii de tip string
// identica cu functia precedenta, dar cu cast la string
void print_string_lines(void *lines) {
  t_stringLine *crt_line = (t_stringLine *)(lines);
  while (crt_line) {
    print_string_line(crt_line);
    crt_line = crt_line->next;
  }
}
// functie de afisare a unei coloane a unui tabel
void print_columns(t_table *table) {
  // pointam la coloana curenta
  t_column *crt_col = table->columns;
  // contor pentru coloanele din tabel
  int col_nr = 0;
  // parcurgem coloanele
  while (crt_col) {
    // incrementam contorul
    col_nr++;
    // afisam numele coloanelor in formatul specificat in enunt
    printf("%*s ", MAX_COLUMN_NAME_LEN * (-1), crt_col->name);
    // avansam in lista
    crt_col = crt_col->next;
  }
  // trecem la urm linie in output
  printf("\n");
  // printam o linie cu '-' in functie de nr de coloane
  for (int i = 1; i <= MAX_COLUMN_NAME_LEN * col_nr; i++) {
    printf("-");
    if (i % MAX_COLUMN_NAME_LEN == 0) {
      printf(" ");
    }
  }
  // trecem la urm linie in output
  printf("\n");
}
// functie de afisare a unui tabel
int PRINT_TABLE(t_db *database, char *table_name) {
  // pointam catre primul tabel din lista
  t_table *crt_table = database->tables;
  t_column *crt_col;
  // contor pentru numar de coloane
  int col_nr = 0, table_data_type;
  // parcurgem lista de tabele
  while (crt_table) {
    // daca tabelul cautat exista in baza de date
    if (strcmp(crt_table->name, table_name) == 0) {
      // afisam numele tabelului
      printf("TABLE: %s\n", crt_table->name);
      // afisam numele coloanelor
      print_columns(crt_table);
      // stabilim tipul de date ale liniilor tabelului
      table_data_type = crt_table->type;
      // afisam liniilie tabelului in functie de tipul de date
      switch (table_data_type) {
        case 0:
          print_int_lines(crt_table->lines);
          break;
        case 1:
          print_float_lines(crt_table->lines);
          break;
        case 2:
          print_string_lines(crt_table->lines);
          break;
      }
      // lasam o linie libera dupa un tabel
      printf("\n");
      // cod pentru tabel gasit si printat
      return 1;
    }
    // avansam in lista de tabele
    crt_table = crt_table->next;
  }
  // cod pt tabel inexistent in lista
  return 0;
}
// functie de printare a unui tabel despre care se cunoaste
// ca exista in baza de date
void PRINT_KNOWN_TABLE(t_table *table, disp_lines fun) {
  // contor nr coloane in tabel
  int col_nr = 0;
  // pointam catre coloana curenta
  t_column *crt_col = table->columns;
  // afisam numele tabelului
  printf("TABLE: %s\n", table->name);
  // afisam numele coloanelor
  print_columns(table);
  // afisam liniile in functie de tipul de date
  fun(table->lines);
  // lasam o linie libire dupa printarea unui tabel
  printf("\n");
}
// functie pt afisarea unei baze de date
void PRINT_DB(t_db *database) {
  // pointam catre primul tabel
  t_table *crt_table = database->tables;
  int table_data_type;
  // afisam numele bazei de date
  printf("DATABASE: %s\n\n", database->name);
  // parcurgem lista de tabele
  while (crt_table) {
    // stablilim tipul de date a liniilor din tabel
    table_data_type = crt_table->type;
    // afisam tabelul in functie de tipul de date
    switch (table_data_type) {
      case 0:
        PRINT_KNOWN_TABLE(crt_table, print_int_lines);
        break;
      case 1:
        PRINT_KNOWN_TABLE(crt_table, print_float_lines);
        break;
      case 2:
        PRINT_KNOWN_TABLE(crt_table, print_string_lines);
        break;
    }
    // avansam in lista de tabele
    crt_table = crt_table->next;
  }
}
// functie care numara cate coloane exista pana la 
// numele celei transmise ca parametru
int find_column_number(t_table *table, char *column_name) {
  // initializam contor de coloane
  int col_number = 0;
  // pointam catre prima coloana
  t_column *p = table->columns;
  // parcurgem coloanele
  while (p) {
    // incrementam contorul
    col_number++;
    // daca coloana este cea dorita returnam nr de coloane
    if (strcmp(p->name, column_name) == 0) {
      return col_number;
    }
    // avansam in lista de coloane
    p = p->next;
  }
  // cod pentru nume de coloane inexistent in tabel
  return 0;
}
// functie de cautare a unei linii cu date de tip int intr-un tabel
void search_int_lines(t_table *table, int col_number, char *value,
                      char *condition) {
  // castam la linii cu elemente de tip int
  t_intLine *crt_line = (t_intLine *)(table->lines);
  t_intCell *crt_cell;
  // transformam parametrul valorii cerute din char in int
  int i, cond_int = atoi(value);
  // parcurgem liniile tabelului
  for (; crt_line != NULL; crt_line = crt_line->next) {
    crt_cell = crt_line->cells;
    // parcurgem celulele liniei de coloane pana ajungem
    // la coloana unde trebuie cautate valorile
    for (i = 0; i < col_number - 1; i++) {
      crt_cell = crt_cell->next;
    }
    // verificam cele 6 conditii posibile ce pot
    // fi primite ca parametru si le tranformam
    // in instructiuni "if".
    // daca o conditie e indeplinita, se printeaza linia
    // respectiva si se apeleaza continue pentru a evita
    // executia redundanta
    if (strcmp(condition, "<") == 0) {
      if (crt_cell->value < cond_int) {
        print_int_line(crt_line);
        continue;
      }
    }
    if (strcmp(condition, "<=") == 0) {
      if (crt_cell->value <= cond_int) {
        print_int_line(crt_line);
        continue;
      }
    }
    if (strcmp(condition, "==") == 0) {
      if (crt_cell->value == cond_int) {
        print_int_line(crt_line);
        continue;
      }
    }
    if (strcmp(condition, "!=") == 0) {
      if (crt_cell->value != cond_int) {
        print_int_line(crt_line);
        continue;
      }
    }
    if (strcmp(condition, ">=") == 0) {
      if (crt_cell->value >= cond_int) {
        print_int_line(crt_line);
        continue;
      }
    }
    if (strcmp(condition, ">") == 0) {
      if (crt_cell->value > cond_int) {
        print_int_line(crt_line);
        continue;
      }
    }
  }
}
// functie de cautare a unei linii cu date de tip float intr-un tabel
// functie aproape identica cu cea precedenta, difera casturile la
// float; voi comenta doar diferentele fata de functia precedenta
void search_float_lines(t_table *table, int col_number, char *value,
                        char *condition) {
  t_floatLine *crt_line = (t_floatLine *)(table->lines);
  t_floatCell *crt_cell;
  int i;
  // transformam parametrul valorii cerute din char in float
  float cond_float = atof(value);
  for (; crt_line != NULL; crt_line = crt_line->next) {
    crt_cell = crt_line->cells;
    for (i = 0; i < col_number - 1; i++) {
      crt_cell = crt_cell->next;
    }
    // in urma conditiilor, se apeleaza functiile de afisare
    // a elementelor de tip int
    if (strcmp(condition, "<") == 0) {
      if (crt_cell->value < cond_float) {
        print_float_line(crt_line);
        continue;
      }
    }
    if (strcmp(condition, "<=") == 0) {
      if (crt_cell->value <= cond_float) {
        print_float_line(crt_line);
        continue;
      }
    }
    if (strcmp(condition, "==") == 0) {
      if (crt_cell->value == cond_float) {
        print_float_line(crt_line);
        continue;
      }
    }
    if (strcmp(condition, "!=") == 0) {
      if (crt_cell->value != cond_float) {
        print_float_line(crt_line);
        continue;
      }
    }
    if (strcmp(condition, ">=") == 0) {
      if (crt_cell->value >= cond_float) {
        print_float_line(crt_line);
        continue;
      }
    }
    if (strcmp(condition, ">") == 0) {
      if (crt_cell->value > cond_float) {
        print_float_line(crt_line);
        continue;
      }
    }
  }
}
// functie de cautare a unei linii cu date de tip string intr-un tabel
// functie aproape identica cu cea precedenta, difera casturile la
// string; voi comenta doar diferentele fata de functia precedenta
void search_string_lines(t_table *table, int col_number, char *value,
                         char *condition) {
  t_stringLine *crt_line = (t_stringLine *)(table->lines), *prev = NULL;
  t_stringCell *crt_cell;
  // dispare conversia argumetului  "value" la alte tipuri de date
  int i;
  for (; crt_line != NULL; prev = crt_line, crt_line = crt_line->next) {
    crt_cell = crt_line->cells;
    for (i = 0; i < col_number - 1; i++) {
      crt_cell = crt_cell->next;
    }
    // conditiile se verifica cu functii strcmp
    // imbricate, nu cu cond_int sau cond_float
    // functiile de printare a liniei sunt pentru linii
    // cu celule de tip string
    if (strcmp(condition, "<") == 0) {
      if (strcmp(crt_cell->value, value) < 0) {
        print_string_line(crt_line);
        continue;
      }
    }
    if (strcmp(condition, "<=") == 0) {
      if (strcmp(crt_cell->value, value) <= 0) {
        print_string_line(crt_line);
        continue;
      }
    }
    if (strcmp(condition, "==") == 0) {
      if (strcmp(crt_cell->value, value) == 0) {
        print_string_line(crt_line);
        continue;
      }
    }
    if (strcmp(condition, "!=") == 0) {
      if (strcmp(crt_cell->value, value) != 0) {
        print_string_line(crt_line);
        continue;
      }
    }
    if (strcmp(condition, ">=") == 0) {
      if (strcmp(crt_cell->value, value) >= 0) {
        print_string_line(crt_line);
        continue;
      }
    }
    if (strcmp(condition, ">") == 0) {
      if (strcmp(crt_cell->value, value) > 0) {
        print_string_line(crt_line);
        continue;
      }
    }
  }
}
// functie de cautare a liniilor dintr-un tabel ce indeplinesc conditiile
// trimise ca parametri
int SEARCH(t_db *database, char *table_name, char *column_name, char *condition,
           char *value) {
  // pointam catre primul tabel
  t_table *p = database->tables;
  int table_data_type;
  int col_number;
  // parcurgem lista de tabele
  while (p) {
    // daca tabelul curent este cel cautat
    if (strcmp(p->name, table_name) == 0) {
      // stabilim la a cata coloana gasim informatiile
      // necessare de analizat
      col_number = find_column_number(p, column_name);
      // daca functia find_column_number returneaza 0, inseamna ca
      // tabelul nu contine coloane cu numele cautat
      if (!col_number) {
        printf("Table \"%s\" does not contain column \"%s\".\n", p->name,
               column_name);
        // cod pentru table fara coloane cu nume cautat
        return 2;
      } else {
        // stabilim tipul de date a liniilor din tabel
        table_data_type = p->type;
        // pointam catre prima coloana din tabelul curent
        t_column *crt_col = p->columns;
        // printam numele tabelului
        printf("TABLE: %s\n", p->name);
        // printam numele coloanelor din tabel
        print_columns(p);
        // cautam linii din tabel in functie de tipul de date
        switch (table_data_type) {
          case 0:
            search_int_lines(p, col_number, value, condition);
            break;
          case 1:
            search_float_lines(p, col_number, value, condition);
            break;
          case 2:
            search_string_lines(p, col_number, value, condition);
            break;
        }
        // lasam un rand liber dupa afisarea unui tabel
        printf("\n");
        // cod pentru tabel printat
        return 1;
      }
    }
    // avansam in lista de tabele
    p = p->next;
  }
  return 0;
}
