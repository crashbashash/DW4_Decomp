struct S { char p[70]; signed char f : 7; unsigned char g : 1; };
void FUN_0020c800(volatile struct S *arg0) {
    if (arg0->f != 1) {
        arg0->f = 6;
    }
}
