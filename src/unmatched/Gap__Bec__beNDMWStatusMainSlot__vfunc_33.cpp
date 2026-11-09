#include "dw4/igSmartPointer.h"

extern "C" {
void *FUN_002eb010(int);
void *StringPool_Construct(void *);
const char *StringPool_Intern(void *, const char *);
void StringChunk_ReleaseHeader(int, int *);
beNDMWStatusSelectE1 *FUN_003b51b0(void *);
void *Memory_GetAllocatorBySelector(int);
void *igObject_GetAllocator();
int beNDMWWindow_BindContext(void *, void *, int, int, int);
int ObjectList_AppendRetained(int, void *);
int beNDMWWindow_RunMessageScript(void *, int *, int);
extern int DAT_00519b50[4];
extern int DAT_00519b90[4];
extern int DAT_00519d98[4];
extern void *DAT_00586f20[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
struct SlotKind { char p[24]; int startPoint; };
class StringRef {
public:
    const char *p;
    StringRef(const char *s) : p(s) {}
    ~StringRef() { if (p) { int *h = (int *)p - 2; int r = ((int *)p)[-1] - 1; ((int *)p)[-1] = r; if (r == 0) StringChunk_ReleaseHeader(*h, h); } }
};

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
extern "C" int StringList_AppendRetained(int, StringRef *);
extern "C" void Gap__Bec__beNDMWStatusMainSlot__vfunc_33(beNDMWStatusMainSlot *self) {
    void *alloc;
    int startPoint;
    alloc = igObject_GetAllocator();
    alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
    igSmartPointer<beNDMWStatusSelectE1> win(FUN_003b51b0(alloc));
    beNDMWWindow_BindContext(win.p, self, self->_insight, self->_playerNo, 0);
    { beNDMWStatusSelectE1 *window = win.p; ObjectList_AppendRetained(self->_subWindow, window); }
    INTERN_APPEND(win.p->_textCloseTypeList, DAT_00519b50)
    INTERN_APPEND(win.p->_textCloseNameList, DAT_00519d98)
    beNDMWWindow_RunMessageScript(win.p, DAT_00519b90, 0x8A);
    startPoint = 1;
    igObjectList *kinds = (igObjectList *)self->_mainSlot;
    if (kinds->_count > 0) {
        SlotKind *kind = ((SlotKind **)kinds->_data)[self->_kindListPos];
        if (kind != 0) startPoint = kind->startPoint;
    }
    win.p->_selectMax = startPoint;
    { beNDMWStatusSelectE1 *window = win.p;
    window->_offsetPos[0] = -83.0f;
    window->_offsetPos[1] = 55.0f;
    window->_offsetPos[2] = 0.0f; }
    win.p->_startPoint = self->_pocketPos;
}
