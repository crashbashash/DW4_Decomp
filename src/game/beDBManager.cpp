#include "dw4/reflected.h"
#include "dw4/igTDataList.h"
#include "dw4/beDataBase.h"
#include "dw4/beDBManager.h"
#include "dw4/beDBManagerInfo.h"
#include "dw4/beMessenger.h"
#include "dw4/igDataLists.h"
#include "dw4/igInsightCore.h"
#include "dw4/igNamedObject.h"
#include "dw4/emptyString.h"

extern "C" void beDBManager_Prepare(void);
extern "C" igMetaObject *beDBManager_GetInfoMeta(void);
extern "C" igMetaObject *beDBManager_GetMeta(void);
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
extern "C" int beDataBase_FindRecordValueIndex(beDataBase *self, int record, const char *key, ColumnList *columns);
extern "C" char DATABASE_9[];
extern "C" void beDBManager_OnAddRam(beDBManager *p0, int p1, char *p2);
extern "C" void beDBManager_UpdateRam(beDBManager *p0, int p1);
extern "C" int beDBManager_OnMessageText(beDBManager *self, beBaseInfoRam *ram, const char *message);

beDataObjInt *igProperty_GetRecord(igObject *container, const char *key)
{
    return (beDataObjInt *)igProperty_FindByName((igObjectList *)container, g_propertyNameField, key);
}

beDataObjIntList *igProperty_GetRecordIntList(igObject *container, const char *key)
{
    return (beDataObjIntList *)igProperty_FindByName((igObjectList *)container, g_propertyNameField, key);
}

beDataObjBool *igProperty_GetRecordByte(igObject *container, const char *key)
{
    return (beDataObjBool *)igProperty_FindByName((igObjectList *)container, g_propertyNameField, key);
}

beDataObjBoolList *igProperty_GetRecordArray(igObject *container, const char *key)
{
    return (beDataObjBoolList *)igProperty_FindByName((igObjectList *)container, g_propertyNameField, key);
}

beDataObjString *igProperty_GetRecordString(igObject *container, const char *key)
{
    return (beDataObjString *)igProperty_FindByName((igObjectList *)container, g_propertyNameField, key);
}

beDataObjStringList *igProperty_GetRecordStringList(igObject *container, const char *key)
{
    return (beDataObjStringList *)igProperty_FindByName((igObjectList *)container, g_propertyNameField, key);
}

beDataObjObjectList *igProperty_GetRecordFolder(igObject *container, const char *key)
{
    return (beDataObjObjectList *)igProperty_FindByName((igObjectList *)container, g_propertyNameField, key);
}

beDataObjFloatList *igProperty_GetRecordFloatList(igObject *container, const char *key)
{
    return (beDataObjFloatList *)igProperty_FindByName((igObjectList *)container, g_propertyNameField, key);
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
    found = igProperty_FindByName((igObjectList *)columns, (igMetaField *)g_propertyNameField, key);
    if (!found) {
        return -1;
    }
    int column = columns->find((igProperty *)found);
    return column + columnCount * record;
}

/* Integer cell for (record, key). Tries the char, short and int columns in turn (sign-extending
 * each) and yields 0 when the key is in none. */
int beDataBase_GetRecordInt(beDataBase *self, int record, const char *key) {
    int result;
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

void beDBManager_Prepare(void)
{
}

igMetaObject *beDBManager_GetInfoMeta(void)
{
    return g_beDBManagerInfo_metaObject;
}

void beDBManager_OnAddRam(beDBManager *p0, int p1, char *p2)
{
    beMessenger_RegisterReceiverFromInfo((beMessenger *)p0->_messenger, (beBaseInfoRam *)p1, DATABASE_9);
}

void beDBManager_UpdateRam(beDBManager *p0, int p1)
{
    igInsightCore_RemoveFromScheduler((igInsightCore *)p0->_insight, (igObject *)p0);
}

int beDBManager_OnMessageText(beDBManager *self, beBaseInfoRam *ram, const char *message) {
    beDBManagerInfo *info = (beDBManagerInfo *)ram->_parentInfo;
    int result;
    switch (beMessenger_ResolveEnumValue((beMessenger *)self->_messenger, beDBManager_GetMsgActionEnum(), message)) {
    case 0:
        beMessenger_AppendObject((beMessenger *)self->_messenger, (igObject *)info->_dataBase);
        result = 1;
        break;
    default:
        result = 0;
        break;
    }
    return result;
}

igMetaObject *beDBManager_GetMeta(void)
{
    return g_beDBManager_metaObject;
}
