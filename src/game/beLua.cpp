#include "dw4/reflected.h"

extern "C" int beLOA_Traverse(beLOA *node, igCommonTraversal *traversal);
extern "C" int beLOA_TraversalFunction(igCommonTraversal *traversal, beLOA *node);
extern "C" int igTraversal_RegisterFunction(int, int, void (*)(void));
extern "C" int FUN_0035cd40(...);
extern "C" void FUN_00389fb0(void);
extern "C" int sprintf(char *, const char *, ...);
extern "C" int StringPool_Allocate(int);
extern "C" int StringPool_Construct(int);
extern "C" int StringPool_Intern(int, const char *);
extern "C" void StringChunk_ReleaseHeader(int, void *);
extern "C" int strcmp(const char *, const char *);
extern "C" int Memory_GetAllocatorBySelector(int);
extern "C" void igInsightCore_AddToScheduler(int, char *);
extern "C" void igInsightCore_RemoveFromScheduler(int, char *);
extern "C" int igInsightCore_FindManager(int, int);
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
extern "C" int g_stringPool[4];
extern "C" char text_s_lua[];
extern "C" char DAT_0050ec88[];
extern "C" char emptyString[];
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
extern "C" int kIGMemoryPoolHandleUser1[4];
extern "C" unsigned char g_useOwnerAllocator;
extern "C" void FUN_0038a2d0(beLua *arg0);
extern "C" void Gap__Bec__beLua__vfunc_21(beLua *self, int unusedArg);
extern "C" void Gap__Bec__beLua__vfunc_22(beLua *self, int unusedArg);
/* reference-counted engine object header: refcount word at +4 */
typedef struct RefCountedHeader { char pad4[4]; int f4; } RefCountedHeader;
extern "C" int g_beSystem_metaObject[4];
extern "C" void Gap__Bec__beLua__vfunc_23(beLua *arg0);
extern "C" int g_beLua_metaObject[4];
extern "C" int g_beLuaInfo_metaObject[4];
extern "C" int Gap__Bec__beLua__vfunc_25(beLua *arg0, int arg1);
/* Reference count at +4 of an igObject. */
typedef struct RefCountedObject { char pad[4]; int f4; } RefCountedObject;
extern "C" void Gap__Bec__beLua__vfunc_26(beLua *arg0);

int beLOA_TraversalFunction(igCommonTraversal *traversal, beLOA *node) {
    return beLOA_Traverse(node, traversal);
}

extern "C" void igMatrix44f_GetTranslation(const float *matrix, float *vector);
extern "C" void List_RemoveWordAt(igObjectList *list, int index);
extern "C" void igAttrStackManager_PushOverrideAttr(igAttrStackManager *attrs, igAttr *attr);
extern "C" void igAttrStackManager_PopOverrideAttr(igAttrStackManager *attrs, igAttr *attr);
extern "C" int igTraversal_TraverseChildren(igCommonTraversal *traversal, beLOA *node);
extern "C" igMetaObject *g_igModelViewMatrixAttr_metaObject[4];
/* the colour attribute's value setter is virtual slot 30 (vtable offset 128) */
class OverrideAttr {
public:
    virtual void vfunc_00(); virtual void vfunc_01(); virtual void vfunc_02(); virtual void vfunc_03();
    virtual void vfunc_04(); virtual void vfunc_05(); virtual void vfunc_06(); virtual void vfunc_07();
    virtual void vfunc_08(); virtual void vfunc_09(); virtual void vfunc_10(); virtual void vfunc_11();
    virtual void vfunc_12(); virtual void vfunc_13(); virtual void vfunc_14(); virtual void vfunc_15();
    virtual void vfunc_16(); virtual void vfunc_17(); virtual void vfunc_18(); virtual void vfunc_19();
    virtual void vfunc_20(); virtual void vfunc_21(); virtual void vfunc_22(); virtual void vfunc_23();
    virtual void vfunc_24(); virtual void vfunc_25(); virtual void vfunc_26(); virtual void vfunc_27();
    virtual void vfunc_28(); virtual void vfunc_29();
    virtual void SetValue(void *value);
};

