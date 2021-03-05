// Picior Catalin 312CB
#ifndef __STRUCTURES__
#define __STRUCTURES__

#define MAX_COLUMN_NAME_LEN 30
#define MAX_TABLE_NAME_LEN  30
#define MAX_DB_NAME_LEN     30
#define MAX_CMD_LEN         300

// int
typedef struct intCell {
	int    value;
	struct intCell* next;
} t_intCell;

typedef struct intLine {
	t_intCell*      cells;
	struct intLine* next;
} t_intLine;

// float
typedef struct floatCell {
	float  value;
	struct floatCell* next;
} t_floatCell;

typedef struct floatLine {
	t_floatCell*      cells;
	struct floatLine* next;
} t_floatLine;

// string
typedef struct stringCell {
	char*  value;
	struct stringCell* next;
} t_stringCell;

typedef struct stringLine {
	t_stringCell*       cells;
	struct stringLine* next;
} t_stringLine;

// cell type
typedef enum {
	INT,
	FLOAT,
	STRING
} t_cellType;

// column
typedef struct column {
	char name[MAX_COLUMN_NAME_LEN];
	struct column* next;
} t_column;

// table
typedef struct table {
	char name[MAX_TABLE_NAME_LEN];
	t_cellType    type;
	t_column*     columns;
	void*         lines;  // t_intLine* | t_floatLine* | t_stringLine*
	struct table* next;
} t_table;

// database
typedef struct db {
	char name[MAX_DB_NAME_LEN];
	t_table* tables;
} t_db;

#endif