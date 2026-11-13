#include "dw4/reflected.h"
#define INTERN_APPEND(field, text) { \
    const char *tok; \
    if ((text) == 0) { \
        tok = 0; \
    } else { \
        if (g_stringPool[0] == 0) { \
            void *pool = StringPool_Allocate(0x10); \
            if (pool != 0) pool = StringPool_Construct(pool); \
            g_stringPool[0] = pool; \
        } \
        tok = StringPool_Intern(g_stringPool[0], (const char *)(text)); \
    } \
    StringRef held(tok); \
    StringList_AppendRetained(field, &held); }
#define STR_RELEASE(s) if (s) { int *h_ = (int *)((s) - 8); if (--h_[1] == 0) StringChunk_ReleaseHeader(h_[0], h_); }

extern "C" void * StringPool_Allocate(...);
extern "C" void * StringPool_Construct(...);
extern "C" const char * StringPool_Intern(...);
extern "C" void StringChunk_ReleaseHeader(...);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_DispatchSelected(int, int *);
extern "C" int beMessenger_SelectReceivers(...);
extern "C" int sprintf(char *, const char *, int);
extern "C" void beNDMWWindow_QueueNumberText(beNDMWWindow *self, const char *textType, const char *textName, int number, const char *align);
extern "C" int beMessenger_AppendObject(int, int);
extern "C" int igInsightCore_FindManager(int, int);
extern "C" int igObject_IsKindOf(int, int);
extern "C" int beLua__RunNamedChunk(int, int, int);
extern "C" void beNDMWWindow_RunMessageScript(beNDMWWindow *self, int chunk, int callNo);
extern "C" int StringList_CopyRetained(...);
extern "C" int List_Resize(void *, int, int);
extern "C" int beMessenger_AppendVec3(int, float *);
extern "C" int beMessenger_GetBool(int, int);
extern "C" int beMessenger_SendNamed(...);
extern "C" int igObject_Destroy(...);
extern "C" void List_RemoveWordAt(void *, int);
extern "C" int TEXTCTL_2[4];
extern "C" int ALIGN_3[4];
extern "C" int TEXTSET_5[4];
extern "C" int SET_4[4];
extern "C" int SWITCH[4];
extern "C" void *g_stringPool[4];
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    const char *p;
    StringRef(const char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(int, StringRef *);
extern "C" void beNDMWWindow_QueueText(beNDMWWindow *self, const char *textType, const char *textName, const char *text, const char *align);
extern "C" char percent_d_2[];
extern "C" void beNDMWWindow_QueueObjectText(beNDMWWindow *self, const char *textType, const char *textName, int *textObject, const char *align);
extern "C" int g_beLua_metaObject[4];
extern "C" int g_txtCallNo[4];
extern "C" int CLR[4];
extern "C" void beNDMWWindow_ClearTextElement(beNDMWWindow *self, int *textType, int *textName);
struct Clr { static inline void ClearList(igStringRefList *l) {
    int n = l->_count;
    int i;
    int **slot; int *ref; int *old; int pool; int *a1; int c;
    for (i = 0; i < n; i++) {
        slot = &((int **)l->_data)[i];
        if (((int *)g_stringPool)[0] == 0) {
            pool = ((int)StringPool_Allocate(16));
            if (pool) pool = ((int)StringPool_Construct(pool));
            ((int *)g_stringPool)[0] = pool;
        }
        ref = (int *)StringPool_Intern(((int *)g_stringPool)[0], 0);
        old = *slot;
        if (old) { a1 = old - 2; c = old[-1] - 1; old[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*a1, a1); }
        *slot = ref;
    }
    l->_count = 0;
} };
extern "C" void beNDMWWindow_ClearQueuedText(beNDMWWindow *self);
extern "C" int MODELCTRL_17[4];
extern "C" int ISRUN_8[4];
extern "C" int GENERATE_11[4];
extern "C" void beNDMWWindow_PresentModel(beNDMWWindow *self, const char *model, int id, const char *sequence, const char *close, float *position);
extern "C" const float g_vec3Zero[4];
extern "C" void beNDMWWindow_PresentModelAtOrigin(beNDMWWindow *self,const char *model,int id,const char *sequence,const char *close);
extern "C" void beNDMWWindow_SendModelSequence(beNDMWWindow *self,int model,int id,int sequence);
extern "C" void beNDMWWindow_PlayQueuedModelClose(beNDMWWindow *w);
extern "C" int beMessenger_GetBoolCount(int);
extern "C" int beNDMWWindow_PollCloseComplete(beNDMWWindow *self);
extern "C" void beNDMWWindow_RequestChildrenClose(beNDMWWindow *self);
extern "C" int g_bePadManager_metaObject[4];
extern "C" int g_beMessenger_metaObject[4];
extern "C" void beNDMWWindow_BindContext(beNDMWWindow *self, igObject *mother, int insight, int playerNo, int entCode);
/* matching construct: dummy-virtual view so ->f21() dispatches through vtable slot 21 of the window */
struct WinView { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void f21(); };
extern "C" void beNDMWWindow_UpdateTree(beNDMWWindow *w);

void beNDMWWindow_QueueText(beNDMWWindow *self, const char *textType, const char *textName, const char *text, const char *align) {
    beMessenger_SelectReceivers(self->_messenger, TEXTCTL_2, 0, -1);
    beMessenger_AppendString(self->_messenger, textType);
    beMessenger_AppendString(self->_messenger, textName);
    beMessenger_AppendString(self->_messenger, align);
    beMessenger_DispatchSelected(self->_messenger, ALIGN_3);
    beMessenger_SelectReceivers(self->_messenger, TEXTCTL_2, 0, -1);
    beMessenger_AppendString(self->_messenger, textType);
    beMessenger_AppendString(self->_messenger, textName);
    beMessenger_AppendString(self->_messenger, text);
    beMessenger_DispatchSelected(self->_messenger, TEXTSET_5);
    beMessenger_SelectReceivers(self->_messenger, TEXTCTL_2, 0, -1);
    beMessenger_AppendString(self->_messenger, textType);
    beMessenger_AppendString(self->_messenger, textName);
    beMessenger_AppendString(self->_messenger, SET_4);
    beMessenger_DispatchSelected(self->_messenger, SWITCH);
    INTERN_APPEND(self->_textCloseTypeList, textType)
    INTERN_APPEND(self->_textCloseNameList, textName)
}

void beNDMWWindow_QueueNumberText(beNDMWWindow *self, const char *textType, const char *textName, int number, const char *align) {
    char text[16];
    sprintf(text, percent_d_2, number);
    beNDMWWindow_QueueText(self, textType, textName, text, align);
}

void beNDMWWindow_QueueObjectText(beNDMWWindow *self, const char *textType, const char *textName, int *textObject, const char *align) {
    beMessenger_SelectReceivers(self->_messenger, TEXTCTL_2, 0, -1);
    beMessenger_AppendString(self->_messenger, textType);
    beMessenger_AppendString(self->_messenger, textName);
    beMessenger_AppendString(self->_messenger, align);
    beMessenger_DispatchSelected(self->_messenger, ALIGN_3);
    beMessenger_SelectReceivers(self->_messenger, TEXTCTL_2, 0, -1);
    beMessenger_AppendString(self->_messenger, textType);
    beMessenger_AppendString(self->_messenger, textName);
    beMessenger_AppendObject(self->_messenger, *textObject);
    beMessenger_DispatchSelected(self->_messenger, TEXTSET_5);
    beMessenger_SelectReceivers(self->_messenger, TEXTCTL_2, 0, -1);
    beMessenger_AppendString(self->_messenger, textType);
    beMessenger_AppendString(self->_messenger, textName);
    beMessenger_AppendString(self->_messenger, SET_4);
    beMessenger_DispatchSelected(self->_messenger, SWITCH);
    INTERN_APPEND(self->_textCloseTypeList, textType)
    INTERN_APPEND(self->_textCloseNameList, textName)
}

static inline int castToLuaManager(int object) {
    if (object != 0 && igObject_IsKindOf(object, g_beLua_metaObject[0]) != 0) {
        return object;
    }
    return 0;
}

void beNDMWWindow_RunMessageScript(beNDMWWindow *self, int chunk, int callNo) {
    int manager = castToLuaManager(igInsightCore_FindManager(self->_insight, g_beLua_metaObject[0]));
    g_txtCallNo[0] = callNo;
    beLua__RunNamedChunk(manager, chunk, 0);
}

void beNDMWWindow_ClearTextElement(beNDMWWindow *self, int *textType, int *textName) {
    beMessenger_SelectReceivers(self->_messenger, &TEXTCTL_2[0], 0, -1);
    beMessenger_AppendString(self->_messenger, textType);
    beMessenger_AppendString(self->_messenger, textName);
    beMessenger_AppendString(self->_messenger, &CLR[0]);
    beMessenger_DispatchSelected(self->_messenger, &SWITCH[0]);
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
        if (type) { header = type - 2; refs = type[-1] - 1; type[-1] = refs; if (refs == 0) StringChunk_ReleaseHeader(*header, header); }
        StringList_CopyRetained(&nameCopy, (igStringRefList *)self->_textCloseNameList, i);
        name = nameCopy;
        if (name) { header = name - 2; refs = name[-1] - 1; name[-1] = refs; if (refs == 0) StringChunk_ReleaseHeader(*header, header); }
        beNDMWWindow_ClearTextElement(self, type, name);
    }
    Clr::ClearList((igStringRefList *)self->_textCloseTypeList);
    Clr::ClearList((igStringRefList *)self->_textCloseNameList);
}

