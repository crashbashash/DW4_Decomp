extern "C" {
int Memory_FreeBufferWithAllocator(int, int);
int Memory_GetAllocatorBySelector(int);
int igObject_GetAllocator();
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}
struct S { int pad[2]; int f8; };

extern "C" {
void FUN_003a9990(struct S *arg0);
}
void FUN_003a9990(struct S *arg0) {
    int var_v0;

    if (arg0->f8 != 0) {
        var_v0 = igObject_GetAllocator();
        var_v0 = (GPR_00554c14 != 0) ? var_v0 : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        Memory_FreeBufferWithAllocator(arg0->f8, var_v0);
    }
    arg0->f8 = 0;
}
