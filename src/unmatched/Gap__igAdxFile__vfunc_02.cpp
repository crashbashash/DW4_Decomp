extern "C" {
typedef struct S0 { char pad48[48]; int f30; int f34; int f38; } S0;
int Memory_FreeBufferWithAllocator(int, int);
int igObject_GetAllocator(S0 *);

void Gap__igAdxFile__vfunc_02(S0 *arg0) {
    if (arg0->f30 != 0) {
        Memory_FreeBufferWithAllocator(arg0->f30, igObject_GetAllocator(arg0));
        arg0->f34 = 0;
    }
    if (arg0->f38 != 0) {
        Memory_FreeBufferWithAllocator(arg0->f38, igObject_GetAllocator(arg0));
    }
}
}
