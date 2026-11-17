#include "dw4/reflected.h"
#include "dw4/igSmartPointer.h"
#include "dw4/beNDMWWindow.h"
#include "dw4/beNDMWWindowDispatchView.h"
#include "dw4/StringPool.h"
#include "dw4/be.h"
#include "dw4/beLua.h"
#include "dw4/beMessenger.h"
#include "dw4/bePadManager.h"
#include "dw4/igDataLists.h"
#include "dw4/igInsightCore.h"
#include "dw4/igObject.h"
#include "dw4/igVec3f.h"
#include <stdio.h>
#include "dw4/igMathConstants.h"
#include "dw4/list-services.h"
#define INTERN_APPEND(field, text) { \
    const char *tok; \
    if ((text) == 0) { \
        tok = 0; \
    } else { \
        if (g_stringPool == 0) { \
            StringPool *pool = (StringPool *)StringPool_Allocate(0x10); \
            if (pool != 0) pool = StringPool_Construct(pool); \
            g_stringPool = pool; \
        } \
        tok = StringPool_Intern(g_stringPool, (const char *)(text)); \
    } \
    StringRef held(tok); \
    StringList_AppendRetained((igStringRefList *)(field), held.ref()); }
#define STR_RELEASE(s) if (s) { int *h_ = (int *)((s) - 8); if (--h_[1] == 0) StringChunk_ReleaseHeader((StringChunk *)h_[0], (StringTokenHeader *)h_); }

/* kept local: StringList_CopyRetained's result holder is not shared yet (open item A7); retail passes
 * the result slot as the hidden first argument. */
extern "C" void StringList_CopyRetained(void *result, igStringRefList *list, int index);
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    const char *p;
    char *const *ref() const { return (char *const *)&p; }
    StringRef(const char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader((StringChunk *)*h, (StringTokenHeader *)h); } }
};
extern "C" void beNDMWWindow_ClearTextElement(beNDMWWindow *self, int *textType, int *textName);
struct Clr { static inline void ClearList(igStringRefList *l) {
    int n = l->_count;
    int i;
    int **slot; int *ref; int *old; int pool; int *a1; int c;
    for (i = 0; i < n; i++) {
        slot = &((int **)l->_data)[i];
        if (g_stringPool == 0) {
            pool = ((int)StringPool_Allocate(16));
            if (pool) pool = ((int)StringPool_Construct((StringPool *)pool));
            g_stringPool = (StringPool *)pool;
        }
        ref = (int *)StringPool_Intern(g_stringPool, 0);
        old = *slot;
        if (old) { a1 = old - 2; c = old[-1] - 1; old[-1] = c; if (c == 0) StringChunk_ReleaseHeader((StringChunk *)*a1, (StringTokenHeader *)a1); }
        *slot = ref;
    }
    l->_count = 0;
} };

#pragma push
#pragma readonly_strings on

void beNDMWWindow_QueueText(beNDMWWindow *self, const char *textType, const char *textName, const char *text, const char *align) {
    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "TEXTCTL", 0, -1);
    beMessenger_AppendString((beMessenger *)self->_messenger, textType);
    beMessenger_AppendString((beMessenger *)self->_messenger, textName);
    beMessenger_AppendString((beMessenger *)self->_messenger, align);
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "ALIGN");
    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "TEXTCTL", 0, -1);
    beMessenger_AppendString((beMessenger *)self->_messenger, textType);
    beMessenger_AppendString((beMessenger *)self->_messenger, textName);
    beMessenger_AppendString((beMessenger *)self->_messenger, text);
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "TEXTSET");
    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "TEXTCTL", 0, -1);
    beMessenger_AppendString((beMessenger *)self->_messenger, textType);
    beMessenger_AppendString((beMessenger *)self->_messenger, textName);
    beMessenger_AppendString((beMessenger *)self->_messenger, "SET");
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SWITCH");
    INTERN_APPEND(self->_textCloseTypeList, textType)
    INTERN_APPEND(self->_textCloseNameList, textName)
}

void beNDMWWindow_QueueNumberText(beNDMWWindow *self, const char *textType, const char *textName, int number, const char *align) {
    char text[16];
    sprintf(text, "%d", number);
    beNDMWWindow_QueueText(self, textType, textName, text, align);
}

void beNDMWWindow_QueueObjectText(beNDMWWindow *self, const char *textType, const char *textName, const igSmartPointer<igObject> &textObject, const char *align) {
    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "TEXTCTL", 0, -1);
    beMessenger_AppendString((beMessenger *)self->_messenger, textType);
    beMessenger_AppendString((beMessenger *)self->_messenger, textName);
    beMessenger_AppendString((beMessenger *)self->_messenger, align);
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "ALIGN");
    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "TEXTCTL", 0, -1);
    beMessenger_AppendString((beMessenger *)self->_messenger, textType);
    beMessenger_AppendString((beMessenger *)self->_messenger, textName);
    beMessenger_AppendObject((beMessenger *)self->_messenger, textObject.p);
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "TEXTSET");
    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "TEXTCTL", 0, -1);
    beMessenger_AppendString((beMessenger *)self->_messenger, textType);
    beMessenger_AppendString((beMessenger *)self->_messenger, textName);
    beMessenger_AppendString((beMessenger *)self->_messenger, "SET");
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SWITCH");
    INTERN_APPEND(self->_textCloseTypeList, textType)
    INTERN_APPEND(self->_textCloseNameList, textName)
}

