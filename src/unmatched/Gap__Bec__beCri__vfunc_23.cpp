#include "dw4/reflected.h"
extern "C" {
struct RefCountedNamedObject { int w0; int rc; int w8; int f12; }; /* igNamedObject-style header; +12 is the word passed to FUN_003a6950 */
int FUN_00236f80(int, int);
struct RefCountedNamedObject *FUN_00366910(int);
int FUN_0037d310(beCri *);
int FUN_003a6950(int, int);
int Memory_GetAllocatorBySelector(int);
int igNamedObject_SetName(int, int);
int igObject_Destroy(RefCountedNamedObject *);
int igObject_GetAllocator(beCri *);
extern int DAT_00587108[4];
extern int DAT_00587d08[4];
extern int DAT_0058a360[4];
extern int DAT_0058a460[4];
extern unsigned char GPR_00554c14;
void Gap__Bec__beCri__vfunc_23(beCri *arg0);
}

void Gap__Bec__beCri__vfunc_23(beCri *arg0) {
    int var_v0;
    int var_v0_2;
    struct RefCountedNamedObject *t;
    int i;
    int *a1;
    int *a0;

    arg0->_system = FUN_00236f80(arg0->_insight, DAT_00587d08[0]);
    var_v0 = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        var_v0 = (int)var_v0;
    } else {
        var_v0 = Memory_GetAllocatorBySelector(DAT_00587108[0]);
    }
    t = (struct RefCountedNamedObject *)arg0->_hdBGM;
    if (t != 0) {
        t->rc = t->rc - 1;
        if ((t->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->_hdBGM = (int)FUN_00366910(var_v0);
    FUN_003a6950(((struct RefCountedNamedObject *)arg0->_hdBGM)->f12, 2);
    igNamedObject_SetName(arg0->_hdBGM, 0);
    var_v0_2 = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        var_v0_2 = (int)var_v0_2;
    } else {
        var_v0_2 = Memory_GetAllocatorBySelector(DAT_00587108[0]);
    }
    t = (struct RefCountedNamedObject *)arg0->_hdENV;
    if (t != 0) {
        t->rc = t->rc - 1;
        if ((t->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->_hdENV = (int)FUN_00366910(var_v0_2);
    FUN_003a6950(((struct RefCountedNamedObject *)arg0->_hdENV)->f12, 2);
    igNamedObject_SetName(arg0->_hdENV, 0);
    FUN_0037d310(arg0);
    arg0->_pauseOnetime = 0;
    for (i = 0; i < 32; i++) {
        DAT_0058a360[i] = 0;
        DAT_0058a360[i + 32] = 0;
        DAT_0058a460[i] = 0;
    }
}
