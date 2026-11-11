/* Exact metadata field builders. FieldPointerStorage and RefHeader are observed ABI views, not
 * original type names. Virtual views declare byte slots and must not be instantiated. */
#include "dw4/reflected.h"
struct FieldPointerStorage { int prefix[2]; igMetaField **data; int count; };
struct RefHeader { int vtable; unsigned refs; };
typedef igMetaField *(*FieldFactory)(void *);
extern "C" void *Memory_GetAllocatorBySelector(int);
extern "C" void *FUN_002c29c0(void *);
extern "C" void ObjectPointerList_Append(void *,void *);
extern "C" void igMetaObject_AppendField(igMetaObject *,igMetaField *);
extern "C" igMetaField *igMetaObject_GetFieldAt(igMetaObject *,int);
extern "C" int igMetaObject_GetFieldCount(igMetaObject *);
extern "C" void igObject_Destroy(void *);
extern "C" void *FUN_00300e00(igMetaField *,unsigned short,int);
extern "C" void igObject_FreeStorage(igMetaField *,void *);
extern "C" int Memory_GetBufferSize(void *);
extern "C" void igMetaField_Configure(igMetaField *,const char *,igMetaField **,int,igMetaObject *);
extern "C" void igMetaField_FinalizeDescriptor(igMetaField *);

class FieldSizeDispatchView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int GetTypeSize(); };

class FieldBuildDispatchView { public: virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3(); virtual void r4(); virtual void r5(); virtual void r6(); virtual void r7(); virtual void r8(); virtual void r9(); virtual void r10(); virtual void r11(); virtual void r12(); virtual void r13(); virtual void r14(); virtual void r15(); virtual void r16(); virtual void r17(); virtual void r18(); virtual void r19(); virtual void r20(); virtual void *TypeInfo(); virtual void r96(); virtual int TypeSize(); virtual void r104(); virtual void r108(); virtual void r112(); virtual void r116(); virtual void r120(); virtual void r124(); virtual void r128(); virtual void r132(); virtual void r136(); virtual void SetDefault(void *); };
extern "C" void igMetaObject_InheritFromBase(igMetaObject *meta,igMetaObject *parent){
    if(parent!=0){
        if(parent->_children==0)parent->_children=(int)FUN_002c29c0(Memory_GetAllocatorBySelector(*(int *)0x587040));
        ObjectPointerList_Append((void *)parent->_children,meta);
        meta->_parent=(int)parent;
        meta->_vTablePointer=parent->_vTablePointer;
        meta->_requiredAlignment=((igMetaObject *)meta->_parent)->_requiredAlignment;
        meta->_runTimeSize=((igMetaObject *)meta->_parent)->_runTimeSize;
        meta->_sizeofSize=((igMetaObject *)meta->_parent)->_sizeofSize;
        int count=((FieldPointerStorage *)parent->_metaFields)->count;
        for(int i=0;i<count;i++)igMetaObject_AppendField(meta,igMetaObject_GetFieldAt(parent,i));
    }
}
