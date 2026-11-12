#include "dw4/reflected.h"
#define INTERN_APPEND(field, text) { \
    const char *tok; \
    if ((text) == 0) { \
        tok = 0; \
    } else { \
        if (DAT_00586f20[0] == 0) { \
            void *pool = FUN_002eb010(0x10); \
            if (pool != 0) pool = StringPool_Construct(pool); \
            DAT_00586f20[0] = pool; \
        } \
        tok = StringPool_Intern(DAT_00586f20[0], (const char *)(text)); \
    } \
    StringRef held(tok); \
    StringList_AppendRetained(field, &held); }
#define STR_RELEASE(s) if (s) { int *h_ = (int *)((s) - 8); if (--h_[1] == 0) StringChunk_ReleaseHeader(h_[0], h_); }

extern "C" void * FUN_002eb010(...);
extern "C" void * StringPool_Construct(...);
extern "C" const char * StringPool_Intern(...);
extern "C" void StringChunk_ReleaseHeader(...);
extern "C" int beMessenger_AppendString(...);
extern "C" int beMessenger_DispatchSelected(int, int *);
extern "C" int beMessenger_SelectReceivers(...);
extern "C" int sprintf(int *, int *, int);
extern "C" void FUN_003f5660(int arg0, int arg1, int arg2, int arg3, int arg4);
extern "C" int beMessenger_AppendObject(int, int);
extern "C" int FUN_00236f80(int, int);
extern "C" int igObject_IsKindOf(int, int);
extern "C" int beLua__RunNamedChunk(int, int, int);
extern "C" void beNDMWWindow_RunMessageScript(int *arg0, int arg1, int arg2);
extern "C" int StringList_CopyRetained(...);
extern "C" int List_Resize(void *, int, int);
extern "C" int beMessenger_AppendVec3(int, float *);
extern "C" int beMessenger_GetBool(int, int);
extern "C" int beMessenger_SendNamed(...);
extern "C" int igObject_Destroy(...);
extern "C" void List_RemoveWordAt(void *, int);
extern "C" int DAT_00518700[4];
extern "C" int DAT_00518708[4];
extern "C" int DAT_00518710[4];
extern "C" int DAT_00518718[4];
extern "C" int DAT_00518720[4];
extern "C" void *DAT_00586f20[4];
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    const char *p;
    StringRef(const char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(int, StringRef *);
extern "C" void FUN_003f5410(beNDMWWindow *arg0, int *arg1, int *arg2, int *arg3, int *arg4);
extern "C" int DAT_00518728[4];
extern "C" void FUN_003f56d0(beNDMWWindow *arg0, const char *arg1, const char *arg2, int *arg3, const char *arg4);
extern "C" int DAT_00589208[4];
extern "C" int DAT_0058a220[4];
extern "C" int TEXTCTL_2[4];
extern "C" int SWITCH[4];
extern "C" int CLR[4];
extern "C" void beNDMWWindow_ClearTextElement(beNDMWWindow *self, int *textType, int *textName);
struct Clr { static inline void ClearList(igStringRefList *l) {
    int n = l->_count;
    int i;
    int **slot; int *ref; int *old; int pool; int *a1; int c;
    for (i = 0; i < n; i++) {
        slot = &((int **)l->_data)[i];
        if (((int *)DAT_00586f20)[0] == 0) {
            pool = ((int)FUN_002eb010(16));
            if (pool) pool = ((int)StringPool_Construct(pool));
            ((int *)DAT_00586f20)[0] = pool;
        }
        ref = (int *)StringPool_Intern(((int *)DAT_00586f20)[0], 0);
        old = *slot;
        if (old) { a1 = old - 2; c = old[-1] - 1; old[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*a1, a1); }
        *slot = ref;
    }
    l->_count = 0;
} };
extern "C" void beNDMWWindow_ClearQueuedText(beNDMWWindow *self);
extern "C" int DAT_00518738[4];
extern "C" int DAT_00518748[4];
extern "C" int DAT_00518750[4];
extern "C" void beNDMWWindow_PresentModel(beNDMWWindow *arg0, const char *arg1, int arg2, const char *arg3, const char *arg4, float *arg5);
extern "C" float D_004e1058[];
extern "C" float D_004e105c[];
extern "C" float D_004e1060[];
extern "C" char D_00518738[];
extern "C" void beNDMWWindow_PresentModelAtOrigin(beNDMWWindow *self,const char *model,int id,const char *sequence,const char *close);
extern "C" void beNDMWWindow_SendModelSequence(beNDMWWindow *self,int model,int id,int sequence);
extern "C" void beNDMWWindow_PlayQueuedModelClose(beNDMWWindow *w);
extern "C" void beNDMWWindow_RequestChildrenClose(beNDMWWindow *arg0);
extern "C" int DAT_00588518[4];
extern "C" int DAT_00588f38[4];
extern "C" void beNDMWWindow_BindContext(beNDMWWindow *arg0, igObject *arg1, int arg2, int arg3, int arg4);
/* matching construct: dummy-virtual view so ->f21() dispatches through vtable slot 21 of the window */
struct WinView { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void f21(); };
extern "C" void beNDMWWindow_UpdateTree(beNDMWWindow *w);

void FUN_003f5410(beNDMWWindow *arg0, int *arg1, int *arg2, int *arg3, int *arg4) {
    beMessenger_SelectReceivers(arg0->_messenger, DAT_00518700, 0, -1);
    beMessenger_AppendString(arg0->_messenger, arg1);
    beMessenger_AppendString(arg0->_messenger, arg2);
    beMessenger_AppendString(arg0->_messenger, arg4);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00518708);
    beMessenger_SelectReceivers(arg0->_messenger, DAT_00518700, 0, -1);
    beMessenger_AppendString(arg0->_messenger, arg1);
    beMessenger_AppendString(arg0->_messenger, arg2);
    beMessenger_AppendString(arg0->_messenger, arg3);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00518710);
    beMessenger_SelectReceivers(arg0->_messenger, DAT_00518700, 0, -1);
    beMessenger_AppendString(arg0->_messenger, arg1);
    beMessenger_AppendString(arg0->_messenger, arg2);
    beMessenger_AppendString(arg0->_messenger, DAT_00518718);
    beMessenger_DispatchSelected(arg0->_messenger, DAT_00518720);
    INTERN_APPEND(arg0->_textCloseTypeList, arg1)
    INTERN_APPEND(arg0->_textCloseNameList, arg2)
}

