/* dw4/arenadb.h — typed beDataBase accessors over arena objects (porting P1 of docs/arena-object-model.md).
 *
 * Clean-C ports of the retail lookups `beDataBase_GetRecordInt` (0x3a9460), `GetRecordBool` (0x3a9540) and `GetRecordString`
 * (0x3a9580), written on the decomp's authoritative structs (beDataBase, igNamedObjectList, igNamedObject, igCharList,
 * igShortList, igIntList, igBoolList in include/dw4/reflected.h) reached through arena handles. The matched C
 * (src/game/beDataBase.c) is the source of behavior; its matching-only constructs are not copied. The column is the first equal
 * name of the table's offset list and the cell is `row * columns + column` (retail wraps this in 32 bits; here a cell or row outside
 * the table is refused, as the host database does). Behavior is checked against dw4_database_* on every row and column of the
 * real tables (tools/test_arenadb.c). */
#ifndef DW4_ARENADB_H
#define DW4_ARENADB_H

#include <stdint.h>
#include <stdio.h>

#include "dw4/arena.h"

/* Numeric cell: the char, then short, then int table that has `column` (retail precedence). 0 found, 1 missing (out = 0),
 * -1 invalid input or a cell outside the table. */
int dw4_adb_number(dw4_arena *, dw4_handle db, int32_t row, const char *column, int32_t *out);
/* Unsigned-byte boolean cell from the separate bool table. Same return codes. */
int dw4_adb_bool(dw4_arena *, dw4_handle db, int32_t row, const char *column, int32_t *out);
/* String cell; "" for a present entry with no name (retail's 4e0858 fallback), NULL for a missing column or invalid row. The
 * pointer is into the arena and valid until the block is freed. */
const char *dw4_adb_string(dw4_arena *, dw4_handle db, int32_t row, const char *column);
/* Rows of the string table (entries / columns), 0 when empty or invalid. */
uint32_t dw4_adb_string_rows(dw4_arena *, dw4_handle db);

/* Check a database the way the retail loader's structure demands (and the host builder did): every list present and of its exact class
 * (igNamedObjectList for the column lists and the string data; igCharList/igShortList/igIntList/igBoolList for the value tables),
 * count <= capacity, every element present with its block large enough, every column an igNamedObject, and each table's value count a
 * multiple of its column count. 0, or -1 with the reason in `why`. */
int dw4_adb_validate(dw4_arena *, dw4_handle db, char *why, size_t cap);
/* Print the table layout (column names and counts) for diagnostics. */
void dw4_adb_describe(dw4_arena *, dw4_handle db, const char *name, FILE *out);

/* A typed table by value: the arena and the beDataBase handle inside it. The rules take this instead of a host database; the owner that
 * built it (dw4_databases_table) keeps the arena alive. A zero table is invalid. */
typedef struct {
    dw4_arena *arena;
    dw4_handle db;
} dw4_dbtable;
static inline int dw4_dbtable_valid(dw4_dbtable t) { return t.arena != 0 && t.db.off != 0; }
static inline int dw4_dbt_number(dw4_dbtable t, int32_t row, const char *column, int32_t *out)
{
    return dw4_adb_number(t.arena, t.db, row, column, out);
}
static inline int dw4_dbt_bool(dw4_dbtable t, int32_t row, const char *column, int32_t *out)
{
    return dw4_adb_bool(t.arena, t.db, row, column, out);
}
static inline const char *dw4_dbt_string(dw4_dbtable t, int32_t row, const char *column)
{
    return dw4_adb_string(t.arena, t.db, row, column);
}

#endif
