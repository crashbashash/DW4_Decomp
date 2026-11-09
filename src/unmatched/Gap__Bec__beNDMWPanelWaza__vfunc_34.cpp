#include "dw4/reflected.h"
extern "C" {
void *FUN_003bdb10(void *);
int FUN_003bee30();
int FUN_003d0760(void *, void *);
int FUN_003d08f0(void *, void *);
int FUN_003d0a90(void *, void *, int, void *);
int FUN_003a7a20(void *, int *, int);
int FUN_003a7e90(void *, int *);
void *Memory_GetAllocatorBySelector(int);
void igObject_Destroy(void *);
void *igObject_GetAllocator(void *);
unsigned int beMessenger_ResolveEnumValue(int, int, int);
int beMessenger_AppendBool(int, unsigned char);
int beMessenger_AppendString(int, int);
int beMessenger_DispatchSelected(int, int *);
int beMessenger_GetBool(int, int);
int beMessenger_GetBoolCount(int);
int beMessenger_GetInt(int, int);
void *beMessenger_GetObject(int, int);
int beMessenger_PopArgContext(int);
int beMessenger_PushArgContext(int);
int beMessenger_SelectGroup(int, int *);
int beMessenger_SendNamed(int, int *, int, int, int *);
int beMessenger_SetBool(int, int, unsigned char);
extern int DAT_005159c0[4];
extern int DAT_005159d8[4];
extern int DAT_00515a98[4];
extern int DAT_00515bd8[4];
extern int DAT_00515be0[4];
extern int DAT_00515be8[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
int Gap__Bec__beNDMWPanelWaza__vfunc_34(beNDMWPanelWaza *, beNDMWPanelWazaInfoRam *, beMessengerWork *);
}
/* Owning stack reference to the freshly created panel work; released on scope exit (reference
 * count in the low 23 bits of _refCount). */
template <class T> class igSmartPointer {
public:
    T *p;
    igSmartPointer(T *o) : p(o) {}
    ~igSmartPointer() { T *o = p; if (o != 0) { --o->_refCount; if ((o->_refCount & 0x7fffff) == 0) igObject_Destroy(o); } }
};
#define REL(o) { igObject *rr = (o); if (rr != 0) { rr->_refCount = rr->_refCount - 1; if (((unsigned long long)((long long)(int)rr->_refCount << 0x29) >> 0x29) == 0) { igObject_Destroy(rr); } } }
#define RET(o) { igObject *rt = (o); if (rt != 0) rt->_refCount = rt->_refCount + 1; }
#define SETP(T, panel, src, field) { igObject *c = (igObject *)(src); T *pp = (T *)(panel); if (c != 0) c->_refCount = c->_refCount + 1; { igObject *o = (igObject *)pp->field; REL(o) } pp->field = (int)c; }
#define HOOK(T, panel) SETP(T, panel, work->_textSetList, _textSetList) SETP(T, panel, work->_textColorList, _textColorList) ((T *)(panel))->_playerNo = ram->_ramNo; ((T *)(panel))->_manager = (int)self; ((T *)(panel))->_messenger = self->_messenger;
/* matching constructs: ok is a C++ bool (daddiu); the AppendBool/SetBool bool arguments are unsigned char so
 * the byte load is scheduled like retail. */
int Gap__Bec__beNDMWPanelWaza__vfunc_34(beNDMWPanelWaza *self, beNDMWPanelWazaInfoRam *ram, beMessengerWork *arg2) {
    unsigned int kind;
    beNDMWPanelWazaInfoWork *work;
    bool ok;
    void *alloc;
    void *obj;
    kind = beMessenger_ResolveEnumValue(self->_messenger, FUN_003bee30(), arg2->_message);
    work = (beNDMWPanelWazaInfoWork *)ram->_work;
    if (work == 0) {
        alloc = igObject_GetAllocator(self);
        alloc = GPR_00554c14 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        igSmartPointer<igObject> created((igObject *)FUN_003bdb10(alloc));
        { igObject *n = created.p; RET(n) { igObject *o = (igObject *)ram->_work; REL(o) } ram->_work = (int)n; }
        work = (beNDMWPanelWazaInfoWork *)created.p;
        HOOK(beNDMWPanelObjectWaza, work->_panelWaza)
        HOOK(beNDMWPanelObjectItem, work->_panelItem)
        HOOK(beNDMWPanelObjectStat, work->_panelStat)
    }
    switch (kind) {
    case 1:
    case 0:
    case 2:
    case 3:
        ok = true;
        beMessenger_PushArgContext(self->_messenger);
        beMessenger_SendNamed(self->_messenger, DAT_00515bd8, 0, 0, DAT_00515be0);
        if (beMessenger_GetBoolCount(self->_messenger) == 0) {
            ok = false;
        } else if (!(beMessenger_GetBool(self->_messenger, 0) & 0xFF)) {
            ok = false;
        }
        beMessenger_PopArgContext(self->_messenger);
        if (ok) {
            return 1;
        }
        break;
    default:
        break;
    }
    switch (kind) {
    case 0:
    case 1:
    case 2:
        obj = beMessenger_GetObject(self->_messenger, 0);
        switch (kind) {
        case 1:
            FUN_003d0a90(self, ram, 0, obj);
            break;
        case 0:
            FUN_003d0a90(self, ram, 1, obj);
            break;
        case 2:
            FUN_003d0a90(self, ram, 2, obj);
            break;
        }
        ((beNDMWPanelObjectWaza *)work->_panelWaza)->_isEmg = 0;
        ((beNDMWPanelObjectItem *)work->_panelItem)->_isEmg = 0;
        ((beNDMWPanelObjectStat *)work->_panelStat)->_isEmg = 0;
        beMessenger_AppendBool(self->_messenger, 1);
        return 1;
    case 3:
        obj = beMessenger_GetObject(self->_messenger, 0);
        if (FUN_003d0760(self, ram) != 0) {
            FUN_003d0a90(self, ram, 1, obj);
        } else if (FUN_003d08f0(self, ram) != 0) {
            FUN_003d0a90(self, ram, 0, obj);
        } else if (FUN_003a7e90(ram, DAT_00515be8) != 0) {
            beMessenger_PushArgContext(self->_messenger);
            beMessenger_SelectGroup(self->_messenger, DAT_005159c0);
            beMessenger_AppendString(self->_messenger, (int)DAT_00515a98);
            beMessenger_DispatchSelected(self->_messenger, DAT_005159d8);
            beMessenger_PopArgContext(self->_messenger);
            FUN_003a7a20(ram, DAT_00515be8, 0x0FE502AA);
        }
        beMessenger_AppendBool(self->_messenger, 1);
        return 1;
    case 5:
        if (ram->_isRun == 0) {
            return 1;
        }
        ram->_st0 = 2;
        ram->_st3 = 0;
        ram->_st2 = 0;
        ram->_st1 = 0;
        work->_retIsFire = 0;
        return 1;
    case 10:
        if (beMessenger_GetBoolCount(self->_messenger) == 0) {
            beMessenger_AppendBool(self->_messenger, ram->_isRun);
        } else if (!(beMessenger_GetBool(self->_messenger, 0) & 0xFF)) {
            beMessenger_SetBool(self->_messenger, 0, ram->_isRun);
        }
        return 1;
    case 4:
        beMessenger_AppendBool(self->_messenger, ram->_isRun);
        switch (work->_page) {
        case 0:
            beMessenger_AppendBool(self->_messenger, 0);
            beMessenger_AppendBool(self->_messenger, work->_retIsFire);
            beMessenger_AppendString(self->_messenger, work->_retWazaLabel);
            break;
        case 1:
            beMessenger_AppendBool(self->_messenger, 1);
            beMessenger_AppendBool(self->_messenger, work->_retIsFire);
            break;
        case 2:
            beMessenger_AppendBool(self->_messenger, 0);
            beMessenger_AppendBool(self->_messenger, 0);
            break;
        }
        work->_retIsFire = 0;
        return 1;
    case 6:
        if (beMessenger_GetInt(self->_messenger, 0) == 1) {
            ((beNDMWPanelObjectItem *)work->_panelItem)->_isNoGateDisk = 1;
        } else {
            ((beNDMWPanelObjectItem *)work->_panelItem)->_isNoGateDisk = 0;
        }
        return 1;
    case 7:
        if (beMessenger_GetInt(self->_messenger, 0) == 1) {
            ((beNDMWPanelObjectItem *)work->_panelItem)->_isNoHealing = 1;
            ((beNDMWPanelObjectWaza *)work->_panelWaza)->_isNoHealing = 1;
        } else {
            ((beNDMWPanelObjectItem *)work->_panelItem)->_isNoHealing = 0;
            ((beNDMWPanelObjectWaza *)work->_panelWaza)->_isNoHealing = 0;
        }
        return 1;
    case 8:
        if (beMessenger_GetInt(self->_messenger, 0) == 1) {
            ((beNDMWPanelObjectWaza *)work->_panelWaza)->_isNoParaUp = 1;
        } else {
            ((beNDMWPanelObjectWaza *)work->_panelWaza)->_isNoParaUp = 0;
        }
        return 1;
    case 9:
        if (beMessenger_GetInt(self->_messenger, 0) == 1) {
            ((beNDMWPanelObjectItem *)work->_panelItem)->_isNoCureling = 1;
            ((beNDMWPanelObjectWaza *)work->_panelWaza)->_isNoCureling = 1;
        } else {
            ((beNDMWPanelObjectItem *)work->_panelItem)->_isNoCureling = 0;
            ((beNDMWPanelObjectWaza *)work->_panelWaza)->_isNoCureling = 0;
        }
        return 1;
    default:
        return 0;
    }
}
