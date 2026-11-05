struct R { int *a; R() {} R(int *x) { a = x; } };
class Q { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int v104(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual R v228(int, int); };
extern "C" {
int sprintf(char *, int *, int *);
int strlen(int *);
int FUN_002eb010(int);
int FUN_00300f50(void *, void *);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
int *StringPool_Intern(int, char *);
char *igObject_AllocateStorage(void *, int);
extern int DAT_004f95a0[4];
extern int DAT_00586f20[4];
int FUN_002fca80(int **arg0, Q *arg1, int arg2, int arg3, int arg4);
}

int FUN_002fca80(int **arg0, Q *arg1, int arg2, int arg3, int arg4)
{
    int i;
    int **list;
    int total;
    int cnt;
    int **slot;
    int *t;
    int *old;
    int *a1;
    int v;
    char *buf;
    char *p;
    int pool;
    int *r;

    list = (int **)igObject_AllocateStorage(arg1, arg3 * 4);
    total = 0;
    cnt = 0;
    for (i = 0; i < arg3; i++) {
        R spAC = arg1->v228(arg2, arg4);
        if (spAC.a != 0) {
            slot = list + cnt;
            cnt++;
            if (spAC.a != 0) {
                spAC.a[-1] = spAC.a[-1] + 1;
            }
            old = *slot;
            if (old != 0) {
                a1 = old - 2;
                v = old[-1] - 1;
                old[-1] = v;
                if (v == 0) {
                    StringChunk_ReleaseHeader(*a1, a1);
                }
            }
            *slot = spAC.a;
            total += strlen(spAC.a);
            arg2 += arg1->v104();
        }
        t = spAC.a;
        if (t != 0) {
            a1 = t - 2;
            v = t[-1] - 1;
            t[-1] = v;
            if (v == 0) {
                StringChunk_ReleaseHeader(*a1, a1);
            }
        }
    }
    buf = igObject_AllocateStorage(arg1, total + 1);
    p = buf;
    for (i = 0; i < cnt; i++) {
        p += sprintf(p, DAT_004f95a0, list[i]);
    }
    *p = 0;
    if (buf == 0) {
        r = 0;
    } else {
        if (DAT_00586f20[0] == 0) {
            pool = FUN_002eb010(16);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            DAT_00586f20[0] = pool;
        }
        r = StringPool_Intern(DAT_00586f20[0], buf);
    }
    int * volatile spA8 = r;
    FUN_00300f50(arg1, list);
    FUN_00300f50(arg1, buf);
    *arg0 = spA8;
    t = *arg0;
    if (t != 0) {
        t[-1] = t[-1] + 1;
    }
    t = spA8;
    if (t != 0) {
        a1 = t - 2;
        v = t[-1] - 1;
        t[-1] = v;
        if (v == 0) {
            StringChunk_ReleaseHeader(*a1, a1);
        }
    }
    return 0;
}
