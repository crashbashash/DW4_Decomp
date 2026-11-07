#include "dw4/reflected.h"
class DescriptorCloneView { public:
    virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
    virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
    virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
    virtual void slot16(); virtual void slot17(); virtual void slot18();
    virtual igMemoryRefMetaField *Clone(int copyFlag);
};
extern "C" {
igMetaField *igMetaObject_FindFieldByName(igMetaObject *, void *);
int ObjectPointerList_FindIndex(int, void *);
int igIntMetaField_GetDefaultDescriptor();
void igMetaObject_FinalizeAndReplaceField(igMetaObject *, int, igMetaField *);
void igObject_Destroy(void *);
extern igMetaObject *g_igIntList_metaObject[4];
extern char data[];
extern int g_igIntList_dataDescriptorCell[4];
void igIntList_InitFields(void);
}
static inline void releaseField(igMemoryRefMetaField *f) {
    f->_refCount = (int)f->_refCount - 1;
    if (((unsigned long long)((long long)(int)f->_refCount << 0x29) >> 0x29) == 0) {
        igObject_Destroy(f);
    }
}
void igIntList_InitFields(void) {
    igMetaObject *meta = g_igIntList_metaObject[0];
    igMemoryRefMetaField *field = (igMemoryRefMetaField *)igMetaObject_FindFieldByName(meta, data);
    int index = ObjectPointerList_FindIndex(meta->_metaFields, field);
    field = ((DescriptorCloneView *)field)->Clone(1);
    field->_memType = igIntMetaField_GetDefaultDescriptor();
    field->_memSize = 0;
    field->_externalEnumStorage = (int)g_igIntList_dataDescriptorCell;
    igMetaObject_FinalizeAndReplaceField(meta, index, (igMetaField *)field);
    releaseField(field);
}
