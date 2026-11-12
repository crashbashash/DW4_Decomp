#include "dw4/reflected.h"
#define INTERN_APPEND(field, text) { \
    char *tok; \
    if ((text) == 0) { \
        tok = 0; \
    } else { \
        if (((void * *)g_stringPool)[0] == 0) { \
            void *pool = ((void *)FUN_002eb010(0x10)); \
            if (pool != 0) pool = ((void *)StringPool_Construct(pool)); \
            ((void * *)g_stringPool)[0] = pool; \
        } \
        tok = (char *)StringPool_Intern(((void * *)g_stringPool)[0], (const char *)(text)); \
    } \
    StringRef held(tok); \
    StringList_AppendRetained(field, &held); }

extern "C" int beMessenger_AppendBool(int, int);
extern "C" int beMessenger_AppendInt(int, int);
extern "C" int beMessenger_AppendString(int, void *);
extern "C" int beMessenger_AppendVec3(int, void *);
extern "C" int beMessenger_DispatchSelected(int, void *);
extern "C" int beMessenger_GetBool(int, int);
extern "C" int beMessenger_GetInt(int, int);
extern "C" int beMessenger_SelectReceivers(int, void *, int, int);
extern "C" int beMessenger_SendNamed(...);
extern "C" int FUN_002eb010(...);
extern "C" int StringPool_Construct(...);
extern "C" const char * StringPool_Intern(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" int beNDMWWindow_PresentModelAtOrigin(...);
extern "C" int beNDMWWindow_RunMessageScript(...);
extern "C" int FUN_003f5410(...);
extern "C" int Gap__Bec__beNDMWStatusSelectE1__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWStatusSelectE0__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWStatusSelect01__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWStatusSelect00__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWWindowSelect__vfunc_20(void);
/* matching construct: dummy-virtual class (22 slots) so arg0->v22() compiles to the retail vtable call; it carries no data. */
class beNDMWWindowSelectVTable { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void v22();
 };
extern "C" int beNDMWWindow_ClearQueuedText(beNDMWWindowSelectVTable *);
extern "C" int beNDMWWindow_PlayQueuedModelClose(beNDMWWindowSelectVTable *);
extern "C" int beNDMWWindow_PollCloseComplete(beNDMWWindowSelectVTable *);
extern "C" int DAT_0051a918[4];
extern "C" int DAT_0051a928[4];
extern "C" int DAT_0051a938[4];
extern "C" int DAT_0051a948[4];
extern "C" int DAT_0051a958[4];
extern "C" int DAT_0051a960[4];
extern "C" void Gap__Bec__beNDMWWindowSelect__vfunc_21(beNDMWWindowSelectVTable *arg0);
extern "C" char D_0051a918[];
extern "C" char D_0051a968[];
extern "C" bool beNDMWWindowSelect_CanRequestFO2TOP(beNDMWWindowSelect *self);
extern "C" int DAT_0051a978[4];
extern "C" int DAT_0051a988[4];
extern "C" int DAT_0051a998[4];
extern "C" int DAT_0051a9a8[4];
extern "C" int DAT_0051a9b8[4];
extern "C" int DAT_0051a9c0[4];
extern "C" int DAT_0051a9c8[4];
extern "C" int DAT_0051a9d0[4];
extern "C" int DAT_0051a9e0[4];
extern "C" int g_stringPool[4];
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    char *p;
    StringRef(char *s) : p(s) {}
    /* take a freshly interned token, dropping the share of the previous one */
    void Assign(char *fresh) { char *old = p; if (old) { int *h = (int *)old - 2; int r = ((int *)old)[-1] - 1; ((int *)old)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } p = fresh; }
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(int, StringRef *);
struct Sh { char p[60]; int f60; int f64; char q[12]; const char *f80; int f84; int f88; int f92; int f96; int pad100; char f104; };
extern "C" void Gap__Bec__beNDMWStatusSelect00__vfunc_22(Sh *arg0);
extern "C" int DAT_0051a9f0[4];
extern "C" int DAT_0051aa08[4];
extern "C" int DAT_0051aa18[4];
extern "C" int DAT_0051aa28[4];
extern "C" int DAT_0051aa30[4];
extern "C" int DAT_0051aa38[4];
extern "C" int DAT_0051aa40[4];
extern "C" int DAT_0051aa50[4];
extern "C" void Gap__Bec__beNDMWStatusSelect01__vfunc_22(beNDMWStatusSelect01 *arg0);
extern "C" int DAT_0051aa58[4];
extern "C" void Gap__Bec__beNDMWStatusSelectE0__vfunc_22(beNDMWStatusSelectE0 *arg0);
extern "C" int DAT_0051aa68[4];
extern "C" void Gap__Bec__beNDMWStatusSelectE1__vfunc_22(beNDMWStatusSelectE1 *arg0);
extern "C" int g_beNDMWStatusSelectE1_metaObject[4];
extern "C" int g_beNDMWStatusSelectE0_metaObject[4];
extern "C" int g_beNDMWStatusSelect01_metaObject[4];
extern "C" int g_beNDMWStatusSelect00_metaObject[4];
extern "C" int g_beNDMWWindowSelect_metaObject[4];

void Gap__Bec__beNDMWWindowSelect__vfunc_21(beNDMWWindowSelectVTable *arg0) {
    /* matching construct: typed view of the dummy-virtual receiver; data is reached only through s. */
    beNDMWWindowSelect *s = (beNDMWWindowSelect *)arg0;
    float sp30[3];
    int i;
    igDataList *t;
    switch (s->_st0) {
    case 0:
        arg0->v22();
        beMessenger_SelectReceivers(s->_messenger, DAT_0051a918, s->_infoName, s->_playerNo);
        beMessenger_AppendInt(s->_messenger, s->_selectMax);
        beMessenger_AppendInt(s->_messenger, s->_startPoint);
        /* _offsetPos is an igVec3f (three floats); the reflected header declares the words as int. */
        sp30[0] = ((float *)s->_offsetPos)[0];
        sp30[1] = ((float *)s->_offsetPos)[1];
        sp30[2] = ((float *)s->_offsetPos)[2];
        beMessenger_AppendVec3(s->_messenger, sp30);
        if (s->_isNoCancel != 0) {
            beMessenger_AppendString(s->_messenger, DAT_0051a928);
        }
        t = *(igDataList **)&s->_decideList;
        if (t != 0) {
            i = 0;
            if (0 < t->_count) {
                do {
                    beMessenger_AppendBool(s->_messenger, ((unsigned char *)(((igDataList *)s->_decideList)->_data + i))[0] /* matching construct: int _data + i keeps retail addu operand order */);
                    i++;
                } while (i < ((igDataList *)s->_decideList)->_count);
            }
        }
        beMessenger_DispatchSelected(s->_messenger, DAT_0051a938);
        s->_st0 = s->_st0 + 1;
        s->_st3 = 0;
        s->_st2 = 0;
        s->_st1 = 0;
    case 1:
        beMessenger_SendNamed(s->_messenger, DAT_0051a918, s->_infoName, s->_playerNo, DAT_0051a948);
        ((beNDMWWindow *)s->_mother)->_retCode = beMessenger_GetInt(s->_messenger, 0);
        beMessenger_SendNamed(s->_messenger, DAT_0051a918, s->_infoName, s->_playerNo, DAT_0051a958);
        if ((beMessenger_GetBool(s->_messenger, 0) & 0xFF) == 0) {
            break;
        }
        s->_st0 = s->_st0 + 1;
        s->_st3 = 0;
        s->_st2 = 0;
        s->_st1 = 0;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(arg0);
        beNDMWWindow_ClearQueuedText(arg0);
        s->_st0 = s->_st0 + 1;
        s->_st3 = 0;
        s->_st2 = 0;
        s->_st1 = 0;
    case 3:
        if (beNDMWWindow_PollCloseComplete(arg0) != 0) {
            s->_isRun = 0;
        }
        break;
    case 4:
        if (beNDMWWindowSelect_CanRequestFO2TOP((beNDMWWindowSelect *)arg0)) {
            beMessenger_SelectReceivers(s->_messenger, DAT_0051a918, s->_infoName, s->_playerNo);
            beMessenger_AppendInt(s->_messenger, s->_selectMax);
            t = *(igDataList **)&s->_decideList;
            if (t != 0) {
                i = 0;
                if (0 < t->_count) {
                    do {
                        beMessenger_AppendBool(s->_messenger, ((unsigned char *)(((igDataList *)s->_decideList)->_data + i))[0] /* matching construct: int _data + i keeps retail addu operand order */);
                        i++;
                    } while (i < ((igDataList *)s->_decideList)->_count);
                }
            }
            beMessenger_DispatchSelected(s->_messenger, DAT_0051a960);
            beMessenger_SendNamed(s->_messenger, DAT_0051a918, s->_infoName, s->_playerNo, DAT_0051a948);
            ((beNDMWWindow *)s->_mother)->_retCode = beMessenger_GetInt(s->_messenger, 0);
        }
        s->_st0 = 1;
        s->_st3 = 0;
        s->_st2 = 0;
        s->_st1 = 0;
        break;
    }
}

bool beNDMWWindowSelect_CanRequestFO2TOP(beNDMWWindowSelect *self){
    beMessenger_SendNamed(self->_messenger,D_0051a918,self->_infoName,self->_playerNo,D_0051a968);
    return !beMessenger_GetBool(self->_messenger,0);
}

void Gap__Bec__beNDMWStatusSelect00__vfunc_22(Sh *arg0) {
    const char *t;
    const char *old;
    beNDMWWindow_PresentModelAtOrigin(arg0, DAT_0051a978, 0, DAT_0051a988, DAT_0051a998);
    INTERN_APPEND(arg0->f60, DAT_0051a9a8)
    INTERN_APPEND(arg0->f64, DAT_0051a9b8)
    INTERN_APPEND(arg0->f60, DAT_0051a9a8)
    INTERN_APPEND(arg0->f64, DAT_0051a9c0)
    INTERN_APPEND(arg0->f60, DAT_0051a9a8)
    INTERN_APPEND(arg0->f64, DAT_0051a9c8)
    beNDMWWindow_RunMessageScript(arg0, DAT_0051a9d0, 0xF);
    if (((void * *)g_stringPool)[0] == 0) {
        void *pool = ((void *)FUN_002eb010(0x10));
        if (pool != 0) pool = ((void *)StringPool_Construct(pool));
        ((void * *)g_stringPool)[0] = pool;
    }
    t = StringPool_Intern(((void * *)g_stringPool)[0], (const char *)DAT_0051a9e0);
    old = arg0->f80;
    if (old != 0) {
        int *hd = (int *)old - 2;
        int cnt = ((int *)old)[-1] - 1;
        ((int *)old)[-1] = cnt;
        if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd);
    }
    arg0->f80 = t;
    arg0->f84 = 3;
    arg0->f88 = 0xC2A60000;
    arg0->f92 = 0x43510000;
    arg0->f96 = 0;
    arg0->f104 = 0;
}

