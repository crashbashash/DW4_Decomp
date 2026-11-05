extern "C" {
int Memory_FreeBufferWithAllocator(int, int);
int Memory_GetAllocatorBySelector(int);
int igObject_GetAllocator(void *);
extern int DAT_00587108[4];
extern int DAT_005878c0[4];
extern unsigned char GPR_00554c14;
int Gap__igCriMovieCodec__vfunc_29(void *arg0);
}
int Gap__igCriMovieCodec__vfunc_29(void *arg0) {
    int a;

    a = igObject_GetAllocator(arg0);
    a = GPR_00554c14 ? a : Memory_GetAllocatorBySelector(DAT_00587108[0]);
    Memory_FreeBufferWithAllocator(DAT_005878c0[0], a);
    return 1;
}
