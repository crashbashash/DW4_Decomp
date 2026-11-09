#include "dw4/igSmartPointer.h"

struct V3 { float x, y, z; };
struct BoundsObject : public igObject { V3 min; V3 max; };
extern "C" {
BoundsObject *FUN_0018a660(...);
int FUN_00190060(int, BoundsObject *);
int FUN_001b21d0(int, V3 *, V3 *);
int igVertexArray2__FindVertexData(BoundsObject *, int, int);
int igObject_GetAllocator(...);
}

extern "C" void FUN_001b23b0(BoundsObject **, int);
extern "C" bool FUN_001b24d0(int arg0, int arg1) {
    igSmartPointer<BoundsObject> bounds(FUN_0018a660(igObject_GetAllocator()));
    BoundsObject *array;
    V3 min;
    V3 max;
    FUN_001b21d0(arg1, &min, &max);
    bounds.get()->min = min;
    bounds.get()->max = max;
    FUN_00190060(arg0, bounds.get());
    FUN_001b23b0(&array, arg1);
    int missing = igVertexArray2__FindVertexData(array, 5, 0);
    if (array != 0) {
        array->_refCount = array->_refCount - 1;
        if ((array->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(array);
        }
    }
    return !missing;
}
