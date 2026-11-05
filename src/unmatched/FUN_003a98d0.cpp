extern "C" {
int memset(void *, int, int);
int FUN_002ed2b0(int, int, int);
int Memory_AllocateBufferDirect(int, int);
int Memory_GetAllocatorBySelector(int);
int igObject_GetAllocator(void *);
extern int DAT_00587110[4];
extern unsigned char GPR_00554c14;
}

struct O {
    char pad[8];
    void *buf;
};

extern "C" {
void FUN_003a98d0(struct O *arg0, int arg1, int arg2);
}
void FUN_003a98d0(struct O *arg0, int arg1, int arg2) {
    int a, b;

    if (arg2 == 0) {
        a = igObject_GetAllocator(arg0);
        b = GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        arg0->buf = (void *)Memory_AllocateBufferDirect(arg1, b);
    } else {
        a = igObject_GetAllocator(arg0);
        b = GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(DAT_00587110[0]);
        arg0->buf = (void *)FUN_002ed2b0(arg1, arg2 & 0xFFFF, b);
    }
    memset(arg0->buf, 0, arg1);
}