void Gap__Bec__beNDMWStatusSelect01__vfunc_22(beNDMWStatusSelect01 *arg0) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    int *temp_a0;
    char *temp_s1;

    {
    /* the model name to present: empty unless the entry code selects one */
    StringRef name(0);
    switch (arg0->_entCode) {
    case 0x1F:
    case 0x5B:
        if (g_stringPool[0] == 0) {
            var_v0 = FUN_002eb010(0x10);
            if (var_v0 != 0) {
                var_v0 = StringPool_Construct(var_v0);
            }
            g_stringPool[0] = var_v0;
        }
        name.Assign(((char *)StringPool_Intern(g_stringPool[0], &DAT_0051a9f0[0])));
        arg0->_selectMax = 3;
        break;
    case 0x3D:
        if (g_stringPool[0] == 0) {
            var_v0 = FUN_002eb010(0x10);
            if (var_v0 != 0) {
                var_v0 = StringPool_Construct(var_v0);
            }
            g_stringPool[0] = var_v0;
        }
        name.Assign(((char *)StringPool_Intern(g_stringPool[0], &DAT_0051aa08[0])));
        arg0->_selectMax = 4;
        break;
    }
    beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051a978[0], 0, name.p, &DAT_0051a998[0]);
    }
    FUN_003f5410(arg0, &DAT_0051aa18[0], &DAT_0051aa28[0], &DAT_0051aa30[0], &DAT_0051aa38[0]);
    FUN_003f5410(arg0, &DAT_0051aa40[0], &DAT_0051a9b8[0], &DAT_0051aa30[0], &DAT_0051aa38[0]);
    FUN_003f5410(arg0, &DAT_0051aa40[0], &DAT_0051a9c0[0], &DAT_0051aa30[0], &DAT_0051aa38[0]);
    FUN_003f5410(arg0, &DAT_0051aa40[0], &DAT_0051a9c8[0], &DAT_0051aa30[0], &DAT_0051aa38[0]);
    FUN_003f5410(arg0, &DAT_0051aa40[0], &DAT_0051aa50[0], &DAT_0051aa30[0], &DAT_0051aa38[0]);
    if (arg0->_entCode > 0) {
        beNDMWWindow_RunMessageScript(arg0, &DAT_0051a9d0[0], arg0->_entCode);
    }
    if (g_stringPool[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        g_stringPool[0] = var_v0;
    }
    temp_s1 = ((char *)StringPool_Intern(g_stringPool[0], &DAT_0051a9e0[0]));
    temp_a0 = (int *)arg0->_infoName;
    if (temp_a0 != 0) {
        temp_a1 = temp_a0 - 2;
        temp_v1 = temp_a0[-1] - 1;
        temp_a0[-1] = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    arg0->_infoName = (int)temp_s1;
    arg0->_offsetPos[0] = -83.0f;
    arg0->_offsetPos[1] = 172.0f;
    arg0->_offsetPos[2] = 0.0f;
    arg0->_isNoCancel = 0;
}

void Gap__Bec__beNDMWStatusSelectE0__vfunc_22(beNDMWStatusSelectE0 *arg0) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    int *temp_a0;
    int *temp_s0;

    FUN_003f5410(arg0, &DAT_0051aa18[0], &DAT_0051aa28[0], &DAT_0051aa30[0], &DAT_0051aa38[0]);
    FUN_003f5410(arg0, &DAT_0051aa18[0], &DAT_0051a9b8[0], &DAT_0051aa30[0], &DAT_0051aa38[0]);
    FUN_003f5410(arg0, &DAT_0051aa18[0], &DAT_0051a9c0[0], &DAT_0051aa30[0], &DAT_0051aa38[0]);
    FUN_003f5410(arg0, &DAT_0051aa18[0], &DAT_0051a9c8[0], &DAT_0051aa30[0], &DAT_0051aa38[0]);
    if (arg0->_entCode > 0) {
        beNDMWWindow_RunMessageScript(arg0, &DAT_0051a9d0[0], arg0->_entCode);
    }
    if (g_stringPool[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        g_stringPool[0] = var_v0;
    }
    temp_s0 = ((int *)StringPool_Intern(g_stringPool[0], &DAT_0051aa58[0]));
    temp_a0 = (int *)arg0->_infoName;
    if (temp_a0 != 0) {
        temp_a1 = temp_a0 - 2;
        temp_v1 = temp_a0[-1] - 1;
        temp_a0[-1] = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    arg0->_infoName = (int)temp_s0;
    arg0->_offsetPos[0] = 0;
    arg0->_offsetPos[1] = 0;
    arg0->_offsetPos[2] = 0;
    arg0->_startPoint = 0;
    arg0->_isNoCancel = 0;
}

void Gap__Bec__beNDMWStatusSelectE1__vfunc_22(beNDMWStatusSelectE1 *arg0) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    int *temp_a0;
    int *temp_s0;

    if (g_stringPool[0] == 0) {
        var_v0 = FUN_002eb010(0x10);
        if (var_v0 != 0) {
            var_v0 = StringPool_Construct(var_v0);
        }
        g_stringPool[0] = var_v0;
    }
    temp_s0 = (int *)StringPool_Intern(g_stringPool[0], &DAT_0051aa68[0]);
    temp_a0 = (int *)arg0->_infoName;
    if (temp_a0 != 0) {
        temp_a1 = temp_a0 - 2;
        temp_v1 = temp_a0[-1] - 1;
        temp_a0[-1] = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
    }
    arg0->_infoName = (int)temp_s0;
    arg0->_isNoCancel = 0;
}

int Gap__Bec__beNDMWStatusSelectE1__vfunc_20(void)
{
    return g_beNDMWStatusSelectE1_metaObject[0];
}

int Gap__Bec__beNDMWStatusSelectE0__vfunc_20(void)
{
    return g_beNDMWStatusSelectE0_metaObject[0];
}

int Gap__Bec__beNDMWStatusSelect01__vfunc_20(void)
{
    return g_beNDMWStatusSelect01_metaObject[0];
}

int Gap__Bec__beNDMWStatusSelect00__vfunc_20(void)
{
    return g_beNDMWStatusSelect00_metaObject[0];
}

int Gap__Bec__beNDMWWindowSelect__vfunc_20(void)
{
    return g_beNDMWWindowSelect_metaObject[0];
}

