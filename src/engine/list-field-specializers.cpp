/* Inherited `_data` specialization callbacks of igObjectList (0x002bd830) and igIntList
 * (0x002cac20).  Each clones the `_data` memory-reference descriptor inherited from the parent
 * list class, retypes the clone's element provider, publishes the clone's descriptor cell and
 * swaps the clone in for the parent's descriptor, so the parent's shared descriptor is never
 * mutated.  See docs/engine/list-descriptor-copy.md ("Actual inherited `_data`
 * specialization"). */
#include "dw4/reflected.h"

/* ABI projection of the descriptor object for the virtual Clone call (vtable offset 84 of the
 * igMemoryRefMetaField vtable at 0x532a50). The leading slots are placeholders that only position
 * Clone; do not instantiate it. */
class DescriptorCloneView {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void *Clone(int copyFlag);};

extern "C" igMetaField *igMetaObject_FindFieldByName(igMetaObject *,const char *);
extern "C" int ObjectPointerList_FindIndex(void *,void *);
extern "C" int igObjectRefMetaField_GetDefaultDescriptor();
extern "C" int igIntMetaField_GetDefaultDescriptor();
extern "C" void igMetaObject_FinalizeAndReplaceField(igMetaObject *,int,igMetaField *);
extern "C" void igObject_Destroy(void *);

/* Class handles of the two list classes (slot holding the published igMetaObject pointer). */
extern "C" int g_igObjectList_metaObject[4];
extern "C" int g_igIntList_metaObject[4];
/* Name of the inherited field that is specialized: "_data". */
extern "C" char data[];
/* Descriptor-publication cells written to the clone's `_externalEnumStorage` (+28), one per list
 * class, 8 bytes after that class's handle. */
extern "C" int g_igObjectList_dataDescriptorCell[4];
extern "C" int g_igIntList_dataDescriptorCell[4];

/* Low 23 bits of igObject::_refCount hold the count; the object is destroyed when they reach 0. */
#define IG_REF_COUNT_MASK 0x7fffff

extern "C" void igObjectList_InitFields(){
    igMemoryRefMetaField *dataField;
    igMetaObject *meta=(igMetaObject *)g_igObjectList_metaObject[0];
    dataField=(igMemoryRefMetaField *)igMetaObject_FindFieldByName(meta,data);
    int fieldIndex=ObjectPointerList_FindIndex((void *)meta->_metaFields,dataField);
    dataField=(igMemoryRefMetaField *)((DescriptorCloneView *)dataField)->Clone(1);
    dataField->_memType=igObjectRefMetaField_GetDefaultDescriptor();
    dataField->_memSize=0;
    dataField->_externalEnumStorage=(int)g_igObjectList_dataDescriptorCell;
    igMetaObject_FinalizeAndReplaceField(meta,fieldIndex,(igMetaField *)dataField);
    /* release the clone-owned temporary reference */
    --((igObject *)dataField)->_refCount;
    if(!(((igObject *)dataField)->_refCount&IG_REF_COUNT_MASK))igObject_Destroy(dataField);
}

extern "C" void igIntList_InitFields(){
    igMemoryRefMetaField *dataField;
    igMetaObject *meta=(igMetaObject *)g_igIntList_metaObject[0];
    dataField=(igMemoryRefMetaField *)igMetaObject_FindFieldByName(meta,data);
    int fieldIndex=ObjectPointerList_FindIndex((void *)meta->_metaFields,dataField);
    dataField=(igMemoryRefMetaField *)((DescriptorCloneView *)dataField)->Clone(1);
    dataField->_memType=igIntMetaField_GetDefaultDescriptor();
    dataField->_memSize=0;
    dataField->_externalEnumStorage=(int)g_igIntList_dataDescriptorCell;
    igMetaObject_FinalizeAndReplaceField(meta,fieldIndex,(igMetaField *)dataField);
    /* release the clone-owned temporary reference */
    --((igObject *)dataField)->_refCount;
    if(!(((igObject *)dataField)->_refCount&IG_REF_COUNT_MASK))igObject_Destroy(dataField);
}
