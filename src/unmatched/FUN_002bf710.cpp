#include "dw4/reflected.h"
class DescriptorCloneView { public:
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
    virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
    virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18();
    virtual igMetaField *Clone(int copyFlag);
};
extern "C" {
int igMetaObject_GetFieldCount(igMetaObject *);
void igMetaObject_CreateFields(igMetaObject *, void *, int);
igMetaField *igMetaObject_FindFieldByName(igMetaObject *, void *);
int ObjectPointerList_FindIndex(int, void *);
void igMetaObject_FinalizeAndReplaceField(igMetaObject *, int, igMetaField *);
igMetaField *igMetaObject_GetFieldAt(igMetaObject *, int);
void igMetaObject_NameFields(igMetaObject *, void *, void *, void *, int);
void igObject_Destroy(void *);
}
static inline void releaseField(igMetaField *f) {
    f->_refCount = (int)f->_refCount - 1;
    if (((unsigned long long)((long long)(int)f->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(f);
    }
}
struct InitFieldView { char pad40[40]; unsigned char f40; char pad41[11]; int f52; int f56; unsigned char f60; };
extern "C" {
void *Memory_GetAllocatorBySelector(int);
igMetaField *FUN_002c5fb0(void *);
void igMetaField_Configure(igMetaField *, void *, void *, int, igMetaObject *);
int FUN_002beca0(void);
void FUN_002bec40(void);
void FUN_002d3890(igMetaField *, int);
void FUN_002d4e40(igMetaField *, int);
void FUN_002dc7a0(igMetaField *, void *);
void FUN_002ea4b0(igMetaField *, int);
extern int DAT_004bffa0[4];
extern int DAT_004bffc0[4];
extern int DAT_004bffe0[4];
extern int DAT_004c0000[4];
extern int DAT_004c0020[4];
extern int DAT_004f5f20[4];
extern int DAT_004f6838[4];
extern igMetaObject *DAT_00585d80[4];
extern int DAT_00585d90[4];
extern int DAT_00585db8[4];
extern int DAT_00587040[4];
void FUN_002bf710(void);
}
void FUN_002bf710(void) {
    igMetaObject *meta = DAT_00585d80[0];
    int base = igMetaObject_GetFieldCount(meta);
    igMetaField *field;
    int index;
    int fields;
    igMetaObject_CreateFields(meta, DAT_004bffa0, 8);
    field = igMetaObject_FindFieldByName(meta, DAT_004f5f20);
    index = ObjectPointerList_FindIndex(meta->_metaFields, field);
    field = ((DescriptorCloneView *)field)->Clone(1);
    FUN_002d4e40(field, 2);
    field->_externalEnumStorage = (int)DAT_00585d90;
    igMetaObject_FinalizeAndReplaceField(meta, index, field);
    releaseField(field);
    igMetaObject_GetFieldAt(meta, base)->_persistent = 0;
    field = igMetaObject_GetFieldAt(meta, base + 1);
    ((InitFieldView *)field)->f56 = FUN_002beca0();
    ((InitFieldView *)field)->f60 = 0;
    ((InitFieldView *)field)->f40 = 1;
    FUN_002d3890(igMetaObject_GetFieldAt(meta, base + 2), 1);
    FUN_002d3890(igMetaObject_GetFieldAt(meta, base + 3), 1);
    fields = meta->_metaFields;
    index = ObjectPointerList_FindIndex(fields, igMetaObject_FindFieldByName(meta, DAT_004f6838));
    field = FUN_002c5fb0(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    igMetaField_Configure(field, DAT_004f6838, DAT_00585db8, 0x24, meta);
    FUN_002dc7a0(field, DAT_004c0020);
    ((InitFieldView *)field)->f52 = (int)FUN_002bec40;
    field->_externalEnumStorage = (int)DAT_00585db8;
    igMetaObject_FinalizeAndReplaceField(meta, index, field);
    releaseField(field);
    FUN_002d3890(igMetaObject_GetFieldAt(meta, base + 4), 1);
    FUN_002ea4b0(igMetaObject_GetFieldAt(meta, base + 5), -1);
    field = igMetaObject_GetFieldAt(meta, base + 6);
    ((InitFieldView *)field)->f56 = FUN_002beca0();
    ((InitFieldView *)field)->f40 = 1;
    igMetaObject_NameFields(meta, DAT_004bffc0, DAT_004bffe0, DAT_004c0000, base);
}
