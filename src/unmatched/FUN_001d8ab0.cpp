#include "dw4/igSmartPointer.h"
#include "dw4/reflected.h"
extern "C" {
igObject *FUN_00198cc0(int);
int FUN_00199080();
int FUN_002d8310(igObject *, igObject *);
igSmartPointer<igObject> FUN_003087a0(int, int *);
int Memory_GetAllocatorBySelector(int);
int igNamedObject_SetName(igObject *, int *);
extern int DAT_004e4870[4];
extern int DAT_004fb3a8[4];
extern int DAT_00586dd0[4];
extern int DAT_00587038[4];
}
extern "C" void FUN_001d8ab0(void) {
    FUN_00199080();
    igSmartPointer<igObject> created(FUN_00198cc0(Memory_GetAllocatorBySelector(DAT_00587038[0])));
    igNamedObject_SetName(created.get(), &DAT_004e4870[0]);
    igSmartPointer<igObject> found = FUN_003087a0(DAT_00586dd0[0], &DAT_004fb3a8[0]);
    FUN_002d8310(found.p, created.get());
}
