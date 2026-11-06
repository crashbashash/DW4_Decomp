/* Typed beDataBase accessors over arena objects. */
#include "dw4/arenadb.h"

#include <stdio.h>
#include <string.h>

#include "dw4/object.h"
#include "dw4/reflected.h"

/* the list classes share one layout: count, capacity and a memory-block handle (igDataList's prefix) */
typedef igIntList list_view;

static const list_view *list_at(dw4_arena *a, int32_t handle)
{
    dw4_handle h = {(uint32_t)handle};
    return handle ? (const list_view *)dw4_arena_at(a, h, (uint32_t)sizeof(list_view)) : NULL;
}

/* element `i` of a list's block, `width` bytes each; NULL when the block cannot hold it */
static const uint8_t *element(dw4_arena *a, const list_view *l, uint32_t i, uint32_t width)
{
    dw4_handle h = {(uint32_t)l->_data};
    if (!l->_data || l->_count < 0 || i >= (uint32_t)l->_count) return NULL;
    return (const uint8_t *)dw4_arena_at(a, h, (i + 1u) * width) + (size_t)i * width;
}

static const char *string_of(dw4_arena *a, int32_t handle)
{
    dw4_handle h = {(uint32_t)handle};
    const char *s;
    if (!handle) return "";                        /* an igNamedObject with no name: 4e0858 */
    s = (const char *)dw4_arena_at(a, h, 1);
    return s ? s : "";
}

/* the name of column `i` of an igNamedObjectList */
static const char *column_name(dw4_arena *a, const list_view *cols, uint32_t i)
{
    const uint8_t *e = element(a, cols, i, 4);
    dw4_handle oh;
    const igNamedObject *o;
    if (!e) return NULL;
    oh.off = e[0] | (uint32_t)e[1] << 8 | (uint32_t)e[2] << 16 | (uint32_t)e[3] << 24;
    o = oh.off ? DW4_ARENA_OBJ(a, igNamedObject, oh) : NULL;
    return o ? string_of(a, o->_name) : NULL;
}

/* retail 0x3a93a0: the first column whose name equals `name`; the cell is row * columns + column, taken in 32 bits */
static int cell_index(dw4_arena *a, const list_view *cols, int32_t row, const char *name, int32_t *index)
{
    int32_t n = cols ? cols->_count : 0, i;
    if (!cols || n <= 0 || !name) return -1;
    for (i = 0; i < n; i++) {
        const char *c = column_name(a, cols, (uint32_t)i);
        if (c && !strcmp(c, name)) {
            uint32_t bits = (uint32_t)row * (uint32_t)n + (uint32_t)i;
            memcpy(index, &bits, 4);
            return 0;
        }
    }
    return -1;
}

/* a numeric table: its columns and values; the cell must lie inside rows * columns */
static int table_cell(dw4_arena *a, int32_t cols_h, int32_t vals_h, int32_t row, const char *column, uint32_t width, int sign,
                      int32_t *out)
{
    const list_view *cols = list_at(a, cols_h), *vals = list_at(a, vals_h);
    int32_t i;
    const uint8_t *p;
    /* no such column in this table: try the next. Retail 0x3a93a0 returns -1 for "not found", and a wrapped cell index of exactly -1
     * is indistinguishable from it (the host database keeps the same quirk). */
    if (!cols || cell_index(a, cols, row, column, &i) || i == -1) return 1;
    if (!vals || cols->_count <= 0 || vals->_count < 0 || (uint32_t)row >= (uint32_t)vals->_count / (uint32_t)cols->_count ||
        i < 0 || i >= vals->_count)
        return -1;
    p = element(a, vals, (uint32_t)i, width);
    if (!p) return -1;
    switch (width) {
    case 1: *out = sign ? (int32_t)(int8_t)p[0] : (int32_t)p[0]; break;
    case 2: *out = (int32_t)(int16_t)(p[0] | (uint32_t)p[1] << 8); break;
    default: *out = (int32_t)(p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24); break;
    }
    return 0;
}

