#include "dw4/reflected.h"
#include "dw4/igTDataList.h"

extern "C" int igProperty_FindByName(...);
extern "C" int igProperty_GetRecord(int container, char *key, int unused);
extern "C" int igProperty_GetRecordByte(int container, char *key, int unused);
extern "C" int igProperty_GetRecordArray(int container, char *key, int unused);
extern "C" int igProperty_GetRecordFolder(int container, char *key, int unused);
extern "C" void FUN_003a9250(int p0, char * p1, int p2);
extern "C" void FUN_003a92e0(int p0, char * p1, int p2);
extern "C" void FUN_003a9310(int p0, char * p1, int p2);
extern "C" void FUN_003a9370(int p0, char * p1, int p2);
extern "C" void Gap__Bec__beDBManager__vfunc_32(void);
extern "C" int Gap__Bec__beDBManager__vfunc_30(void);
extern "C" int Gap__Bec__beDBManager__vfunc_20(void);
extern "C" void beMessenger_RegisterReceiverFromInfo(int, int, char *);
extern "C" void FUN_00236c40(int, void *);
extern "C" int FUN_00366070(...);
extern "C" int beMessenger_AppendObject(int, int);
extern "C" int beMessenger_ResolveEnumValue(int, int, int);
extern "C" int g_propertyNameField[4];
// clang-format off
/* beDataBase record lookup and row count, 0x003a93a0..0x003a9708. A beDataBase is a table of
 * records (rows). Its cells are split by type into six data lists (char, short, int, float, bool,
 * string); each data list is paired with an "offset list" that names the table's columns for that
 * type. A cell of record R and column C is stored row-major at index (columnCount * R + C) of the
 * matching data list (the Junk Shop table is 9 rows x 36 columns; the enemy
 * table keys MODEL, HPMAX, ... by column name). The lists are reached through the reflected
 * object-reference fields and viewed here as the igDataList count/data prefix. */


/* Index returned by beDataBase_FindRecordValueIndex when the key has no column. */


struct igProperty;
typedef igTDataList<igProperty *> ColumnList;
extern "C" char emptyString[];
extern "C" int beDataBase_FindRecordValueIndex(beDataBase *self, int record, const char *key, ColumnList *columns);
extern "C" long long beDataBase_GetRecordInt(beDataBase *self, int record, const char *key);
extern "C" unsigned long long beDataBase_GetRecordBool(beDataBase *self, int record, const char *key);
extern "C" char *beDataBase_GetRecordString(beDataBase *self, int record, const char *key);
extern "C" int beDataBase_GetRecordCount(beDataBase *self);
extern "C" int g_beDBManagerInfo_metaObject[4];
extern "C" int g_beDBManager_metaObject[4];
extern "C" char DAT_005102a0[];
extern "C" void Gap__Bec__beDBManager__vfunc_29(beDBManager *p0, int p1, char *p2);
extern "C" void Gap__Bec__beDBManager__vfunc_31(beDBManager *p0, int p1);
extern "C" int Gap__Bec__beDBManager__vfunc_33(beDBManager *arg0, beBaseInfoRam *arg1, int arg2);

int igProperty_GetRecord(int container, char *key, int unused)
{
    return igProperty_FindByName(container, g_propertyNameField[0], key);
}

void FUN_003a9250(int p0, char * p1, int p2)
{
    igProperty_FindByName(p0, *(int *)0x00585be0, p1);
}

int igProperty_GetRecordByte(int container, char *key, int unused)
{
    return igProperty_FindByName(container, g_propertyNameField[0], key);
}

int igProperty_GetRecordArray(int container, char *key, int unused)
{
    return igProperty_FindByName(container, g_propertyNameField[0], key);
}

void FUN_003a92e0(int p0, char * p1, int p2)
{
    igProperty_FindByName(p0, *(int *)0x00585be0, p1);
}

void FUN_003a9310(int p0, char * p1, int p2)
{
    igProperty_FindByName(p0, *(int *)0x00585be0, p1);
}

