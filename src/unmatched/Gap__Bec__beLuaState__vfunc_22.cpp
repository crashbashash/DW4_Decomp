/* Load a Lua script file into the state's buffer and run it. Resolves the script name through a
 * locator object (FUN_00362f90 / FUN_0037f1b0; 2 = not found), opens it through a reader object
 * (FUN_00334dc0; v23 = open, v25 = read, v24 = close), reads the whole file into a fresh _lp
 * buffer, replaces the "[EOF]" marker's bracket by '0' to terminate the chunk and runs the text
 * with igLuaState_RunBuffer; -1 on any failure. Both helper objects live on the stack in owning
 * references whose releases the retail exception table records. */
#include "dw4/reflected.h"
extern "C" {
void igObject_Destroy(igObject *);
int igObject_GetAllocator(...);
int Memory_GetAllocatorBySelector(...);
int Memory_FreeBufferWithAllocator(...);
igObject *FUN_00362f90(int);
int FUN_0037f1b0(igObject *, int);
igObject *FUN_00334dc0(int);
int FUN_00334370(igObject *);
int FUN_002ed2b0(int, int, int);
int FUN_00333a40(igObject *, int);
int FUN_00333a50(igObject *, int);
int FUN_00333990(igObject *);
int igLuaState_RunBuffer(...);
extern int DAT_0050ecc8[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
/* matching construct: dummy-virtual receiver for the reader's vtable calls */
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int v23(int, int *); virtual void v24(); virtual void v25(int, int, int); };
/* Owning stack reference to the script locator (FUN_00362f90): released on scope exit (reference count
 * in the low 23 bits of _refCount).  The out-of-line copy the exception table names is the retail body
 * 0x0038abf0 (config/SLUS-20836/unit-objects.json, duplicate __dt__9ObjectRefFv). */
class ObjectRef {
public:
    igObject *p;
    ObjectRef(igObject *o) : p(o) {}
    ~ObjectRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to the script reader (FUN_00334dc0; hypothesis: a file stream, see the open /
 * read / close vtable calls): released on scope exit.  The out-of-line copy the exception table names is
 * the retail body 0x0038ab70 (config/SLUS-20836/unit-objects.json, duplicate __dt__9ReaderRefFv). */
class ReaderRef {
public:
    igObject *p;
    ReaderRef(igObject *o) : p(o) {}
    ~ReaderRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" int Gap__Bec__beLuaState__vfunc_22(beLuaState *arg0, int arg1);
int Gap__Bec__beLuaState__vfunc_22(beLuaState *arg0, int arg1) {
    int var_v0;
    int s0;
    char *a1;
    int a2;
    bool found;
    var_v0 = igObject_GetAllocator();
    var_v0 = (GPR_00554c14 != 0) ? var_v0 : Memory_GetAllocatorBySelector(DAT_00587110[0]);
    ObjectRef locator(FUN_00362f90(var_v0));
    if (FUN_0037f1b0(locator.p, arg1) == 0) {
        return 2;
    }
    var_v0 = igObject_GetAllocator(arg0);
    var_v0 = (GPR_00554c14 != 0) ? var_v0 : Memory_GetAllocatorBySelector(DAT_00587110[0]);
    ReaderRef reader(FUN_00334dc0(var_v0));
    if (((V *)reader.p)->v23(arg1, DAT_0050ecc8) == 0) {
        return -1;
    }
    s0 = FUN_00334370(reader.p);
    if (arg0->_lp != 0) {
        var_v0 = igObject_GetAllocator(arg0);
        var_v0 = (GPR_00554c14 != 0) ? var_v0 : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        Memory_FreeBufferWithAllocator(arg0->_lp, var_v0);
    }
    var_v0 = igObject_GetAllocator(arg0);
    var_v0 = (GPR_00554c14 != 0) ? var_v0 : Memory_GetAllocatorBySelector(DAT_00587110[0]);
    arg0->_lp = (int)FUN_002ed2b0(s0, 0x40, var_v0);
    if (arg0->_lp == 0) {
        ((V *)reader.p)->v24();
        return -1;
    }
    FUN_00333a40(reader.p, 0);
    FUN_00333a50(reader.p, 0);
    ((V *)reader.p)->v25(arg0->_lp, 1, s0);
    FUN_00333990(reader.p);
    FUN_00333a40(reader.p, 1);
    FUN_00333a50(reader.p, 1);
    ((V *)reader.p)->v24();
    a1 = (char *)arg0->_lp;
    found = false;
    a2 = 0;
    for (; a2 < s0; a2++) {
        char *p = a1 + a2;
        if (p[0] == 0x5B && p[1] == 0x45 && p[2] == 0x4F && p[3] == 0x46 && p[4] == 0x5D) {
            found = true;
            p[0] = 0x30;
            break;
        }
    }
    if (!found) {
        return -1;
    }
    s0 = igLuaState_RunBuffer(arg0, a1, a2, arg1);
    return s0;
}
