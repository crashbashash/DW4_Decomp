extern "C" {
int sprintf(char *, int *, char *);
int strlen(char *);
int FUN_002eb010(int);
int FUN_00300f50(void *, void *);
int StringChunk_ReleaseHeader(int, int *);
int StringPool_Construct(int);
char *StringPool_Intern(int, char *);
char *igObject_AllocateStorage(void *, int);
extern int DAT_004f95a0[4];
extern int DAT_00586f20[4];
}
struct igString {
    char *p;
    igString(char *text) : p(text) {}
    igString(const igString &other) : p(other.p) {
        char *o = p;
        if (o != 0) {
            *(int *)(o - 4) = *(int *)(o - 4) + 1;
        }
    }
    ~igString() {
        char *s = p;
        if (s != 0) {
            int *header = (int *)(s - 8);
            int count = *(int *)(s - 4) - 1;
            *(int *)(s - 4) = count;
            if (count == 0) {
                StringChunk_ReleaseHeader(*header, header);
            }
        }
    }
    void assign(const igString &other) {
        char *o = other.p;
        char *s;
        if (o != 0) {
            *(int *)(o - 4) = *(int *)(o - 4) + 1;
        }
        s = p;
        if (s != 0) {
            int *header = (int *)(s - 8);
            int count = *(int *)(s - 4) - 1;
            *(int *)(s - 4) = count;
            if (count == 0) {
                StringChunk_ReleaseHeader(*header, header);
            }
        }
        p = other.p;
    }
};
class Q { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual int v104(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual igString v228(int, int); };
struct InternedStrings {
    static inline int get() {
        if (DAT_00586f20[0] == 0) {
            int pool = FUN_002eb010(16);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            DAT_00586f20[0] = pool;
        }
        return DAT_00586f20[0];
    }
};
extern "C" igString FUN_002fca80(Q *arg1, int arg2, int arg3, int arg4)
{
    int i;
    igString *list;
    int total;
    int cnt;
    char *buf;
    char *p;

    list = (igString *)igObject_AllocateStorage(arg1, arg3 * 4);
    total = 0;
    cnt = 0;
    for (i = 0; i < arg3; i++) {
        igString part = arg1->v228(arg2, arg4);
        if (part.p != 0) {
            list[cnt++].assign(part);
            total += strlen(part.p);
            arg2 += arg1->v104();
        }
    }
    buf = igObject_AllocateStorage(arg1, total + 1);
    p = buf;
    for (i = 0; i < cnt; i++) {
        p += sprintf(p, DAT_004f95a0, list[i].p);
    }
    *p = 0;
    igString result(buf == 0 ? (char *)0 : StringPool_Intern(InternedStrings::get(), buf));
    FUN_00300f50(arg1, list);
    FUN_00300f50(arg1, buf);
    return result;
}
