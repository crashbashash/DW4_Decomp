/* Update state machine of the status-screen item page (D0 = the 12-row page list: devices or the
 * bank folder). State 0 registers the page-turn text/script names, opens the list window, sets its
 * decide list and the page offset and queues the model; state 1 handles the page / cursor choice
 * (_st1 0 = prepare, 1 = wait for the window and act on _retCode, 2 = rebuild the list window for the
 * new page); state 2 closes everything and re-sends the page-name text groups for the 12 rows;
 * state 3 waits for the close and clears _isRun.
 * Matching constructs: HA::Add fixes the operand order of page*12+ret, `list->_count <= x` gives the
 * slt-at branch, the record folder is held in a block-local per arm (delay-slot fill), and the window
 * pointers stay in memory-resident RP holders that are re-read for each field store. */
#include "dw4/reflected.h"
extern "C" {
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, int *);
void *igObject_GetAllocator(void *);
void *Memory_GetAllocatorBySelector(int);
void igObject_Destroy(void *);
void ObjectList_AppendRetained(...);
void *FUN_003b51b0(void *);
void FUN_003f5410(...);
int FUN_00418ac0(...);
int FUN_004191f0(...);
void beMessenger_SelectGroup(...);
void beMessenger_AppendInt(...);
void beMessenger_AppendString(...);
void beMessenger_DispatchSelected(...);
void beMessenger_SendNamed(...);
int beMessenger_GetObject(int, int);
struct Rec { int p[3]; igObjectList *f12; };
Rec *igProperty_GetRecordFolder(int, const void *);
int beNDMWWindowSelect_CanRequestFO2TOP(...);
void beNDMWWindow_PresentModelAtOrigin(...);
void beNDMWWindow_RunMessageScript(...);
void beNDMWWindow_BindContext(...);
void beNDMWWindow_ClearQueuedText(...);
void beNDMWWindow_PlayQueuedModelClose(...);
void beNDMWWindow_RequestChildrenClose(...);
int beNDMWWindow_PollCloseComplete(...);
extern void *DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
extern char *DAT_004cf670[];
extern char *DAT_004cf674[];
extern int DAT_00519a40[4];
extern int DAT_00519a50[4];
extern int DAT_00519a58[4];
extern int DAT_00519a70[4];
extern int DAT_00519a90[4];
extern int DAT_00519b50[4];
extern int DAT_00519b60[4];
extern int DAT_00519b68[4];
extern int DAT_00519b90[4];
extern int DAT_00519ba0[4];
extern int DAT_00519ba8[4];
extern int DAT_00519c00[4];
extern int DAT_00519c28[4];
extern int DAT_00519c30[4];
extern int DAT_0051a040[4];
extern int DAT_0051a050[4];
extern int DAT_0051a060[4];
extern int DAT_0051a070[4];
extern int DAT_0051a080[4];
extern int DAT_0051a088[4];
extern int DAT_0051a098[4];
extern int DAT_0051a0a8[4];
extern int DAT_0051a0b8[4];
extern int DAT_0051a0c8[4];
}

typedef igObject RefHeader;
/* Owning stack reference to a pooled string token (reference count at p[-1], chunk header at
 * p[-2]); releases the token on scope exit. */
class StringRef {
public:
    const char *p;
    StringRef(const char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};
/* Owning stack reference to a sub-window created here; released on scope exit (reference count in
 * the low 23 bits of _refCount). */
class WindowRef {
public:
    RefHeader *p;
    WindowRef(RefHeader *w) : p(w) {}
    ~WindowRef() { RefHeader *w = p; if (w != 0) { --w->_refCount; if ((w->_refCount & 0x7fffff) == 0) igObject_Destroy(w); } }
};
extern "C" int StringList_AppendRetained(int, const StringRef &);
struct HA { static int Add(int a, int b) { return a + b; } };
struct DummyVirtual {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5();
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11();
    virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
    virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21();
    virtual void v24(void *, void *); virtual int v25(); virtual int v26();
};

#define GET_ALLOC(v) { void *ga = igObject_GetAllocator(self); if (GPR_00554c14 != 0) { v = ga; } else { v = Memory_GetAllocatorBySelector(DAT_00587110[0]); } }
#define INTERN(slot, text) { \
    const char *tok; \
    if ((text) == 0) { tok = 0; } else { \
        if (DAT_00586f20[0] == 0) { \
            void *pool = FUN_002eb010(0x10); \
            if (pool != 0) pool = StringPool_Construct(pool); \
            DAT_00586f20[0] = pool; \
        } \
        tok = StringPool_Intern(DAT_00586f20[0], (const char *)(text)); \
    } \
    slot = tok; }
