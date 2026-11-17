#ifndef DW4_BEDBMANAGER_H
#define DW4_BEDBMANAGER_H

struct beDBManager;
struct beDataObjInt;
struct beDataObjStringList;
struct beDataObjString;
struct beDataObjIntList;
struct beDataObjObjectList;
struct beDataObjFloatList;
struct beDataObjBool;
struct beDataObjBoolList;
struct igMetaEnum;
struct igObject;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beDBManager *beDBManager_CreateInstance(int allocator);
struct igMetaEnum *beDBManager_GetMsgActionEnum(void);
struct beDataObjInt *igProperty_GetRecord(struct igObject *container, const char *key);
struct beDataObjBoolList *igProperty_GetRecordArray(struct igObject *container, const char *key);
struct beDataObjBool *igProperty_GetRecordByte(struct igObject *container, const char *key);
struct beDataObjFloatList *igProperty_GetRecordFloatList(struct igObject *container, const char *key);
struct beDataObjObjectList *igProperty_GetRecordFolder(struct igObject *container, const char *key);
struct beDataObjIntList *igProperty_GetRecordIntList(struct igObject *container, const char *key);
struct beDataObjString *igProperty_GetRecordString(struct igObject *container, const char *key);
struct beDataObjStringList *igProperty_GetRecordStringList(struct igObject *container, const char *key);

extern struct igMetaObject *g_beDBManager_metaObject;

#ifdef __cplusplus
}
#endif

#endif
