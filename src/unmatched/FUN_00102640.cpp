extern "C" {
char *FUN_00100cf0(char *a, void *b);
struct O {
    char p0[20];
    int f20;
    int f24;
    char p28[484];
    __int128 f512;
    int q528[4];
    int f544;
    int f548;
    int f552;
    int f556;
    int f560;
    int f564;
    int f568;
};
struct S { char p0[4]; char *p; };

void FUN_00102640(struct O *o, struct S *s) {
    char *p = s->p;
    char *r;
    int c = *p & 0x40;
    o->f560 = *p & 0x20;
    o->f556 = *p & 0x10;
    o->f552 = *p & 0xf;
    r = FUN_00100cf0(FUN_00100cf0(p + 1, &o->f544), &o->f548);
    if (o->f560 != 0) {
        o->f24 = (int)o->f512;
    } else {
        o->f24 = o->f20;
    }
    if (c) {
        FUN_00100cf0(r, &o->f564);
    } else {
        o->f564 = 0;
    }
}
}
