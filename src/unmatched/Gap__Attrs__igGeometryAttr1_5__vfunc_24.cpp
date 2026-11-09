#include "dw4/reflected.h"

class StripLengths {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3();
    virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24(); virtual int get(int index);
};

extern "C" {
void Gap__Gfx__igPsx2VisualContext__vfunc_59(void *context, int vertexArray);
void Gap__Gfx__igPsx2VisualContext__vfunc_60(void *context, int indexArray);
void Gap__Gfx__igPsx2VisualContext__vfunc_63(void *context, StripLengths *lengths);
void Gap__Gfx__igPsx2VisualContext__vfunc_71(void *context, int primType, int count, unsigned offset);
void Gap__Gfx__igPsx2VisualContext__vfunc_74(void *context, int primType, unsigned numPrims, unsigned offset, int flags);
}

extern "C" void Gap__Attrs__igGeometryAttr1_5__vfunc_24(igGeometryAttr1_5 *self, void *context)
{
    /* matching construct: declaration and load order permutation sweep (5040 + 120 variants) */
    int primType;
    unsigned numPrims;
    unsigned offset;
    int stripType;
    int indexArray;
    int overlap;
    StripLengths *lengths;

    Gap__Gfx__igPsx2VisualContext__vfunc_59(context, self->_vertexArray);
    offset = self->_offset;
    numPrims = self->_numPrims;
    primType = self->_primType;
    lengths = (StripLengths *)self->_stripLengths;
    indexArray = self->_indexArray;
    if (indexArray != 0) Gap__Gfx__igPsx2VisualContext__vfunc_60(context, indexArray);
    if (lengths != 0) {
        if (primType == 2) {
            stripType = 0;
            overlap = 1;
        } else if (primType == 4) {
            stripType = 1;
            overlap = 2;
        } else {
            if (primType != 5) return;
            stripType = 2;
            overlap = 2;
        }
        switch (numPrims) {
        case 0:
            break;
        case 1:
            Gap__Gfx__igPsx2VisualContext__vfunc_71(context, primType, lengths->get(0) - overlap, offset);
            break;
        default:
            Gap__Gfx__igPsx2VisualContext__vfunc_63(context, lengths);
            Gap__Gfx__igPsx2VisualContext__vfunc_74(context, stripType, numPrims, offset, 0);
        }
        if (lengths != 0) Gap__Gfx__igPsx2VisualContext__vfunc_63(context, 0);
    } else {
        Gap__Gfx__igPsx2VisualContext__vfunc_71(context, primType, numPrims, offset);
    }
    if (indexArray != 0) Gap__Gfx__igPsx2VisualContext__vfunc_60(context, 0);
}
