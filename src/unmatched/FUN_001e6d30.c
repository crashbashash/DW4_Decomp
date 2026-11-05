/* 0x1e6d30 — FUN_001e6d30. Retyped m2c draft, verified byte-identical by tools/verify.py. */
int FUN_00129ef8(int, int, int *, int *, int *);
int FUN_0018be80(int, int *, int, int, int);
int FUN_001e6d30(int arg0, int *arg1, int arg2) {
    if (arg2 != 0) {
        return FUN_00129ef8(arg0, arg2, arg1, arg1 + 1, arg1 + 2) == 3;
    }
    return FUN_0018be80(arg0, arg1, 3, 4, 1) != 0;
}
