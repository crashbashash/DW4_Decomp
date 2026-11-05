struct O {
  virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9();
  virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
  virtual void d20(); virtual void d21(); virtual void d22();
  virtual int v23(int *, int *);
  int references; char pad8[64]; void *f72; };
extern "C" {
int FUN_002d01a0(...);
int FUN_002eb010(...);
int FUN_002f8a20(...);
int FUN_00304350(...);
int FUN_003043c0(...);
int FUN_00306e50(...);
int Memory_GetAllocatorBySelector(...);
int StringChunk_ReleaseHeader(...);
int StringPool_Construct(...);
void *StringPool_Intern(...);
int igObject_Destroy(...);
extern int DAT_004f9c50[4];
extern int DAT_004ffcf0[4];
extern int DAT_004ffd08[4];
extern int DAT_004ffd18[4];
extern void * DAT_00586dc8[4];
extern int DAT_00586f20[4];
extern int DAT_00587038[4];
extern int DAT_00587338[4];
extern int DAT_00587358[4];
extern unsigned char GPR_00554c14;
void FUN_0032d220(void);
}

void FUN_0032d220(void) {
    unsigned char sp3F;
    struct O * volatile sp38;
    struct O * volatile sp34;
    int a;
    int s;
    int *p;
    int t;
    struct O *o;
    int *pool;
    struct O *o2;
    int s2;

    FUN_00306e50(*(int *)((char *)(DAT_00586dc8[0]) + 56), 2, &DAT_004ffcf0[0], &sp3F, 1, 0);
    if (sp3F != 0) {
        FUN_00304350(0);
        FUN_003043c0(0);
        a = FUN_002f8a20();
        sp38 = (struct O *)FUN_002d01a0(GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(DAT_00587038[0]));
        a = FUN_002f8a20();
        sp34 = (struct O *)FUN_002d01a0(GPR_00554c14 != 0 ? a : Memory_GetAllocatorBySelector(DAT_00587038[0]));
        if (DAT_00587338[0] != 0) {
            s = DAT_00587358[0];
            o = sp38;
            if (DAT_00586f20[0] == 0) {
                a = FUN_002eb010(0x10);
                if (a != 0) {
                    a = StringPool_Construct(a);
                }
                DAT_00586f20[0] = a;
            }
            p = (int *)StringPool_Intern(DAT_00586f20[0], s);
            if (o->f72 != 0) {
                int *h = (int *)o->f72 - 2;
                t = ((int *)o->f72)[-1] - 1;
                ((int *)o->f72)[-1] = t;
                if (t == 0) {
                    StringChunk_ReleaseHeader(*h, h);
                }
            }
            o->f72 = p;
            s2 = DAT_00587358[0];
            o2 = sp34;
            if (DAT_00586f20[0] == 0) {
                a = FUN_002eb010(0x10);
                if (a != 0) {
                    a = StringPool_Construct(a);
                }
                DAT_00586f20[0] = a;
            }
            p = (int *)StringPool_Intern(DAT_00586f20[0], s2);
            if (o2->f72 != 0) {
                int *h = (int *)o2->f72 - 2;
                t = ((int *)o2->f72)[-1] - 1;
                ((int *)o2->f72)[-1] = t;
                if (t == 0) {
                    StringChunk_ReleaseHeader(*h, h);
                }
            }
            o2->f72 = p;
        }
        if (sp38->v23(&DAT_004ffd08[0], &DAT_004f9c50[0]) != 0) {
            FUN_00304350(sp38);
        }
        if (sp34->v23(&DAT_004ffd18[0], &DAT_004f9c50[0]) != 0) {
            FUN_003043c0(sp34);
        }
        o = sp34;
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0) {
                igObject_Destroy(o);
            }
        }
        o = sp38;
        if (o != 0) {
            o->references = o->references - 1;
            if (((unsigned long long)(long long)o->references & 0x7fffffULL) == 0) {
                igObject_Destroy(o);
            }
        }
    }
}