void FUN_003f5660(int arg0, int arg1, int arg2, int arg3, int arg4) {
    int sp50[4];
    sprintf(sp50, &DAT_00518728[0], arg3);
    FUN_003f5410((beNDMWWindow *)arg0, (int *)arg1, (int *)arg2, sp50, (int *)arg4);
}

void FUN_003f56d0(beNDMWWindow *arg0, const char *arg1, const char *arg2, int *arg3, const char *arg4) {
    beMessenger_SelectReceivers(arg0->_messenger, &DAT_00518700[0], 0, -1);
    beMessenger_AppendString(arg0->_messenger, arg1);
    beMessenger_AppendString(arg0->_messenger, arg2);
    beMessenger_AppendString(arg0->_messenger, arg4);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_00518708[0]);
    beMessenger_SelectReceivers(arg0->_messenger, &DAT_00518700[0], 0, -1);
    beMessenger_AppendString(arg0->_messenger, arg1);
    beMessenger_AppendString(arg0->_messenger, arg2);
    beMessenger_AppendObject(arg0->_messenger, *arg3);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_00518710[0]);
    beMessenger_SelectReceivers(arg0->_messenger, &DAT_00518700[0], 0, -1);
    beMessenger_AppendString(arg0->_messenger, arg1);
    beMessenger_AppendString(arg0->_messenger, arg2);
    beMessenger_AppendString(arg0->_messenger, (const char *)&DAT_00518718[0]);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_00518720[0]);
    INTERN_APPEND(arg0->_textCloseTypeList, arg1)
    INTERN_APPEND(arg0->_textCloseNameList, arg2)
}

static inline int castToLuaManager(int object) {
    if (object != 0 && igObject_IsKindOf(object, DAT_00589208[0]) != 0) {
        return object;
    }
    return 0;
}

void beNDMWWindow_RunMessageScript(int *arg0, int arg1, int arg2) {
    int manager = castToLuaManager(FUN_00236f80(arg0[2], DAT_00589208[0]));
    DAT_0058a220[0] = arg2;
    beLua__RunNamedChunk(manager, arg1, 0);
}

void beNDMWWindow_ClearTextElement(beNDMWWindow *self, int *textType, int *textName) {
    beMessenger_SelectReceivers(self->_messenger, &TEXTCTL_2[0], 0, -1);
    beMessenger_AppendString(self->_messenger, textType);
    beMessenger_AppendString(self->_messenger, textName);
    beMessenger_AppendString(self->_messenger, &CLR[0]);
    beMessenger_DispatchSelected(self->_messenger, &SWITCH[0]);
}