int dw4_adb_number(dw4_arena *a, dw4_handle db, int32_t row, const char *column, int32_t *out)
{
    const beDataBase *d = a ? DW4_ARENA_OBJ(a, beDataBase, db) : NULL;
    int rc;
    if (!d || row < 0 || !column || !out) return -1;
    *out = 0;
    rc = table_cell(a, d->_charOffsetList, d->_charData, row, column, 1, 1, out);
    if (rc != 1) return rc;
    rc = table_cell(a, d->_shortOffsetList, d->_shortData, row, column, 2, 1, out);
    if (rc != 1) return rc;
    rc = table_cell(a, d->_intOffsetList, d->_intData, row, column, 4, 1, out);
    return rc;                                                           /* 1: missing from all three */
}

int dw4_adb_bool(dw4_arena *a, dw4_handle db, int32_t row, const char *column, int32_t *out)
{
    const beDataBase *d = a ? DW4_ARENA_OBJ(a, beDataBase, db) : NULL;
    if (!d || row < 0 || !column || !out) return -1;
    *out = 0;
    return table_cell(a, d->_boolOffsetList, d->_boolData, row, column, 1, 0, out);
}

uint32_t dw4_adb_string_rows(dw4_arena *a, dw4_handle db)
{
    const beDataBase *d = a ? DW4_ARENA_OBJ(a, beDataBase, db) : NULL;
    const list_view *cols = d ? list_at(a, d->_stringOffsetList) : NULL, *vals = d ? list_at(a, d->_stringData) : NULL;
    if (!cols || !vals || cols->_count <= 0 || vals->_count < 0) return 0;
    return (uint32_t)vals->_count / (uint32_t)cols->_count;
}

const char *dw4_adb_string(dw4_arena *a, dw4_handle db, int32_t row, const char *column)
{
    const beDataBase *d = a ? DW4_ARENA_OBJ(a, beDataBase, db) : NULL;
    const list_view *cols, *vals;
    int32_t i;
    if (!d || row < 0 || (uint32_t)row >= dw4_adb_string_rows(a, db)) return NULL;
    cols = list_at(a, d->_stringOffsetList);
    vals = list_at(a, d->_stringData);
    if (cell_index(a, cols, row, column, &i) || i < 0 || i >= vals->_count) return NULL;
    return column_name(a, vals, (uint32_t)i);
}

/* ---- validation and description ---------------------------------------------------------------------------------------- */

static uint32_t class_vtable(const char *name)
{
    const dw4_metaobject *mo = dw4_metaobject_find(name);
    return mo ? mo->vtable : 0;
}

static int fail_why(char *why, size_t cap, const char *what)
{
    if (why && cap) snprintf(why, cap, "%s", what);
    return -1;
}

/* a list of exactly class `cls` whose block holds `_count` elements of `width` bytes; fills `*count` */
static int check_list(dw4_arena *a, int32_t handle, const char *cls, uint32_t width, int32_t *count, char *why, size_t wcap)
{
    dw4_handle h = {(uint32_t)handle}, bh;
    const list_view *l = handle ? (const list_view *)dw4_arena_at(a, h, (uint32_t)sizeof(list_view)) : NULL;
    uint32_t vt = class_vtable(cls);
    if (!l) return fail_why(why, wcap, "a list is missing");
    if (!vt || (uint32_t)l->_vtable != vt) return fail_why(why, wcap, "a list has the wrong class");
    if (l->_count < 0 || l->_count > l->_capacity) return fail_why(why, wcap, "a list count exceeds its capacity");
    bh.off = (uint32_t)l->_data;
    if (l->_count && (!l->_data || !dw4_arena_at(a, bh, (uint32_t)l->_count * width)))
        return fail_why(why, wcap, "a list block is too small for its count");
    *count = l->_count;
    return 0;
}

