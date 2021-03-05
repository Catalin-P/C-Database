// Picior Catalin 312CB
#include "structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fun_decl.h"

// functie de initializare a unei baze de date
t_db *INIT_DB(char *name) {
  // alocam memorie pt o baza de date
  t_db *database = malloc(sizeof(t_db));
  // verificam daca s-a alocat corect
  if (!database) {
    return NULL;
  }
  // copiem numele bazei de date in campul aferent
  strcpy(database->name, name);
  // baza de date este vida; nu pointam catre niciun tabel
  database->tables = NULL;
  // returnam adresa bazei de date
  return database;
}
// functie de eliberare a unei linii de tabel cu date de tip int
// linia dorita pentru a fi eliberata este data ca parametru
void free_int_line(t_table *table, void *line) {
  // facem cast la int pentru liniile din tabel
  t_intLine *p = (t_intLine *)table->lines, *prev;
  t_intLine *crt_line = (t_intLine *)(line);
  t_intCell *aux_cell, *crt_cell;
  // prima celula din linie
  crt_cell = crt_line->cells;
  // stergem celulele existente
  while (crt_cell) {
    // celula curenta devine aux pentru a pastra legaturile in lista
    aux_cell = crt_cell;
    // avansam la urm celula
    crt_cell = crt_cell->next;
    // eliberam celula curenta
    free(aux_cell);
  }
  // parcurgem liniile din tabel
  for (prev = NULL; p != NULL; prev = p, p = p->next) {
    // daca linia curenta este cea dorita
    if (p == crt_line) {
      // conditie pentru a fi prima linie din tabel
      if (prev == NULL) {
        // modificam capul tabelului
        table->lines = p->next;
      } else {
        // daca nu e prima linie, legam celula precedenta
        // cu cea de dupa p
        prev->next = p->next;
      }
      // eliberam celula
      free(crt_line);
      // iesim din bucla, evitam calcul redundant
      break;
    }
  }
}
// functia functioneaza exact ca precedenta acesteia
// aceleasi linii de cod ca functia precedenta,
// cast pentru linii cu elemente de tip float
void free_float_line(t_table *table, void *line) {
  t_floatLine *p = (t_floatLine *)table->lines, *prev;
  t_floatLine *crt_line = (t_floatLine *)(line);
  t_floatCell *aux_cell, *crt_cell;
  crt_cell = crt_line->cells;
  while (crt_cell) {
    aux_cell = crt_cell;
    crt_cell = crt_cell->next;
    free(aux_cell);
  }
  crt_line->cells = NULL;
  for (prev = NULL; p != NULL; prev = p, p = p->next) {
    if (p == crt_line) {
      if (prev == NULL) {
        table->lines = p->next;
      } else {
        prev->next = p->next;
      }
      free(crt_line);
      break;
    }
  }
}
// functia functioneaza similar cu precedentele acesteia
// voi comenta doar singura diferenta
void free_string_line(t_table *table, void *line) {
  t_stringLine *p = (t_stringLine *)table->lines, *prev;
  t_stringLine *crt_line = (t_stringLine *)(line);
  t_stringCell *aux_cell, *crt_cell;
  crt_cell = crt_line->cells;
  while (crt_cell) {
    aux_cell = crt_cell;
    crt_cell = crt_cell->next;
    // se elibereaza valoarea celulei,
    // un sir de caractere alocat dinamic
    free(aux_cell->value);
    free(aux_cell);
  }
  for (prev = NULL; p != NULL; prev = p, p = p->next) {
    if (p == crt_line) {
      if (prev == NULL) {
        table->lines = p->next;
      } else {
        prev->next = p->next;
      }
      free(line);
      break;
    }
  }
}
// functie de eliberare a liniilor de tip int dintr-un tabel
void free_int_lines(void *lines) {
  t_intLine *aux_line;
  // castam linia curenta la o linie cu celule de tip int
  t_intLine *crt_line = (t_intLine *)(lines);
  t_intCell *aux_cell, *crt_cell;
  // parcurgem tabelul linie cu linie
  while (crt_line) {
    // pointam catre prima celula a linie curente
    crt_cell = crt_line->cells;
    // parcurgem linia de celule
    while (crt_cell) {
      // celula curenta devine aux
      // pentru a pastra legaturile in lista
      aux_cell = crt_cell;
      // avansam la urmatoarea celula
      crt_cell = crt_cell->next;
      // eliberam celula curenta
      free(aux_cell);
    }
    // marcam linia curenta ca fiind vida
    crt_line->cells = NULL;
    // linia curenta devine aux pentru a pastra legaturile in lista
    aux_line = crt_line;
    // avansam la urmatoarea linie
    crt_line = crt_line->next;
    // eliberam celula unei liste de linii
    free(aux_line);
  }
}
// functie de eliberare a liniilor de tip float dintr-un tabel
// este identica cu functia precedenta ca si scriere
// castul se realizeaza la linii cu elemente de tip float si
// celule cu elemente de tip float
void free_float_lines(void *lines) {
  t_floatLine *aux_line;
  t_floatLine *crt_line = (t_floatLine *)(lines);
  t_floatCell *aux_cell, *crt_cell;
  while (crt_line) {
    crt_cell = crt_line->cells;
    while (crt_cell) {
      aux_cell = crt_cell;
      crt_cell = crt_cell->next;
      free(aux_cell);
    }
    crt_line->cells = NULL;
    aux_line = crt_line;
    crt_line = crt_line->next;
    free(aux_line);
  }
}
// functie de eliberare a liniilor de tip string dintr-un tabel
// este aproape identica cu functia precedenta ca si scriere
// castul se realizeaza la linii cu elemente de tip string si
// celule cu elemente ce contin siruri de caractere
// voi comenta doar diferenta fata de functiile precedente
void free_string_lines(void *lines) {
  t_stringLine *aux_line;
  t_stringLine *crt_line = (t_stringLine *)(lines);
  t_stringCell *aux_cell, *crt_cell;
  while (crt_line) {
    crt_cell = crt_line->cells;
    while (crt_cell) {
      aux_cell = crt_cell;
      crt_cell = crt_cell->next;
      // se elibereaza valoarea celulei,
      // un sir de caractere alocat dinamic
      free(aux_cell->value);
      free(aux_cell);
    }
    crt_line->cells = NULL;
    aux_line = crt_line;
    crt_line = crt_line->next;
    free(aux_line);
  }
}
// functie pentru a elibera o structura de tip tabel
// functia primeste ca parametru o functie care de
// stergere a liniilor de un anumit tip
void free_table(t_table *table, Distr_lines fun) {
  t_column *crt_col, *aux_col;
  void *crt_line, *aux_line, *crt_cell, *aux_cell;
  // pointam catre prima celula de tip coloana din tabel
  crt_col = table->columns;
  // parcurgem tabelul
  while (crt_col) {
    // celula curenta devine aux
    // pentru a pastra legaturile in lista
    aux_col = crt_col;
    // avansam la urm celula
    crt_col = crt_col->next;
    // eliberam celula curenta
    free(aux_col);
  }
  // marcam ca tabelul nu mai are celule de tip coloana
  table->columns = NULL;
  // apelam functia de distrugere a liniilor unei tabel
  fun(table->lines);
  // marcam ca tabelul nu contine nicio linie
  table->lines = NULL;
  // eliberam celula de tip tabel
  free(table);
}
// functie pentru stergerea unei baze de date
void DELETE_DB(t_db **database) {
  int table_type_value;
  // pointam catre primul tabel din baza de date
  t_table *crt_table = (*database)->tables;
  t_table *aux_table;
  // parcurgem lista de tabele
  while (crt_table) {
    // tabelul curent devine aux
    // pentru a pastra legaturile in lista
    aux_table = crt_table;
    // determinam tipul de date al tabelului curent
    table_type_value = crt_table->type;
    // avansam la urm tabel
    crt_table = crt_table->next;
    // cazuri de eliberare tabel in functie de tipul
    // de date stocat
    switch (table_type_value) {
      case 0:
        free_table(aux_table, free_int_lines);
        break;
      case 1:
        free_table(aux_table, free_float_lines);
        break;
      case 2:
        free_table(aux_table, free_string_lines);
        break;
    }
  }
  // marcam ca baza de date nu contine nicun tabel
  (*database)->tables = NULL;
  // eliberam celula de tip baza de date
  free(*database);
  //marcam baza de date eliberata cu NULL
  *database = NULL;
}
//functie de eliberare a celulelor dintr-o coloana
void free_col_list(t_column **head) {
  t_column *p, *aux;
  // parcurgem celulele coloanei
  for (p = *head; p != NULL;) {
    // celula curenta devine aux
    // pentru a pastra legaturile in lista
    aux = p;
    // avansam la urm celula
    p = p->next;
    // eliberam celula curenta
    free(aux);
  }
  // marcam coloana ca fiind vida
  (*head) = NULL;
}
// functie de alocare a unei coloane
t_column *alloc_col(char *columns_names) {
  t_column *head, *last = NULL, *aux;
  // obtinem numele primei celule din coloana
  // prin tokenizare
  char *token = strtok(columns_names, " ");
  // alocam o celula de tip coloana
  aux = (t_column *)malloc(sizeof(t_column));
  // verifcam alocarea
  if (!aux) {
    return NULL;
  }
  // marcam urm element cu NULL
  aux->next = NULL;
  // actualizam ultima celula
  last = aux;
  // marcam capul listei de celule
  head = aux;
  // copiem numele celulei in campul aferent din celula
  strcpy(aux->name, token);
  // continuam tokenizarea pana la NULL
  token = strtok(NULL, " ");
  while (token != NULL) {
    // alocam o celula 
    aux = (t_column *)malloc(sizeof(t_column));
    // daca nu s-a alocat corect stergem tot ce am alocat anterior
    if (!aux) {
      free_col_list(&head);
      return NULL;
    }
    // marcam urm element cu NULL
    aux->next = NULL;
    //copiem numele celulei in campul aferent din celula
    strcpy(aux->name, token);
    // adaugam celula alocata in lista
    last->next = aux;
    // actualizam ultimul element
    last = aux;
    // continuam tokenizarea
    token = strtok(NULL, " ");
  }
  // returnam capul coloanei
  return head;
}
// functie de creare a unui tabel
int CREATE_TABLE(t_db *database, char *name, int data_type,
                 char *columns_name) {
  t_table *prev, *p;
  // parcurgem lista de tabele pana gasim ultimul tabel
  for (prev = NULL, p = database->tables; p != NULL; prev = p, p = p->next) {
    // verificam daca un table cu acelasi nume nu a fost deja creat
    if (strcmp(p->name, name) == 0) {
      // mesaj pentru table existent
      printf("Table \"%s\" already exists.\n", name);
      // cod eroare
      return 1;
    }
  }
  //alocam memorie pentru un tabel nou
  t_table *aux = (t_table *)malloc(sizeof(t_table));
  // verificam alocarea
  if (!aux) {
    return 1;
  }
  // setam tipul de date
  aux->type = data_type;
  // marcam campurile din tabel cu NULL
  aux->next = NULL;
  aux->lines = NULL;
  aux->columns = NULL;
  strcpy(aux->name, name);
  // conditie daca tabelul pe care il creez
  // este primul
  if (database->tables == NULL) {
    // modificam capul de lista
    database->tables = aux;
  } else {
    // inseram tabelul la sfarsitul listei curente
    prev->next = aux;
  }
  // alocam coloanele pentru tabelul curent
  aux->columns = alloc_col(columns_name);
  // verificam alocarea
  if (aux->columns == NULL) {
    return 1;
  }
  // cod alocare cu succes
  return 0;
}
// stergem un tabel dintr- o baza de date
int DELETE_TABLE(t_db *database, char *table_name) {
  t_table *prev, *p, *aux_table;
  int table_data_type;
  // parcurgem lista de tabele
  for (prev = NULL, p = database->tables; p != NULL; prev = p, p = p->next) {
    // stabilim tipul de date din tabel
    table_data_type = p->type;
    // daca numele tabelului este acelasi cu cel primit ca parametru
    if (strcmp(p->name, table_name) == 0) {
      // pastram adresa lui p intr-un aux pentru a pastra legaturile
      // in lista de tabele
      aux_table = p;
      // conditie de verificare daca tabelul a fost primul in lista
      if (database->tables == p) {
        // actualizam capul de lista de tabele
        database->tables = p->next;
      } else {
        // legam anteriorul lui p cu urm lui p
        prev->next = p->next;
      }
      // eliberam tabelul in functie de tipul de date
      switch (table_data_type) {
        case 0:
          free_table(aux_table, free_int_lines);
          break;
        case 1:
          free_table(aux_table, free_float_lines);
          break;
        case 2:
          free_table(aux_table, free_string_lines);
          break;
      }
      // cod pentru tabel gasit si sters
      return 1;
    }
  }
  // cod pentru tabel inexistent
  return 0;
}
