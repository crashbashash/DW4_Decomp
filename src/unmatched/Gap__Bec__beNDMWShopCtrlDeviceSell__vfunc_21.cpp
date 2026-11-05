#include "dw4/reflected.h"
extern "C" {
extern void beNDMWWindow_PresentModelAtOrigin(void *, void *, int, void *, void *);
extern int FUN_004367c0(void *);
extern int FUN_002eb010(int);
extern int StringPool_Construct(int);
extern int StringPool_Intern(int, void *);
extern void StringChunk_ReleaseHeader(int, void *);
extern void beNDMWWindow_RunMessageScript(void *, void *, int);
extern void FUN_003f5410(void *, void *, int, void *, void *);
extern int igObject_GetAllocator(void *, ...);
extern int Memory_GetAllocatorBySelector(int);
extern void *FUN_003b51b0(int);
extern void *FUN_003b4f50(int);
extern void *FUN_003b4d90(int);
extern void beNDMWWindow_BindContext(void *, void *, int, int, int);
extern void ObjectList_AppendRetained(int, void *);
extern void igObject_Destroy(void *);
extern void FUN_00436060(void *, int, int);
extern int beNDMWWindowSelect_CanRequestFO2TOP(void *, int, void *);
extern void FUN_00435250(int, int);
extern int FUN_00236f80(int, int);
extern int FUN_00447ed0(int, int, void *);
extern void beMessenger_SelectGroup(int, void *);
extern void beMessenger_AppendInt(int, int);
extern void beMessenger_DispatchSelected(int, void *);
extern int beMessenger_GetObject(int, int);
extern int igProperty_GetRecordFolder(int, void *);
extern int igProperty_GetRecord(int, void *);
extern void beMessenger_SendNamed(int, void *, void *, int, void *);
extern void beNDMWWindow_PlayQueuedModelClose(void *);
extern void beNDMWWindow_ClearQueuedText(void *);
extern void beNDMWWindow_RequestChildrenClose(void *);
extern int beNDMWWindow_PollCloseComplete(void *);
extern void FUN_004369f0(void *);

extern int *DAT_004cf8a0[];
extern int DAT_004cf8a4[4];
extern char DAT_0051b308[], DAT_0051b398[], DAT_0051b3b0[], DAT_0051b3c8[], DAT_0051b3e8[], DAT_0051b460[],
    DAT_0051b470[], DAT_0051b498[], DAT_0051b4a0[], DAT_0051b528[], DAT_0051b548[], DAT_0051b560[],
    DAT_0051b590[], DAT_0051b598[], DAT_0051b610[], DAT_0051b620[], DAT_0051b630[], DAT_0051b640[],
    DAT_0051b650[], DAT_0051b668[], DAT_0051b680[], DAT_0051bd50[], DAT_0051bd60[], DAT_0051bd70[];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern int DAT_0058b028[4];
extern unsigned char GPR_00554c14;
void Gap__Bec__beNDMWShopCtrlDeviceSell__vfunc_21(beNDMWShopCtrlDeviceSell *self);
}

struct List { int vt; int rc; int count; int cap; int *data; };
struct RefCountedObject { int vt; int rc; };

/* matching construct: dummy virtual slots so the vN() calls dispatch through the retail vtable offsets */
struct DummyVirtual {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual void v24(void *, void *); virtual int v25(); virtual int v26();
};

/* owning reference to a freshly created window: the destructor drops one reference and destroys at zero.  One class per window
 * kind (the compiler emits one out-of-line destructor per class; retail keeps the copies named in config/SLUS-20836/unit-objects.json). */
