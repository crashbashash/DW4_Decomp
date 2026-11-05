struct Ref { int pad; union { int w; struct { unsigned cnt : 23; unsigned f : 9; } b; } u; char *str; int len; };
struct Ref *FUN_002b9500();
int FUN_002eb010();
int FUN_0030b3c0();
int FUN_0030b5c0();
int FUN_0030bbf0();
int Memory_GetAllocatorBySelector();
int StringPool_Construct();
int StringPool_Intern();
int igObject_Destroy();
extern char *DAT_004c22f0[4];
extern int DAT_00586f20[4];
extern int DAT_00587048[4];
int FUN_001554a0(int *arg0, int arg1) {
    struct Ref *volatile p;
    struct Ref *t;
    int i;
    char *s;
    int r;

    p = FUN_002b9500(Memory_GetAllocatorBySelector(DAT_00587048[0]));
    FUN_0030b3c0(p, arg1);
    FUN_0030b5c0(p);
    for (i = p->len - 1; i >= 0; i--) {
        t = p;
        if (t->str[i] == 0x5F) {
            FUN_0030bbf0(t, i, 1);
        }
    }
    s = p->str;
    if (s == 0) {
        s = DAT_004c22f0[0];
    }
    if (s == 0) {
        r = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            r = FUN_002eb010(0x10);
            if (r != 0) {
                r = StringPool_Construct(r);
            }
            DAT_00586f20[0] = r;
        }
        r = StringPool_Intern(DAT_00586f20[0], s);
    }
    *arg0 = r;
    t = p;
    if (t) {
        t->u.w = t->u.w - 1;
        if (t->u.b.cnt == 0) {
            igObject_Destroy(t);
        }
    }
    return 0;
}
