#include "dw4/reflected.h"
#define INTERN_APPEND(field, text) { \
    const char *tok; \
    if ((text) == 0) { \
        tok = 0; \
    } else { \
        if (((void * *)DAT_00586f20)[0] == 0) { \
            void *pool = FUN_002eb010(0x10); \
            if (pool != 0) pool = StringPool_Construct(pool); \
            ((void * *)DAT_00586f20)[0] = pool; \
        } \
        tok = StringPool_Intern(((void * *)DAT_00586f20)[0], (const char *)(text)); \
    } \
    StringRef held(tok); \
    StringList_AppendRetained(field, (const StringRef &)held); }
#define INTERN_APPEND_440a20(field, text) { \
    void *tok; \
    if ((text) == 0) { tok = (void *)0; } else { \
        if (DAT_00586f20[0] == 0) { int pool = ((int)FUN_002eb010(0x10)); if (pool != 0) { pool = ((int)StringPool_Construct(pool)); } DAT_00586f20[0] = pool; } \
        tok = ((void *)StringPool_Intern(DAT_00586f20[0], (text))); } \
    StringList_AppendRetained(field, StringRef(tok)); }

class StringRef;
extern "C" void * FUN_002eb010(...);
extern "C" int StringChunk_ReleaseHeader(...);
extern "C" void * StringPool_Construct(...);
extern "C" const char * StringPool_Intern(...);
extern "C" int beNDMWWindow_RunMessageScript(...);
extern "C" int beNDMWWindow_PresentModelAtOrigin(...);
extern "C" int FUN_003f5410(...);
extern "C" int beMessenger_AppendBool(...);
extern "C" int beMessenger_AppendInt(...);
extern "C" int beMessenger_DispatchSelected(...);
extern "C" int beMessenger_SelectGroup(...);
extern "C" int beMessenger_AppendString(...);
extern "C" void beMessenger_AppendVec3(int, int *);
extern "C" int beMessenger_GetObject(int, int);
extern "C" void sprintf(...);
extern "C" int strlen(char *);
extern "C" int Gap__Bec__beNDMWShopSelectB0__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopSelectA0__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopSelect52__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopSelect34__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopSelect11__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopSelect03__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopSelect02__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopSelect01__vfunc_20(void);
extern "C" int Gap__Bec__beNDMWShopSelect00__vfunc_20(void);
extern "C" int DAT_0051c488[4];
extern "C" int DAT_0051c498[4];
extern "C" int DAT_0051c4a0[4];
extern "C" int DAT_0051c4b0[4];
extern "C" int DAT_00586f20[4];
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    char *p;
    StringRef(int s) : p((char *)s) {}
    StringRef(const char *s) : p((char *)s) {}
    StringRef(void *s) : p((char *)s) {}
    StringRef(int s, int retain) : p((char *)s) { char *t = p; if (t) ((int *)t)[-1] = ((int *)t)[-1] + 1; }
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(int, const StringRef &);
struct Str { static inline int intern(int *s) {
    int ref;
    int pool;
    if (s == 0) {
        ref = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            pool = ((int)FUN_002eb010(16));
            if (pool)
                pool = ((int)StringPool_Construct(pool));
            DAT_00586f20[0] = pool;
        }
        ref = ((int)StringPool_Intern(DAT_00586f20[0], s));
    }
    return ref;
}
static inline void release(int ref) {
    int *header;
    int count;
    if (ref) {
        header = (int *)(ref - 8);
        count = *(int *)(ref - 4) - 1;
        *(int *)(ref - 4) = count;
        if (!count)
            StringChunk_ReleaseHeader(*header, header);
    }
} };
extern "C" void Gap__Bec__beNDMWShopSelect00__vfunc_22(beNDMWShopSelect00 *arg0);
extern "C" int DAT_0051c4c0[4];
extern "C" int DAT_0051c4c8[4];
extern "C" int DAT_0051c4d0[4];
extern "C" void Gap__Bec__beNDMWShopSelect01__vfunc_22(beNDMWShopSelect01 *arg0);
extern "C" int DAT_0051c530[4];
extern "C" int DAT_0051c5a8[4];
extern "C" int DAT_0051c5b0[4];
extern "C" void Gap__Bec__beNDMWShopSelect03__vfunc_22(beNDMWShopSelect03 *arg0);
extern "C" int DAT_0051c500[4];
extern "C" int DAT_0051c540[4];
extern "C" int DAT_0051c5c0[4];
extern "C" int DAT_0051c5d0[4];
extern "C" int DAT_0051c5e8[4];
extern "C" int DAT_0051c5f8[4];
extern "C" int DAT_0051c600[4];
extern "C" int DAT_0051c610[4];
extern "C" int DAT_0051c620[4];
extern "C" int DAT_0051c630[4];
extern "C" int DAT_0051c638[4];
extern "C" int DAT_0051c640[4];
extern "C" int DAT_0051c648[4];
extern "C" int DAT_0051c650[4];
extern "C" int DAT_0051c660[4];
extern "C" int DAT_0051c668[4];
extern "C" int DAT_0051c670[4];
extern "C" int DAT_0051c680[4];
struct StringRefHelpers { static inline int intern(int *s) {
    int ref;
    int pool;
    if (s == 0) {
        ref = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            pool = ((int)FUN_002eb010(16));
            if (pool)
                pool = ((int)StringPool_Construct(pool));
            DAT_00586f20[0] = pool;
        }
        ref = ((int)StringPool_Intern(DAT_00586f20[0], s));
    }
    return ref;
}
static inline void release(int ref) {
    int *header;
    int count;
    if (ref) {
        header = (int *)(ref - 8);
        count = *(int *)(ref - 4) - 1;
        *(int *)(ref - 4) = count;
        if (!count)
            StringChunk_ReleaseHeader(*header, header);
    }
} };
extern "C" void Gap__Bec__beNDMWShopSelect11__vfunc_22(beNDMWShopSelect11 *arg0);
typedef struct PropertyRecord {
    char pad[12];
    int value;
} PropertyRecord;
extern "C" PropertyRecord *igProperty_GetRecord(int, const char *);
extern "C" const char DAT_0051c508[];
extern "C" const char DAT_0051c6d8[];
extern "C" int DAT_0051c6e0[4];
extern "C" int DAT_0051c6e8[4];
extern "C" int DAT_0051c6f0[4];
extern "C" const char DAT_0051c6f8[];
extern "C" int DAT_0051c700[4];
/* DEFAULTCOLOR */

