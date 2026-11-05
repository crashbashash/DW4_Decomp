/* 0x0015b140
 * Index read for a PS2 index array, dispatched on the stored index width
 * (_dataSize, an igEnumMetaField; docs/engine/platform-seam.md).  Value 0 calls
 * the accessor at vtable byte offset 128 with the index and the result both
 * truncated to 16 bits; value 1 calls the accessor at offset 132 with the index
 * unmasked (presumably the 32-bit variant -- hypothesis, the enum names are not
 * recovered); any other width reads as 0.  The second call's index argument is
 * already in the right register, which is why the draft had dropped it. */
#include "dw4/reflected.h"
extern "C" {
int Gap__Core__igPsx2IndexArray__vfunc_34(igPsx2IndexArray *self, int index);
}
/* Dummy class: slot at vtable byte offset 128 (30 slots precede it). */
class IndexArrayNarrowReadSlot {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual int ReadNarrow(int index);
};
/* Dummy class: slot at vtable byte offset 132 (31 slots precede it). */
class IndexArrayWideReadSlot {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
    virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14();
    virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24();
    virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29();
    virtual void d30();
    virtual int ReadWide(int index);
};
int Gap__Core__igPsx2IndexArray__vfunc_34(igPsx2IndexArray *self, int index) {
    int dataSize;

    dataSize = self->_dataSize;
    switch (dataSize) {
    case 1:
        return ((IndexArrayWideReadSlot *)(self))->ReadWide(index);
    case 0:
        return ((IndexArrayNarrowReadSlot *)(self))->ReadNarrow((int)(index & 0xFFFF)) & 0xFFFF;
    default:
        return 0;
    }
}
