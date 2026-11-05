/* callee body compiled before its caller in the same unit: the compiler then knows which registers it leaves untouched (interprocedural register use). Verified as a duplicate of the real function at 0x00320960. */
static void FUN_00320960(unsigned char *arg0) {
    union { unsigned char b[4]; int w; } u;
    u.b[0] = arg0[3];
    u.b[1] = arg0[2];
    u.b[2] = arg0[1];
    u.b[3] = arg0[0];
    *(int *)arg0 = u.w;
}
