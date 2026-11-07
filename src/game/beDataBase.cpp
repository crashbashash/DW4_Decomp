// clang-format off
/* beDataBase record lookup and row count, 0x003a93a0..0x003a9708. A beDataBase is a table of
 * records (rows). Its cells are split by type into six data lists (char, short, int, float, bool,
 * string); each data list is paired with an "offset list" that names the table's columns for that
 * type. A cell of record R and column C is stored row-major at index (columnCount * R + C) of the
 * matching data list (the Junk Shop table is 9 rows x 36 columns; the enemy
 * table keys MODEL, HPMAX, ... by column name). The lists are reached through the reflected
 * object-reference fields and viewed here as the igDataList count/data prefix. "matching
 * construct" marks the volatile local and the hand-placed asm (joins, delay-slot NOPs, register
 * moves) that reproduce the retail scheduling. */
#include "dw4/reflected.h"

/* Index returned by beDataBase_FindRecordValueIndex when the key has no column. */
#define BEDATABASE_NO_INDEX (-1)

/* C++ with exceptions on; the C-ABI names stay unmangled through this block. */
extern "C" {
extern int g_beDataBase_metaObject[4];
int igProperty_FindByName(void *, void *, const char *);
/* Descriptor of the property record's name member. */
extern int g_propertyNameField[4];
static inline int findColumn(igDataList *columns, const volatile int &name) {
    int i = 0;
    int count = columns->_count;
    if (i < count) {
        int *entry = (int *)columns->_data;
        int wanted = name;
        do {
            if (wanted == *entry) {
                return i;
            }
            i++;
            entry++;
        } while (i < count);
    }
    return -1;
}
static inline int columnsOf(igDataList *list) { return list->_count; }

/* Empty string returned for a null string cell. */
extern char emptyString[];

int Gap__Bec__beDataBase__vfunc_20(void);
int beDataBase_FindRecordValueIndex(beDataBase *, int, const char *, igDataList *);
long long beDataBase_GetRecordInt(beDataBase *, int, const char *);
/* Boolean cell (one byte) for (record, key). The index is used unchecked, as in retail, so the key
 * must name a bool column. */
unsigned long long beDataBase_GetRecordBool(beDataBase *, int, const char *);
/* string cell for (record, key): the characters of the stored igStringObj, or an empty string when
 * the cell is null. */
char *beDataBase_GetRecordString(beDataBase *, int, const char *);
int beDataBase_GetRecordCount(beDataBase *);
}

int Gap__Bec__beDataBase__vfunc_20(void) { return g_beDataBase_metaObject[0]; }

/* Flat index of the cell for (record, key) in the data list that pairs with the offset list
 * `columns`. The key is resolved to a column name through igProperty_FindByName, then located
 * among the list entries; the result is columnCount * record + columnPosition, or -1 when the list
 * has no columns or does not contain the key. */
int beDataBase_FindRecordValueIndex(beDataBase *self, int record, const char *key,
                                    igDataList *columns) {
    int found;
    /* matching construct: retail keeps the found name in a stack slot */
    volatile int cell;
    int columnCount = columnsOf(columns);

    if (!columnCount) {
        return -1;
    }
    found = igProperty_FindByName(columns, (void *)g_propertyNameField[0], key);
    if (!found) {
        return -1;
    }
    cell = found;
    int column = findColumn(columns, cell);
    return column + columnCount * record;
}

/* Integer cell for (record, key). Tries the char, short and int columns in turn (sign-extending
 * each) and yields 0 when the key is in none. */
long long beDataBase_GetRecordInt(beDataBase *self, int record, const char *key) {
    long long result;
    int index =
        beDataBase_FindRecordValueIndex(self, record, key, (igDataList *)self->_charOffsetList);
    if (index != BEDATABASE_NO_INDEX)
        return *(signed char *)(((igDataList *)self->_charData)->_data + index);
    index =
        beDataBase_FindRecordValueIndex(self, record, key, (igDataList *)self->_shortOffsetList);
    if (index != BEDATABASE_NO_INDEX)
        return *(short *)(((igDataList *)self->_shortData)->_data + index * 2);
    index =
        beDataBase_FindRecordValueIndex(self, record, key, (igDataList *)self->_intOffsetList);
    if (index != BEDATABASE_NO_INDEX)
        result = *(int *)(((igDataList *)self->_intData)->_data + index * 4);
    else
        result = 0;

    /* matching construct: hand-placed instruction/delay-slot padding */

    asm {
        nop
    }

    return result;
}

/* Boolean cell (one byte) for (record, key). The index is used unchecked, as in retail, so the key
 * must name a bool column. */
unsigned long long beDataBase_GetRecordBool(beDataBase *self, int record, const char *key) {
    int index = (int)beDataBase_FindRecordValueIndex(self, record, key,
                                                     (igDataList *)self->_boolOffsetList);
    return *(unsigned char *)(((igDataList *)self->_boolData)->_data + index);
}

/* string cell for (record, key): the characters of the stored igStringObj, or an empty string when
 * the cell is null. */
char *beDataBase_GetRecordString(beDataBase *self, int record, const char *key) {
    int index = (int)beDataBase_FindRecordValueIndex(self, record, key,
                                                     (igDataList *)self->_stringOffsetList);
    char *text = (char *)((igStringObj *)*(int *)(((igDataList *)self->_stringData)->_data + index * 4))->_buffer;
    return text ? text : emptyString;
}

/* Number of records, i.e. data-list length divided by column count, taken from the first populated
 * type in the order string, char, short, int, float, bool; 0 when the table has no columns. */
int beDataBase_GetRecordCount(beDataBase *self) {
    int columns;
    columns = ((igDataList *)self->_stringOffsetList)->_count;
    if (columns)
        return ((igDataList *)self->_stringData)->_count / columns;
    columns = ((igDataList *)self->_charOffsetList)->_count;
    if (columns)
        return ((igDataList *)self->_charData)->_count / columns;
    columns = ((igDataList *)self->_shortOffsetList)->_count;
    if (columns)
        return ((igDataList *)self->_shortData)->_count / columns;
    columns = ((igDataList *)self->_intOffsetList)->_count;
    if (columns)
        return ((igDataList *)self->_intData)->_count / columns;
    columns = ((igDataList *)self->_floatOffsetList)->_count;
    if (columns)
        return ((igDataList *)self->_floatData)->_count / columns;
    columns = ((igDataList *)self->_boolOffsetList)->_count;
    if (columns)
        return ((igDataList *)self->_boolData)->_count / columns;
    return 0;
}
// clang-format on
