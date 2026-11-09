#include "dw4/igSmartPointer.h"

extern "C" {
extern int DAT_00587108[4];
extern unsigned char GPR_00554c14;
struct Obj : public igObject { int w8; int w12; };
extern void *FUN_00366910(int);
extern int FUN_0037d4a0(int);
extern int FUN_003a6950(int, int);
extern int Memory_GetAllocatorBySelector(int);
extern int ObjectList_AppendRetained(void *, void *);
extern int igNamedObject_SetName(void *, int);
extern int igObject_GetAllocator(int);
}

#define LIST(a) (*(void **)((a) + 40))
extern "C" void FUN_0037d310(int arg0) {
    int i;
    if (*(int *)((char *)LIST(arg0) + 8) > 0) FUN_0037d4a0(arg0);
    i = 0;
    do {
        {
        int a = igObject_GetAllocator(arg0);
        a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587108[0]);
        igSmartPointer<Obj> r((Obj *)FUN_00366910(a));
        FUN_003a6950(r.p->w12, 1);
        igNamedObject_SetName(r, 0);
        ObjectList_AppendRetained(LIST(arg0), r);
        }
        i++;
    } while (i < 4);
    i = 0;
    do {
        {
        int a = igObject_GetAllocator(arg0);
        a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587108[0]);
        igSmartPointer<Obj> r((Obj *)FUN_00366910(a));
        FUN_003a6950(r.p->w12, -1);
        igNamedObject_SetName(r, 0);
        ObjectList_AppendRetained(LIST(arg0), r);
        }
        i++;
    } while (i < 48);
}
