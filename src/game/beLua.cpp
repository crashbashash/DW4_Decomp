#include "dw4/reflected.h"
#include "dw4/igobject_release.h"
#include "dw4/igObjectDispatchView.h"
#include "dw4/beLOA.h"
#include "dw4/beLua.h"
#include "dw4/StringPool.h"
#include "dw4/beLuaInfo.h"
#include "dw4/beLuaState.h"
#include "dw4/beSystem.h"
#include "dw4/igAttrStackManager.h"
#include "dw4/igDataLists.h"
#include "dw4/igInsightCore.h"
#include "dw4/igMatrix44f.h"
#include "dw4/igMemoryPoolContext.h"
#include "dw4/igModelViewMatrixAttr.h"
#include "dw4/igObject.h"
#include "dw4/igTraversal.h"
#include <stdio.h>
#include <string.h>
/* kept local: no include/dw4 home; SceneGraph reads igCommonTraversal::_travProcs through its own load-bearing view. */
extern "C" int g_igCommonTraversal_travProcs[4];
#include "dw4/emptyString.h"

extern "C" int beLOA_Traverse(beLOA *node, igCommonTraversal *traversal);
extern "C" int beLOA_TraversalFunction(igCommonTraversal *traversal, beLOA *node);
extern "C" void beLua_Stop(void);
extern "C" void beLua_Update(void);
extern "C" igMetaObject *beLua_GetMeta(void);
/* Resolves a script name through the interned-string pool (the given name, or "<stage>/lua" when none
 * is given), walks every beLuaInfo in the receiver's info list and every beLuaData in that info's data
 * list, and runs the first data object whose name equals `name` through the Lua state's buffer-run
 * virtual (slot 100). When nothing ran (-1), it builds "<interned>/<name>" and runs that path through
 * the file-run virtual (slot 96).
 * Matching constructs: the interned-name holder's inline destructor releases the string on every
 * exit; the `unsigned size` parameter fixes the lw a2/a1 load order. */


/* beLuaState's virtual functions past igObject's: slot 22 runs a Lua file (beLuaState_RunFile) and
 * slot 23 a Lua chunk held in memory (beLuaState_RunBuffer).
 * ABI view only: never instantiated. */
class beLuaStateDispatchView : public igObjectDispatchView {
public:
    virtual void d21();
    virtual int RunFile(char *path);                                        /* slot 22 */
    virtual int RunBuffer(void *data, unsigned size, const char *name);     /* slot 23 */
};
extern "C" char text_s_lua[];
extern "C" char percent_s_slash_percent_s_2[];
/* stack holder for the interned name: the destructor drops one reference to the pooled string and frees its chunk at zero */
class LuaStrRef {
public:
    char *value;
    LuaStrRef() : value(0) {}
    ~LuaStrRef() { char *o = value; if (o) { int *hd = (int *)o - 2; int r = *(int *)(o - 4) - 1; *(int *)(o - 4) = r; if (r == 0) StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd); } }
};
extern "C" void beLua_Activate(beLua *self, int unusedArg);
extern "C" void beLua_Deactivate(beLua *self, int unusedArg);
extern "C" void beLua_Start(beLua *self);
extern "C" int beLua_AddInfo(beLua *self, int info);
extern "C" void beLua_RemoveAllInfo(beLua *self);

int beLOA_TraversalFunction(igCommonTraversal *traversal, beLOA *node) {
    return beLOA_Traverse(node, traversal);
}

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
        modelView = (igModelViewMatrixAttr *)CurrentAttr(traversal, g_igModelViewMatrixAttr_metaObject);
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
            List_RemoveWordAt((igDataList *)list, 0);
            ((igObject **)list->_data)[list->_count] = 0;
        }
    } else {
        list = (igObjectList *)node->_overrideAttrList;
        if (list->_count == 0) {
            ObjectList_AppendRetained((igObjectList *)list, (igObject *)node->_blendStateAttr);
            ObjectList_AppendRetained((igObjectList *)node->_overrideAttrList, (igObject *)node->_blendFunctionAttr);
            ObjectList_AppendRetained((igObjectList *)node->_overrideAttrList, (igObject *)node->_colorAttr);
        }
        ((OverrideAttr *)node->_colorAttr)->SetValue(node->_color);
    }
    node->_oldTime = now;
    for (i = 0; i < ((igObjectList *)node->_overrideAttrList)->_count; i++) {
        igAttrStackManager_PushOverrideAttr(attrs, ((igAttr **)OverrideAttrsOf(node)->_data)[i]);
    }
    result = igTraversal_TraverseChildren((igTraversal *)traversal, (igNode *)node);
    for (j = ((igObjectList *)node->_overrideAttrList)->_count - 1; j >= 0; j--) {
        igAttrStackManager_PopOverrideAttr(attrs, ((igAttr **)OverrideAttrsOf(node)->_data)[j]);
    }
    if (result == 2) {
        return 2;
    }
    return 0;
}