void beNDMWWindow_ClearQueuedText(beNDMWWindow *self) {
    int *sp1;
    int *t2;
    int *sp2;
    int n;
    int *a1;
    int i;
    int *t1;
    int c;
    n = ((igStringRefList *)self->_textCloseTypeList)->_count;
    for (i = 0; i < n; i++) {
        StringList_CopyRetained(&sp1, (igStringRefList *)self->_textCloseTypeList, i);
        t1 = sp1;
        if (t1) { a1 = t1 - 2; c = t1[-1] - 1; t1[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*a1, a1); }
        StringList_CopyRetained(&sp2, (igStringRefList *)self->_textCloseNameList, i);
        t2 = sp2;
        if (t2) { a1 = t2 - 2; c = t2[-1] - 1; t2[-1] = c; if (c == 0) StringChunk_ReleaseHeader(*a1, a1); }
        beNDMWWindow_ClearTextElement(self, t1, t2);
    }
    Clr::ClearList((igStringRefList *)self->_textCloseTypeList);
    Clr::ClearList((igStringRefList *)self->_textCloseNameList);
}

static inline int count(const igDataList *list) { return list->_count; }

void beNDMWWindow_PresentModel(beNDMWWindow *arg0, const char *arg1, int arg2, const char *arg3, const char *arg4, float *arg5) {
    float v[3];
    beMessenger_SendNamed(arg0->_messenger, DAT_00518738, arg1, arg2, (const char *)DAT_00518748);
    if (beMessenger_GetBool(arg0->_messenger, 0) != 0) {
        beMessenger_SendNamed(arg0->_messenger, DAT_00518738, arg1, arg2, arg3);
    } else {
        beMessenger_SelectReceivers(arg0->_messenger, DAT_00518738, arg1, arg2);
        beMessenger_AppendString(arg0->_messenger, arg3);
        v[0] = arg5[0];
        v[1] = arg5[1];
        v[2] = arg5[2];
        beMessenger_AppendVec3(arg0->_messenger, v);
        beMessenger_DispatchSelected(arg0->_messenger, DAT_00518750);
    }
    if (arg4 != 0) {
        INTERN_APPEND(arg0->_modelCloseInfoNameList, arg1)
        {
            int n; igDataList *l = (igDataList *)arg0->_modelCloseRamNoList;
            n = l->_count;
            if (n < l->_capacity) l->_count = count(l) + 1; else List_Resize(l, n + 1, 4);
            ((int *)l->_data)[n] = arg2;
        }
        INTERN_APPEND(arg0->_modelCloseSeqNameList, arg4)
    }
}

void beNDMWWindow_PresentModelAtOrigin(beNDMWWindow *self,const char *model,int id,const char *sequence,const char *close){
    float origin[3];origin[0]=D_004e1058[0];origin[1]=D_004e105c[0];origin[2]=D_004e1060[0];
    beNDMWWindow_PresentModel(self, (const char *)model, (int)id, (const char *)sequence, (const char *)close, (float *)origin);
}

void beNDMWWindow_SendModelSequence(beNDMWWindow *self,int model,int id,int sequence){
    beMessenger_SendNamed((void *)self->_messenger,D_00518738,model,id,sequence);
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

void beNDMWWindow_RequestChildrenClose(beNDMWWindow *arg0) {
    int n;
    int i;
    beNDMWWindow *t;

    n = ((igDataList *)arg0->_subWindow)->_count;
    for (i = 0; i < n; i++) {
        t = ((beNDMWWindow **)((igDataList *)arg0->_subWindow)->_data)[i];
        if (t->_st0 < 2) {
            t->_st0 = 2;
            t->_st3 = 0;
            t->_st2 = 0;
            t->_st1 = 0;
        }
    }
}

/* igObject header: vtable, packed refcount */
void beNDMWWindow_BindContext(beNDMWWindow *arg0, igObject *arg1, int arg2, int arg3, int arg4) {
    igObject *t;

    if (arg1 != 0) {
        arg1->_refCount = arg1->_refCount + 1;
    }
    t = (igObject *)arg0->_mother;
    if (t != 0) {
        t->_refCount = t->_refCount - 1;
        if ((t->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    arg0->_mother = (int)arg1;
    arg0->_insight = arg2;
    arg0->_messenger = FUN_00236f80(arg2, DAT_00588f38[0]);
    arg0->_padManager = FUN_00236f80(arg2, DAT_00588518[0]);
    arg0->_playerNo = arg3;
    arg0->_entCode = arg4;
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

