#ifndef DW4_BENDMWITEMBASE_H
#define DW4_BENDMWITEMBASE_H

struct beNDMWItemBase;
struct beNDMWStatus;
struct igObjectList;
struct igVec3f;

extern "C" {
unsigned long long beNDMWItemBase_GetRecordBool(beNDMWItemBase *self, beNDMWStatus *status, const char *key);
int beNDMWItemBase_GetRecordInt(beNDMWItemBase *self, beNDMWStatus *status, const char *key);
char *beNDMWItemBase_GetRecordString(beNDMWItemBase *self, beNDMWStatus *status, const char *key);
void beNDMWItemBase_GetRevisionColor(igVec3f *color, beNDMWItemBase *item);
int beNDMWItemBase_IndexOfRecNo(igObjectList *items, int recNo);
}

#endif
