int igObject_Destroy();
struct R { int w0; int rc; };
struct S { char pad[8]; int f8; };
struct R *FUN_002b9500();
int FUN_0030b7e0();
int igObject_GetAllocator();
extern int DAT_004f9a78[4];
int FUN_002e3950(struct R **out, struct S *a1, int a2) {
    struct R * volatile sp4C;
    struct R *q;
    struct R *t;
    sp4C = FUN_002b9500(igObject_GetAllocator(a1));
    FUN_0030b7e0(sp4C, &DAT_004f9a78[0], a1->f8, a2);
    *out = sp4C;
    q = *out;
    if (q != 0) {
        q->rc = q->rc + 1;
    }
    t = sp4C;
    if (t != 0) {
        t->rc = t->rc - 1;
        if ((t->rc & 0x7FFFFF) == 0) {
            igObject_Destroy(t);
        }
    }
    return 0;
}
