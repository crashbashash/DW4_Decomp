/* callee body compiled before its caller in the same unit: the compiler then knows which registers it leaves untouched (interprocedural register use). Verified as a duplicate of the real function at 0x0015f430. */
static int FUN_0015f430(void *arg0, int arg1, int arg2, int arg3) { if (arg1 == *(int *)((char *)(arg0) + 16)) { if (arg2 == *(int *)((char *)(arg0) + 20)) { return 1; } } return 0; }