#define RELEASE_STR(slot) { const char *held = slot; \
    if (held != 0) { int *hd = (int *)held - 2; \
        int cnt = ((int *)held)[-1] - 1; ((int *)held)[-1] = cnt; \
        if (cnt == 0) StringChunk_ReleaseHeader(*hd, hd); } }
#define INTERN_APPEND(field, text) { const char *token; INTERN(token, text) StringList_AppendRetained(field, StringRef(token)); }
#define INTERNP(slot, ptr) { \
    const char *src = (const char *)(ptr); \
    const char *tok; \
    if (src == 0) { tok = 0; } else { \
        if (DAT_00586f20[0] == 0) { \
            void *pool = FUN_002eb010(0x10); \
            if (pool != 0) pool = StringPool_Construct(pool); \
            DAT_00586f20[0] = pool; \
        } \
        tok = StringPool_Intern(DAT_00586f20[0], src); \
    } \
    slot = tok; }
#define INTERNP_APPEND(field, ptr) { const char *token; INTERNP(token, ptr) StringList_AppendRetained(field, StringRef(token)); }
#define RETAIN_OBJ(o) { RefHeader *rr = (RefHeader *)(o); if (rr != 0) rr->_refCount = rr->_refCount + 1; }
#define RELEASE_OBJ(o) { RefHeader *rr = (RefHeader *)(o); \
    if (rr != 0) { rr->_refCount = rr->_refCount - 1; \
        if (((unsigned long long)((long long)(int)rr->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
#define NEXT_ST0() { self->_st0 = self->_st0 + 1; self->_st3 = 0; self->_st2 = 0; self->_st1 = 0; }

extern "C" void Gap__Bec__beNDMWStatusCtrlD0__vfunc_21(beNDMWStatusCtrlD0 *self);
void Gap__Bec__beNDMWStatusCtrlD0__vfunc_21(beNDMWStatusCtrlD0 *self)
{
    float vecA[3];
    float vecB[3];
    void *alloc;
    int i;
    char **fp;
    beNDMWWindowSelect *mother;
    igObjectList *list;
    int rec;

    switch (self->_st0) {
    case 0:
        INTERN_APPEND(self->_textCloseTypeList, &DAT_0051a040[0])
        INTERNP_APPEND(self->_textCloseNameList, DAT_004cf670[0])
        if (self->_isBankFolder != 0) {
            beNDMWWindow_RunMessageScript(self, &DAT_0051a050[0], 0x517);
        } else {
            beNDMWWindow_RunMessageScript(self, &DAT_00519b90[0], 0x46);
        }
        i = 0;
        fp = &DAT_004cf670[0];
        do {
            FUN_003f5410(self, &DAT_0051a060[0], *fp, &DAT_00519b60[0], &DAT_00519b68[0]);
            i += 1;
            fp += 1;
        } while (i < 12);
        i = 0;
        fp = &DAT_004cf670[0];
        do {
            FUN_003f5410(self, &DAT_0051a070[0], *fp, &DAT_00519b60[0], &DAT_0051a080[0]);
            i += 1;
            fp += 1;
        } while (i < 12);
        if (self->_isBankFolder != 0) {
            FUN_003f5410(self, &DAT_0051a088[0], DAT_004cf670[0], &DAT_00519b60[0], &DAT_0051a080[0]);
            FUN_003f5410(self, &DAT_0051a088[0], DAT_004cf674[0], &DAT_00519b60[0], &DAT_0051a080[0]);
        } else {
            FUN_003f5410(self, &DAT_0051a098[0], DAT_004cf670[0], &DAT_00519b60[0], &DAT_0051a080[0]);
            FUN_003f5410(self, &DAT_0051a098[0], DAT_004cf674[0], &DAT_00519b60[0], &DAT_0051a080[0]);
        }
        FUN_003f5410(self, &DAT_00519b50[0], DAT_004cf670[0], &DAT_00519b60[0], &DAT_00519b68[0]);
        GET_ALLOC(alloc)
        {
        WindowRef win((RefHeader *)FUN_003b51b0(alloc));
        beNDMWWindow_BindContext(win.p, self, self->_insight, self->_playerNo, 0);
        ObjectList_AppendRetained(self->_subWindow, win.p);
        ((beNDMWWindowSelect *)win.p)->_selectMax = FUN_004191f0(self);
        {
            RefHeader *dl = (RefHeader *)self->_decideList;
            beNDMWWindowSelect *w;
            w = (beNDMWWindowSelect *)win.p;
            RETAIN_OBJ(dl)
            { RefHeader *old = (RefHeader *)w->_decideList; RELEASE_OBJ(old) }
            w->_decideList = (int)dl;
        }
        { beNDMWWindowSelect *wp = (beNDMWWindowSelect *)win.p; wp->_offsetPos[0] = -121.0f; wp->_offsetPos[1] = 128.0f; wp->_offsetPos[2] = 0.0f; }
        ((beNDMWWindowSelect *)win.p)->_startPoint = 0;
        }
        self->_nowProcKazu = ((igObjectList *)self->_subWindow)->_count;
        beNDMWWindow_PresentModelAtOrigin(self, &DAT_0051a0a8[0], 0, &DAT_0051a0b8[0], &DAT_00519a58[0]);
        vecB[0] = 85.0f;
        vecB[2] = 0.0f;
        vecB[1] = 25.0f;
        vecA[0] = -146.0f;
        vecA[1] = 25.0f;
        vecA[2] = 0.0f;
        ((DummyVirtual *)self)->v24(&vecA[0], &vecB[0]);
        NEXT_ST0()
    case 1:
        switch (self->_st1) {
        case 0:
            FUN_00418ac0(self, 1, 1);
            self->_st1 = self->_st1 + 1;
            self->_st3 = 0;
            self->_st2 = 0;
        case 1:
            if (((igObjectList *)self->_subWindow)->_count == self->_nowProcKazu) {
                if (self->_retCode != -1) {
                    if (self->_retCode != self->_st3) {
                        FUN_00418ac0(self, 0, 1);
                        self->_st3 = self->_retCode;
                        return;
                    }
                    mother = (beNDMWWindowSelect *)*(int *)((int)((igObjectList *)self->_subWindow)->_data);
                    if (beNDMWWindowSelect_CanRequestFO2TOP(mother, self->_subWindow) != 0) {
                        bool ready = false;
                        if (((DummyVirtual *)self)->v25() != 0) {
                            ready = true;
                        } else if (((DummyVirtual *)self)->v26() != 0) {
                            ready = true;
                        }
                        if (ready) {
                            ((beNDMWStatusCtrlD0 *)mother)->_st0 = 4;
                            ((beNDMWStatusCtrlD0 *)mother)->_st3 = 0;
                            ((beNDMWStatusCtrlD0 *)mother)->_st2 = 0;
                            ((beNDMWStatusCtrlD0 *)mother)->_st1 = 0;
                            mother->_selectMax = FUN_004191f0(self);
                            {
                                RefHeader *dl = (RefHeader *)self->_decideList;
                                RETAIN_OBJ(dl)
                                { RefHeader *old = (RefHeader *)mother->_decideList; RELEASE_OBJ(old) }
                                mother->_decideList = (int)dl;
                            }
                            self->_st1 = 0;
                            self->_st3 = 0;
                            self->_st2 = 0;
                            return;
                        }
                    }
                }
            } else {
                if (self->_retCode != -1) {
                    ((beNDMWWindowSelect *)self->_mother)->_retCode = HA::Add(self->_nowPage * 12, self->_retCode);
                    self->_cursor = self->_retCode;
                } else {
                    ((beNDMWWindowSelect *)self->_mother)->_retCode = -1;
                }
                if (self->_isAutoClose != 0) {
                    NEXT_ST0()
                    return;
                }
                self->_st1 = self->_st1 + 1;
                self->_st3 = 0;
                self->_st2 = 0;
                return;
            }
            break;
        case 2:
            switch (self->_st2) {
            case 1:
                GET_ALLOC(alloc)
                {
                WindowRef win((RefHeader *)FUN_003b51b0(alloc));
                beNDMWWindow_BindContext(win.p, self, self->_insight, self->_playerNo, 0);
                ObjectList_AppendRetained(self->_subWindow, win.p);
                beMessenger_SelectGroup(self->_messenger, &DAT_00519ba0[0]);
                beMessenger_AppendInt(self->_messenger, self->_playerNo);
                beMessenger_DispatchSelected(self->_messenger, &DAT_00519ba8[0]);
                rec = beMessenger_GetObject(self->_messenger, 0);
                if (self->_isBankFolder != 0) {
                    Rec *fo = igProperty_GetRecordFolder(rec, &DAT_0051a0c8[0]);
                    list = fo->f12;
                } else {
                    Rec *fo = igProperty_GetRecordFolder(rec, &DAT_00519c00[0]);
                    list = fo->f12;
                }
                if (self->_cursor + self->_nowPage * 12 >= list->_count) {
                    if (self->_cursor == 0) {
                        if (self->_nowPage > 0) {
                            self->_nowPage = self->_nowPage - 1;
                        }
                    } else {
                        self->_cursor = self->_cursor - 1;
                    }
                }
                if (self->_nowPage == 0) {
                    beMessenger_SendNamed(self->_messenger, &DAT_00519a90[0], &DAT_00519a40[0], 0, &DAT_00519a50[0]);
                }
                if (list->_count <= (self->_nowPage + 1) * 12) {
                    beMessenger_SendNamed(self->_messenger, &DAT_00519a90[0], &DAT_00519a70[0], 0, &DAT_00519a50[0]);
                }
                ((beNDMWWindowSelect *)win.p)->_selectMax = FUN_004191f0(self);
                {
                    RefHeader *dl = (RefHeader *)self->_decideList;
                    beNDMWWindowSelect *w;
                    w = (beNDMWWindowSelect *)win.p;
                    RETAIN_OBJ(dl)
                    { RefHeader *old = (RefHeader *)w->_decideList; RELEASE_OBJ(old) }
                    w->_decideList = (int)dl;
                }
                { beNDMWWindowSelect *wp = (beNDMWWindowSelect *)win.p; wp->_offsetPos[0] = -121.0f; wp->_offsetPos[1] = 128.0f; wp->_offsetPos[2] = 0.0f; }
                ((beNDMWWindowSelect *)win.p)->_startPoint = self->_cursor;
                }
                self->_st0 = 1;
                self->_st3 = 0;
                self->_st2 = 0;
                self->_st1 = 0;
                return;
            }
            break;
        }
        break;
    case 2:
        beNDMWWindow_PlayQueuedModelClose(self);
        beNDMWWindow_ClearQueuedText(self);
        beNDMWWindow_RequestChildrenClose(self);
        i = 0;
        fp = &DAT_004cf670[0];
        self->_st0 = self->_st0 + 1;
        self->_st3 = 0;
        self->_st2 = 0;
        self->_st1 = 0;
        do {
            beMessenger_SelectGroup(self->_messenger, &DAT_00519c28[0]);
            beMessenger_AppendString(self->_messenger, &DAT_0051a060[0]);
            beMessenger_AppendString(self->_messenger, *fp);
            beMessenger_DispatchSelected(self->_messenger, &DAT_00519c30[0]);
            beMessenger_SelectGroup(self->_messenger, &DAT_00519c28[0]);
            beMessenger_AppendString(self->_messenger, &DAT_0051a070[0]);
            beMessenger_AppendString(self->_messenger, *fp);
            beMessenger_DispatchSelected(self->_messenger, &DAT_00519c30[0]);
            i += 1;
            fp += 1;
        } while (i < 12);
        return;
    case 3:
        if (beNDMWWindow_PollCloseComplete(self) != 0) {
            self->_isRun = 0;
        }
        break;
    }
}
