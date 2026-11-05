struct S { char pad[20]; int f; };
void FUN_001c6230(struct S *arg0, int arg1, int arg2) {
    if (arg2 != 0) {
        arg0->f = arg0->f | arg1;
    } else {
        arg0->f = arg0->f & ~arg1;
    }
}
