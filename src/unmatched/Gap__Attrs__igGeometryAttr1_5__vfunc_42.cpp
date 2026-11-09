class PrimLengthArray {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15();
    virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
    virtual void d24();
    virtual unsigned int getLength(unsigned int index);
};
struct VertexCountSource { int _vtable; unsigned int _refCount; int _pad8; unsigned int _vertexCount; };
struct GeometryPrimitiveView {
    int _vtable;
    unsigned int _refCount;
    short _cachedAttrIndex;
    short _cachedUnitID;
    VertexCountSource *_vertexArray;
    void *_indexArray;
    int _primType;
    unsigned int _numPrims;
    unsigned int _offset;
    char _pad32[16];
    PrimLengthArray *_stripLengths;
};
extern "C" unsigned int Gap__Attrs__igGeometryAttr1_5__vfunc_42(GeometryPrimitiveView *self);
unsigned int Gap__Attrs__igGeometryAttr1_5__vfunc_42(GeometryPrimitiveView *self) {
    unsigned int i;
    unsigned int total;
    PrimLengthArray *lengths;
    int type;
    unsigned int count;
    unsigned int vertexCount;
    unsigned int offset;

    /* matching construct: statement-order sweep — offset read second */
    vertexCount = self->_vertexArray->_vertexCount;
    offset = self->_offset;
    count = self->_numPrims;
    type = self->_primType;
    lengths = self->_stripLengths;
    if (self->_indexArray != 0) {
        total = vertexCount - offset;
    } else {
        total = 0;
        if (type == 4 || type == 5 || type == 2) {
            for (i = 0; i < count; i++) {
                total += lengths->getLength(i);
            }
        } else {
            if (type == 0) {
                total = count;
            } else {
                if (type == 1) {
                    count *= 2;
                } else if (type == 3) {
                    count *= 3;
                } else {
                    count = 0;
                }
                total = count;
            }
        }
    }
    return total;
}