/* matching construct: these read the reference field through a typed pointer; the compiler does
 * not merge such a load with the field's plain int reads, which keeps retail's separate reloads */
static inline igAttrStackManager *AttrManagerOf(igCommonTraversal *traversal) { return *(igAttrStackManager **)&traversal->_attrStack; }
static inline igObjectList *OverrideAttrsOf(beLOA *node) { return *(igObjectList **)&node->_overrideAttrList; }

/* the attribute currently in effect for a type: the cached override, else the top of its stack, else the default */
static inline igAttr *CurrentAttr(igCommonTraversal *traversal, igMetaObject *meta)
{
    igAttrStackManager *manager = AttrManagerOf(traversal);
    igAttrStack *stack = ((igAttrStack **)((igObjectList *)manager->_attrStacks)->_data)
        [((int *)manager->_attrStackIndexTable)[meta->_id]];
    int top = stack->_cachedOverride;
    if (top >= 0) {
        return ((igAttr **)stack->_data)[top];
    }
    top = stack->_count;
    if (top != 0) {
        int last = top - 1;
        return ((igAttr **)stack->_data)[last];
    }
    return (igAttr *)stack->_default;
}

/* beLOA fades its subtree by camera distance. Status 0 (opaque) / 2 (faded): the model-view
 * translation's squared length against _range starts a fade out (1) / in (3). Fading moves the
 * alpha _color[3] by _addAlpha per 1/60 s of traversal time towards _maxAlpha (out) or 1 (in).
 * At alpha 1 the override attributes are dropped; otherwise the blend state, blend function and
 * colour attributes are pushed around the children with the colour set to _color. */
int beLOA_Traverse(beLOA *node, igCommonTraversal *traversal)
{
    igAttrStackManager *attrs;
    long long now;
    igModelViewMatrixAttr *modelView;
    float position[3];
    float *alpha;
    float frames;
    igObjectList *list;
    igObject *attr;
    int i;
    int result;
    int j;

    attrs = (igAttrStackManager *)traversal->_attrStack;
    now = *(long long *)((igLongList *)traversal->_timeStack)->_data;
    switch (node->_status) {
    case 0:
    case 2:
        modelView = (igModelViewMatrixAttr *)CurrentAttr(traversal, g_igModelViewMatrixAttr_metaObject[0]);
        igMatrix44f_GetTranslation(modelView->_m, position);
        if (position[0] * position[0] + position[1] * position[1] + position[2] * position[2] < node->_range) {
            if (node->_status == 0) {
                node->_status = 1;
            }
        } else if (node->_status == 2) {
            node->_status = 3;
        }
        break;
    case 1:
        if (node->_color[3] > node->_maxAlpha) {
            alpha = &node->_color[3];
            frames = (float)(now - node->_oldTime) / 16666667.0f;
            *alpha -= frames * node->_addAlpha;
            if (*alpha < node->_maxAlpha) {
                *alpha = node->_maxAlpha;
                node->_status = 2;
            }
        }
        break;
    case 3:
        alpha = &node->_color[3];
        if (*alpha < 1.0f) {
            frames = (float)(now - node->_oldTime) / 16666667.0f;
            if ((*alpha += frames * node->_addAlpha) > 1.0f) {
                *alpha = 1.0f;
                node->_status = 0;
            }
        }
        break;
    }
    if (node->_color[3] == 1.0f) {
        while (((igObjectList *)node->_overrideAttrList)->_count != 0) {
            list = OverrideAttrsOf(node);
            attr = ((igObject **)list->_data)[0];
            if (attr != 0) {
                attr->_refCount = attr->_refCount - 1;
                if ((attr->_refCount & 0x7FFFFF) == 0) {
                    igObject_Destroy(attr);
                }
            }
            List_RemoveWordAt(list, 0);
            ((igObject **)list->_data)[list->_count] = 0;
        }
    } else {
        list = (igObjectList *)node->_overrideAttrList;
        if (list->_count == 0) {
            ObjectList_AppendRetained((int)list, node->_blendStateAttr);
            ObjectList_AppendRetained(node->_overrideAttrList, node->_blendFunctionAttr);
            ObjectList_AppendRetained(node->_overrideAttrList, node->_colorAttr);
        }
        ((OverrideAttr *)node->_colorAttr)->SetValue(node->_color);
    }
    node->_oldTime = now;
    for (i = 0; i < ((igObjectList *)node->_overrideAttrList)->_count; i++) {
        igAttrStackManager_PushOverrideAttr(attrs, ((igAttr **)OverrideAttrsOf(node)->_data)[i]);
    }
    result = igTraversal_TraverseChildren(traversal, node);
    for (j = ((igObjectList *)node->_overrideAttrList)->_count - 1; j >= 0; j--) {
        igAttrStackManager_PopOverrideAttr(attrs, ((igAttr **)OverrideAttrsOf(node)->_data)[j]);
    }
    if (result == 2) {
        return 2;
    }
    return 0;
}

