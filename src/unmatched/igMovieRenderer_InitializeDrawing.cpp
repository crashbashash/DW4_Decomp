/* 0x0033bd30 igMovieRenderer_InitializeDrawing: on first use (no movie manager yet, flag byte 0x554e4c clear) probe
 * the platform with FUN_00308320 and latch the flag when it answers 2, then hand the renderer's visual context to
 * the movie manager (FUN_00339110) through a counted reference that this call releases afterwards.  C++ unit: retail
 * keeps the exception record for that reference (one range at the FUN_00339110 call, destroy at sp+44 with the
 * out-of-line copy 0x00130140 = config/SLUS-20836/unit-objects.json duplicate __dt__9ObjectRefFv). */
#include "dw4/reflected.h"
extern "C" {
int FUN_00308320(int *);
int igObject_Destroy(igObject *);
extern int DAT_005012f0[4];
extern unsigned char GPR_00554e4c;
void igMovieRenderer_InitializeDrawing(igMovieRenderer *arg0);
}
/* Counted reference to an igObject: takes a reference on construction and drops it on scope exit
 * (reference count in the low 23 bits of _refCount). */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) { if (p != 0) p->_refCount = p->_refCount + 1; }
#if __MWERKS__ >= 0x3000
    /* matching construct: this unit's inline release re-reads p after the decrement */
    ~ObjectRef() { if (p != 0) { p->_refCount = p->_refCount - 1; if ((p->_refCount & 0x7FFFFF) == 0) igObject_Destroy(p); } }
#else
    ~ObjectRef() { igObject *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7FFFFF) == 0) igObject_Destroy(o); } }
#endif
};
extern "C" int FUN_00339110(int, ObjectRef *);
void igMovieRenderer_InitializeDrawing(igMovieRenderer *arg0) {
    int temp_v0;

    if ((arg0->_movieManager == 0) && (GPR_00554e4c == 0)) {
        temp_v0 = FUN_00308320(&DAT_005012f0[0]);
        if ((temp_v0 != 1) && (temp_v0 == 2)) {
            GPR_00554e4c = 1;
        }
    }
    ObjectRef context((igObject *)arg0->_visualContext);
    FUN_00339110(arg0->_movieManager, &context);
}
