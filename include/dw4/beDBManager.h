#ifndef DW4_BEDBMANAGER_H
#define DW4_BEDBMANAGER_H

struct beDBManager;
struct igMetaEnum;
struct igMetaObject;

#ifdef __cplusplus
extern "C" {
#endif

struct beDBManager *beDBManager_CreateInstance(int allocator);
struct igMetaEnum *beDBManager_GetMsgActionEnum(void);
int igProperty_GetRecord(int container, char *key, int unused);
int igProperty_GetRecordArray(int container, char *key, int unused);
int igProperty_GetRecordByte(int container, char *key, int unused);
void igProperty_GetRecordFloatList(int p0, char *p1, int p2);
int igProperty_GetRecordFolder(int container, char *key, int unused);
void igProperty_GetRecordIntList(int p0, char *p1, int p2);
void igProperty_GetRecordString(int p0, char *p1, int p2);
void igProperty_GetRecordStringList(int p0, char *p1, int p2);

extern struct igMetaObject *g_beDBManager_metaObject;

#ifdef __cplusplus
}
#endif

#endif
