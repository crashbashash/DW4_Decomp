/* Reference-field operations in retail order. The header and virtual-slot projections describe ABI
 * positions, not original C++ declarations. FieldSizeDispatchView must not be instantiated. */
#include "dw4/reflected.h"
extern "C" void igObject_Destroy(void *);
extern "C" void *igObject_GetAllocator(void *);
extern "C" void *Memory_GetAllocatorByName(const char *);
extern "C" void *igMetaObject_CreateInstance(void *,void *);
extern "C" int memset(...);
extern "C" void igObjectRefMetaField_Assign(igObjectRefMetaField *,void *,igObject *);
extern "C" void igRefMetaField_ClearValue(igMetaField *,void *);

class FieldSizeDispatchView { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int GetTypeSize(); };
extern "C" void igRefMetaField_ZeroValue(igMetaField *field,void *object) {
    int destination=(int)object+field->_offset;
    memset(destination,0,((FieldSizeDispatchView *)field)->GetTypeSize() & 0xffff);
}
extern "C" void igRefMetaField_ClearValue(igMetaField *field,void *object) {
    int destination=(int)object+field->_offset;
    memset(destination,0,((FieldSizeDispatchView *)field)->GetTypeSize() & 0xffff);
}

extern "C" unsigned char igRefMetaField_IsConstruct(igRefMetaField *field) { return field->_construct; }
