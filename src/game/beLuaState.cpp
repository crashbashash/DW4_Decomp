#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"

extern "C" int Memory_FreeBufferWithAllocator(...);
extern "C" int Memory_GetAllocatorBySelector(...);
extern "C" int igObject_GetAllocator(...);
extern "C" void igLuaState_RunString(void);
extern "C" int igLuaState_RunBuffer(...);
extern "C" void Gap__Bec__beLuaState__vfunc_21(void);
extern "C" void Gap__Bec__beLuaState__vfunc_23(void);
extern "C" int Memory_AllocateAlignedWithAllocator(int, int, int);
extern "C" int Gap__Bec__beLuaState__vfunc_20(void);
extern "C" int igLuaState_Close(beLuaState *);
extern "C" int g_defaultAllocatorSelector[4];
extern "C" unsigned char GPR_00554c14;
extern "C" void Gap__Bec__beLuaState__vfunc_08(beLuaState *arg0);
extern "C" igObject *FUN_00362f90(int);
extern "C" int FUN_0037f1b0(igObject *, int);
extern "C" igObject *FUN_00334dc0(int);
extern "C" int igAdxFile_GetFileSize(igObject *);
extern "C" int igAdxFile_SetUseBuffer(igObject *, int);
extern "C" int igAdxFile_SetUseAsync(igObject *, int);
extern "C" int igAdxFile_WaitForReadEnd(igObject *);
extern "C" int DAT_0050ecc8[4];
/* matching construct: dummy-virtual receiver for the reader's vtable calls */
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int v23(int, int *); virtual void v24(); virtual void v25(int, int, int); };
/* Owning stack reference to the script locator; released on scope exit (reference count in the low
 * 23 bits of _refCount). */

/* Owning stack reference to the script reader; released on scope exit. */
class ReaderRef {
public:
    igObject *p;
    ReaderRef(igObject *o) : p(o) {}
    ~ReaderRef() { igObject *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
extern "C" int Gap__Bec__beLuaState__vfunc_22(beLuaState *arg0, int arg1);
extern "C" int g_beLuaState_metaObject[4];

void Gap__Bec__beLuaState__vfunc_08(beLuaState *arg0) {
    int var_v0;

    if (arg0->_lp != 0) {
        var_v0 = igObject_GetAllocator(arg0);
        var_v0 = (GPR_00554c14 != 0) ? var_v0 : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        Memory_FreeBufferWithAllocator(arg0->_lp, var_v0);
    }
    igLuaState_Close(arg0);
}

void Gap__Bec__beLuaState__vfunc_21(void)
{
    igLuaState_RunString();
}

int Gap__Bec__beLuaState__vfunc_22(beLuaState *arg0, int arg1) {
    int var_v0;
    int s0;
    char *a1;
    int a2;
    bool found;
    var_v0 = igObject_GetAllocator();
    var_v0 = (GPR_00554c14 != 0) ? var_v0 : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
    igSmartPointer<igObject> locator(FUN_00362f90(var_v0));
    if (FUN_0037f1b0(locator.p, arg1) == 0) {
        return 2;
    }
    var_v0 = igObject_GetAllocator(arg0);
    var_v0 = (GPR_00554c14 != 0) ? var_v0 : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
    ReaderRef reader(FUN_00334dc0(var_v0));
    if (((V *)reader.p)->v23(arg1, DAT_0050ecc8) == 0) {
        return -1;
    }
    s0 = igAdxFile_GetFileSize(reader.p);
    if (arg0->_lp != 0) {
        var_v0 = igObject_GetAllocator(arg0);
        var_v0 = (GPR_00554c14 != 0) ? var_v0 : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
        Memory_FreeBufferWithAllocator(arg0->_lp, var_v0);
    }
    var_v0 = igObject_GetAllocator(arg0);
    var_v0 = (GPR_00554c14 != 0) ? var_v0 : Memory_GetAllocatorBySelector(g_defaultAllocatorSelector[0]);
    arg0->_lp = (int)Memory_AllocateAlignedWithAllocator(s0, 0x40, var_v0);
    if (arg0->_lp == 0) {
        ((V *)reader.p)->v24();
        return -1;
    }
    igAdxFile_SetUseBuffer(reader.p, 0);
    igAdxFile_SetUseAsync(reader.p, 0);
    ((V *)reader.p)->v25(arg0->_lp, 1, s0);
    igAdxFile_WaitForReadEnd(reader.p);
    igAdxFile_SetUseBuffer(reader.p, 1);
    igAdxFile_SetUseAsync(reader.p, 1);
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

void Gap__Bec__beLuaState__vfunc_23(void)
{
    igLuaState_RunBuffer();
}

int Gap__Bec__beLuaState__vfunc_20(void)
{
    return g_beLuaState_metaObject[0];
}

