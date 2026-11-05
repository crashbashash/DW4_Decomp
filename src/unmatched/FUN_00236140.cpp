extern "C" {
struct T { int word0; int references; int f8; };
void igObject_Destroy(T *);
T *FUN_002c43b0(...);
int FUN_002e3850(...);
int FUN_002eb010(...);
int FUN_00304720(...);
int Memory_GetAllocatorBySelector(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
int StringPool_Intern(...);
extern int DAT_004e9740[4];
extern int DAT_004e9748[4];
extern int DAT_004e9750[4];
extern int DAT_00587038[4];
extern int DAT_00586f20[4];
}
struct G { char p[76]; int f76; };
extern G *DAT_00586dc8[4];
struct Rel { static inline void go(T *object) {
    if (object) {
        --object->references;
        if (((unsigned long long)(long long)object->references & 0x7fffffULL) == 0)
            igObject_Destroy(object);
    }
} };
extern "C" void FUN_00236140(void);
void FUN_00236140(void) {
    T * volatile sp3C;
    T *s0;
    T *t;
    int *old;
    int *s1;
    int v;
    sp3C = FUN_002c43b0(Memory_GetAllocatorBySelector(DAT_00587038[0]));
    s0 = sp3C;
    if (DAT_00586f20[0] == 0) {
        v = FUN_002eb010(0x10);
        if (v != 0) {
            v = StringPool_Construct(v);
        }
        DAT_00586f20[0] = v;
    }
    s1 = (int *)StringPool_Intern(DAT_00586f20[0], &DAT_004e9740[0]);
    old = (int *)s0->f8;
    if (old != 0) {
        int *hdr = old - 2;
        int r = old[-1] - 1;
        old[-1] = r;
        if (r == 0) {
            StringChunk_ReleaseHeader(*hdr, hdr);
        }
    }
    s0->f8 = (int)s1;
    FUN_002e3850(sp3C, &DAT_004e9748[0]);
    FUN_00304720(DAT_00586dc8[0]->f76, &DAT_004e9750[0], sp3C->f8, 1);
    Rel::go(t = sp3C);
}