static inline igObject *castToLuaManager(igObject *object) {
    if (object != 0 && igObject_IsKindOf(object, g_beLua_metaObject) != 0) {
        return object;
    }
    return 0;
}

void beNDMWWindow_RunMessageScript(beNDMWWindow *self, const char *chunk, int callNo) {
    igObject *manager = castToLuaManager(igInsightCore_FindManager((igInsightCore *)self->_insight, g_beLua_metaObject));
    g_txtCallNo = callNo;
    beLua__RunNamedChunk((beLua *)manager, chunk, 0);
}

void beNDMWWindow_ClearTextElement(beNDMWWindow *self, int *textType, int *textName) {
    beMessenger_SelectReceivers((beMessenger *)self->_messenger, "TEXTCTL", 0, -1);
    beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)textType);
    beMessenger_AppendString((beMessenger *)self->_messenger, (const char *)textName);
    beMessenger_AppendString((beMessenger *)self->_messenger, "CLR");
    beMessenger_DispatchSelected((beMessenger *)self->_messenger, "SWITCH");
}

void beNDMWWindow_ClearQueuedText(beNDMWWindow *self) {
    int *typeCopy;
    int *name;
    int *nameCopy;
    int n;
    int *header;
    int i;
    int *type;
    int refs;
    n = ((igStringRefList *)self->_textCloseTypeList)->_count;
    for (i = 0; i < n; i++) {
        StringList_CopyRetained(&typeCopy, (igStringRefList *)self->_textCloseTypeList, i);
        type = typeCopy;
        if (type) { header = type - 2; refs = type[-1] - 1; type[-1] = refs; if (refs == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header); }
        StringList_CopyRetained(&nameCopy, (igStringRefList *)self->_textCloseNameList, i);
        name = nameCopy;
        if (name) { header = name - 2; refs = name[-1] - 1; name[-1] = refs; if (refs == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header); }
        beNDMWWindow_ClearTextElement(self, type, name);
    }
    Clr::ClearList((igStringRefList *)self->_textCloseTypeList);
    Clr::ClearList((igStringRefList *)self->_textCloseNameList);
}

static inline int count(const igDataList *list) { return list->_count; }

void beNDMWWindow_PresentModel(beNDMWWindow *self, const char *model, int id, const char *sequence, const char *close, float *position) {
    float at[3];
    beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", model, id, (const char *)"ISRUN");
    if (beMessenger_GetBool((beMessenger *)self->_messenger, 0)) {
        beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", model, id, sequence);
    } else {
        beMessenger_SelectReceivers((beMessenger *)self->_messenger, "MODELCTRL", model, id);
        beMessenger_AppendString((beMessenger *)self->_messenger, sequence);
        at[0] = position[0];
        at[1] = position[1];
        at[2] = position[2];
        beMessenger_AppendVec3((beMessenger *)self->_messenger, at);
        beMessenger_DispatchSelected((beMessenger *)self->_messenger, "GENERATE");
    }
    if (close != 0) {
        INTERN_APPEND(self->_modelCloseInfoNameList, model)
        {
            int n; igDataList *l = (igDataList *)self->_modelCloseRamNoList;
            n = l->_count;
            if (n < l->_capacity) l->_count = count(l) + 1; else List_Resize(l, n + 1, 4);
            ((int *)l->_data)[n] = id;
        }
        INTERN_APPEND(self->_modelCloseSeqNameList, close)
    }
}

void beNDMWWindow_PresentModelAtOrigin(beNDMWWindow *self, const char *model, int id, const char *sequence, const char *close) {
    float origin[3];
    origin[0] = g_vec3Zero.x;
    origin[1] = g_vec3Zero.y;
    origin[2] = g_vec3Zero.z;
    beNDMWWindow_PresentModel(self, model, id, sequence, close, origin);
}

void beNDMWWindow_SendModelSequence(beNDMWWindow *self, const char *model, int id, const char *sequence) {
    beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", model, id, sequence);
}

void beNDMWWindow_PlayQueuedModelClose(beNDMWWindow *w) {
    int n = ((igDataList *)w->_modelCloseInfoNameList)->_count;
    int i = 0;
    int m;
    int s;
    int t;
    int off;
    if (0 < n) {
        off = 0;
        do {
            char *a;
            char *b;
            StringList_CopyRetained(&a, (igStringRefList *)w->_modelCloseInfoNameList, i);
            s = (int)a;
            STR_RELEASE(s);
            m = *(int *)((char *)((igIntList *)w->_modelCloseRamNoList)->_data + off);
            StringList_CopyRetained(&b, (igStringRefList *)w->_modelCloseSeqNameList, i);
            t = (int)b;
            STR_RELEASE(t);
            beNDMWWindow_SendModelSequence(w, (const char *)s, m, (const char *)t);
            i++;
            off += 4;
        } while (i < n);
    }
}

