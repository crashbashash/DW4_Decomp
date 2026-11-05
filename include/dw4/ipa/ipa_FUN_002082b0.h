/* callee body compiled before its caller in the same unit: the compiler then knows which registers it leaves untouched (interprocedural register use). Duplicate of the real function at 0x002082b0. */
typedef struct O {
    long long f0;
    long long f8;
    int pad[2];
    void *f24;
    int f28;
    char pad2[38];
    signed char lo : 7;
    unsigned char hi : 1;
} O;
extern void *DAT_0056c0c8[4];
static void FUN_002082b0(O *arg0) {
    arg0->lo = 0;
    arg0->f8 = 0;
    arg0->f0 = 0;
    arg0->f24 = DAT_0056c0c8[0];
    arg0->f28 = 0;
    DAT_0056c0c8[0] = arg0;
}
