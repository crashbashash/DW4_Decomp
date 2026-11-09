#include "dw4/igSmartPointer.h"
struct O : public igVirtualObject {
  virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
  virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
  virtual void d20(); virtual void d21(); virtual void d22();
  virtual int v23(int *, int *);
  char pad8[64]; void *f72; };
extern "C" {
int FUN_002d01a0(...);
int FUN_002eb010(...);
int FUN_002f8a20(...);
int FUN_00304350(...);
int FUN_003043c0(...);
int FUN_00306e50(...);
int Memory_GetAllocatorBySelector(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
void *StringPool_Intern(...);
extern int DAT_004f9c50[4];
extern int DAT_004ffcf0[4];
extern int DAT_004ffd08[4];
extern int DAT_004ffd18[4];
extern void * DAT_00586dc8[4];
extern int DAT_00586f20[4];
extern int DAT_00587038[4];
extern int DAT_00587338[4];
extern int DAT_00587358[4];
extern unsigned char GPR_00554c14;
}

static inline int internPool(void) {
    if (DAT_00586f20[0] == 0) {
        int a = FUN_002eb010(0x10);
        if (a != 0) {
            a = StringPool_Construct(a);
        }
        DAT_00586f20[0] = a;
    }
    return DAT_00586f20[0];
}
static inline void setName(O *object, int name) {
    int *interned = (int *)StringPool_Intern(internPool(), name);
    if (object->f72 != 0) {
        int *header = (int *)object->f72 - 2;
        int count = ((int *)object->f72)[-1] - 1;
        ((int *)object->f72)[-1] = count;
        if (count == 0) {
            StringChunk_ReleaseHeader(*header, header);
        }
    }
    object->f72 = interned;
}
static inline int fileAllocator(void) {
    int a = FUN_002f8a20();
    return GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(DAT_00587038[0]);
}
extern "C" void FUN_0032d220(void) {
    unsigned char enabled;
    FUN_00306e50(*(int *)((char *)(DAT_00586dc8[0]) + 56), 2, &DAT_004ffcf0[0], &enabled, 1, 0);
    if (enabled != 0) {
        FUN_00304350(0);
        FUN_003043c0(0);
        igSmartPointer<O> first((O *)FUN_002d01a0(fileAllocator()));
        igSmartPointer<O> second((O *)FUN_002d01a0(fileAllocator()));
        if (DAT_00587338[0] != 0) {
            setName(first.p, DAT_00587358[0]);
            setName(second.p, DAT_00587358[0]);
        }
        if (first->v23(&DAT_004ffd08[0], &DAT_004f9c50[0]) != 0) {
            FUN_00304350(first.p);
        }
        if (second->v23(&DAT_004ffd18[0], &DAT_004f9c50[0]) != 0) {
            FUN_003043c0(second.p);
        }
    }
}
