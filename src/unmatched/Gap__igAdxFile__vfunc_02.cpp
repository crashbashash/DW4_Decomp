extern "C" {
/* 0x003338d0 — Gap__igAdxFile__vfunc_02. Banked by tools/retype_struct_member.py (shape: struct0):
 * the m2c draft plus a mechanical source respelling, verified
 * byte-identical to retail by tools/verify.py. */
typedef struct S0 { char pad48[48]; int f30; int f34; int f38; } S0;
int Memory_FreeBufferWithAllocator(int, int);
int igObject_GetAllocator(S0 *); /* takes the object; the C draft dropped the argument at the first site */

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
