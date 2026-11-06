#include "dw4/reflected.h"
extern "C" {
extern int FUN_002eb010(int);
extern int StringPool_Construct(int);
extern int StringPool_Intern(int, void *);
extern void StringChunk_ReleaseHeader(int, void *);
extern void beNDMWWindow_RunMessageScript(void *, void *, int);
extern int FUN_003f5410(...);
extern int igObject_GetAllocator(void *, ...);
extern int Memory_GetAllocatorBySelector(int);
extern void *FUN_003b4d90(int);
extern void *FUN_003b4790(int);
extern void *FUN_003b4f50(int);
extern void *FUN_003b6940(int);
extern void beNDMWWindow_BindContext(void *, void *, int, int, int);
extern void ObjectList_AppendRetained(int, void *);
extern void igObject_Destroy(void *);
extern void beMessenger_SelectGroup(int, void *);
extern void beMessenger_AppendInt(int, int);
extern void beMessenger_AppendBool(int, int);
extern void beMessenger_AppendString(int, void *);
extern void beMessenger_DispatchSelected(int, void *);
extern int beMessenger_GetObject(int, int);
extern int igProperty_GetRecord(int, void *);
extern int FUN_003a9250(int, void *);
extern int sprintf(...);
extern void beNDMWWindow_PlayQueuedModelClose(void *);
extern void beNDMWWindow_ClearQueuedText(void *);
extern void beNDMWWindow_RequestChildrenClose(void *);
extern int beNDMWWindow_PollCloseComplete(void *);

extern char DAT_0051b220[], DAT_0051b248[], DAT_0051b398[], DAT_0051b3a0[], DAT_0051b3b0[], DAT_0051b3c0[],
    DAT_0051b3c8[], DAT_0051b3d8[], DAT_0051b3e8[], DAT_0051b3f8[], DAT_0051b400[], DAT_0051b408[],
    DAT_0051b418[], DAT_0051b420[], DAT_0051b430[], DAT_0051b438[], DAT_0051b440[], DAT_0051b448[],
    DAT_0051b458[], DAT_0051b460[], DAT_0051b468[], DAT_0051b470[], DAT_0051b480[], DAT_0051b488[],
    DAT_0051b490[], DAT_0051b498[], DAT_0051b4a0[];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void Gap__Bec__beNDMWShopCtrl10__vfunc_21(beNDMWShopCtrl10 *self);
}

struct RefCountedObject { int vt; int rc; };
struct Tbl7 { int v[7]; };
extern Tbl7 DAT_004cf950, DAT_004cf970;

/* Scope holder for a freshly built window: its destructor releases the reference. One class per
 * kind, so each kind gets its own out-of-line destructor. */
