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
extern "C" {
void *Memory_GetAllocatorBySelector(int);
igMetaField *igObjectRefMetaField_Create(void *);
void igMetaField_Configure(igMetaField *, void *, void *, int, igMetaObject *);
void igStringMetaField_SetDefaultText(igMetaField *, void *);
extern int DAT_004c0cd0[4];
extern int DAT_004c0ce0[4];
extern int DAT_004c0cf0[4];
extern int DAT_004c0d00[4];
extern int DAT_004f6520[4];
extern int DAT_004f78f8[4];
extern int DAT_004f7908[4];
extern int DAT_004f7910[4];
extern igMetaObject *DAT_00586450[4];
extern int DAT_00586458[4];
extern int DAT_00587040[4];
extern int DAT_00587198[4];
void FUN_002c55f0(void);
}
void FUN_002c55f0(void) {
    igMetaObject *meta = DAT_00586450[0];
    int base = igMetaObject_GetFieldCount(meta);
    igMetaField *field;
    int index;
    int fields;
    igMetaObject_CreateFields(meta, DAT_004c0cd0, 4);
    fields = meta->_metaFields;
    index = ObjectPointerList_FindIndex(fields, igMetaObject_FindFieldByName(meta, DAT_004f6520));
    field = igObjectRefMetaField_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    igMetaField_Configure(field, DAT_004f6520, DAT_00586458, 0x18, meta);
    ((igObjectRefMetaField *)field)->_metaObject = DAT_00587198[0];
    field->_persistent = 0;
    field->_externalEnumStorage = (int)DAT_00586458;
    igMetaObject_FinalizeAndReplaceField(meta, index, field);
    releaseField(field);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base), DAT_004f78f8);
    igStringMetaField_SetDefaultText(igMetaObject_GetFieldAt(meta, base + 1), DAT_004f7908);
    field = igMetaObject_GetFieldAt(meta, base + 3);
    igStringMetaField_SetDefaultText(field, DAT_004f7910);
    field->_persistent = 0;
    igMetaObject_NameFields(meta, DAT_004c0ce0, DAT_004c0cf0, DAT_004c0d00, base);
}
