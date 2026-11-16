#ifndef DW4_BENDMWLOADINTF2_H
#define DW4_BENDMWLOADINTF2_H

struct AllocatorValue;
struct ObjectRefTarget;
struct beNDMWLoadIntf2;
struct igDataList;
struct igMetaObject;
struct igObject;

extern "C" {
extern igMetaObject *g_beNDMWLoadIntf2_metaObject;
void Vec3f_Copy(void *destination, void *source);
beNDMWLoadIntf2 *beNDMWLoadIntf2_CreateInstance(int allocator);
int beNDMWLoadIntf2_Memory_SelectAllocator(const int *selector, int ownAllocator);
void *beNDMWLoadIntf2_beBaseInfoDataList_FindProperty(int list, int nameField, const void *name);
AllocatorValue beNDMWLoadIntf2_beBaseInfoDataList_MakeAllocatorValue(int allocator);
int beNDMWLoadIntf2_beNDMWLoadSavePlWorkList_Get(igDataList *list, int index);
int beNDMWLoadIntf2_igIntList_GetData(igDataList *list);
int beNDMWLoadIntf2_igObjectList_Get(igDataList *list, int index);
void beNDMWLoadIntf2_igObjectList_Set(igDataList *list, int index, ObjectRefTarget *replacement);
void beNDMWLoadIntf2_igObject_Release(igObject *object);
void beNDMWLoadIntf2_igObject_Retain(ObjectRefTarget *object);
ObjectRefTarget **beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Assign(ObjectRefTarget **destination, ObjectRefTarget **source);
int beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Deref(int *reference);
int beNDMWLoadIntf2_igSmartPointer_beBaseInfoDataList_Get(int *reference);
}

#endif