typedef struct NameTab { const char *a[7]; } NameTab;
typedef struct LimitTab { int a[7]; } LimitTab;
extern "C" const NameTab DAT_004cfad0;
extern "C" const LimitTab DAT_004cfaf0;
extern "C" const NameTab DAT_004cfb10;
extern "C" void beNDMWShopSelect11_RefreshStatCosts(beNDMWShopSelect11 *self);
extern "C" int DAT_0051c710[4];
extern "C" char DAT_0051c720[];
extern "C" int DAT_0051c730[4];
extern "C" int DAT_0051c738[4];
extern "C" char DAT_0051c740[];
extern "C" int DAT_0051c750[4];
extern "C" int DAT_0051c760[4];
extern "C" int DAT_0051c770[4];
extern "C" void Gap__Bec__beNDMWShopSelect34__vfunc_22(beNDMWShopSelect34 *arg0);
extern "C" char DAT_0051c780[];
extern "C" int DAT_0051c788[4];
extern "C" char DAT_0051c790[];
extern "C" void FUN_00440110(beNDMWShopCtrlEditBit *arg0, int arg1, int arg2);
extern "C" int DAT_0051c798[4];
extern "C" int DAT_0051c7a0[4];
extern "C" int DAT_0051c7a8[4];
extern "C" int DAT_0051c7b0[4];
extern "C" int DAT_0051c7b8[4];
extern "C" int DAT_0051c7c0[4];
extern "C" void FUN_004402e0(beNDMWWindow *arg0, int arg1, unsigned int arg2, int *arg3);
extern "C" int DAT_0051c7f0[4];
extern "C" void Gap__Bec__beNDMWShopSelect52__vfunc_22(beNDMWShopSelect52 *arg0);
extern "C" int DAT_0051c800[4];
extern "C" int DAT_0051c810[4];
extern "C" int DAT_0051c818[4];
extern "C" int DAT_0051c828[4];
extern "C" int DAT_0051c838[4];
extern "C" void Gap__Bec__beNDMWShopSelectA0__vfunc_22(beNDMWShopSelectA0 *arg0);
/* _decideList target: count at +8, byte flags at +16. */
typedef struct DecideFlagList { char p0[8]; int count; char p12[4]; unsigned char *data; } DecideFlagList;
typedef struct { int lo; int hi; } IntPair;
extern "C" IntPair DAT_004cfb30[4];
extern "C" int DAT_0051c848[4];
extern "C" void Gap__Bec__beNDMWShopSelectB0__vfunc_22(beNDMWShopSelectB0 *arg0);
extern "C" int g_beNDMWShopSelectB0_metaObject[4];
extern "C" int g_beNDMWShopSelectA0_metaObject[4];
extern "C" int g_beNDMWShopSelect52_metaObject[4];
extern "C" int g_beNDMWShopSelect34_metaObject[4];
extern "C" int g_beNDMWShopSelect11_metaObject[4];
extern "C" int g_beNDMWShopSelect03_metaObject[4];
extern "C" int g_beNDMWShopSelect02_metaObject[4];
extern "C" int g_beNDMWShopSelect01_metaObject[4];
extern "C" int g_beNDMWShopSelect00_metaObject[4];

