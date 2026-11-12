#include "dw4/reflected.h"

extern "C" int FUN_00389bc0(void *, void *);
extern "C" int FUN_00389b90(void *node, void *traversal);
extern "C" int igTraversal_RegisterFunction(int, int, void (*)(void));
extern "C" int FUN_0035cd40(...);
extern "C" void FUN_00389fb0(void);
extern "C" int sprintf(char *, const char *, ...);
extern "C" int FUN_002eb010(int);
extern "C" int StringPool_Construct(int);
extern "C" int StringPool_Intern(int, const char *);
extern "C" void StringChunk_ReleaseHeader(int, void *);
extern "C" int strcmp(const char *, const char *);
extern "C" int Memory_GetAllocatorBySelector(int);
extern "C" void FUN_00236be0(int, char *);
extern "C" void FUN_00236c40(int, char *);
extern "C" int FUN_00236f80(int, int);
extern "C" int igObject_Destroy(...);
extern "C" void Gap__Bec__beLua__vfunc_24(void);
extern "C" void Gap__Bec__beLua__vfunc_27(void);
extern "C" int Gap__Bec__beLua__vfunc_20(void);
extern "C" int igObject_IsKindOf(int, int);
extern "C" int ObjectList_AppendRetained(int, int);
extern "C" int DAT_00562640[4];
/* Resolves a script name through the interned-string pool (the given name, or "<stage>/lua" when none
 * is given), walks every beLuaInfo in the receiver's info list and every beLuaData in that info's data
 * list, and runs the first data object whose name equals `name` through the Lua state's buffer-run
 * virtual (slot 100). When nothing ran (-1), it builds "<interned>/<name>" and runs that path through
 * the file-run virtual (slot 96).
 * Matching constructs: the interned-name holder's inline destructor releases the string on every
 * exit; the `unsigned size` parameter fixes the lw a2/a1 load order. */


/* matching construct: 22 dummy virtuals put Run at vtable offset 96 and RunBuffer at 100 */
class LuaStateVt {
public:
    virtual void vfunc_00();
    virtual void vfunc_01();
    virtual void vfunc_02();
    virtual void vfunc_03();
    virtual void vfunc_04();
    virtual void vfunc_05();
    virtual void vfunc_06();
    virtual void vfunc_07();
    virtual void vfunc_08();
    virtual void vfunc_09();
    virtual void vfunc_10();
    virtual void vfunc_11();
    virtual void vfunc_12();
    virtual void vfunc_13();
    virtual void vfunc_14();
    virtual void vfunc_15();
    virtual void vfunc_16();
    virtual void vfunc_17();
    virtual void vfunc_18();
    virtual void vfunc_19();
    virtual void vfunc_20();
    virtual void vfunc_21();
    virtual int Run(char *path);
    virtual int RunBuffer(void *data, unsigned size, const char *name);
};
extern "C" int DAT_00586f20[4];
extern "C" char DAT_0050ec80[];
extern "C" char DAT_0050ec88[];
extern "C" char DAT_004e0858[];
/* stack holder for the interned name: the destructor drops one reference to the pooled string and frees its chunk at zero */
class LuaStrRef {
public:
    char *value;
    LuaStrRef() : value(0) {}
    ~LuaStrRef() { char *o = value; if (o) { int *hd = (int *)o - 2; int r = *(int *)(o - 4) - 1; *(int *)(o - 4) = r; if (r == 0) StringChunk_ReleaseHeader(*hd, hd); } }
};
extern "C" int beLua__RunNamedChunk(beLua *self, const char *name, const char *given);
extern "C" igObject *FUN_0035aa20(int);
extern "C" int igObject_GetAllocator(beLua *);
extern "C" int DAT_00587110[4];
extern "C" unsigned char GPR_00554c14;
extern "C" void FUN_0038a2d0(beLua *arg0);
extern "C" void Gap__Bec__beLua__vfunc_21(beLua *self, int unusedArg);
extern "C" void Gap__Bec__beLua__vfunc_22(beLua *self, int unusedArg);
/* reference-counted engine object header: refcount word at +4 */
typedef struct RefCountedHeader { char pad4[4]; int f4; } RefCountedHeader;
extern "C" int DAT_00587d08[4];
extern "C" void Gap__Bec__beLua__vfunc_23(beLua *arg0);
extern "C" int g_beLua_metaObject[4];
extern "C" int DAT_005891c0[4];
extern "C" int Gap__Bec__beLua__vfunc_25(beLua *arg0, int arg1);
/* Reference count at +4 of an igObject. */
typedef struct RefCountedObject { char pad[4]; int f4; } RefCountedObject;
extern "C" void Gap__Bec__beLua__vfunc_26(beLua *arg0);

int FUN_00389b90(void *node, void *traversal) {
    return FUN_00389bc0(traversal, node);
}

void FUN_00389fb0(void) {
    igTraversal_RegisterFunction(DAT_00562640[0], FUN_0035cd40(), (void (*)())FUN_00389b90);
}