void FUN_00389fb0(void) {
    igTraversal_RegisterFunction(DAT_00562640[0], FUN_0035cd40(), (void (*)())beLOA_TraversalFunction);
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
        sprintf(buf1, text_s_lua, (char *)((beSystem *)self->_system)->_stageName);
        if (g_stringPool[0] == 0) {
            a = StringPool_Allocate(16);
            if (a) a = StringPool_Construct(a);
            g_stringPool[0] = a;
        }
        s = (char *)StringPool_Intern(g_stringPool[0], buf1);
        old = ref.value;
        if (old) {
            int *hd = (int *)old - 2;
            int r = *(int *)(old - 4) - 1;
            *(int *)(old - 4) = r;
            if (r == 0) StringChunk_ReleaseHeader(*hd, hd);
        }
        ref.value = s;
    } else {
        if (g_stringPool[0] == 0) {
            a = StringPool_Allocate(16);
            if (a) a = StringPool_Construct(a);
            g_stringPool[0] = a;
        }
        s = (char *)StringPool_Intern(g_stringPool[0], given);
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
            const char *nm = d->_name ? (const char *)d->_name : emptyString;
            if (nm != 0 && strcmp(d->_name ? (const char *)d->_name : emptyString, name) == 0) {
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
    if (g_useOwnerAllocator != 0) {
        var_v0 = alloc;
    } else {
        var_v0 = Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1[0]);
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

/* Hands the object to the insight core's helper igInsightCore_AddToScheduler, which asks the scheduler at +12 of
 * the insight object (_insight) whether it already has the object (scheduler slot 26) and, if not,
 * calls scheduler slot 24 with it. Same body as beMessenger slot 21. The second argument is
 * unused. */
void Gap__Bec__beLua__vfunc_21(beLua *self, int unusedArg)
{
    igInsightCore_AddToScheduler(self->_insight, (char *)self);
}

/* Counterpart of slot 21 through igInsightCore_RemoveFromScheduler, which calls scheduler slot 25 with the object only
 * when scheduler slot 26 reports it present. Same body as beMessenger slot 22. The second argument
 * is unused. */
void Gap__Bec__beLua__vfunc_22(beLua *self, int unusedArg)
{
    igInsightCore_RemoveFromScheduler(self->_insight, (char *)self);
}

void Gap__Bec__beLua__vfunc_23(beLua *arg0) {
    RefCountedHeader *temp_a0;
    arg0->_system = igInsightCore_FindManager(arg0->_insight, g_beSystem_metaObject[0]);
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
    if (igObject_IsKindOf(arg1, g_beLuaInfo_metaObject[0]) != 0) {
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

