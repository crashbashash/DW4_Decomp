struct S { int *vt; char pad[468]; int a; char b[72]; int c; };
int FUN_001a10a0();
int FUN_001a1090();
int FUN_001510a0();
int FUN_001a1080();
int FUN_001a1000();
int FUN_00198190();
int FUN_001a0910();
extern int DAT_00528f10[4];
extern void * DAT_00586dc8[4];
int igFrustCullTraversal_GetVTable(void) {
    struct S s; char *p;
    int r;
    p = (char *)&s; FUN_001a10a0(p);
    s.vt = &DAT_00528f10[0];
    FUN_001a1090(&s.a);
    FUN_001510a0(s.b);
    FUN_001a1080(p + 548);
    r = *(int *)((char *)&s + *(int *)((char *)(DAT_00586dc8[0]) + 916));
    s.vt = &DAT_00528f10[0];
    FUN_001a1000(&s.c, -1);
    FUN_00198190(&s.a, -1);
    FUN_001a0910(&s, 0);
    return r;
}
