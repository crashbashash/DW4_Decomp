struct T { int word0; int references; int w8; int w12; };
extern int strlen();
extern char FUN_0012c4c8();
extern struct T *FUN_002b9500();
extern int FUN_002eb010();
extern int FUN_0030b3c0();
extern int FUN_0030b460();
extern int Memory_GetAllocatorBySelector();
extern int StringChunk_ReleaseHeader();
extern int StringPool_Construct();
extern char *StringPool_Intern();
extern int igObject_Destroy();
extern char *DAT_004c22f0[4];
extern char DAT_004ffbe8[];
extern char DAT_004ffbf0[];
extern int DAT_00586f20[4];
extern int DAT_00587048[4];
int FUN_0032c240(char **arg0, char *arg1, char *arg2) {
    struct T * volatile sp5C;
    char * volatile sp58;
    struct T *q;
    int lim, s0, s1;
    char *p, *s;
    char c;
    char *v;
    sp5C = FUN_002b9500(Memory_GetAllocatorBySelector(DAT_00587048[0]));
    if (arg1 == 0) {
        FUN_0030b3c0(sp5C, arg2);
    } else if (*arg1 == 0x63) {
        FUN_0030b3c0(sp5C, arg1);
        c = *arg2;
        if (c != 0x5C && c != 0x2F) {
            q = sp5C;
            s1 = q->w12;
            FUN_0030b460(q, DAT_004ffbe8, s1, strlen(DAT_004ffbe8));
        }
        q = sp5C;
        s1 = q->w12;
        FUN_0030b460(q, arg2, s1, strlen(arg2));
        q = sp5C;
        s1 = q->w12;
        FUN_0030b460(q, DAT_004ffbf0, s1, strlen(DAT_004ffbf0));
        lim = strlen(arg2) + 8;
        for (s0 = 7; s0 < lim; s0++) {
            p = (char *)(sp5C->w8 + s0);
            if (*p == 0x2F) {
                *p = 0x5C;
            } else {
                *p = FUN_0012c4c8(*p);
            }
        }
    } else {
        FUN_0030b3c0(sp5C, arg1);
        q = sp5C;
        s1 = q->w12;
        FUN_0030b460(q, arg2, s1, strlen(arg2));
    }
    s = (char *)sp5C->w8;
    if (s == 0) s = DAT_004c22f0[0];
    if (s == 0) {
        v = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            int pool = FUN_002eb010(16);
            if (pool != 0) pool = StringPool_Construct(pool);
            DAT_00586f20[0] = pool;
        }
        v = StringPool_Intern(DAT_00586f20[0], s);
    }
    sp58 = v;
    *arg0 = sp58;
    if (*arg0 != 0) {
        ((int *)*arg0)[-1] = ((int *)*arg0)[-1] + 1;
    }
    v = sp58;
    if (v != 0) {
        int *h = (int *)(v - 8);
        if (--h[1] == 0) StringChunk_ReleaseHeader(h[0], h);
    }
    q = sp5C;
    if (q != 0) {
        q->references = q->references - 1;
        if ((q->references & 0x7FFFFF) == 0) igObject_Destroy(q);
    }
    return 0;
}