static inline int count(const igDataList *list) { return list->_count; }

void beNDMWWindow_PresentModel(beNDMWWindow *self, const char *model, int id, const char *sequence, const char *close, float *position) {
    float at[3];
    beMessenger_SendNamed(self->_messenger, MODELCTRL_17, model, id, (const char *)ISRUN_8);
    if (beMessenger_GetBool(self->_messenger, 0) != 0) {
        beMessenger_SendNamed(self->_messenger, MODELCTRL_17, model, id, sequence);
    } else {
        beMessenger_SelectReceivers(self->_messenger, MODELCTRL_17, model, id);
        beMessenger_AppendString(self->_messenger, sequence);
        at[0] = position[0];
        at[1] = position[1];
        at[2] = position[2];
        beMessenger_AppendVec3(self->_messenger, at);
        beMessenger_DispatchSelected(self->_messenger, GENERATE_11);
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
    origin[0] = g_vec3Zero[0];
    origin[1] = g_vec3Zero[1];
    origin[2] = g_vec3Zero[2];
    beNDMWWindow_PresentModel(self, model, id, sequence, close, origin);
}

void beNDMWWindow_SendModelSequence(beNDMWWindow *self, int model, int id, int sequence) {
    beMessenger_SendNamed(self->_messenger, MODELCTRL_17, model, id, sequence);
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
            StringList_CopyRetained(&a, w->_modelCloseInfoNameList, i);
            s = (int)a;
            STR_RELEASE(s);
            m = *(int *)((char *)((igIntList *)w->_modelCloseRamNoList)->_data + off);
            StringList_CopyRetained(&b, w->_modelCloseSeqNameList, i);
            t = (int)b;
            STR_RELEASE(t);
            beNDMWWindow_SendModelSequence(w, s, m, t);
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
        /* matching construct: cxx_sweep — the token copy moved into the release test */
        if ((model = modelCopy)) { header = model - 2; refs = model[-1] - 1; model[-1] = refs; if (refs == 0) StringChunk_ReleaseHeader(*header, header); }
        id = ((int *)((igStringRefList *)self->_modelCloseRamNoList)->_data)[i];
        StringList_CopyRetained(&sequenceCopy, (igStringRefList *)self->_modelCloseSeqNameList, i);
        sequence = sequenceCopy;
        if (sequence) { header = sequence - 2; refs = sequence[-1] - 1; sequence[-1] = refs; if (refs == 0) StringChunk_ReleaseHeader(*header, header); }
        beMessenger_SendNamed(self->_messenger, MODELCTRL_17, model, id, ISRUN_8);
        if (beMessenger_GetBoolCount(self->_messenger) > 0 && beMessenger_GetBool(self->_messenger, 0)) return 0;
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
    self->_messenger = igInsightCore_FindManager(insight, g_beMessenger_metaObject[0]);
    self->_padManager = igInsightCore_FindManager(insight, g_bePadManager_metaObject[0]);
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
        ((WinView *)w)->f21();
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
                List_RemoveWordAt(k, i);
                i--;
                n--;
                *(int *)(k->_data + k->_count * 4) = 0;
            }
            i++;
        } while (i < n);
    }
}