int igProperty_GetRecordFolder(int container, char *key, int unused)
{
    return igProperty_FindByName(container, g_propertyNameField[0], key);
}

void FUN_003a9370(int p0, char * p1, int p2)
{
    igProperty_FindByName(p0, *(int *)0x00585be0, p1);
}

#define BEDATABASE_NO_INDEX (-1)
/* Flat index of the cell for (record, key) in the data list that pairs with the offset list
 * `columns`. The key is resolved to a column name through igProperty_FindByName, then located
 * among the list entries; the result is columnCount * record + columnPosition, or -1 when the list
 * has no columns or does not contain the key. */
int beDataBase_FindRecordValueIndex(beDataBase *self, int record, const char *key,
                                    ColumnList *columns) {
    int found;
    int columnCount = columns->count();

    if (!columnCount) {
        return -1;
    }
    found = igProperty_FindByName(columns, (void *)g_propertyNameField[0], key);
    if (!found) {
        return -1;
    }
    int column = columns->find((igProperty *)found);
    return column + columnCount * record;
}

/* Integer cell for (record, key). Tries the char, short and int columns in turn (sign-extending
 * each) and yields 0 when the key is in none. */
long long beDataBase_GetRecordInt(beDataBase *self, int record, const char *key) {
    long long result;
    int index =
        beDataBase_FindRecordValueIndex(self, record, key, (ColumnList *)self->_charOffsetList);
    if (index != BEDATABASE_NO_INDEX)
        return *(signed char *)(((igDataList *)self->_charData)->_data + index);
    index =
        beDataBase_FindRecordValueIndex(self, record, key, (ColumnList *)self->_shortOffsetList);
    if (index != BEDATABASE_NO_INDEX)
        return *(short *)(((igDataList *)self->_shortData)->_data + index * 2);
    index =
        beDataBase_FindRecordValueIndex(self, record, key, (ColumnList *)self->_intOffsetList);
    if (index != BEDATABASE_NO_INDEX)
        result = *(int *)(((igDataList *)self->_intData)->_data + index * 4);
    else
        result = 0;

    return result;
}

/* Boolean cell (one byte) for (record, key). The index is used unchecked, as in retail, so the key
 * must name a bool column. */
unsigned long long beDataBase_GetRecordBool(beDataBase *self, int record, const char *key) {
    int index = (int)beDataBase_FindRecordValueIndex(self, record, key,
                                                     (ColumnList *)self->_boolOffsetList);
    return *(unsigned char *)(((igDataList *)self->_boolData)->_data + index);
}

/* string cell for (record, key): the characters of the stored igStringObj, or an empty string when
 * the cell is null. */
char *beDataBase_GetRecordString(beDataBase *self, int record, const char *key) {
    int index = (int)beDataBase_FindRecordValueIndex(self, record, key,
                                                     (ColumnList *)self->_stringOffsetList);
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

#undef BEDATABASE_NO_INDEX

void Gap__Bec__beDBManager__vfunc_32(void)
{
}

int Gap__Bec__beDBManager__vfunc_30(void)
{
    return g_beDBManagerInfo_metaObject[0];
}

void Gap__Bec__beDBManager__vfunc_29(beDBManager *p0, int p1, char *p2)
{
    beMessenger_RegisterReceiverFromInfo(p0->_messenger, p1, DAT_005102a0);
}

void Gap__Bec__beDBManager__vfunc_31(beDBManager *p0, int p1)
{
    FUN_00236c40(p0->_insight, p0);
}

int Gap__Bec__beDBManager__vfunc_33(beDBManager *arg0, beBaseInfoRam *arg1, int arg2) {
    beBaseInfoRam *p = (beBaseInfoRam *)arg1->_parentInfo;
    int r;
    switch (beMessenger_ResolveEnumValue(arg0->_messenger, FUN_00366070(), arg2)) {
    case 0:
        beMessenger_AppendObject(arg0->_messenger, p->_st1);
        r = 1;
        break;
    default:
        r = 0;
        break;
    }
    return r;
}

int Gap__Bec__beDBManager__vfunc_20(void)
{
    return g_beDBManager_metaObject[0];
}
