struct S { char pad[8]; int f8; int fc; };
extern "C" {
int Memory_FreeBufferWithAllocator(int, int);
int Memory_GetAllocatorBySelector(int);
int igObject_GetAllocator(S *);
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void FUN_003a9870(struct S *arg0);
}

void FUN_003a9870(struct S *arg0) {
    int var_v0;

    if (arg0->f8 != 0) {
        var_v0 = igObject_GetAllocator(arg0);
        var_v0 = (GPR_00554c14 != 0) ? var_v0 : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        Memory_FreeBufferWithAllocator(arg0->f8, var_v0);
    }
    arg0->f8 = 0;
    arg0->fc = 0;
}
