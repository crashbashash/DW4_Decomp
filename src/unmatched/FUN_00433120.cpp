#include "dw4/reflected.h"
extern "C" {
int igObject_IsKindOf(beNDMWWindow *, int);
void *FUN_003b3ac0(int);
int FUN_00425fb0(beNDMWWindow *);
int Memory_GetAllocatorBySelector(int);
int ObjectList_AppendRetained(int, igObject *);
int beNDMWWindow_BindContext(beNDMWWindow *, beNDMWWindow *, int, int, int);
int igObject_Destroy(igObject *);
int igObject_GetAllocator(beNDMWWindow *);
extern int DAT_00587110[4];
extern int DAT_0058ab68[4];
extern unsigned char GPR_00554c14;
void FUN_00433120(beNDMWWindow *arg0, int arg1);
}
/* Owning stack reference to the new sub-window, released on scope exit (reference count in the low
 * 23 bits of _refCount). */
class ObjectRef {
public:
    beNDMWWindow *p;
    ObjectRef(beNDMWWindow *o) : p(o) {}
    ~ObjectRef() { beNDMWWindow *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy((igObject *)o); } }
};
void FUN_00433120(beNDMWWindow *arg0, int arg1) {
    beNDMWWindow *var_s2;
    int var_s1;
    int var_s0;
    int var_v0;
    int w;
    beNDMWWindow *e;

    var_s2 = 0;
    var_s1 = 0;
    if (0 < ((igObjectList *)*(volatile int *)&arg0->_subWindow)->_count) {
        var_s0 = 0;
        do {
            e = (beNDMWWindow *)((int *)((igObjectList *)*(volatile int *)&arg0->_subWindow)->_data)[var_s1];
            if ((e != 0) && (igObject_IsKindOf(e, DAT_0058ab68[0]) != 0)) {
                var_s2 = e;
            } else {
                var_s2 = 0;
            }
            if (var_s2 != 0) break;
            var_s1 += 1;
            var_s0 += 4;
        } while (var_s1 < ((igObjectList *)*(volatile int *)&arg0->_subWindow)->_count);
    }
    if (var_s2 == 0) {
        var_v0 = igObject_GetAllocator(arg0);
        if (GPR_00554c14 != 0) {
            w = var_v0;
        } else {
            w = Memory_GetAllocatorBySelector(DAT_00587110[0]);
        }
        /* The new window is owned by the stack reference until the sub-window list has taken its own. */
        ObjectRef created((beNDMWWindow *)FUN_003b3ac0(w));
        beNDMWWindow_BindContext(created.p, arg0, arg0->_insight, arg1, 1);
        ObjectList_AppendRetained(*(volatile int *)&arg0->_subWindow, (igObject *)created.p);
    } else {
        var_s2->_playerNo = arg1;
        FUN_00425fb0(var_s2);
    }
}
