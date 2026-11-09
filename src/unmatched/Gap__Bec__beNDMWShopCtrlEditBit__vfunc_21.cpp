#include "dw4/reflected.h"
static inline int st2(const beNDMWShopCtrlEditBit *self) { return self->_st2; }
extern "C" {
int sprintf(...);
int FUN_002eb010(...);
int FUN_003b45d0(...);
int FUN_003b4d90(...);
int FUN_003b4f50(...);
int FUN_00440110(...);
int FUN_004402e0(...);
void *Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
char *StringPool_Intern(...);
int beMessenger_AppendInt(...);
int beMessenger_AppendString(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetBool(...);
int beMessenger_GetObject(...);
int beMessenger_SelectGroup(...);
int beMessenger_SendNamed(...);
int beNDMWWindow_BindContext(...);
int beNDMWWindow_ClearQueuedText(...);
int beNDMWWindow_PlayQueuedModelClose(...);
int beNDMWWindow_PollCloseComplete(...);
int beNDMWWindow_PresentModelAtOrigin(...);
int beNDMWWindow_RequestChildrenClose(...);
int beNDMWWindow_RunMessageScript(...);
int igObject_Destroy(...);
void *igObject_GetAllocator(...);
int igProperty_GetRecord(...);
bePadData *bePadManager_GetPadForPlayer(...);
extern int DAT_0051b1c8[4];
extern int DAT_0051b1d0[4];
extern int DAT_0051b1d8[4];
extern int DAT_0051b398[4];
extern int DAT_0051b3b0[4];
extern int DAT_0051b3c0[4];
extern int DAT_0051b3e8[4];
extern int DAT_0051b470[4];
extern int DAT_0051b548[4];
extern int DAT_0051b550[4];
extern int DAT_0051b558[4];
extern int DAT_0051b560[4];
extern int DAT_0051b568[4];
extern int DAT_0051b610[4];
extern int DAT_0051b620[4];
extern int DAT_0051b888[4];
extern int DAT_0051b8a0[4];
extern int DAT_0051bc60[4];
extern int DAT_0051bc70[4];
extern int DAT_0051bc80[4];
extern int DAT_0051bc98[4];
extern int DAT_0051bca8[4];
extern int DAT_0051bcb8[4];
extern int DAT_0051bcc8[4];
extern int DAT_0051bcd8[4];
extern int DAT_0051bce8[4];
extern int DAT_0051bcf8[4];
extern int DAT_0051bd08[4];
extern int DAT_0051bd18[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;

void Gap__Bec__beNDMWShopCtrlEditBit__vfunc_21(beNDMWShopCtrlEditBit *self);
}
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    char *p;
    StringRef(char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(int, const StringRef &);
#define INTERN_APPEND(lst, text) { \
    char *tok; \
    if ((text) == 0) { \
        tok = 0; \
    } else { \
        if (DAT_00586f20[0] == 0) { \
            int pool = FUN_002eb010(0x10); \
            if (pool != 0) pool = StringPool_Construct(pool); \
            DAT_00586f20[0] = pool; \
        } \
        tok = StringPool_Intern(DAT_00586f20[0], (char *)(text)); \
    } \
    StringList_AppendRetained(lst, StringRef(tok)); }

#define ALLOC(a, self) { \
    a = igObject_GetAllocator(self); \
    a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]); }

typedef igObject Rc;
/* Scope holder for a freshly built window: its destructor releases the reference. One class per
 * kind (0..2), so each gets its own out-of-line destructor. */
