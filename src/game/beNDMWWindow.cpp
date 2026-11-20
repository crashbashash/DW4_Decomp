#include "dw4/support/reflected.h"
#include "dw4/core/igSmartPointer.h"
#include "dw4/game/ndmw/beNDMWWindow.h"
#include "dw4/game/ndmw/beNDMWWindowDispatchView.h"
#include "dw4/core/StringPool.h"
#include "dw4/core/igStringRef.h"
#include "dw4/game/be.h"
#include "dw4/game/beLua.h"
#include "dw4/game/beMessenger.h"
#include "dw4/game/bePadManager.h"
#include "dw4/core/igDataLists.h"
#include "dw4/insight/igInsightCore.h"
#include "dw4/core/igObject.h"
#include "dw4/maths/igVec3f.h"
#include <stdio.h>
#include "dw4/maths/igMathConstants.h"
#include "dw4/support/list-services.h"
#define INTERN_APPEND(field, text) { \
    igStringRef held((char *)(text)); \
    StringList_AppendRetained((igStringRefList *)(field), held.ref()); }

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
    if (object != 0 && ((Gap::Core::igObject *)object)->isOfType(g_beLua_metaObject) != 0) {
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
    int n;
    int i;
    int *type;
    int *name;
    n = ((igStringRefList *)self->_textCloseTypeList)->_count;
    for (i = 0; i < n; i++) {
        type = (int *)StringList_CopyRetained((igStringRefList *)self->_textCloseTypeList, i).p;
        name = (int *)StringList_CopyRetained((igStringRefList *)self->_textCloseNameList, i).p;
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
            s = (int)StringList_CopyRetained((igStringRefList *)w->_modelCloseInfoNameList, i).p;
            m = *(int *)((char *)((igIntList *)w->_modelCloseRamNoList)->_data + off);
            t = (int)StringList_CopyRetained((igStringRefList *)w->_modelCloseSeqNameList, i).p;
            beNDMWWindow_SendModelSequence(w, (const char *)s, m, (const char *)t);
            i++;
            off += 4;
        } while (i < n);
    }
}

int beNDMWWindow_PollCloseComplete(beNDMWWindow *self) {
    int i;
    int id;
    int n;
    int *model;
    int *sequence;
    n = ((igStringRefList *)self->_modelCloseInfoNameList)->_count;
    for (i = 0; i < n; i++) {
        model = (int *)StringList_CopyRetained((igStringRefList *)self->_modelCloseInfoNameList, i).p;
        id = ((int *)((igStringRefList *)self->_modelCloseRamNoList)->_data)[i];
        sequence = (int *)StringList_CopyRetained((igStringRefList *)self->_modelCloseSeqNameList, i).p;
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
