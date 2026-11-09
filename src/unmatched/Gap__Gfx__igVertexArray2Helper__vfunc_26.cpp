#include "dw4/igSmartPointer.h"

struct VertexArrayFormat : igObject {
    char pad8[16];
    int primitiveMode;
};

struct VertexFormatOwner : igObject {
    char pad8[12];
    VertexArrayFormat *format;

    void setFormat(const igSmartPointer<VertexArrayFormat> &next) {
        VertexArrayFormat *object = next.p;
        VertexArrayFormat *previous;

        if (object != 0) {
            object->_refCount = object->_refCount + 1;
        }
        previous = format;
        if (previous != 0) {
            previous->_refCount = previous->_refCount - 1;
            if ((previous->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(previous);
            }
        }
        format = object;
    }
};

extern "C" {
void *igObject_GetAllocator(void *object);
VertexArrayFormat *FUN_0014adc0(void *allocator);
void Gap__Gfx__igVertexArray2Helper__vfunc_26(igVertexArray2Helper *helper, unsigned int flags);
}

void Gap__Gfx__igVertexArray2Helper__vfunc_26(igVertexArray2Helper *helper, unsigned int flags) {
    int mode = 0;
    VertexFormatOwner *array;

    if (flags & 1) {
        mode = 2;
    }
    array = (VertexFormatOwner *)helper->_vertexArray;
    if (array == 0) {
        return;
    }
    if (array->format != 0) {
        array->format->primitiveMode = mode;
        return;
    }
    {
        igSmartPointer<VertexArrayFormat> format(FUN_0014adc0(igObject_GetAllocator(helper)));
        if (format != 0) {
            format->primitiveMode = mode;
            array = (VertexFormatOwner *)helper->_vertexArray;
            array->setFormat(format);
        }
    }
}