void beLOA_RegisterTraversalFunction(void) {
    igTraversal_RegisterFunction((igTraversalFunctionList *)g_igCommonTraversal_travProcs[0], (igMetaObject *)beLOA_GetMetaObject(), (void *)beLOA_TraversalFunction);
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
        if (g_stringPool == 0) {
            a = (int)StringPool_Allocate(16);
            if (a) a = (int)(StringPool_Construct((StringPool *)a));
            g_stringPool = (StringPool *)a;
        }
        s = (char *)StringPool_Intern(g_stringPool, buf1);
        old = ref.value;
        if (old) {
            int *hd = (int *)old - 2;
            int r = *(int *)(old - 4) - 1;
            *(int *)(old - 4) = r;
            if (r == 0) StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd);
        }
        ref.value = s;
    } else {
        if (g_stringPool == 0) {
            a = (int)StringPool_Allocate(16);
            if (a) a = (int)(StringPool_Construct((StringPool *)a));
            g_stringPool = (StringPool *)a;
        }
        s = (char *)StringPool_Intern(g_stringPool, given);
        old = ref.value;
        if (old) {
            int *hd = (int *)old - 2;
            int r = *(int *)(old - 4) - 1;
            *(int *)(old - 4) = r;
            if (r == 0) StringChunk_ReleaseHeader((StringChunk *)*hd, (StringTokenHeader *)hd);
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
                result = ((beLuaStateDispatchView *)self->_luaState)->RunBuffer((void *)o->_data, o->_dataSize, name);
                break;
            }
        }
    }
    if (result == -1) {
        sprintf(buf2, percent_s_slash_percent_s_2, ref.value, name);
        result = ((beLuaStateDispatchView *)self->_luaState)->RunFile(buf2);
    }
    return result;
}

void beLua_ResetLuaState(beLua *self) {
    int allocator;
    int ownerAllocator;
    igObject *luaState;

    ownerAllocator = (int)igObject_GetAllocator(self);
    if (g_useOwnerAllocator != 0) {
        allocator = ownerAllocator;
    } else {
        allocator = (int)Memory_GetAllocatorBySelector(kIGMemoryPoolHandleUser1);
    }
    luaState = (igObject *)self->_luaState;
    if (luaState != 0) {
        --luaState->_refCount;
        if (((unsigned long long)(long long)luaState->_refCount & 0x7fffffULL) == 0) {
            igObject_Destroy(luaState);
        }
    }
    self->_luaState = (int)beLuaState_Create(allocator);
}

/* Hands the object to the insight core's helper igInsightCore_AddToScheduler, which asks the scheduler at +12 of
 * the insight object (_insight) whether it already has the object (scheduler slot 26) and, if not,
 * calls scheduler slot 24 with it. Same body as beMessenger slot 21. The second argument is
 * unused. */
void beLua_Activate(beLua *self, int unusedArg)
{
    igInsightCore_AddToScheduler((igInsightCore *)self->_insight, (igObject *)self);
}

/* Counterpart of slot 21 through igInsightCore_RemoveFromScheduler, which calls scheduler slot 25 with the object only
 * when scheduler slot 26 reports it present. Same body as beMessenger slot 22. The second argument
 * is unused. */
void beLua_Deactivate(beLua *self, int unusedArg)
{
    igInsightCore_RemoveFromScheduler((igInsightCore *)self->_insight, (igObject *)self);
}

void beLua_Start(beLua *self) {
    igObject *luaState;
    self->_system = (int)(igInsightCore_FindManager((igInsightCore *)self->_insight, g_beSystem_metaObject));
    luaState = (igObject *)(self->_luaState);
    IG_OBJECT_RELEASE(luaState);
    self->_luaState = 0;
}

void beLua_Stop(void)
{
}

int beLua_AddInfo(beLua *self, int info) {
    if (igObject_IsKindOf((igObject *)info, g_beLuaInfo_metaObject) != 0) {
        ObjectList_AppendRetained((igObjectList *)self->_infoList, (igObject *)info);
        return 1;
    }
    return 0;
}

void beLua_RemoveAllInfo(beLua *self) {
    igInfoList *infos;
    int infoCount;
    int i;
    int clearCount;
    igObject *object;
    infos = (igInfoList *)self->_infoList;
    infoCount = infos->_count;
    for (i = 0; i < infoCount; i++) {
        object = ((igObject **)infos->_data)[i];
        IG_OBJECT_RELEASE(object);
    }
    clearCount = infos->_count;
    for (i = 0; i < clearCount; i++) {
        ((int *)infos->_data)[i] = 0;
    }
    infos->_count = 0;
    object = (igObject *)self->_luaState;
    IG_OBJECT_RELEASE(object);
    self->_luaState = 0;
}

void beLua_Update(void)
{
}

igMetaObject *beLua_GetMeta(void)
{
    return g_beLua_metaObject;
}

