/* Prepared beDBManagerInfo / beDataBase string tables. */
#ifndef DW4_DATABASE_H
#define DW4_DATABASE_H
#include <stdio.h>
#include "dw4/stageobjects.h"
#include "dw4/arenadb.h"
typedef struct dw4_databases dw4_databases;
typedef struct dw4_database dw4_database;
/* Copy authored names/strings in collection order. No pack or scene references
 * escape this owner; close after native borrowers have been released. */
dw4_databases *dw4_databases_open(const dw4_stageobjects *,char *,size_t);
void dw4_databases_close(dw4_databases *);
/* Ordered DATABASE/name/GETDATABASE receivers. Registry outlives this owner;
 * invalidate its Lua objects before close (or close/recreate the VM first). */
int dw4_databases_publish(dw4_databases *,dw4_scriptservices *,uint64_t);
size_t dw4_databases_count(const dw4_databases *);
/* Native DATABASE/name/GETDATABASE result. First equal name, matching receiver
 * order. Object results are not encoded as Lua numbers or four-byte pointers. */
const dw4_database *dw4_databases_get(const dw4_databases *,const char *name);
/* The same first-equal-name database as a typed table: the decomp's beDataBase instance in the
 * owner's arena. Valid until the owner is closed; an invalid (zero) table when the name is
 * unknown. The fight rules read their data through it. */
dw4_dbtable dw4_databases_table(const dw4_databases *,const char *name);
/* The typed twin of a host database (an invalid table for NULL). Same lifetime as the owner. */
dw4_dbtable dw4_database_typed(const dw4_database *);
size_t dw4_database_string_rows(const dw4_database *);
const char *dw4_database_string(const dw4_database *,int32_t row,const char *column);
/* STATUS callback: DATABASE shinka -> GETDATABASE -> string NAME. */
const char *dw4_databases_shinka_name(void *,int32_t);
/* Retail 3a93a0's string-column offset with wrapped EE multiplication.
 * Empty/missing columns return -1. The safe string accessor additionally checks
 * row and data bounds before accessing any host memory. */
int32_t dw4_database_string_offset(const char *const *,uint32_t,int32_t,const char *);
/* Retail 3a9460: signed char, short, then int column precedence.
 * 0 found; 1 missing (out=0, retail fallback); -1 invalid input/row. */
int dw4_database_number(const dw4_database *,int32_t,const char *,int32_t *);
/* 3a9540 uses its separate unsigned-byte boolean table, not numeric columns.
 * 0 found, 1 missing (safe out=0), -1 invalid row/input. */
int dw4_database_bool(const dw4_database *,int32_t,const char *,int32_t *);
/* Diagnostic: print the column layout. */
void dw4_database_describe(const dw4_database *,FILE *);
#endif
