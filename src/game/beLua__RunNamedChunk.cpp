/* beLua__RunNamedChunk 0x00389ff0, 732 bytes: beLua script lookup-and-run.
 *
 * Resolves a script name through the interned-string pool (the given name, or "<stage>/lua"
 * when none is given), walks every beLuaInfo in the receiver's info list and every beLuaData
 * in that info's data list, and runs the first data object whose name equals `name` through
 * the Lua state's buffer-run virtual (slot 100).  When nothing ran (-1), it builds
 * "<interned>/<name>" and runs that path through the Lua state's file-run virtual (slot 96).
 * Receiver fields come from the reflected beLua / beLuaInfo / beLuaData / beLuaDataObject.
 *
 * Build profile: alternate combat compiler, -O3,p -Cpp_exceptions off -Iinclude, with
 * unit-objects duplicate __dt__9LuaStrRefFv = 0x00130720 (the shared string-reference destructor
 * retail keeps once) and external __dl__FPv = 0x00100610.
 * Matching constructs: the interned-name holder's inline destructor releases the string on every
 * exit, as retail's one protected range does; the `unsigned size` parameter fixes the lw a2/a1 load
 * order. */
#include "dw4/reflected.h"

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

extern "C" {
int sprintf(char *, const char *, ...);
int FUN_002eb010(int);
int StringPool_Construct(int);
int StringPool_Intern(int, const char *);
void StringChunk_ReleaseHeader(int, void *);
int igStrCmp(const char *, const char *);
extern int DAT_00586f20[4];
extern char DAT_0050ec80[], DAT_0050ec88[], DAT_004e0858[];
}

/* stack holder for the interned name: the destructor drops one reference to the pooled string and frees its chunk at zero */
class LuaStrRef {
public:
    char *value;
    LuaStrRef() : value(0) {}
    ~LuaStrRef() { char *o = value; if (o) { int *hd = (int *)o - 2; int r = *(int *)(o - 4) - 1; *(int *)(o - 4) = r; if (r == 0) StringChunk_ReleaseHeader(*hd, hd); } }
};

extern "C"
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
            if (nm != 0 && igStrCmp(d->_name ? (const char *)d->_name : DAT_004e0858, name) == 0) {
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
