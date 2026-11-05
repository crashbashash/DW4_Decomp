struct S { char pad[60]; int f60; };
int ReferThreadStatus();
unsigned char FUN_003301f0(struct S *arg0) {
    int a; unsigned char r;
    a = arg0->f60; r = 0; if (a != -1) { int s = ReferThreadStatus(a, 0); if (s & 0xF) r = 1; }
    return r;
}