template <int kind> struct RP {
    RefCountedObject *p;
    RP(RefCountedObject *x) { p = x; }
    ~RP() { RefCountedObject *o = p; if (o != 0) { o->rc = o->rc - 1; if ((o->rc & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    const char *p;
    StringRef(const char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" void StringList_AppendRetained(int, const StringRef &);

#define APPENDSTR(list, text) { const char *tok; if ((text) == 0) { tok = 0; } else { if (DAT_00586f20[0] == 0) { int pool = FUN_002eb010(0x10); if (pool != 0) pool = StringPool_Construct(pool); DAT_00586f20[0] = pool; } tok = (const char *)StringPool_Intern(DAT_00586f20[0], (void *)(text)); } StringList_AppendRetained(list, StringRef(tok)); }

#define DEREF(o) if (o) { (o)->rc = (o)->rc - 1; if (((unsigned long long)((long long)(o)->rc << 0x29) >> 0x29) == 0) igObject_Destroy(o); }

#define NEWWIN(kind, w, ctor, code) int alloc; int a; alloc = igObject_GetAllocator(self); a = GPR_00554c14 != 0 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]); RP<kind> w((RefCountedObject *)ctor(a)); beNDMWWindow_BindContext(w.p, self, self->_insight, self->_playerNo, code); ObjectList_AppendRetained(self->_subWindow, w.p);

#define INC(l, n) { int ix = n; int cnt; int *dp; int *pp; int nv; dp = (int *)(l)->_data; pp = &dp[ix]; cnt = (l)->_count; nv = *pp + 1; if (cnt != 0 && ix < cnt) *pp = nv; }
#define CEILD(dst, e) { int m = (e); int r = (m - 45) % 5; int q = (m - 45 - r) / 5; dst = q + (r != 0); }
#define CNT ((igObjectList *)self->_subWindow)->_count

#define BUMP(sub) self->_st2 = self->_st2 + 1; self->_st3 = 0;

#define PRICE(rec, key, lim) { }

void Gap__Bec__beNDMWShopCtrl10__vfunc_21(beNDMWShopCtrl10 *self)
{
    Tbl7 names;
    char buf[128];
    Tbl7 arr2;
    switch (self->_st0) {
    default:
        return;
    case 0:
        self->_st0 = ((volatile beNDMWShopCtrl10 *)self)->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        self->_st1 = 0;
        self->_st3 = 0;
        self->_st2 = 0;
    case 1:
        switch (self->_st1) {
        case 0:
            switch (self->_st2) {
            case 0:
                {
                NEWWIN(0, w364, FUN_003b4d90, 1150)
                ((beNDMWShopSelect01 *)w364.p)->_startPoint = self->_xdataMenu;
                }
                self->_nowProcKazu = CNT;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (CNT != self->_nowProcKazu) {
                    self->_parameter = 0;
                    switch (self->_retCode) {
                    case 0:
                        self->_xdataMenu = 0;
                        self->_st1 = 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    case 1:
                        self->_xdataMenu = 1;
                        self->_st1 = 2;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    case 2:
                    default:
                        self->_st0 = self->_st0 + 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_st1 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 1:
            switch (self->_st2) {
            case 0:
                beMessenger_SelectGroup(self->_messenger, DAT_0051b398);
                beMessenger_AppendInt(self->_messenger, self->_playerNo);
                beMessenger_AppendBool(self->_messenger, 0);
                beMessenger_DispatchSelected(self->_messenger, DAT_0051b3a0);
                {
                NEWWIN(1, w360, FUN_003b4790, self->_parameter)
                }
                self->_nowProcKazu = CNT;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                self->_st3 = self->_parameter;
                return;
            case 1:
                if (CNT == self->_nowProcKazu) {
                    int rc = self->_retCode;
                    if (rc != -1 && rc != self->_st3) {
                        beNDMWWindow_RunMessageScript(self, DAT_0051b3b0, rc + 1154);
                        self->_st3 = self->_retCode;
                    }
                    break;
                } else {
                    int obj;
                    int limit;
                    int need;
                    int have;
                    int money;
                    char *key;
                    int i;
                    int *np;
                    int *q;
                    names = DAT_004cf950;
                    np = names.v;
                    i = 0;
                    q = np;
                    for (; i < 7; i++) {
                        beMessenger_SelectGroup(self->_messenger, DAT_0051b3c0);
                        beMessenger_AppendString(self->_messenger, DAT_0051b3c8);
                        beMessenger_AppendString(self->_messenger, (void *)*q);
                        beMessenger_DispatchSelected(self->_messenger, DAT_0051b3d8);
                        q++;
                    }
                    beMessenger_SelectGroup(self->_messenger, DAT_0051b398);
                    beMessenger_AppendInt(self->_messenger, self->_playerNo);
                    beMessenger_DispatchSelected(self->_messenger, DAT_0051b3e8);
                    obj = beMessenger_GetObject(self->_messenger, 0);
                    limit = 9999;
                    switch (self->_retCode) {
                    default:
                        self->_st1 = 0;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    case 0: key = DAT_0051b3f8; break;
                    case 1: key = DAT_0051b400; break;
                    case 2: key = DAT_0051b408; break;
                    case 3: key = DAT_0051b418; break;
                    case 4: key = DAT_0051b420; break;
                    case 5: key = DAT_0051b430; limit = 99999; break;
                    case 6: key = DAT_0051b438; limit = 99999; break;
                    }
                    money = *(int *)(igProperty_GetRecord(obj, key) + 12);
                    CEILD(need, money)
                    need = need > 400 ? 400 : (need < 0 ? 1 : need);
                    self->_parameter = self->_retCode;
                    {
                    NEWWIN(2, w356, FUN_003b4f50, 0)
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                    have = *(int *)(igProperty_GetRecord(obj, DAT_0051b440) + 12);
                    if (money >= limit) {
                        ((beNDMWWindow *)w356.p)->_entCode = 1162;
                        self->_st3 = 0;
                    } else if (have < need) {
                        ((beNDMWWindow *)w356.p)->_entCode = 1161;
                        self->_st3 = 0;
                    } else {
                        int j;
                        FUN_003f5410(w356.p, DAT_0051b448, DAT_0051b220, DAT_0051b458, DAT_0051b460);
                        sprintf(buf, DAT_0051b468, have - need);
                        FUN_003f5410(w356.p, DAT_0051b448, DAT_0051b248, buf, DAT_0051b460);
                        for (j = 0; j < 4; j++) {
                            APPENDSTR(((beNDMWWindow *)w356.p)->_textCloseTypeList, DAT_0051b448)
                            { int *t = (int *)*np; APPENDSTR(((beNDMWWindow *)w356.p)->_textCloseNameList, t) }
                            np++;
                        }
                        APPENDSTR(((beNDMWWindow *)w356.p)->_textCloseTypeList, DAT_0051b448)
                        APPENDSTR(((beNDMWWindow *)w356.p)->_textCloseNameList, DAT_0051b220)
                        APPENDSTR(((beNDMWWindow *)w356.p)->_textCloseTypeList, DAT_0051b448)
                        APPENDSTR(((beNDMWWindow *)w356.p)->_textCloseNameList, DAT_0051b248)
                        APPENDSTR(((beNDMWWindow *)w356.p)->_textCloseTypeList, DAT_0051b470)
                        { int *t = (int *)names.v[2]; APPENDSTR(((beNDMWWindow *)w356.p)->_textCloseNameList, t) }
                        arr2 = DAT_004cf970;
                        ((beNDMWWindow *)w356.p)->_entCode = arr2.v[self->_retCode];
                        self->_st3 = 1;
                    }
                    }
                    self->_nowProcKazu = CNT;
                    return;
                }
                break;
            case 2:
                if (CNT != self->_nowProcKazu) {
switch (self->_st3) { case 0: default: { self->_st1 = 1; self->_st3 = 0; self->_st2 = 0; return; } case 1: break; }
                    {
                    NEWWIN(0, w352, FUN_003b4d90, 1163)
                    }
                    self->_nowProcKazu = CNT;
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                    return;
                }
                break;
            case 3:
                if (CNT != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case 0: {
                        int obj;
                        char *key;
                        int need;
                        int have;
                        igIntList *lst;
                        beMessenger_SelectGroup(self->_messenger, DAT_0051b398);
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, DAT_0051b3e8);
                        obj = beMessenger_GetObject(self->_messenger, 0);
                        switch (self->_parameter) {
                        case 0: key = DAT_0051b3f8; break;
                        case 1: key = DAT_0051b400; break;
                        case 2: key = DAT_0051b408; break;
                        case 3: key = DAT_0051b418; break;
                        case 4: key = DAT_0051b420; break;
                        case 5: key = DAT_0051b430; break;
                        case 6: key = DAT_0051b438; break;
                        }
                        CEILD(need, *(int *)(igProperty_GetRecord(obj, key) + 12))
                        need = need > 400 ? 400 : (need < 0 ? 1 : need);
                        have = *(int *)(igProperty_GetRecord(obj, DAT_0051b440) + 12);
                        { int rec = igProperty_GetRecord(obj, DAT_0051b440); *(int *)(rec + 12) = have - need; }
                        lst = (igIntList *)*(int *)(FUN_003a9250(obj, DAT_0051b480) + 12);
                        switch (self->_parameter) {
                        case 0: INC(lst, 2) break;
                        case 1: INC(lst, 3) break;
                        case 2: INC(lst, 4) break;
                        case 3: INC(lst, 5) break;
                        case 4: INC(lst, 6) break;
                        case 5: INC(lst, 0) break;
                        case 6: INC(lst, 1) break;
                        }
                        beMessenger_SelectGroup(self->_messenger, DAT_0051b398);
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, DAT_0051b3a0);
                        beMessenger_SelectGroup(self->_messenger, DAT_0051b398);
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, DAT_0051b3e8);
                        obj = beMessenger_GetObject(self->_messenger, 0);
                        {
                            int a = *(int *)(igProperty_GetRecord(obj, DAT_0051b430) + 12);
                            *(int *)(igProperty_GetRecord(obj, DAT_0051b488) + 12) = a;
                            a = *(int *)(igProperty_GetRecord(obj, DAT_0051b438) + 12);
                            *(int *)(igProperty_GetRecord(obj, DAT_0051b490) + 12) = a;
                        }
                        beMessenger_SelectGroup(self->_messenger, DAT_0051b498);
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, DAT_0051b4a0);
                        {
                        NEWWIN(2, w348, FUN_003b4f50, 1165)
                        }
                        self->_nowProcKazu = CNT;
                        self->_st2 = self->_st2 + 1;
                        self->_st3 = 0;
                        return;
                    }
                    case 1:
                    default:
                        self->_st1 = 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    }
                }
                break;
            case 4:
                if (CNT != self->_nowProcKazu) {
                    {
                    NEWWIN(0, w344, FUN_003b4d90, 1166)
                    }
                    self->_nowProcKazu = CNT;
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                    return;
                }
                break;
            case 5:
                if (CNT != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case 0:
                        self->_st1 = 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    case 1:
                    default:
                        self->_st1 = 0;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    }
                }
                break;
            }
            break;
        case 2:
            switch (self->_st2) {
            case 0:
                beMessenger_SelectGroup(self->_messenger, DAT_0051b398);
                beMessenger_AppendInt(self->_messenger, self->_playerNo);
                beMessenger_DispatchSelected(self->_messenger, DAT_0051b3a0);
                {
                NEWWIN(3, w340, FUN_003b6940, 0)
                }
                self->_nowProcKazu = CNT;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (CNT != self->_nowProcKazu) {
                    self->_st1 = 0;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st3 = 1;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 2: {
        int obj;
        int a;
        beMessenger_SelectGroup(self->_messenger, DAT_0051b398);
        beMessenger_AppendInt(self->_messenger, self->_playerNo);
        beMessenger_DispatchSelected(self->_messenger, DAT_0051b3a0);
        beMessenger_SelectGroup(self->_messenger, DAT_0051b398);
        beMessenger_AppendInt(self->_messenger, self->_playerNo);
        beMessenger_DispatchSelected(self->_messenger, DAT_0051b3e8);
        obj = beMessenger_GetObject(self->_messenger, 0);
        a = *(int *)(igProperty_GetRecord(obj, DAT_0051b430) + 12);
        *(int *)(igProperty_GetRecord(obj, DAT_0051b488) + 12) = a;
        a = *(int *)(igProperty_GetRecord(obj, DAT_0051b438) + 12);
        *(int *)(igProperty_GetRecord(obj, DAT_0051b490) + 12) = a;
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        return;
    }
    case 3:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}