template <int kind> struct RP {
    Rc *p;
    RP(Rc *x) { p = x; }
    ~RP() { Rc *o = p; if (o != 0) { o->_refCount = o->_refCount - 1; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
    operator Rc *() { return p; }
};
#define W(p, off) (*(int *)((int)(p) + (off)))
#define REL(o) { Rc *rr = (o); if (rr != 0) { *(int *)&rr->_refCount = *(int *)&rr->_refCount - 1; if (((unsigned long long)((long long)*(int *)&rr->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }

void Gap__Bec__beNDMWShopCtrlEditBit__vfunc_21(beNDMWShopCtrlEditBit *self) {
    char sp50[20];
    void *alloc;
    int obj;
    int s2v;
    int s1v;
    int s0v;
    int i;
    int mult;
    int cnt;
    bePadData *pad;
    int pa;
    int pb;
    int oldv;
    int v;
    int lim;
    int a2v;
    int rc;
    int h;

    switch (self->_st0) {
    default:
        return;
    case 0:
        switch (self->_entCode) {
        case 0:
            beNDMWWindow_PresentModelAtOrigin(self, &DAT_0051b610[0], 0, &DAT_0051bc60[0], &DAT_0051b620[0]);
            INTERN_APPEND(self->_textCloseTypeList, &DAT_0051bc70[0])
            INTERN_APPEND(self->_textCloseNameList, &DAT_0051b1c8[0])
            INTERN_APPEND(self->_textCloseTypeList, &DAT_0051bc70[0])
            INTERN_APPEND(self->_textCloseNameList, &DAT_0051b1d0[0])
            beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x515);
            INTERN_APPEND(self->_textCloseTypeList, &DAT_0051b470[0])
            INTERN_APPEND(self->_textCloseNameList, &DAT_0051b548[0])
            beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x550);
            break;
        case 1:
            beNDMWWindow_PresentModelAtOrigin(self, &DAT_0051b610[0], 0, &DAT_0051bc80[0], &DAT_0051b620[0]);
            INTERN_APPEND(self->_textCloseTypeList, &DAT_0051bc70[0])
            INTERN_APPEND(self->_textCloseNameList, &DAT_0051b1c8[0])
            INTERN_APPEND(self->_textCloseTypeList, &DAT_0051bc70[0])
            INTERN_APPEND(self->_textCloseNameList, &DAT_0051b1d0[0])
            INTERN_APPEND(self->_textCloseTypeList, &DAT_0051bc70[0])
            INTERN_APPEND(self->_textCloseNameList, &DAT_0051b1d8[0])
            beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x55F);
            INTERN_APPEND(self->_textCloseTypeList, &DAT_0051b470[0])
            INTERN_APPEND(self->_textCloseNameList, &DAT_0051b548[0])
            beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x557);
            break;
        case 2:
            beNDMWWindow_PresentModelAtOrigin(self, &DAT_0051b610[0], 0, &DAT_0051bc98[0], &DAT_0051b620[0]);
            INTERN_APPEND(self->_textCloseTypeList, &DAT_0051bc70[0])
            INTERN_APPEND(self->_textCloseNameList, &DAT_0051b1c8[0])
            beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x562);
            break;
        }
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
    case 1:
        switch (self->_st2) {
        case 0:
            ALLOC(alloc, self)
            {
            RP<0> spAC((Rc *)FUN_003b45d0(alloc));
            beNDMWWindow_BindContext(spAC.p, self, self->_insight, self->_playerNo, self->_entCode);
            ObjectList_AppendRetained(self->_subWindow, spAC.p);
            }
            self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count;
            self->_st2 = self->_st2 + 1;
            self->_st3 = 0;
            return;
        case 1:
            beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
            beMessenger_AppendInt(self->_messenger, self->_playerNo);
            beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
            obj = beMessenger_GetObject(self->_messenger, 0);
            self->_editBit = 0;
            s2v = ((int *)((igObjectList *)self->_subWindow)->_data)[0];
            s1v = W(igProperty_GetRecord(obj, &DAT_0051b560[0]), 12);
            s0v = W(igProperty_GetRecord(obj, &DAT_0051b568[0]), 12);
            switch (self->_entCode) {
            case 0:
                FUN_004402e0(s2v, self->_editBit, 1, &DAT_0051bca8[0]);
                v = 9999999 - s0v;
                s1v = s1v < v ? s1v : v;
                self->_editMax = s1v;
                FUN_00440110(s2v, self->_entCode, s0v);
                break;
            case 1:
                FUN_004402e0(s2v, self->_editBit, 1, &DAT_0051bcb8[0]);
                v = 9999999 - s1v;
                self->_editMax = s0v < v ? s0v : v;
                FUN_00440110(s2v, self->_entCode, s1v);
                FUN_004402e0(s2v, s0v, 1, &DAT_0051bcc8[0]);
                break;
            case 2:
                FUN_004402e0(s2v, self->_editBit, 1, &DAT_0051bca8[0]);
                v = 999999999 - s1v;
                s1v = s1v < v ? s1v : v;
                self->_editMax = s1v;
                break;
            }
            self->_st2 = self->_st2 + 1;
            self->_st3 = 0;
            return;
        case 2:
            if (((igObjectList *)self->_subWindow)->_count == self->_nowProcKazu) {
                rc = self->_retCode;
                if (rc != -1) {
                    if (self->_st3 == rc) {
                        beMessenger_SendNamed(self->_messenger, &DAT_0051bcd8[0], &DAT_0051bce8[0], self->_playerNo, &DAT_0051bcf8[0]);
                        if (beMessenger_GetBool(self->_messenger, 0) & 0xFF) {
                            pad = bePadManager_GetPadForPlayer(self->_padManager, self->_playerNo);
                            pa = pad->_trigger;
                            pb = pad->_repeat;
                            cnt = pad->_lTrg | pad->_lRpt;
                            bool up = true;
                            if (!(cnt & 1) && !((pa | pb) & 0x10)) up = false;
                            bool dn = true;
                            if (!(cnt & 4) && !((pa | pb) & 0x40)) dn = false;
                            if (up || dn) {
                                oldv = self->_editBit;
                                mult = 1;
                                a2v = 7 - self->_retCode;
                                for (i = a2v; i > 1; i--) mult *= 10;
                                if (up) {
                                    self->_editBit = self->_editBit + mult;
                                    lim = self->_editMax;
                                    if (self->_editBit >= lim) self->_editBit = lim;
                                } else if (dn) {
                                    self->_editBit = self->_editBit - mult;
                                    if (self->_editBit <= 0) self->_editBit = 0;
                                }
                                v = self->_editBit;
                                if (v != oldv) {
                                    h = ((int *)((igObjectList *)self->_subWindow)->_data)[0];
                                    switch (self->_entCode) {
                                    case 2:
                                    case 0:
                                        FUN_004402e0(h, v, a2v, &DAT_0051bca8[0]);
                                        break;
                                    case 1:
                                        FUN_004402e0(h, v, a2v, &DAT_0051bcb8[0]);
                                        break;
                                    }
                                    beMessenger_SelectGroup(self->_messenger, &DAT_0051b888[0]);
                                    beMessenger_AppendString(self->_messenger, &DAT_0051bd08[0]);
                                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051b8a0[0]);
                                    return;
                                }
                            }
                        }
                    } else {
                        h = ((int *)((igObjectList *)self->_subWindow)->_data)[0];
                        a2v = 7 - rc;
                        switch (self->_entCode) {
                        case 2:
                        case 0:
                            FUN_004402e0(h, self->_editBit, a2v, &DAT_0051bca8[0]);
                            break;
                        case 1:
                            FUN_004402e0(h, self->_editBit, a2v, &DAT_0051bcb8[0]);
                            break;
                        }
                        self->_st3 = self->_retCode;
                        return;
                    }
                }
            } else {
                if (self->_retCode == -1 || self->_editBit <= 0) {
                    ((beNDMWWindow *)self->_mother)->_retCode = -1;
                    self->_st0 = self->_st0 + 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st1 = 0;
                    return;
                } else {
                    ((beNDMWWindow *)self->_mother)->_retCode = self->_editBit;
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                    beMessenger_SelectGroup(self->_messenger, &DAT_0051b3c0[0]);
                    beMessenger_AppendString(self->_messenger, &DAT_0051b470[0]);
                    beMessenger_AppendString(self->_messenger, &DAT_0051b548[0]);
                    beMessenger_AppendString(self->_messenger, &DAT_0051b550[0]);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051b558[0]);
                    return;
                }
            }
            break;
        case 3:
            ALLOC(alloc, self)
            {
            RP<1> spA8((Rc *)FUN_003b4f50(alloc));
            beNDMWWindow_BindContext(spA8.p, self, self->_insight, self->_playerNo, 0);
            ObjectList_AppendRetained(self->_subWindow, spA8.p);
            switch (self->_entCode) {
            case 0:
                ((beNDMWShopSelect00 *)spA8.p)->_entCode = 0x552;
                break;
            case 1:
                ((beNDMWShopSelect00 *)spA8.p)->_entCode = 0x559;
                break;
            case 2:
                ((beNDMWShopSelect00 *)spA8.p)->_entCode = 0x7A9;
                break;
            }
            }
            self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count;
            self->_st2 = self->_st2 + 1;
            self->_st3 = 0;
            return;
        case 4:
            if (((igObjectList *)self->_subWindow)->_count != self->_nowProcKazu) {
                if (self->_entCode == 2) {
                    self->_st2 = st2(self) + 1;
                    self->_st3 = 0;
                    return;
                }
                self->_st0 = self->_st0 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
                return;
            }
            break;
        case 5:
            ALLOC(alloc, self)
            {
            RP<2> spA4((Rc *)FUN_003b4d90(alloc));
            beNDMWWindow_BindContext(spA4.p, self, self->_insight, self->_playerNo, 0x7AA);
            ObjectList_AppendRetained(self->_subWindow, spA4.p);
            }
            self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count;
            self->_st2 = self->_st2 + 1;
            self->_st3 = 0;
            return;
        case 6:
            if (((igObjectList *)self->_subWindow)->_count != self->_nowProcKazu) {
                if (self->_retCode != 0) {
                    ((beNDMWWindow *)self->_mother)->_retCode = -1;
                }
                self->_st0 = self->_st0 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
                return;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose();
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        i = 0;
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        do {
            sprintf(&sp50[0], &DAT_0051bca8[0], i);
            beMessenger_SelectGroup(self->_messenger, &DAT_0051b3c0[0]);
            beMessenger_AppendString(self->_messenger, &DAT_0051bd18[0]);
            beMessenger_AppendString(self->_messenger, &sp50[0]);
            beMessenger_AppendString(self->_messenger, &DAT_0051b550[0]);
            beMessenger_DispatchSelected(self->_messenger, &DAT_0051b558[0]);
            sprintf(&sp50[0], &DAT_0051bcb8[0], i);
            beMessenger_SelectGroup(self->_messenger, &DAT_0051b3c0[0]);
            beMessenger_AppendString(self->_messenger, &DAT_0051bd18[0]);
            beMessenger_AppendString(self->_messenger, &sp50[0]);
            beMessenger_AppendString(self->_messenger, &DAT_0051b550[0]);
            beMessenger_DispatchSelected(self->_messenger, &DAT_0051b558[0]);
            sprintf(&sp50[0], &DAT_0051bcc8[0], i);
            beMessenger_SelectGroup(self->_messenger, &DAT_0051b3c0[0]);
            beMessenger_AppendString(self->_messenger, &DAT_0051bd18[0]);
            beMessenger_AppendString(self->_messenger, &sp50[0]);
            beMessenger_AppendString(self->_messenger, &DAT_0051b550[0]);
            beMessenger_DispatchSelected(self->_messenger, &DAT_0051b558[0]);
            i += 1;
        } while (i < 7);
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete() != 0) {
            self->_isRun = 0;
        }
        break;
    }
}