int beLua__RunNamedChunk(beLua *self, const char *name, const char *given)
{
    LuaStrRef ref;
    char buf1[256];
    char buf2[256];
    int result = -1;
    int count;
    int i;
    char *s;
    int a;
    char *old;

    if (given == 0) {
        sprintf(buf1, DAT_0050ec80, (char *)((beSystem *)self->_system)->_stageName);
        if (DAT_00586f20[0] == 0) {
            a = FUN_002eb010(16);
            if (a) a = StringPool_Construct(a);
            DAT_00586f20[0] = a;
        }
        s = (char *)StringPool_Intern(DAT_00586f20[0], buf1);
        old = ref.value;
        if (old) {
            int *hd = (int *)old - 2;
            int r = *(int *)(old - 4) - 1;
            *(int *)(old - 4) = r;
            if (r == 0) StringChunk_ReleaseHeader(*hd, hd);
        }
        ref.value = s;
    } else {
        if (DAT_00586f20[0] == 0) {
            a = FUN_002eb010(16);
            if (a) a = StringPool_Construct(a);
            DAT_00586f20[0] = a;
        }
        s = (char *)StringPool_Intern(DAT_00586f20[0], given);
        old = ref.value;
        if (old) {
            int *hd = (int *)old - 2;
            int r = *(int *)(old - 4) - 1;
            *(int *)(old - 4) = r;
            if (r == 0) StringChunk_ReleaseHeader(*hd, hd);
        }
        ref.value = s;
    }

    count = ((beLuaDataList *)self->_infoList)->_count;
    for (i = 0; i < count; i++) {
        beLuaInfo *info = ((beLuaInfo **)((beLuaDataList *)self->_infoList)->_data)[i];
        int n = ((beLuaDataList *)info->_dataList_)->_count;
        int j;
        for (j = 0; j < n; j++) {
            beLuaData *d = ((beLuaData **)((beLuaDataList *)info->_dataList_)->_data)[j];
            const char *nm = d->_name ? (const char *)d->_name : DAT_004e0858;
            if (nm != 0 && strcmp(d->_name ? (const char *)d->_name : DAT_004e0858, name) == 0) {
                beLuaDataObject *o = (beLuaDataObject *)d->_dataObject;
                result = ((LuaStateVt *)self->_luaState)->RunBuffer((void *)o->_data, o->_dataSize, name);
                break;
            }
        }
    }
    if (result == -1) {
        sprintf(buf2, DAT_0050ec88, ref.value, name);
        result = ((LuaStateVt *)self->_luaState)->Run(buf2);
    }
    return result;
}

void FUN_0038a2d0(beLua *arg0) {
    int var_v0;
    int alloc;
    igObject *temp_a0;

    alloc = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        var_v0 = alloc;
    } else {
        var_v0 = Memory_GetAllocatorBySelector(DAT_00587110[0]);
    }
    temp_a0 = (igObject *)arg0->_luaState;
    if (temp_a0 != 0) {
        --temp_a0->_refCount;
        if (((unsigned long long)(long long)temp_a0->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->_luaState = (int)FUN_0035aa20(var_v0);
}

/* Hands the object to the insight core's helper FUN_00236be0, which asks the scheduler at +12 of
 * the insight object (_insight) whether it already has the object (scheduler slot 26) and, if not,
 * calls scheduler slot 24 with it. Same body as beMessenger slot 21. The second argument is
 * unused. */
void Gap__Bec__beLua__vfunc_21(beLua *self, int unusedArg)
{
    FUN_00236be0(self->_insight, (char *)self);
}

/* Counterpart of slot 21 through FUN_00236c40, which calls scheduler slot 25 with the object only
 * when scheduler slot 26 reports it present. Same body as beMessenger slot 22. The second argument
 * is unused. */
void Gap__Bec__beLua__vfunc_22(beLua *self, int unusedArg)
{
    FUN_00236c40(self->_insight, (char *)self);
}

void Gap__Bec__beLua__vfunc_23(beLua *arg0) {
    RefCountedHeader *temp_a0;
    arg0->_system = FUN_00236f80(arg0->_insight, DAT_00587d08[0]);
    temp_a0 = (RefCountedHeader *)(arg0->_luaState);
    if (temp_a0 != 0) {
        temp_a0->f4 = (int)((int) (temp_a0->f4 - 1));
        if (((unsigned long long) ((long long) temp_a0->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->_luaState = 0;
}

void Gap__Bec__beLua__vfunc_24(void)
{
}

int Gap__Bec__beLua__vfunc_25(beLua *arg0, int arg1) {
    if (igObject_IsKindOf(arg1, DAT_005891c0[0]) != 0) {
        ObjectList_AppendRetained(arg0->_infoList, arg1);
        return 1;
    }
    return 0;
}

void Gap__Bec__beLua__vfunc_26(beLua *arg0) {
    igInfoList *temp_s3;
    int temp_s2;
    int i;
    int n;
    RefCountedObject *t;
    temp_s3 = (igInfoList *)arg0->_infoList;
    temp_s2 = temp_s3->_count;
    for (i = 0; i < temp_s2; i++) {
        t = ((RefCountedObject **)temp_s3->_data)[i];
        if (t != 0) {
            t->f4 = t->f4 - 1;
            if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(t);
            }
        }
    }
    n = temp_s3->_count;
    for (i = 0; i < n; i++) {
        ((int *)temp_s3->_data)[i] = 0;
    }
    temp_s3->_count = 0;
    t = (RefCountedObject *)arg0->_luaState;
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long) ((long long) t->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->_luaState = 0;
}

void Gap__Bec__beLua__vfunc_27(void)
{
}

int Gap__Bec__beLua__vfunc_20(void)
{
    return g_beLua_metaObject[0];
}