template <int K> struct WindowRef {
    RefCountedObject *p;
    WindowRef(RefCountedObject *o) : p(o) {}
    ~WindowRef() { igObject *o = (igObject *)p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
/* owning reference to an interned string token (reference count at p[-1], chunk header at p[-2]); retail destructor 0x130720 */
struct StringRef {
    const char *p;
    StringRef(const char *s) : p(s) {}
    ~StringRef() { if (p) { int *hd = (int *)p - 2; int cnt = ((int *)p)[-1] - 1; ((int *)p)[-1] = cnt; if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd); } }
};
/* matching construct: the token reference is an expression temporary; a named local would take a stack slot above the window holders */
/* the removed element comes back as a 4-byte struct through a hidden result pointer */
struct RemovedRef { int x; };
extern "C" RemovedRef ObjectList_RemoveFirstRetained(void *list, int item, int flags);
extern "C" void StringList_AppendRetained(int, const StringRef &);

#define APPENDSTR(list, text) { const char *tok; if ((text) == 0) { tok = 0; } else { if (DAT_00586f20[0] == 0) { int pool = FUN_002eb010(0x10); if (pool != 0) pool = StringPool_Construct(pool); DAT_00586f20[0] = pool; } tok = (const char *)StringPool_Intern(DAT_00586f20[0], (void *)(text)); } StringList_AppendRetained(list, StringRef(tok)); }

#define DEREF(o) if (o) { (o)->rc = (o)->rc - 1; if (((unsigned long long)((long long)(o)->rc << 0x29) >> 0x29) == 0) igObject_Destroy(o); }

void Gap__Bec__beNDMWShopCtrlDeviceSell__vfunc_21(beNDMWShopCtrlDeviceSell *self)
{
    switch (self->_st0) {
    case 0: {
        int vB[3];
        int vA[3];
        int i;
        beNDMWWindow_PresentModelAtOrigin(self, DAT_0051b610, 0, DAT_0051bd50, DAT_0051b620);
        FUN_004367c0(self);
        vA[0] = 0x436C0000;
        vA[2] = 0;
        vA[1] = 0x41C80000;
        vB[0] = 0xC3120000;
        vB[1] = 0x41C80000;
        vB[2] = 0;
        ((DummyVirtual *)self)->v24(vB, vA);
        APPENDSTR(self->_textCloseTypeList, DAT_0051b470)
        APPENDSTR(self->_textCloseNameList, DAT_0051b548)
        beNDMWWindow_RunMessageScript(self, DAT_0051b3b0, 0x676);
        APPENDSTR(self->_textCloseTypeList, DAT_0051b668)
        { int *tx = DAT_004cf8a0[0];
        APPENDSTR(self->_textCloseNameList, tx) }
        beNDMWWindow_RunMessageScript(self, DAT_0051b3b0, 0x3E8);
        i = 0;
        {
            int **p = DAT_004cf8a0;
            do {
                FUN_003f5410(self, DAT_0051b3c8, (int)*p, DAT_0051b590, DAT_0051b598);
                FUN_003f5410(self, DAT_0051b680, (int)*p, DAT_0051b590, DAT_0051b460);
                i++;
                p += 1;
            } while (i < 12);
        }
        FUN_003f5410(self, DAT_0051bd60, (int)DAT_004cf8a0[0], DAT_0051b590, DAT_0051b460);
        FUN_003f5410(self, DAT_0051bd60, DAT_004cf8a4[0], DAT_0051b590, DAT_0051b460);
        self->_cursor = 0;
        self->_nowPage = 0;
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        self->_st1 = 4;
        self->_st3 = 0;
        self->_st2 = 0;
    }
    case 1:
        switch (self->_st1) {
        case 4:
            switch (self->_st2) {
            case 0: {
                int alloc;
                int a;
                alloc = igObject_GetAllocator(self, 5);
                if (GPR_00554c14 != 0) {
                    a = alloc;
                } else {
                    a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
                }
                {
                    WindowRef<1> w188((RefCountedObject *)FUN_003b51b0(a));
                self->_retCode = self->_cursor;
                beNDMWWindow_BindContext(w188.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, w188.p);
                {
                    float *pos = ((beNDMWWindowSelect *)w188.p)->_offsetPos;
                    pos[0] = -121.0f;
                    pos[1] = 128.0f;
                    pos[2] = 0.0f;
                    ((beNDMWWindowSelect *)w188.p)->_startPoint = self->_cursor;
                    { RefCountedObject *wp = *(RefCountedObject * volatile *)&w188.p; FUN_003f5410(wp, DAT_0051b470, (int)DAT_004cf8a0[0], DAT_0051b590, DAT_0051b598); }
                    ((beNDMWWindowSelect *)w188.p)->_selectMax = FUN_004367c0(self);
                    {
                        RefCountedObject *d = (RefCountedObject *)self->_decideList;
                        beNDMWWindowSelect *ws = (beNDMWWindowSelect *)w188.p;
                        RefCountedObject *o;
                        if (d) d->rc = d->rc + 1;
                        o = (RefCountedObject *)ws->_decideList;
                        DEREF(o);
                        ws->_decideList = (int)d;
                    }
                }
                }
                self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            }
            case 1:
                FUN_00436060(self, 1, 1);
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
                return;
            case 2: {
                igObjectList *sub = (igObjectList *)self->_subWindow;
                if (sub->_count == self->_nowProcKazu) {
                    int rc = self->_retCode;
                    if (rc != -1) {
                        if (rc != self->_st3) {
                            FUN_00436060(self, 0, 1);
                            self->_st3 = self->_retCode;
                            return;
                        }
                        {
                            beNDMWWindowSelect *w = (beNDMWWindowSelect *)*(int *)sub->_data;
                            if (beNDMWWindowSelect_CanRequestFO2TOP(w, 5, sub) != 0) {
                                bool flag = false;
                                if (((DummyVirtual *)self)->v25() != 0) {
                                    flag = true;
                                } else if (((DummyVirtual *)self)->v26() != 0) {
                                    flag = true;
                                }
                                if (flag) {
                                    RefCountedObject *d;
                                    RefCountedObject *o;
                                    w->_st0 = 4;
                                    w->_st3 = 0;
                                    w->_st2 = 0;
                                    w->_st1 = 0;
                                    w->_selectMax = FUN_004367c0(self);
                                    d = (RefCountedObject *)self->_decideList;
                                    if (d) d->rc = d->rc + 1;
                                    o = (RefCountedObject *)w->_decideList;
                                    DEREF(o);
                                    w->_decideList = (int)d;
                                    self->_st2 = 1;
                                    self->_st3 = 0;
                                    return;
                                }
                            }
                        }
                    }
                } else {
                    switch (self->_retCode) {
                    default:
                        self->_st1 = 5;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_cursor = self->_retCode;
                        FUN_00435250(self->_mother, self->_cursor);
                        return;
                    case -1:
                        ((beNDMWWindow *)self->_mother)->_retCode = -1;
                        self->_st0 = self->_st0 + 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_st1 = 0;
                        return;
                    }
                }
                break;
            }
            }
            break;
        case 5:
            switch (self->_st2) {
            case 0: {
                int alloc;
                int a;
                alloc = igObject_GetAllocator(self, 5);
                if (GPR_00554c14 != 0) {
                    a = alloc;
                } else {
                    a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
                }
                {
                    WindowRef<2> w184((RefCountedObject *)FUN_003b4f50(a));
                beNDMWWindow_BindContext(w184.p, self, self->_insight, self->_playerNo, 0x619);
                ObjectList_AppendRetained(self->_subWindow, w184.p);
                }
            }
                self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (((igObjectList *)self->_subWindow)->_count != self->_nowProcKazu) {
                    int alloc;
                    int a;
                    alloc = igObject_GetAllocator(self);
                    if (GPR_00554c14 != 0) {
                        a = alloc;
                    } else {
                        a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
                    }
                    {
                        WindowRef<3> w180((RefCountedObject *)FUN_003b4d90(a));
                    beNDMWWindow_BindContext(w180.p, self, self->_insight, self->_playerNo, 0x61A);
                    ObjectList_AppendRetained(self->_subWindow, w180.p);
                    }
                    self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count;
                    self->_st2 = self->_st2 + 1;
                    self->_st3 = 0;
                    return;
                }
                break;
            case 2:
                if (((igObjectList *)self->_subWindow)->_count != self->_nowProcKazu) {
                    int rc = self->_retCode;
                    switch (rc) {
                    case 0: {
                        int obj;
                        igIntList *fold;
                        int total;
                        int idx;
                        int money;
                        int price;
                        int ins;
                        int item;
                        beMessenger_SelectGroup(self->_messenger, DAT_0051b398);
                        beMessenger_AppendInt(self->_messenger, self->_playerNo);
                        beMessenger_DispatchSelected(self->_messenger, DAT_0051b3e8);
                        obj = beMessenger_GetObject(self->_messenger, 0);
                        fold = (igIntList *)*(int *)(igProperty_GetRecordFolder(obj, DAT_0051b528) + 12);
                        idx = self->_cursor + self->_nowPage * 12;
                        if (idx < fold->_count) {
                            ins = FUN_00236f80(self->_insight, DAT_0058b028[0]);
                            item = ((int *)fold->_data)[idx];
                            price = FUN_00447ed0(item, ins, DAT_0051bd70);
                            money = *(int *)(igProperty_GetRecord(obj, DAT_0051b560) + 12);
                            money = money + price;
                            if (money > 9999999) money = 9999999;
                            *(int *)(igProperty_GetRecord(obj, DAT_0051b560) + 12) = money;
                            ObjectList_RemoveFirstRetained(fold, item, 0);
                            beMessenger_SelectGroup(self->_messenger, DAT_0051b498);
                            beMessenger_AppendInt(self->_messenger, self->_playerNo);
                            beMessenger_DispatchSelected(self->_messenger, DAT_0051b4a0);
                            total = fold->_count;
                            if (total <= 0) {
                                self->_st0 = self->_st0 + 1;
                                self->_st3 = 0;
                                self->_st2 = 0;
                                self->_st1 = 0;
                            } else {
                                if (idx >= total) {
                                    if (self->_cursor == 0) {
                                        if (self->_nowPage > 0) self->_nowPage = self->_nowPage - 1;
                                    } else {
                                        self->_cursor = self->_cursor - 1;
                                    }
                                }
                                if (self->_nowPage == 0)
                                    beMessenger_SendNamed(self->_messenger, DAT_0051b308, DAT_0051b630, 0, DAT_0051b640);
                                if (fold->_count <= (self->_nowPage + 1) * 12)
                                    beMessenger_SendNamed(self->_messenger, DAT_0051b308, DAT_0051b650, 0, DAT_0051b640);
                            }
                        } else {
                            self->_st0 = self->_st0 + 1;
                            self->_st3 = 0;
                            self->_st2 = 0;
                            self->_st1 = 0;
                        }
                        break;
                    }
                    case 1:
                        break;
                    }
                    self->_st1 = 4;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    FUN_00435250(self->_mother, -1);
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        FUN_004369f0(self);
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}
