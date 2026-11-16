#ifndef DW4_BEDATABASE_H
#define DW4_BEDATABASE_H

/* A beDataBase is a table of records (rows). Its cells are split by type into six data lists (char,
 * short, int, float, bool, string); each data list is paired with an "offset list" that names the
 * table's columns for that type. A cell of record R and column C is stored row-major at index
 * (columnCount * R + C) of the matching data list. The record getters look a cell up by column name. */

struct beDataBase;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

void beDataBase_EnsureRegistered(void);
struct igMetaObject *beDataBase_GetOrCreateMetaObject(void);
unsigned long long beDataBase_GetRecordBool(struct beDataBase *self, int record, const char *key);
int beDataBase_GetRecordCount(struct beDataBase *self);
long long beDataBase_GetRecordInt(struct beDataBase *self, int record, const char *key);
char *beDataBase_GetRecordString(struct beDataBase *self, int record, const char *key);

#ifdef __cplusplus
}
#endif

#endif