int beNDMWWindow_PollCloseComplete(beNDMWWindow *self) {
    int *modelCopy;
    int *sequenceCopy;
    int *header;
    int refs;
    int i;
    int id;
    int n;
    int *model;
    int *sequence;
    n = ((igStringRefList *)self->_modelCloseInfoNameList)->_count;
    for (i = 0; i < n; i++) {
        StringList_CopyRetained(&modelCopy, (igStringRefList *)self->_modelCloseInfoNameList, i);
        /* matching construct: cxx_sweep — the token copy moved into the release test; as a statement of its own, like
         * the sequence copy below, the loop index moves from s1 to s2 */
        if ((model = modelCopy)) { header = model - 2; refs = model[-1] - 1; model[-1] = refs; if (refs == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header); }
        id = ((int *)((igStringRefList *)self->_modelCloseRamNoList)->_data)[i];
        StringList_CopyRetained(&sequenceCopy, (igStringRefList *)self->_modelCloseSeqNameList, i);
        sequence = sequenceCopy;
        if (sequence) { header = sequence - 2; refs = sequence[-1] - 1; sequence[-1] = refs; if (refs == 0) StringChunk_ReleaseHeader((StringChunk *)*header, (StringTokenHeader *)header); }
        beMessenger_SendNamed((beMessenger *)self->_messenger, "MODELCTRL", (const char *)model, id, "ISRUN");
        if (beMessenger_GetBoolCount((beMessenger *)self->_messenger) > 0 && beMessenger_GetBool((beMessenger *)self->_messenger, 0)) return 0;
    }
    if (((igStringRefList *)self->_subWindow)->_count) return 0;
    Clr::ClearList((igStringRefList *)self->_modelCloseInfoNameList);
    ((igStringRefList *)self->_modelCloseRamNoList)->_count = 0;
    Clr::ClearList((igStringRefList *)self->_modelCloseSeqNameList);
    return 1;
}

void beNDMWWindow_RequestChildrenClose(beNDMWWindow *self) {
    int n;
    int i;
    beNDMWWindow *child;

    n = ((igDataList *)self->_subWindow)->_count;
    for (i = 0; i < n; i++) {
        child = ((beNDMWWindow **)((igDataList *)self->_subWindow)->_data)[i];
        if (child->_st0 < 2) {
            child->_st0 = 2;
            child->_st3 = 0;
            child->_st2 = 0;
            child->_st1 = 0;
        }
    }
}

void beNDMWWindow_BindContext(beNDMWWindow *self, igObject *mother, int insight, int playerNo, int entCode) {
    igObject *old;

    if (mother != 0) {
        mother->_refCount = mother->_refCount + 1;
    }
    old = (igObject *)self->_mother;
    if (old != 0) {
        old->_refCount = old->_refCount - 1;
        if ((old->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(old);
        }
    }
    self->_mother = (int)mother;
    self->_insight = insight;
    self->_messenger = (int)igInsightCore_FindManager((igInsightCore *)insight, g_beMessenger_metaObject);
    self->_padManager = (int)igInsightCore_FindManager((igInsightCore *)insight, g_bePadManager_metaObject);
    self->_playerNo = playerNo;
    self->_entCode = entCode;
}

void beNDMWWindow_UpdateTree(beNDMWWindow *w) {
    int n;
    int i;
    int c;
    int j;
    beNDMWWindow *ch;
    igObjectList *k;
    if (w->_isRun != 0) {
        ((beNDMWWindowDispatchView *)w)->Update();
    }
    if (w->_isRun == 0 || w->_st0 >= 2) {
        c = ((igObjectList *)w->_subWindow)->_count;
        j = 0;
        if (0 < c) {
            int off = 0;
            do {
                ch = *(beNDMWWindow **)(((igObjectList *)w->_subWindow)->_data + off);
                if (ch->_st0 < 2) {
                    ch->_st0 = 2;
                    ch->_st3 = 0;
                    ch->_st2 = 0;
                    ch->_st1 = 0;
                }
                j++;
                off += 4;
            } while (j < c);
        }
    }
    n = ((igObjectList *)w->_subWindow)->_count;
    i = 0;
    if (n > 0) {
        do {
            int off = i * 4;
            beNDMWWindow_UpdateTree(*(beNDMWWindow **)(((igObjectList *)w->_subWindow)->_data + off));
            k = (igObjectList *)w->_subWindow;
            ch = *(beNDMWWindow **)(k->_data + off);
            if (ch->_isRun == 0) {
                if (ch != 0) {
                    ch->_refCount = (int)ch->_refCount - 1;
                    if (((unsigned long long)((long long)(int)ch->_refCount << 0x29) >> 0x29) == 0) {
                        igObject_Destroy(ch);
                    }
                }
                List_RemoveWordAt((igDataList *)k, i);
                i--;
                n--;
                *(int *)(k->_data + k->_count * 4) = 0;
            }
            i++;
        } while (i < n);
    }
}

#pragma pop
