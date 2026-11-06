#include "dw4/reflected.h"
/* self is the PEBase model controller (_messenger), obj a beBaseInfoRam (_ramNo) and the work
 * record a beNDMWMdlPEBaseInfoWork (_isPlayer, _downDataList). */
typedef struct Rc { int w0; int references; } Rc;
typedef struct List { int w0; int references; int size; int cap; int *data; } List;
typedef struct Obj { char pad[12]; Rc *f12; } Obj;
extern "C" {
extern void *FUN_002caa70(int);
extern void *FUN_003a9250(void *, int *);
extern int List_Reserve(List *, int, int);
extern int List_Resize(List *, int, int);
extern int Memory_GetAllocatorBySelector(int);
extern int beMessenger_AppendInt(int, int);
extern int beMessenger_DispatchSelected(int, int *);
extern void *beMessenger_GetObject(int, int);
extern int beMessenger_PopArgContext(int);
extern int beMessenger_PushArgContext(int);
extern int beMessenger_SelectGroup(int, int *);
extern int igObject_Destroy(void *);
extern int igObject_GetAllocator();
extern int DAT_004cfdd8[4];
extern int DAT_0051d4b0[4];
extern int DAT_0051d4b8[4];
extern int DAT_0051d4d8[4];
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void FUN_004456c0(beNDMWMdlPEBase *arg0, beBaseInfoRam *arg1, beNDMWMdlPEBaseInfoWork *arg2);
}
/* Owning stack reference to the freshly created down-data list, released on scope exit (reference
 * count in the low 23 bits of references). */
class ObjectRef {
public:
    List *p;
    ObjectRef(List *o) : p(o) {}
    ~ObjectRef() { List *o = p; if (o != 0) { --o->references; if ((o->references & 0x7fffff) == 0) igObject_Destroy(o); } }
};

void FUN_004456c0(beNDMWMdlPEBase *arg0, beBaseInfoRam *arg1, beNDMWMdlPEBaseInfoWork *arg2) {
    if (arg2->_isPlayer != 0) {
        Rc *s0;
        Rc *old;
        beMessenger_PushArgContext(arg0->_messenger);
        beMessenger_SelectGroup(arg0->_messenger, &DAT_0051d4b0[0]);
        beMessenger_AppendInt(arg0->_messenger, arg1->_ramNo);
        beMessenger_DispatchSelected(arg0->_messenger, &DAT_0051d4b8[0]);
        s0 = ((Obj *)FUN_003a9250(beMessenger_GetObject(arg0->_messenger, 0), &DAT_0051d4d8[0]))->f12;
        if (s0 != 0) s0->references = s0->references + 1;
        old = (Rc *)arg2->_downDataList;
        if (old != 0) {
            old->references = old->references - 1;
            if (((unsigned long long)((long long)old->references << 0x29) >> 0x29) == 0) igObject_Destroy(old);
        }
        arg2->_downDataList = (int)s0;
        beMessenger_PopArgContext(arg0->_messenger);
        return;
    }
    {
        int alloc;
        int n;
        int *data;
        int j;
        Rc *s0;
        Rc *old;
        alloc = igObject_GetAllocator(); /* matching construct: a0 still holds arg0, retail passes it without a move */
        /* The six-entry list is owned by the stack reference until the work record has taken its own. */
        ObjectRef created((List *)FUN_002caa70(GPR_00554c14 != 0 ? alloc : Memory_GetAllocatorBySelector(DAT_00587110[0])));
        if (created.p->size < 7) List_Reserve(created.p, 6, 4);
        if (created.p->cap >= 6) created.p->size = 6;
        else List_Resize(created.p, 6, 4);
        n = created.p->size;
        data = created.p->data;
        for (j = 0; j < n; j++) data[j] = DAT_004cfdd8[0];
        s0 = (Rc *)created.p;
        if (s0 != 0) s0->references = s0->references + 1;
        old = (Rc *)arg2->_downDataList;
        if (old != 0) {
            old->references = old->references - 1;
            if (((unsigned long long)((long long)old->references << 0x29) >> 0x29) == 0) igObject_Destroy(old);
        }
        arg2->_downDataList = (int)s0;
    }
}
