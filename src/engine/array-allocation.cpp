/* igMetaField_AllocateArray: allocate the backing array of a memory-reference field. The element
 * descriptor (_memType) supplies the element size and alignment through its virtual methods; the
 * allocator is asked for count * size bytes at that alignment and the pointer is published into
 * the owning object at the field's _offset. The *View classes below only project the observed
 * vtable slots (the numbered placeholders stand for slots this routine never calls); do not
 * instantiate them. */
#include "dw4/reflected.h"
class ElementLayoutView {public:
virtual void d0();
virtual void d1();
virtual void d2();
virtual void d3();
virtual void d4();
virtual void d5();
virtual void d6();
virtual void d7();
virtual void d8();
virtual void d9();
virtual void d10();
virtual void d11();
virtual void d12();
virtual void d13();
virtual void d14();
virtual void d15();
virtual void d16();
virtual void d17();
virtual void d18();
virtual void d19();
virtual void d20();
virtual void d21();
virtual void d22();
virtual int Size();virtual void d104();virtual int Alignment();};
class AlignedAllocatorView {public:
virtual void a0();
virtual void a1();
virtual void a2();
virtual void a3();
virtual void a4();
virtual void a5();
virtual void a6();
virtual void a7();
virtual void a8();
virtual void a9();
virtual void a10();
virtual void a11();
virtual void a12();
virtual void a13();
virtual void a14();
virtual void a15();
virtual void a16();
virtual void a17();
virtual void a18();
virtual void a19();
virtual void a20();
virtual void a21();
virtual void a22();
virtual void a23();
virtual void a24();
virtual void a25();
virtual void a26();
virtual void a27();
virtual void a28();
virtual void a29();
virtual void a30();
virtual void a31();
virtual void a32();
virtual void a33();
virtual void a34();
virtual void a35();
virtual void a36();
virtual void a37();
virtual void a38();
virtual void a39();
virtual void a40();
virtual void a41();
virtual void a42();
virtual void a43();
virtual void a44();
virtual void a45();
virtual void a46();
virtual void a47();
virtual void a48();
virtual void a49();
virtual void a50();
virtual void a51();
virtual void a52();
virtual void *Allocate(int,int);};
extern "C" int igObject_IsKindOf(void *,int);
extern "C" void memset(void *,int,int);
/* Class handle of igRefMetaField, and the two status words reported to callers (success /
 * failure); array form keeps the load absolute. */
extern "C" int g_igRefMetaField_metaObject[4],g_statusSucceeded[4],g_allocatorFailureStatus[4];
extern "C" void igMetaField_AllocateArray(int *outStatus,igMemoryRefMetaField *field,void *object,int count,AlignedAllocatorView *allocator){
    unsigned int bytes=(unsigned int)count*(unsigned short)((ElementLayoutView *)field->_memType)->Size();
    int alignment=(unsigned short)((ElementLayoutView *)field->_memType)->Alignment();
    void *data=allocator->Allocate(bytes,alignment);
    if(!data){*outStatus=g_allocatorFailureStatus[0];return;}
    /* Reference-typed elements start zeroed; other element types keep the allocator's contents. */
    if(igObject_IsKindOf((void *)field->_memType,g_igRefMetaField_metaObject[0]))memset(data,0,bytes);
    *(void **)((char *)object+field->_offset)=data;
    *outStatus=g_statusSucceeded[0];
}
