#include "dw4/reflected.h"
extern "C" {
int strcpy(...);
int strlen(...);
int FUN_002eb010(...);
void *FUN_00300e00(...);
int FUN_00300f50(...);
void StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
void *StringPool_Intern(...);
char *igObject_AllocateStorage(...);
extern int DAT_004f95f8[4];
extern int DAT_004f9600[4];
extern int DAT_00586f20[4];
}
struct RecoveryString {
    char *p;
    RecoveryString(char *q) { p = q; }
    RecoveryString(const RecoveryString &o) { p = o.p; if (p != 0) *(int *)(p - 4) = *(int *)(p - 4) + 1; }
    ~RecoveryString() {
        if (p != 0) {
            int *t = (int *)(p - 8);
            int v = *(int *)(p - 4) - 1;
            *(int *)(p - 4) = v;
            if (v == 0) StringChunk_ReleaseHeader(*t, t);
        }
    }
    RecoveryString &operator=(const RecoveryString &o) {
        if (o.p != 0) *(int *)(o.p - 4) = *(int *)(o.p - 4) + 1;
        if (p != 0) {
            int *t = (int *)(p - 8);
            int v = *(int *)(p - 4) - 1;
            *(int *)(p - 4) = v;
            if (v == 0) StringChunk_ReleaseHeader(*t, t);
        }
        p = o.p;
        return *this;
    }
};
class Elem {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); 
    virtual RecoveryString vf(int, int);
};
class Ctx { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual igCompoundMetaField *get(); };
extern "C" int FUN_002d5df0(RecoveryString *out, Ctx *ctx, int a2, int a3) {
    char *sepA = (char *)&DAT_004f95f8[0];
    char *sepB = (char *)&DAT_004f9600[0];
    igMetaFieldList *list = (igMetaFieldList *)ctx->get()->_fieldList;
    int n = list->_count;
    RecoveryString *arr = (RecoveryString *)FUN_00300e00(ctx, n, 4);
    int total = 9;
    int i;
    for (i = 0; i < n; i++) {
        int off = i * 4;
        Elem *e = ((Elem **)list->_data)[i];
        *(RecoveryString *)((char *)arr + off) = e->vf(a2 + ((igMetaField *)e)->_offset, a3);
        total += strlen(((RecoveryString *)((char *)arr + off))->p) + 1;
    }
    char *buf = igObject_AllocateStorage(ctx, total);
    strcpy(buf, sepA);
    char *p = buf + 4;
    buf[3] = 0x20;
    for (i = 0; i < n; i++) {
        strcpy(p, arr[i].p);
        p += strlen(arr[i].p);
        *p = 0x20;
        p++;
    }
    strcpy(p, sepB);
    char *r;
    if (buf == 0) r = 0;
    else {
        if (DAT_00586f20[0] == 0) {
            int v = FUN_002eb010(0x10);
            if (v != 0) v = StringPool_Construct(v);
            DAT_00586f20[0] = v;
        }
        r = (char *)StringPool_Intern(DAT_00586f20[0], buf);
    }
    RecoveryString res(r);
    FUN_00300f50(ctx, buf);
    out->p = res.p;
    if (out->p != 0) *(int *)(out->p - 4) = *(int *)(out->p - 4) + 1;
    return 0;
}
