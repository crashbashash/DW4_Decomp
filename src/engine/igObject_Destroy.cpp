/* RTTI-headed dispatch projection; slot names are indices, not a claim of original C++ method
 * declarations. One explicit four-byte DMOVE preserves the receiver capture after the system-mode
 * read; plain assignment would hoist that copy into the null-system branch's delay slot. */
#include "dw4/reflected.h"
class igObjectDispatchView {
public:
    virtual void slot_00(); virtual void slot_01(); virtual void slot_02();
    virtual void slot_03(); virtual void slot_04(); virtual void slot_05();
    virtual void slot_06(); virtual void slot_07(); virtual void slot_08();
    virtual void slot_09(); virtual void slot_10(); virtual void slot_11();
    virtual void slot_12(); virtual void slot_13(); virtual void slot_14();
    virtual void slot_15(); virtual void slot_16(); virtual void slot_17();
    virtual void slot_18(); virtual void slot_19();
    virtual igMetaObject *slot_20();
};
extern unsigned char *D_00586dc8[];
extern "C" {
void Memory_FreeBuffer(void *);
void ObjectPointerList_EraseAt(void *,int);
int ObjectPointerList_FindIndex(void *,void *);
void igObject_ClearFieldValues(void *);
void igObject_DestructFieldValues(void *);
void *igObject_GetAllocationBase(void *);
void igObject_Destroy(igObjectDispatchView *);
}
void igObject_Destroy(igObjectDispatchView *input){
    /* matching construct: variant search — decl order [2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    igObjectDispatchView *object;
    igMetaObject *type;
    void *instances;
    if(D_00586dc8[0]){
        unsigned char mode=*D_00586dc8[0];
        /* CW's dmove pseudo-op carries copy dataflow and emits DADDU.
         * move emits a 32-bit ADDU; generic daddu loses the same scheduling. */
        asm { dmove object,input }
        if(!mode){
            object->slot_08();object->slot_10();object->slot_00();
            Memory_FreeBuffer(object);return;
        }
        type=object->slot_20();
        type->_instanceCount=(int)((unsigned)type->_instanceCount-1);
        instances=(void *)type->_instances;
        if(instances)ObjectPointerList_EraseAt(instances,ObjectPointerList_FindIndex(instances,object));
        object->slot_16();object->slot_08();object->slot_10();
        igObject_DestructFieldValues(object);igObject_ClearFieldValues(object);
        Memory_FreeBuffer(igObject_GetAllocationBase(object));
    }
}
