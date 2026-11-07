struct S { char pad[8]; int f8; char pad2[32]; int f44; };
extern "C" {
int FUN_0026b728(...);
int Memory_FreeBufferWithAllocator(...);
int igObject_GetAllocator(...);
void FUN_003323d0(S *arg0);
}
void FUN_003323d0(S *arg0) {
    if (arg0->f44 != 0) {
        FUN_0026b728(arg0->f44);
    }
    if (arg0->f8 != 0) {
        Memory_FreeBufferWithAllocator(arg0->f8, igObject_GetAllocator(arg0));
    }
}
