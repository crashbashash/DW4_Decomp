/* 0x002dc6c0
 * The array field's +0xd0 hook (SwapBytes, config/SLUS-20836/names/ObjectModel.tsv): the
 * endian swap of the IGB raw-field transfer.  An array field holds `_num`
 * elements per instance, so it forwards to the shared igEnumMetaField descriptor
 * with `count * _num` elements (finding 364). */
#include "dw4/reflected.h"
extern "C" {
/* Returns the shared igEnumMetaField descriptor (global 0x005865a0), registering
 * the class on first use; same shape as igIntMetaField_GetDefaultDescriptor. */
void **igEnumMetaField_GetDefaultDescriptor(...);
void Gap__Core__igEnumArrayMetaField__vfunc_52(igEnumArrayMetaField *self, int buffer, int count);
}
/* Dummy class whose slot 52 (vtable +0xd0) is the SwapBytes(buffer, count) call. */
class MetaFieldSwapBytesSlot {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34();
    virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39();
    virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44();
    virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49();
    virtual int SwapBytes(int buffer, int count);
};
void Gap__Core__igEnumArrayMetaField__vfunc_52(igEnumArrayMetaField *self, int buffer, int count) {
    void **elementField;

    elementField = (void **)(igEnumMetaField_GetDefaultDescriptor());
    ((MetaFieldSwapBytesSlot *)(elementField))->SwapBytes((int)(buffer), (int)(count * self->_num));
}
