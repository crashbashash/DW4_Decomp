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
void FUN_0030eda0(igMetaField *, int);
void FUN_002ea4b0(igMetaField *, int);
extern int DAT_004bf5e0[4];
extern int DAT_004bf5f0[4];
extern int DAT_004bf600[4];
extern int DAT_004bf610[4];
extern int DAT_004f5e70[4];
extern igMetaObject *DAT_00585880[4];
extern int DAT_00585890[4];
void FUN_002b8b50(void);
}
void FUN_002b8b50(void) {
    igMetaObject *meta = DAT_00585880[0];
    int base = igMetaObject_GetFieldCount(meta);
    igMetaField *field;
    int index;
    igMetaObject_CreateFields(meta, DAT_004bf5e0, 3);
    field = igMetaObject_FindFieldByName(meta, DAT_004f5e70);
    index = ObjectPointerList_FindIndex(meta->_metaFields, field);
    field = ((DescriptorCloneView *)field)->Clone(1);
    FUN_0030eda0(field, 1);
    field->_persistent = 0;
    field->_externalEnumStorage = (int)DAT_00585890;
    igMetaObject_FinalizeAndReplaceField(meta, index, field);
    releaseField(field);
    field = igMetaObject_GetFieldAt(meta, base);
    FUN_002ea4b0(field, 1);
    field->_persistent = 0;
    igMetaObject_NameFields(meta, DAT_004bf5f0, DAT_004bf600, DAT_004bf610, base);
}
