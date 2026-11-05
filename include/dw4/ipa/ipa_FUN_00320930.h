/* callee body compiled before its caller in the same unit: the compiler then knows which registers it leaves untouched (interprocedural register use). Verified as a duplicate of the real function at 0x00320930. */
static void FUN_00320930(unsigned char *arg0) {
    unsigned short x;
    ((unsigned char *)&x)[0] = arg0[1];
    ((unsigned char *)&x)[1] = arg0[0];
    *(unsigned short *)arg0 = x;
}
