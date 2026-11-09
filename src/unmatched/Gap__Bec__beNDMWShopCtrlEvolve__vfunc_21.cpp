/* Shop evolve-menu state machine (typed recovery). Matching constructs: DummyVirtual (dummy slots
 * so v24/v25/v26 dispatch through vtable offsets 96/100/104), WindowRef (owning stack reference,
 * one per window; StringRef temporaries for the string-list appends), `> 8`/`> 1` compares (slti
 * at), `case 1: default:` arm, case -1 first in the retCode switch, obj/found split in the cast-
 * search loop, cnt/idx declaration order in state 6. Profile: alt compiler, -O3,p -Cpp_exceptions
 * off. */
#include "dw4/reflected.h"
extern "C" {
int FUN_002eb010(...);
int igObject_IsKindOf(...);
void *FUN_003b4d90(...);
void *FUN_003b4f50(...);
void *FUN_003b51b0(...);
int FUN_003f5410(...);
int FUN_00430d20(...);
int FUN_004313b0(...);
int FUN_00443110(...);
void *Memory_GetAllocatorBySelector(...);
int ObjectList_AppendRetained(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
char *StringPool_Intern(...);
char *beDataBase_GetRecordString(...);
int beMessenger_AppendInt(...);
int beMessenger_AppendString(...);
int beMessenger_DispatchSelected(...);
int beMessenger_GetBool(...);
int beMessenger_GetObject(...);
int beMessenger_SelectGroup(...);
int beMessenger_SelectReceivers(...);
int beMessenger_SendNamed(...);
int beNDMWWindowSelect_CanRequestFO2TOP(...);
int beNDMWWindow_BindContext(...);
int beNDMWWindow_ClearQueuedText(...);
int beNDMWWindow_PlayQueuedModelClose(...);
int beNDMWWindow_PollCloseComplete(...);
int beNDMWWindow_PresentModelAtOrigin(...);
int beNDMWWindow_RequestChildrenClose(...);
int beNDMWWindow_RunMessageScript(...);
int igObject_Destroy(...);
void *igObject_GetAllocator(...);
int *igProperty_GetRecord(...);
extern char *DAT_004cf8a0[];
extern char *DAT_004cf8a4[];
extern char *DAT_004cf8d0[];
extern int DAT_0051b1c8[4];
extern int DAT_0051b308[4];
extern int DAT_0051b318[4];
extern int DAT_0051b328[4];
extern int DAT_0051b338[4];
extern int DAT_0051b398[4];
extern int DAT_0051b3b0[4];
extern int DAT_0051b3c0[4];
extern int DAT_0051b3e8[4];
extern int DAT_0051b460[4];
extern int DAT_0051b470[4];
extern int DAT_0051b548[4];
extern int DAT_0051b558[4];
extern int DAT_0051b590[4];
extern int DAT_0051b598[4];
extern int DAT_0051b5d8[4];
extern int DAT_0051b5e8[4];
extern int DAT_0051b610[4];
extern int DAT_0051b620[4];
extern int DAT_0051b6b0[4];
extern int DAT_0051b6b8[4];
extern int DAT_0051b888[4];
extern int DAT_0051b890[4];
extern int DAT_0051b8a0[4];
extern int DAT_0051ba28[4];
extern int DAT_0051ba38[4];
extern int DAT_0051ba48[4];
extern int DAT_0051ba60[4];
extern int DAT_0051ba70[4];
extern int DAT_0051ba80[4];
extern int DAT_0051ba90[4];
extern int DAT_0051baa0[4];
extern int DAT_0051bab0[4];
extern int DAT_0051bac0[4];
extern int DAT_0051bad0[4];
extern int DAT_0051bae8[4];
extern int DAT_0051baf0[4];
extern int DAT_00586f20[4];
extern int DAT_00587110[4];
extern int DAT_0058abd8[4];
extern unsigned char GPR_00554c14;

void Gap__Bec__beNDMWShopCtrlEvolve__vfunc_21(beNDMWShopCtrlEvolve *self);
}

struct Rc { int w0; int references; };
struct DummyVirtual {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual void v24(void *, void *); virtual int v25(); virtual int v26();
};

/* Owning stack reference to a freshly created sub-window of one class (kind 0 the page selector, 1
 * the select window, 2 the item window). */
template <int kind> struct WindowRef {
    Rc *p;
    WindowRef(Rc *w) : p(w) {}
    ~WindowRef() { Rc *w = p; if (w != 0) { --w->references; if ((w->references & 0x7fffff) == 0) igObject_Destroy(w); } }
};
/* The interned text handed to a string list as a temporary; its destructor drops the interning
 * share. */
struct StringRef {
    char *p;
    StringRef(char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
extern "C" int StringList_AppendRetained(int, const StringRef &);

#define ALLOC(a, self) { a = igObject_GetAllocator(self); a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]); }
#define APPENDSTR(list, text) { char *tok; if ((text) == 0) { tok = 0; } else { if (DAT_00586f20[0] == 0) { int pool = FUN_002eb010(0x10); if (pool != 0) pool = StringPool_Construct(pool); DAT_00586f20[0] = pool; } tok = StringPool_Intern(DAT_00586f20[0], (void *)(text)); } StringList_AppendRetained(list, StringRef(tok)); }
#define APPENDSTRV(list, text) { char *tx = (char *)(text); APPENDSTR(list, tx) }
#define W(p, off) (*(int *)((int)(p) + (off)))
#define SLIST(self) ((beNDMWShinkaObjectList *)((beNDMWShinkaCtrl *)(self)->_shinkaCtrl)->_list)
#define SUB(self) ((igObjectList *)(self)->_subWindow)

void Gap__Bec__beNDMWShopCtrlEvolve__vfunc_21(beNDMWShopCtrlEvolve *self) {
    int vB[3];
    int vA[3];
    void *alloc;
    int v;
    beNDMWShinkaObject *el;
    int money;

    switch (self->_st0) {
    case 0:
        switch (self->_st1) {
        case 0:
            beNDMWWindow_PresentModelAtOrigin(self, &DAT_0051b318[0], 0, &DAT_0051b328[0], &DAT_0051ba28[0]);
            self->_st1 = self->_st1 + 1;
            self->_st3 = 0;
            self->_st2 = 0;
        case 1:
            beMessenger_SelectReceivers(self->_messenger, &DAT_0051b308[0], &DAT_0051b318[0], 0);
            beMessenger_AppendString(self->_messenger, &DAT_0051b328[0]);
            beMessenger_DispatchSelected(self->_messenger, &DAT_0051b338[0]);
            if ((beMessenger_GetBool(self->_messenger, 0) & 0xFF) != 1) {
                FUN_00443110(self->_shinkaCtrl, self->_insight, self->_playerNo);
                if (SLIST(self)->_count > 8) {
                    self->_maxPage = 2;
                } else {
                    self->_maxPage = 1;
                }
                self->_nowPage = 0;
                self->_cursor = 0;
                if (self->_maxPage > 1) {
                    beNDMWWindow_PresentModelAtOrigin(self, &DAT_0051b610[0], 0, &DAT_0051ba38[0], &DAT_0051b620[0]);
                    vA[0] = 0xC24C0000;
                    vA[2] = 0;
                    vA[1] = 0x41C80000;
                    vB[0] = 0xC39A0000;
                    vB[1] = 0x41C80000;
                    vB[2] = 0;
                    ((DummyVirtual *)self)->v24(vB, vA);
                    FUN_003f5410(self, &DAT_0051ba48[0], DAT_004cf8a0[0], &DAT_0051b590[0], &DAT_0051b460[0]);
                    FUN_003f5410(self, &DAT_0051ba48[0], DAT_004cf8a4[0], &DAT_0051b590[0], &DAT_0051b460[0]);
                } else {
                    beNDMWWindow_PresentModelAtOrigin(self, &DAT_0051b610[0], 0, &DAT_0051ba60[0], &DAT_0051b620[0]);
                }
                APPENDSTR(self->_textCloseTypeList, &DAT_0051b470[0])
                APPENDSTR(self->_textCloseNameList, &DAT_0051b548[0])
                beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x4E6);
                APPENDSTR(self->_textCloseTypeList, &DAT_0051ba70[0])
                APPENDSTRV(self->_textCloseNameList, DAT_004cf8a0[0])
                APPENDSTR(self->_textCloseTypeList, &DAT_0051ba70[0])
                APPENDSTRV(self->_textCloseNameList, DAT_004cf8a4[0])
                beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x4C2);
                {
                int i = 0;
                char **fp = DAT_004cf8a0;
                do {
                    FUN_003f5410(self, &DAT_0051ba80[0], *fp, &DAT_0051b590[0], &DAT_0051b598[0]);
                    FUN_003f5410(self, &DAT_0051ba90[0], *fp, &DAT_0051b590[0], &DAT_0051b598[0]);
                    FUN_003f5410(self, &DAT_0051baa0[0], *fp, &DAT_0051b590[0], &DAT_0051b460[0]);
                    i += 1;
                    fp += 1;
                } while (i < 8);
                }
                {
                int j = 0;
                char **gp = DAT_004cf8d0;
                do {
                    FUN_003f5410(self, &DAT_0051bab0[0], gp[0], &DAT_0051b590[0], &DAT_0051b598[0]);
                    FUN_003f5410(self, &DAT_0051bab0[0], gp[1], &DAT_0051b590[0], &DAT_0051b460[0]);
                    j += 1;
                    gp += 2;
                } while (j < 16);
                }
                beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x4B2);
                FUN_003f5410(self, &DAT_0051b470[0], DAT_004cf8a0[0], &DAT_0051b590[0], &DAT_0051b598[0]);
                self->_st0 = self->_st0 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
                self->_st1 = 0;
                self->_st3 = 0;
                self->_st2 = 0;
                return;
            }
            break;
        }
        break;
    case 1:
        switch (self->_st1) {
        case 0:
            ALLOC(alloc, self)
            {
            WindowRef<0> win((Rc *)FUN_003b51b0(alloc));
            beNDMWWindow_BindContext(win.p, self, self->_insight, self->_playerNo, 0);
            ObjectList_AppendRetained(self->_subWindow, win.p);
            {
            float *pos = ((beNDMWWindowSelect *)win.p)->_offsetPos;
            pos[0] = -283.0f;
            pos[1] = 92.0f;
            pos[2] = 0.0f;
            ((beNDMWWindowSelect *)win.p)->_startPoint = self->_cursor;
            v = SLIST(self)->_count;
            if (v == 0) {
                ((beNDMWWindowSelect *)win.p)->_selectMax = 2;
            } else {
                switch (self->_nowPage) {
                case 0:
                    if (v > 8) {
                        ((beNDMWWindowSelect *)win.p)->_selectMax = 8;
                    } else {
                        ((beNDMWWindowSelect *)win.p)->_selectMax = v;
                    }
                    break;
                case 1:
                    ((beNDMWWindowSelect *)win.p)->_selectMax = v - 8;
                    break;
                }
            }
            }
            }
            self->_nowProcKazu = SUB(self)->_count;
            self->_st1 = self->_st1 + 1;
            self->_st3 = 0;
            self->_st2 = 0;
            self->_retCode = self->_cursor;
            FUN_00430d20(self, 1, 0);
        case 1:
            if (self->_retCode != -1) {
                FUN_00430d20(self, 0, 1);
            }
            self->_st1 = self->_st1 + 1;
            self->_st3 = 0;
            self->_st2 = 0;
            self->_st3 = self->_retCode;
        case 2:
            if (SUB(self)->_count == self->_nowProcKazu) {
                if (self->_retCode != -1) {
                    if (self->_st3 != self->_retCode) {
                        self->_st1 = 1;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        return;
                    }
                    {
                    int *found = 0;
                    int i = 0;
                    int *obj;
                    if (0 < SUB(self)->_count) {
                        do {
                            obj = (int *)((int *)((igObjectList *)*(int *)&self->_subWindow)->_data)[i];
                            if ((obj != 0) && (igObject_IsKindOf(obj, DAT_0058abd8[0]) != 0)) {
                                found = obj;
                            } else {
                                found = 0;
                            }
                            if (found != 0) break;
                            i += 1;
                        } while (i < SUB(self)->_count);
                    }
                    if (beNDMWWindowSelect_CanRequestFO2TOP(found) != 0) {
                        bool flag = false;
                        if (((DummyVirtual *)self)->v25() != 0) {
                            flag = true;
                        } else if (((DummyVirtual *)self)->v26() != 0) {
                            flag = true;
                        }
                        if (flag) {
                            ((beNDMWWindowSelect *)found)->_st0 = 4;
                            ((beNDMWWindowSelect *)found)->_st3 = 0;
                            ((beNDMWWindowSelect *)found)->_st2 = 0;
                            ((beNDMWWindowSelect *)found)->_st1 = 0;
                            v = SLIST(self)->_count;
                            if (v == 0) {
                                ((beNDMWWindowSelect *)found)->_selectMax = 2;
                            } else {
                                switch (self->_nowPage) {
                                case 0:
                                    if (v > 8) {
                                        ((beNDMWWindowSelect *)found)->_selectMax = 8;
                                    } else {
                                        ((beNDMWWindowSelect *)found)->_selectMax = v;
                                    }
                                    break;
                                case 1:
                                    ((beNDMWWindowSelect *)found)->_selectMax = v - 8;
                                    break;
                                }
                            }
                            self->_st1 = 1;
                            self->_st3 = 0;
                            self->_st2 = 0;
                            self->_retCode = 0;
                            FUN_00430d20(self, 1, 0);
                            return;
                        }
                    }
                    }
                }
            } else {
                switch (self->_retCode) {
                case -1:
                    ((beNDMWWindow *)self->_mother)->_retCode = -1;
                    self->_st0 = self->_st0 + 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st1 = 0;
                    return;
                default:
                    self->_cursor = self->_retCode;
                    el = (beNDMWShinkaObject *)((int *)SLIST(self)->_data)[self->_cursor + self->_nowPage * 8];
                    beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
                    beMessenger_AppendInt(self->_messenger, self->_playerNo);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051b3e8[0]);
                    money = W(igProperty_GetRecord(beMessenger_GetObject(self->_messenger, 0), &DAT_0051bac0[0]), 12);
                    beMessenger_SelectGroup(self->_messenger, &DAT_0051b398[0]);
                    beMessenger_AppendInt(self->_messenger, self->_playerNo);
                    beMessenger_AppendInt(self->_messenger, el->_id);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051bad0[0]);
                    if (money == el->_id) {
                        self->_st1 = 4;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_st2 = 0;
                        self->_st3 = 0;
                        beMessenger_SelectGroup(self->_messenger, &DAT_0051b888[0]);
                        beMessenger_AppendString(self->_messenger, &DAT_0051b890[0]);
                        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b8a0[0]);
                        return;
                    }
                    if (!(beMessenger_GetBool(self->_messenger, 0) & 0xFF)) {
                        self->_st1 = 4;
                        self->_st3 = 0;
                        self->_st2 = 0;
                        self->_st2 = 1;
                        self->_st3 = 0;
                        beMessenger_SelectGroup(self->_messenger, &DAT_0051b888[0]);
                        beMessenger_AppendString(self->_messenger, &DAT_0051b890[0]);
                        beMessenger_DispatchSelected(self->_messenger, &DAT_0051b8a0[0]);
                        return;
                    }
                    self->_st1 = 3;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    return;
                }
            }
            break;
        case 3:
            switch (self->_st2) {
            case 0:
                ALLOC(alloc, self)
                {
                WindowRef<1> win((Rc *)FUN_003b4d90(alloc));
                beNDMWWindow_BindContext(win.p, self, self->_insight, self->_playerNo, 0x4E7);
                ObjectList_AppendRetained(self->_subWindow, win.p);
                }
                self->_nowProcKazu = SUB(self)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 1:
                if (SUB(self)->_count != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case 0:
                        self->_st2 = self->_st2 + 1;
                        self->_st3 = 0;
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
            case 2:
                ALLOC(alloc, self)
                {
                WindowRef<2> win((Rc *)FUN_003b4f50(alloc));
                beNDMWWindow_BindContext(win.p, self, self->_insight, self->_playerNo, 0x4E9);
                ObjectList_AppendRetained(self->_subWindow, win.p);
                }
                self->_nowProcKazu = SUB(self)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 3:
                if (SUB(self)->_count == self->_nowProcKazu) break;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 4:
                ALLOC(alloc, self)
                {
                WindowRef<1> win((Rc *)FUN_003b4d90(alloc));
                beNDMWWindow_BindContext(win.p, self, self->_insight, self->_playerNo, 0x4EA);
                ObjectList_AppendRetained(self->_subWindow, win.p);
                }
                self->_nowProcKazu = SUB(self)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            case 5:
                if (SUB(self)->_count != self->_nowProcKazu) {
                    switch (self->_retCode) {
                    case 0:
                        self->_st2 = self->_st2 + 1;
                        self->_st3 = 0;
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
            case 6: {
                beNDMWShinkaObjectList *ar;
                int cnt;
                int idx;
                ALLOC(alloc, self)
                {
                WindowRef<2> win((Rc *)FUN_003b4f50(alloc));
                beNDMWWindow_BindContext(win.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, win.p);
                APPENDSTR(((beNDMWWindowSelect *)win.p)->_textCloseTypeList, &DAT_0051b470[0])
                APPENDSTR(((beNDMWWindowSelect *)win.p)->_textCloseNameList, &DAT_0051b548[0])
                beNDMWWindow_RunMessageScript(self, &DAT_0051b3b0[0], 0x4EC);
                }
                ar = SLIST(self);
                idx = self->_cursor + self->_nowPage * 8;
                cnt = ar->_count;
                if (cnt > 0 && idx < cnt) {
                    beNDMWShinkaObject *e = (beNDMWShinkaObject *)((int *)ar->_data)[idx];
                    char *rs;
                    beMessenger_SendNamed(self->_messenger, &DAT_0051b5d8[0], &DAT_0051bae8[0], 0, &DAT_0051b5e8[0]);
                    rs = beDataBase_GetRecordString(beMessenger_GetObject(self->_messenger, 0), e->_id, &DAT_0051baf0[0]);
                    beMessenger_SelectGroup(self->_messenger, &DAT_0051b3c0[0]);
                    beMessenger_AppendString(self->_messenger, &DAT_0051b470[0]);
                    beMessenger_AppendString(self->_messenger, DAT_004cf8a0[0]);
                    beMessenger_AppendString(self->_messenger, rs);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051b6b0[0]);
                    beMessenger_SelectGroup(self->_messenger, &DAT_0051b3c0[0]);
                    beMessenger_AppendString(self->_messenger, &DAT_0051b470[0]);
                    beMessenger_AppendString(self->_messenger, DAT_004cf8a0[0]);
                    beMessenger_AppendString(self->_messenger, &DAT_0051b6b8[0]);
                    beMessenger_DispatchSelected(self->_messenger, &DAT_0051b558[0]);
                    FUN_004313b0(self);
                }
                self->_nowProcKazu = SUB(self)->_count;
                self->_st2 = self->_st2 + 1;
                self->_st3 = 0;
            }
            case 7:
                if (SUB(self)->_count != self->_nowProcKazu) {
                    ((beNDMWWindow *)self->_mother)->_retCode = 1;
                    self->_st0 = self->_st0 + 1;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    self->_st1 = 0;
                    return;
                }
                break;
            }
            break;
        case 4:
            switch (self->_st3) {
            case 0:
                ALLOC(alloc, self)
                {
                WindowRef<2> win((Rc *)FUN_003b4f50(alloc));
                beNDMWWindow_BindContext(win.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, win.p);
                APPENDSTR(((beNDMWWindowSelect *)win.p)->_textCloseTypeList, &DAT_0051b470[0])
                APPENDSTR(((beNDMWWindowSelect *)win.p)->_textCloseNameList, &DAT_0051b1c8[0])
                if (self->_st2 == 0) {
                    beNDMWWindow_RunMessageScript(win.p, &DAT_0051b3b0[0], 0x7E4);
                } else {
                    beNDMWWindow_RunMessageScript(win.p, &DAT_0051b3b0[0], 0x7E5);
                }
                }
                self->_nowProcKazu = SUB(self)->_count;
                self->_st3 = self->_st3 + 1;
            case 1:
                if (SUB(self)->_count != self->_nowProcKazu) {
                    self->_st1 = 0;
                    self->_st3 = 0;
                    self->_st2 = 0;
                    return;
                }
                break;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose();
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete() != 0) {
            self->_isRun = 0;
        }
        break;
    }
}
