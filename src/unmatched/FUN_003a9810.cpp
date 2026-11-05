extern "C" {
int Memory_AllocateBufferDirect(int, int);
int Memory_GetAllocatorBySelector(int);
int igObject_GetAllocator(void *);
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
void FUN_003a9810(void *arg0, int arg1);
}
void FUN_003a9810(void *arg0, int arg1) {
    int t;
    int a;
    *(int *)((char *)(arg0) + 12) = arg1;
    t = igObject_GetAllocator(arg0);
    if (GPR_00554c14 != 0) {
        a = t;
    } else {
        a = Memory_GetAllocatorBySelector(DAT_00587110[0]);
    }
    *(int *)((char *)(arg0) + 8) = Memory_AllocateBufferDirect(arg1, a);
}
