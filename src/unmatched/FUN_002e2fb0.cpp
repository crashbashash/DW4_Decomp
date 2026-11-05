extern "C" {
int FUN_002eb010(...);
void **FUN_002f8a20(...);
void **Memory_GetAllocatorBySelector(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
void *StringPool_Intern(...);
extern int DAT_004c2128[4];
extern void **DAT_00586e18[4];
extern int DAT_00586f20[4];
extern int DAT_00587060[4];
extern unsigned char GPR_00554c14;
void ***FUN_002e2fb0(void);
}
struct RC { char pad[4]; int rc; };
class VC_216 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51();  virtual void **vX(int); };
void ***FUN_002e2fb0(void) {
    void **a;
    void **al;
    void **cell;
    void **t;
    int name;
    int pool;
    RC *old;
    void *nw;
    int *hdr;
    int c;
    if (DAT_00586e18[0] == 0) {
        al = (void **)FUN_002f8a20();
        if (GPR_00554c14 != 0) {
            a = al;
        } else {
            a = (void **)Memory_GetAllocatorBySelector(DAT_00587060[0]);
        }
        cell = t = (void **)((VC_216 *)a)->vX(4);
        if (t != 0) { *t = 0; }
        DAT_00586e18[0] = cell;
        name = DAT_004c2128[0];
        if (DAT_00586f20[0] == 0) {
            pool = FUN_002eb010(16);
            if (pool != 0) {
                pool = StringPool_Construct(pool);
            }
            DAT_00586f20[0] = pool;
        }
        nw = StringPool_Intern(DAT_00586f20[0], name);
        old = (RC *)*cell;
        if (old != 0) {
            hdr = (int *)((char *)old - 8);
            c = *(int *)((char *)old - 4) - 1;
            *(int *)((char *)old - 4) = c;
            if (c == 0) {
                StringChunk_ReleaseHeader(*hdr, hdr);
            }
        }
        *cell = nw;
    }
    return &DAT_00586e18[0];
}
