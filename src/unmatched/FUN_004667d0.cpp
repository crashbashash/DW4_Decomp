#include "dw4/reflected.h"
extern "C" {
int FUN_00191f30(...);
int FUN_004569c0(...);
int FUN_00456a60(...);
int List_Resize(...);
int ObjectList_AppendRetained(...);
int igObject_Destroy(...);
int FUN_004665e0(...);
igProbe *FUN_0019e680(int);
static inline int count_of(const igIntList *list) { return list->_count; }
struct ProbeRef {
    igProbe *p;
    ProbeRef(igProbe *object) : p(object) {}
    ~ProbeRef() {
        igObject *object = (igObject *)p;
        if (object != 0) {
            object->_refCount = object->_refCount - 1;
            if ((object->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(object);
            }
        }
    }
    igProbe *get() const { return p; }
};
static inline void setProbe(igPickMode *pickMode, const ProbeRef &probe) {
    igObject *retained = (igObject *)probe.get();
    igIntersectTraversal *traversal = (igIntersectTraversal *)pickMode->_intersectTraversal;
    igObject *previous;
    if (retained != 0) {
        retained->_refCount = retained->_refCount + 1;
    }
    previous = (igObject *)traversal->_probe;
    if (previous != 0) {
        previous->_refCount = previous->_refCount - 1;
        if ((previous->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(previous);
        }
    }
    traversal->_probe = (int)retained;
}
void FUN_004667d0(igPickMode *pickMode) {
    struct { int pad; char b; int w; } unprojected;
    igProbe *created;
    igIntList *faceTypes;
    int top;
    igIntersectTraversal *traversal;
    igObject *previous;
    igObject *cursor;
    FUN_00191f30(&unprojected.w, pickMode->_inverseProjectionMatrix, pickMode->_parameters + 0x2C);
    unprojected.b = 0;
    ProbeRef probe(FUN_0019e680(0));
    created = probe.get();
    ObjectList_AppendRetained(created->_rays, pickMode->_ray);
    faceTypes = (igIntList *)created->_intersectFaceType;
    top = count_of(faceTypes);
    if (top < faceTypes->_capacity) {
        faceTypes->_count = faceTypes->_count + 1;
    } else {
        List_Resize(faceTypes, top + 1, 4);
    }
    ((int *)faceTypes->_data)[top] = 2;
    setProbe(pickMode, probe);
    ((igIntersectTraversal *)pickMode->_intersectTraversal)->_mode = 0;
    ((igIntersectTraversal *)pickMode->_intersectTraversal)->_mode = ((igIntersectTraversal *)pickMode->_intersectTraversal)->_mode | 4;
    ((igIntersectTraversal *)pickMode->_intersectTraversal)->_hitProc = (int)&FUN_004665e0;
    ((igIntersectTraversal *)pickMode->_intersectTraversal)->_userTimeState = 1;
    if (pickMode->_guiSystem != 0) {
        cursor = (igObject *)((igGuiSystem *)pickMode->_guiSystem)->_mouseCursor;
        if (cursor != 0) {
            cursor->_refCount = cursor->_refCount + 1;
        }
        previous = (igObject *)pickMode->_savedCursor;
        if (previous != 0) {
            previous->_refCount = previous->_refCount - 1;
            if ((previous->_refCount & 0x7FFFFF) == 0) {
                igObject_Destroy(previous);
            }
        }
        pickMode->_savedCursor = (int)cursor;
        pickMode->_savedCursorState = ((igGuiSystem *)pickMode->_guiSystem)->_mouseCursorVisible;
        FUN_00456a60(pickMode->_guiSystem, pickMode->_cursor);
        FUN_004569c0(pickMode->_guiSystem, 1);
    }
}
}