static int check_names(dw4_arena *a, int32_t handle, int32_t *count, char *why, size_t wcap)
{
    int32_t i;
    const list_view *l;
    dw4_handle h = {(uint32_t)handle};
    if (check_list(a, handle, "igNamedObjectList", 4, count, why, wcap)) return -1;
    l = (const list_view *)dw4_arena_at(a, h, (uint32_t)sizeof(list_view));
    for (i = 0; i < *count; i++) {
        const uint8_t *e = element(a, l, (uint32_t)i, 4);
        dw4_handle oh;
        const igNamedObject *o;
        if (!e) return fail_why(why, wcap, "a name list element is missing");
        oh.off = e[0] | (uint32_t)e[1] << 8 | (uint32_t)e[2] << 16 | (uint32_t)e[3] << 24;
        o = oh.off ? DW4_ARENA_OBJ(a, igNamedObject, oh) : NULL;
        if (!o || (uint32_t)o->_vtable != class_vtable("igNamedObject")) return fail_why(why, wcap, "a column is not an igNamedObject");
    }
    return 0;
}

int dw4_adb_validate(dw4_arena *a, dw4_handle db, char *why, size_t cap)
{
    static const char *const kinds[4] = {"igCharList", "igShortList", "igIntList", "igBoolList"};
    static const uint32_t widths[4] = {1, 2, 4, 1};
    const beDataBase *d = a ? DW4_ARENA_OBJ(a, beDataBase, db) : NULL;
    int32_t cols_h[5], vals_h[5], ncols, nvals, k;
    if (!d || (uint32_t)d->_vtable != class_vtable("beDataBase")) return fail_why(why, cap, "not a beDataBase");
    cols_h[0] = d->_charOffsetList;  vals_h[0] = d->_charData;
    cols_h[1] = d->_shortOffsetList; vals_h[1] = d->_shortData;
    cols_h[2] = d->_intOffsetList;   vals_h[2] = d->_intData;
    cols_h[3] = d->_boolOffsetList;  vals_h[3] = d->_boolData;
    cols_h[4] = d->_stringOffsetList; vals_h[4] = d->_stringData;
    for (k = 0; k < 5; k++) {
        if (check_names(a, cols_h[k], &ncols, why, cap)) return -1;
        if (k == 4) {
            if (check_names(a, vals_h[k], &nvals, why, cap)) return -1;
        } else if (check_list(a, vals_h[k], kinds[k], widths[k], &nvals, why, cap)) {
            return -1;
        }
        if (ncols ? nvals % ncols : nvals != 0) return fail_why(why, cap, "a table's value count is not a whole number of rows");
    }
    return 0;
}

void dw4_adb_describe(dw4_arena *a, dw4_handle db, const char *name, FILE *out)
{
    static const char *const kind[4] = {"char", "short", "int", "bool?"};
    const beDataBase *d = a ? DW4_ARENA_OBJ(a, beDataBase, db) : NULL;
    int32_t cols_h[5], vals_h[5], k, i;
    if (!d) return;
    cols_h[0] = d->_charOffsetList;  vals_h[0] = d->_charData;
    cols_h[1] = d->_shortOffsetList; vals_h[1] = d->_shortData;
    cols_h[2] = d->_intOffsetList;   vals_h[2] = d->_intData;
    cols_h[3] = d->_boolOffsetList;  vals_h[3] = d->_boolData;
    cols_h[4] = d->_stringOffsetList; vals_h[4] = d->_stringData;
    {
        const list_view *c = list_at(a, cols_h[4]), *v = list_at(a, vals_h[4]);
        fprintf(out, "database %s: %d string column(s), %d string(s)\n", name, c ? c->_count : 0, v ? v->_count : 0);
        for (i = 0; c && i < c->_count; i++) fprintf(out, "  string column %s\n", column_name(a, c, (uint32_t)i));
    }
    for (k = 0; k < 4; k++) {
        const list_view *c = list_at(a, cols_h[k]), *v = list_at(a, vals_h[k]);
        fprintf(out, "  %s table: %d column(s), %d value(s)\n", kind[k], c ? c->_count : 0, v ? v->_count : 0);
        for (i = 0; c && i < c->_count; i++) fprintf(out, "    %s\n", column_name(a, c, (uint32_t)i));
    }
}