void Gap__Bec__beNDMWShopSelect00__vfunc_22(beNDMWShopSelect00 *arg0) {
    int pool;
    int ref;
    int old;
    int obj;
    if (arg0->_entCode > 0) {
        { int tok = Str::intern(&DAT_0051c488[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
        obj = arg0->_panelName;
        if (obj == 0) {
            { int tok = Str::intern(&DAT_0051c498[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
        } else {
            StringList_AppendRetained(arg0->_textCloseNameList, StringRef(obj, 1));
        }
        beNDMWWindow_RunMessageScript(arg0, &DAT_0051c4a0[0], arg0->_entCode);
    }
    if (DAT_00586f20[0] == 0) {
        pool = ((int)FUN_002eb010(16));
        if (pool)
            pool = ((int)StringPool_Construct(pool));
        DAT_00586f20[0] = pool;
    }
    ref = ((int)StringPool_Intern(DAT_00586f20[0], &DAT_0051c4b0[0]));
    old = arg0->_infoName;
    Str::release(old);
    arg0->_infoName = ref;
    arg0->_selectMax = 1;
    arg0->_offsetPos[0] = 0;
    arg0->_offsetPos[1] = 0;
    arg0->_offsetPos[2] = 0;
    arg0->_startPoint = 0;
    arg0->_isNoCancel = 0;
}

void Gap__Bec__beNDMWShopSelect01__vfunc_22(beNDMWShopSelect01 *arg0) {
    const char *sp4C;
    const char *sp48;
    const char *u1, *u2, *u3, *u4;
    const char *t4C, *t48;
    const char *old;
    const char *n;
    switch (arg0->_entCode) {
    case 0x48B: case 0x48E: case 0x493: case 0x4E7: case 0x4EA: case 0x4F8: case 0x54B:
    case 0x614: case 0x678: case 0x6DC: case 0x740: case 0x61A: case 0x5AD: case 0x7AA:
        INTERN_APPEND(arg0->_textCloseTypeList, DAT_0051c488)
        INTERN_APPEND(arg0->_textCloseNameList, DAT_0051c498)
        INTERN_APPEND(arg0->_textCloseTypeList, DAT_0051c488)
        INTERN_APPEND(arg0->_textCloseNameList, DAT_0051c4c0)
        beNDMWWindow_RunMessageScript(arg0, DAT_0051c4a0, arg0->_entCode);
        arg0->_selectMax = 2;
        break;
    case 0x47E: case 0x546: case 0x60E: case 0x672: case 0x6D6: case 0x73A: case 0x79E:
        INTERN_APPEND(arg0->_textCloseTypeList, DAT_0051c488)
        INTERN_APPEND(arg0->_textCloseNameList, DAT_0051c498)
        INTERN_APPEND(arg0->_textCloseTypeList, DAT_0051c488)
        INTERN_APPEND(arg0->_textCloseNameList, DAT_0051c4c0)
        INTERN_APPEND(arg0->_textCloseTypeList, DAT_0051c488)
        INTERN_APPEND(arg0->_textCloseNameList, DAT_0051c4c8)
        beNDMWWindow_RunMessageScript(arg0, DAT_0051c4a0, arg0->_entCode);
        arg0->_selectMax = 3;
        break;
    }
    if (((void * *)DAT_00586f20)[0] == 0) {
        void *pool = FUN_002eb010(0x10);
        if (pool != 0) pool = StringPool_Construct(pool);
        ((void * *)DAT_00586f20)[0] = pool;
    }
    n = StringPool_Intern(((void * *)DAT_00586f20)[0], (const char *)DAT_0051c4d0);
    old = (const char *)arg0->_infoName;
    if (old != 0) {
        int *hd = (int *)old - 2;
        int cnt = ((int *)old)[-1] - 1;
        ((int *)old)[-1] = cnt;
        if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd);
    }
    arg0->_infoName = (int)n;
    arg0->_offsetPos[0] = 0;
    arg0->_offsetPos[1] = 0;
    arg0->_offsetPos[2] = 0;
    arg0->_isNoCancel = 0;
}

void Gap__Bec__beNDMWShopSelect03__vfunc_22(beNDMWShopSelect03 *arg0) {
    const char *old;
    const char *n;
    if (arg0->_entCode > 0) {
        INTERN_APPEND(arg0->_textCloseTypeList, DAT_0051c530)
        INTERN_APPEND(arg0->_textCloseNameList, DAT_0051c5a8)
        beNDMWWindow_RunMessageScript(arg0, DAT_0051c4a0, arg0->_entCode);
    }
    if (((void * *)DAT_00586f20)[0] == 0) {
        void *pool = FUN_002eb010(0x10);
        if (pool != 0) pool = StringPool_Construct(pool);
        ((void * *)DAT_00586f20)[0] = pool;
    }
    n = StringPool_Intern(((void * *)DAT_00586f20)[0], (const char *)DAT_0051c5b0);
    old = (const char *)arg0->_infoName;
    if (old != 0) {
        int *hd = (int *)old - 2;
        int cnt = ((int *)old)[-1] - 1;
        ((int *)old)[-1] = cnt;
        if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd);
    }
    arg0->_infoName = (int)n;
    arg0->_selectMax = 1;
    arg0->_offsetPos[0] = 0;
    arg0->_offsetPos[1] = 0;
    arg0->_offsetPos[2] = 0;
    arg0->_startPoint = 0;
    arg0->_isNoCancel = 0;
}

void Gap__Bec__beNDMWShopSelect11__vfunc_22(beNDMWShopSelect11 *arg0) {
    int pool;
    int ref;
    int old;
    beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051c5c0[0], 0, &DAT_0051c5d0[0], &DAT_0051c5e8[0]);
    { int tok = StringRefHelpers::intern(&DAT_0051c488[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c5f8[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    beNDMWWindow_RunMessageScript(arg0, &DAT_0051c4a0[0], 0x481);
    { int tok = StringRefHelpers::intern(&DAT_0051c600[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c498[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c610[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c4c0[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    beNDMWWindow_RunMessageScript(arg0, &DAT_0051c4a0[0], 0x44D);
    { int tok = StringRefHelpers::intern(&DAT_0051c620[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c498[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c620[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c4c0[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c620[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c4c8[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c620[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c630[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c620[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c638[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c620[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c640[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c620[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c648[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    beNDMWWindow_RunMessageScript(arg0, &DAT_0051c4a0[0], 0x44F);
    FUN_003f5410(arg0, &DAT_0051c650[0], &DAT_0051c498[0], &DAT_0051c660[0], &DAT_0051c668[0]);
    FUN_003f5410(arg0, &DAT_0051c650[0], &DAT_0051c4c0[0], &DAT_0051c660[0], &DAT_0051c668[0]);
    FUN_003f5410(arg0, &DAT_0051c650[0], &DAT_0051c4c8[0], &DAT_0051c660[0], &DAT_0051c668[0]);
    FUN_003f5410(arg0, &DAT_0051c650[0], &DAT_0051c630[0], &DAT_0051c660[0], &DAT_0051c668[0]);
    FUN_003f5410(arg0, &DAT_0051c650[0], &DAT_0051c638[0], &DAT_0051c660[0], &DAT_0051c668[0]);
    FUN_003f5410(arg0, &DAT_0051c650[0], &DAT_0051c640[0], &DAT_0051c660[0], &DAT_0051c668[0]);
    FUN_003f5410(arg0, &DAT_0051c650[0], &DAT_0051c648[0], &DAT_0051c660[0], &DAT_0051c668[0]);
    FUN_003f5410(arg0, &DAT_0051c488[0], &DAT_0051c498[0], &DAT_0051c660[0], &DAT_0051c540[0]);
    beMessenger_SelectGroup(arg0->_messenger, &DAT_0051c500[0]);
    beMessenger_AppendInt(arg0->_messenger, arg0->_playerNo);
    beMessenger_AppendBool(arg0->_messenger, 0);
    beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051c670[0]);
    beNDMWShopSelect11_RefreshStatCosts(arg0);
    beNDMWWindow_RunMessageScript(arg0, &DAT_0051c4a0[0], arg0->_entCode + 0x482);
    if (DAT_00586f20[0] == 0) {
        pool = ((int)FUN_002eb010(16));
        if (pool)
            pool = ((int)StringPool_Construct(pool));
        DAT_00586f20[0] = pool;
    }
    ref = ((int)StringPool_Intern(DAT_00586f20[0], &DAT_0051c680[0]));
    old = arg0->_infoName;
    StringRefHelpers::release(old);
    arg0->_infoName = ref;
    arg0->_selectMax = 7;
    arg0->_offsetPos[0] = -121.0f;
    arg0->_offsetPos[1] = 128.0f;
    arg0->_offsetPos[2] = 0.0f;
    arg0->_startPoint = arg0->_entCode;
    arg0->_isNoCancel = 0;
}

void beNDMWShopSelect11_RefreshStatCosts(beNDMWShopSelect11 *self)
{
    int col[3];
    char buf[16];
    NameTab props;
    LimitTab limits;
    NameTab fonts;
    int *c1;
    int *c2;
    int obj;
    int i;
    int cur;
    const char **pp;
    int *pl;
    const char **pf;

    beMessenger_SelectGroup(self->_messenger, ((const char *)DAT_0051c500));
    beMessenger_AppendInt(self->_messenger, self->_playerNo);
    beMessenger_DispatchSelected(self->_messenger, DAT_0051c508);
    obj = beMessenger_GetObject(self->_messenger, 0);
    props = DAT_004cfad0;
    limits = DAT_004cfaf0;
    fonts = DAT_004cfb10;
    pp = props.a;
    pl = limits.a;
    pf = fonts.a;
    i = 0;
    c1 = &col[1];
    c2 = &col[2];
    do {
        cur = igProperty_GetRecord(obj, *pp)->value;
        {
        int r = (cur - 45) % 5;
        int q = (cur - 45 - r) / 5 + (r ? 1 : 0);
        if (q > 400)
            q = 400;
        else if (q < 0)
            q = 1;
        else
            q = (int)q;
        if (cur >= *pl)
            sprintf(buf, DAT_0051c6d8, q);
        else
            sprintf(buf, ((const char *)DAT_0051c6e0), q);
        }
        beMessenger_SelectGroup(self->_messenger, ((const char *)DAT_0051c6e8));
        beMessenger_AppendString(self->_messenger, ((const char *)DAT_0051c650));
        beMessenger_AppendString(self->_messenger, *pf);
        beMessenger_AppendString(self->_messenger, buf);
        beMessenger_DispatchSelected(self->_messenger, ((const char *)DAT_0051c6f0));
        beMessenger_SelectGroup(self->_messenger, ((const char *)DAT_0051c6e8));
        beMessenger_AppendString(self->_messenger, ((const char *)DAT_0051c620));
        beMessenger_AppendString(self->_messenger, *pf);
        if (cur >= *pl) {
            col[0] = 0x3F666666;
            *c1 = 0x3ECCCCCD;
            *c2 = 0x3E4CCCCD;
            beMessenger_AppendVec3(self->_messenger, col);
            beMessenger_DispatchSelected(self->_messenger, DAT_0051c6f8);
        } else {
            beMessenger_DispatchSelected(self->_messenger, ((const char *)DAT_0051c700));
        }
        i++; pp++; pl++; pf++;
    } while (i < 7);
}

void Gap__Bec__beNDMWShopSelect34__vfunc_22(beNDMWShopSelect34 *arg0) {
    int sp30[4];
    int i;
    const char *n;
    const char *old;
    i = 0;
    do {
        switch (arg0->_entCode) {
        case 3:
            sprintf(sp30, DAT_0051c710, i);
            beMessenger_SelectGroup(arg0->_messenger, DAT_0051c6e8);
            beMessenger_AppendString(arg0->_messenger, ((int *)DAT_0051c720));
            beMessenger_AppendString(arg0->_messenger, sp30);
            beMessenger_AppendString(arg0->_messenger, DAT_0051c730);
            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051c738);
            break;
        default:
            sprintf(sp30, DAT_0051c710, i);
            beMessenger_SelectGroup(arg0->_messenger, DAT_0051c6e8);
            beMessenger_AppendString(arg0->_messenger, ((int *)DAT_0051c740));
            beMessenger_AppendString(arg0->_messenger, sp30);
            beMessenger_AppendString(arg0->_messenger, DAT_0051c730);
            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051c738);
            sprintf(sp30, DAT_0051c750, i);
            beMessenger_SelectGroup(arg0->_messenger, DAT_0051c6e8);
            beMessenger_AppendString(arg0->_messenger, ((int *)DAT_0051c740));
            beMessenger_AppendString(arg0->_messenger, sp30);
            beMessenger_AppendString(arg0->_messenger, DAT_0051c730);
            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051c738);
            sprintf(sp30, DAT_0051c760, i);
            beMessenger_SelectGroup(arg0->_messenger, DAT_0051c6e8);
            beMessenger_AppendString(arg0->_messenger, ((int *)DAT_0051c740));
            beMessenger_AppendString(arg0->_messenger, sp30);
            beMessenger_AppendString(arg0->_messenger, DAT_0051c730);
            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051c738);
            break;
        }
        i++;
    } while (i < 7);
    if (((void * *)DAT_00586f20)[0] == 0) {
        void *pool = FUN_002eb010(0x10);
        if (pool != 0) pool = StringPool_Construct(pool);
        ((void * *)DAT_00586f20)[0] = pool;
    }
    n = StringPool_Intern(((void * *)DAT_00586f20)[0], (const char *)DAT_0051c770);
    old = (const char *)arg0->_infoName;
    if (old != 0) {
        int *hd = (int *)old - 2;
        int cnt = ((int *)old)[-1] - 1;
        ((int *)old)[-1] = cnt;
        if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd);
    }
    arg0->_infoName = (int)n;
    arg0->_selectMax = 7;
    arg0->_startPoint = 6;
    arg0->_isNoCancel = 0;
    switch (arg0->_entCode) {
    case 2:
    case 0:
        *(unsigned *)&arg0->_offsetPos[0] = 0xC1A00000;
        *(unsigned *)&arg0->_offsetPos[1] = 0x430A0000;
        arg0->_offsetPos[2] = 0;
        break;
    case 1:
        *(unsigned *)&arg0->_offsetPos[0] = 0xC1A00000;
        *(unsigned *)&arg0->_offsetPos[1] = 0xBF800000;
        arg0->_offsetPos[2] = 0;
        break;
    case 3:
        *(unsigned *)&arg0->_offsetPos[0] = 0x43130000;
        *(unsigned *)&arg0->_offsetPos[1] = 0xC0000000;
        arg0->_offsetPos[2] = 0;
        break;
    }
}

void FUN_00440110(beNDMWShopCtrlEditBit *arg0, int arg1, int arg2) {
    char buf[16];
    char tmp[12];
    char ch[2];
    int *tbl;
    int n;
    int i;
    int j;

    switch (arg1) {
    default:
        tbl = DAT_0051c750;
        break;
    case 1:
        tbl = DAT_0051c710;
        break;
    }
    i = 0;
    do {
        sprintf(buf, tbl, i);
        beMessenger_SelectGroup(arg0->_messenger, DAT_0051c6e8);
        beMessenger_AppendString(arg0->_messenger, ((const char *)DAT_0051c740));
        beMessenger_AppendString(arg0->_messenger, buf);
        beMessenger_AppendString(arg0->_messenger, ((const char *)DAT_0051c780));
        beMessenger_DispatchSelected(arg0->_messenger, DAT_0051c788);
        i += 1;
    } while (i < 7);
    sprintf(tmp, DAT_0051c6e0, arg2);
    n = strlen(tmp);
    j = n - 1;
    ch[1] = 0;
    if (j > -1) {
        do {
            sprintf(buf, tbl, j);
            ch[0] = tmp[(n - 1) - j];
            beMessenger_SelectGroup(arg0->_messenger, DAT_0051c6e8);
            beMessenger_AppendString(arg0->_messenger, ((const char *)DAT_0051c740));
            beMessenger_AppendString(arg0->_messenger, buf);
            beMessenger_AppendString(arg0->_messenger, ch);
            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051c6f0);
            beMessenger_SelectGroup(arg0->_messenger, DAT_0051c6e8);
            beMessenger_AppendString(arg0->_messenger, ((const char *)DAT_0051c740));
            beMessenger_AppendString(arg0->_messenger, buf);
            beMessenger_AppendString(arg0->_messenger, ((const char *)DAT_0051c790));
            beMessenger_DispatchSelected(arg0->_messenger, DAT_0051c788);
            j -= 1;
        } while (j > -1);
    }
}

void FUN_004402e0(beNDMWWindow *arg0, int arg1, unsigned int arg2, int *arg3) {
    char b70[16];
    char b80[12];
    char c[2];
    char *s1;
    int i, n;
    void *fmt;

    if (arg0->_entCode == 3) {
        s1 = &DAT_0051c720[0];
    } else {
        s1 = &DAT_0051c740[0];
    }
    i = 0;
    do {
        sprintf(b70, arg3, i);
        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051c6e8[0]);
        beMessenger_AppendString(arg0->_messenger, s1);
        beMessenger_AppendString(arg0->_messenger, b70);
        beMessenger_AppendString(arg0->_messenger, &DAT_0051c780[0]);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051c788[0]);
        i++;
    } while (i < 7);
    switch (arg2) {
    case 0: return;
    case 1: sprintf(b80, &DAT_0051c6e0[0], arg1); break;
    case 2: sprintf(b80, &DAT_0051c798[0], arg1); break;
    case 3: sprintf(b80, &DAT_0051c7a0[0], arg1); break;
    case 4: sprintf(b80, &DAT_0051c7a8[0], arg1); break;
    case 5: sprintf(b80, &DAT_0051c7b0[0], arg1); break;
    case 6: sprintf(b80, &DAT_0051c7b8[0], arg1); break;
    case 7: sprintf(b80, &DAT_0051c7c0[0], arg1); break;
    default: return;
    }
    n = strlen(b80);
    i = n - 1;
    c[1] = 0;
    if (i > -1) {
        do {
            sprintf(b70, arg3, i);
            c[0] = b80[(n - 1) - i];
            beMessenger_SelectGroup(arg0->_messenger, &DAT_0051c6e8[0]);
            beMessenger_AppendString(arg0->_messenger, s1);
            beMessenger_AppendString(arg0->_messenger, b70);
            beMessenger_AppendString(arg0->_messenger, c);
            beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051c6f0[0]);
            beMessenger_SelectGroup(arg0->_messenger, &DAT_0051c6e8[0]);
            beMessenger_AppendString(arg0->_messenger, s1);
            beMessenger_AppendString(arg0->_messenger, b70);
            beMessenger_AppendString(arg0->_messenger, &DAT_0051c790[0]);
            beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051c788[0]);
            i--;
        } while (i > -1);
    }
}

void Gap__Bec__beNDMWShopSelect52__vfunc_22(beNDMWShopSelect52 *arg0) {
    int *temp_a1;
    int temp_v1;
    int var_v0;
    char *temp_a0;
    void *temp_s1;
    if (DAT_00586f20[0] == 0) {
        var_v0 = ((int)FUN_002eb010(0x10));
        if (var_v0 != 0) {
            var_v0 = ((int)StringPool_Construct(var_v0));
        }
        DAT_00586f20[0] = var_v0;
    }
    temp_s1 = (void *)(((void *)StringPool_Intern(DAT_00586f20[0], &DAT_0051c7f0[0])));
    temp_a0 = (char *)arg0->_infoName;
    if (temp_a0 != 0) {
        temp_a1 = (int *)(temp_a0 - 8);
        temp_v1 = *(int *)(temp_a0 - 4) - 1;
        *(int *)(temp_a0 - 4) = temp_v1;
        if (temp_v1 == 0) {
            StringChunk_ReleaseHeader(*temp_a1, temp_a1);
        }
        }
    arg0->_infoName = (int)temp_s1;
    arg0->_selectMax = arg0->_entCode;
    arg0->_startPoint = arg0->_entCode - 1;
    arg0->_isNoCancel = 0;
}

void Gap__Bec__beNDMWShopSelectA0__vfunc_22(beNDMWShopSelectA0 *arg0) {
    int pool;
    int ref;
    int old;
    beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051c800[0], 0, &DAT_0051c810[0], &DAT_0051c5e8[0]);
    { int tok = StringRefHelpers::intern(&DAT_0051c818[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c498[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c818[0]); StringList_AppendRetained(arg0->_textCloseTypeList, StringRef(tok)); }
    { int tok = StringRefHelpers::intern(&DAT_0051c4c0[0]); StringList_AppendRetained(arg0->_textCloseNameList, StringRef(tok)); }
    beNDMWWindow_RunMessageScript(arg0, &DAT_0051c4a0[0], 0x7D1);
    FUN_003f5410(arg0, &DAT_0051c828[0], &DAT_0051c498[0], &DAT_0051c660[0], &DAT_0051c730[0]);
    FUN_003f5410(arg0, &DAT_0051c828[0], &DAT_0051c4c0[0], &DAT_0051c660[0], &DAT_0051c730[0]);
    if (DAT_00586f20[0] == 0) {
        pool = ((int)FUN_002eb010(16));
        if (pool)
            pool = ((int)StringPool_Construct(pool));
        DAT_00586f20[0] = pool;
    }
    ref = ((int)StringPool_Intern(DAT_00586f20[0], &DAT_0051c838[0]));
    old = arg0->_infoName;
    StringRefHelpers::release(old);
    arg0->_infoName = ref;
    arg0->_selectMax = 9;
    arg0->_offsetPos[0] = 0;
    arg0->_offsetPos[1] = 0;
    arg0->_offsetPos[2] = 0;
    arg0->_startPoint = 0;
    arg0->_isNoCancel = 0;
}

static inline DecideFlagList *decideList(const beNDMWShopSelectB0 *self) { return (DecideFlagList *)self->_decideList; }

void Gap__Bec__beNDMWShopSelectB0__vfunc_22(beNDMWShopSelectB0 *arg0) {
    int tv1;
    int s1;
    int *a1;
    int *s0;
    void *a0;
    int t;
    int *s3;
    void *s0b;
    INTERN_APPEND_440a20(arg0->_textCloseTypeList, &DAT_0051c488[0])
    INTERN_APPEND_440a20(arg0->_textCloseNameList, &DAT_0051c5f8[0])
    INTERN_APPEND_440a20(arg0->_textCloseTypeList, &DAT_0051c488[0])
    INTERN_APPEND_440a20(arg0->_textCloseNameList, &DAT_0051c498[0])
    INTERN_APPEND_440a20(arg0->_textCloseTypeList, &DAT_0051c488[0])
    INTERN_APPEND_440a20(arg0->_textCloseNameList, &DAT_0051c4c0[0])
    beNDMWWindow_RunMessageScript(arg0, &DAT_0051c4a0[0], 0x625);
    if (arg0->_decideList != 0) {
        IntPair labels = DAT_004cfb30[0];
        s0 = (int *)&labels;
        s1 = 0;
        if (0 < decideList(arg0)->count) {
            do {
                if (((DecideFlagList *)arg0->_decideList)->data[s1] != 0) {
                    s3 = &DAT_0051c700[0];
                } else {
                    s3 = &DAT_0051c848[0];
                }
                beMessenger_SelectGroup(arg0->_messenger, &DAT_0051c6e8[0]);
                beMessenger_AppendString(arg0->_messenger, &DAT_0051c488[0]);
                beMessenger_AppendString(arg0->_messenger, (int *)*s0);
                beMessenger_DispatchSelected(arg0->_messenger, s3);
                s1 = s1 + 1;
                s0 = s0 + 1;
            } while (s1 < ((DecideFlagList *)arg0->_decideList)->count);
        }
    }
    if (DAT_00586f20[0] == 0) {
        t = ((int)FUN_002eb010(0x10));
        if (t != 0) {
            t = ((int)StringPool_Construct(t));
        }
        DAT_00586f20[0] = t;
    }
    s0b = ((void *)StringPool_Intern(DAT_00586f20[0], &DAT_0051c4d0[0]));
    a0 = (void *)arg0->_infoName;
    if (a0 != 0) {
        a1 = (int *)((char *)a0 - 8);
        tv1 = *(int *)((char *)a0 - 4) - 1;
        *(int *)((char *)a0 - 4) = tv1;
        if (tv1 == 0) {
            StringChunk_ReleaseHeader(*a1, a1);
        }
    }
    arg0->_infoName = (int)s0b;
    arg0->_selectMax = 2;
    arg0->_offsetPos[0] = 0;
    arg0->_offsetPos[1] = 0;
    arg0->_offsetPos[2] = 0;
    arg0->_startPoint = 0;
    arg0->_isNoCancel = 0;
}

int Gap__Bec__beNDMWShopSelectB0__vfunc_20(void)
{
    return g_beNDMWShopSelectB0_metaObject[0];
}

int Gap__Bec__beNDMWShopSelectA0__vfunc_20(void)
{
    return g_beNDMWShopSelectA0_metaObject[0];
}

int Gap__Bec__beNDMWShopSelect52__vfunc_20(void)
{
    return g_beNDMWShopSelect52_metaObject[0];
}

int Gap__Bec__beNDMWShopSelect34__vfunc_20(void)
{
    return g_beNDMWShopSelect34_metaObject[0];
}

int Gap__Bec__beNDMWShopSelect11__vfunc_20(void)
{
    return g_beNDMWShopSelect11_metaObject[0];
}

int Gap__Bec__beNDMWShopSelect03__vfunc_20(void)
{
    return g_beNDMWShopSelect03_metaObject[0];
}

int Gap__Bec__beNDMWShopSelect02__vfunc_20(void)
{
    return g_beNDMWShopSelect02_metaObject[0];
}

int Gap__Bec__beNDMWShopSelect01__vfunc_20(void)
{
    return g_beNDMWShopSelect01_metaObject[0];
}

int Gap__Bec__beNDMWShopSelect00__vfunc_20(void)
{
    return g_beNDMWShopSelect00_metaObject[0];
}

