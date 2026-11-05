extern "C" {
int memset(int *, int, int);
int Gap__Core__igObject__vfunc_11();
int igObject_Destroy(struct T *);
extern int DAT_005873c0[4];
extern int DAT_005873c8[4];
extern int DAT_005874d0[4];
extern int DAT_005875e8[4];
typedef struct T { int w0; int refs; } T;
extern T * DAT_00587620[4];
extern char GPR_00554de4;
extern char GPR_00554de8;
extern char GPR_00554dec;

void Gap__igAdx__vfunc_11(void) {
    T *p;
    Gap__Core__igObject__vfunc_11();
    DAT_005873c0[0] = 0;
    GPR_00554de8 = 0;
    GPR_00554dec = 0;
    DAT_005873c8[0] = 0;
    GPR_00554de4 = 0;
    memset(&DAT_005874d0[0], 0, 0x100);
    p = DAT_00587620[0];
    if (p != 0) {
        p->refs = p->refs - 1;
        if (((unsigned long long) ((long long) p->refs << 0x29) >> 0x29) == 0) {
            igObject_Destroy(p);
        }
    }
    DAT_00587620[0] = 0;
    DAT_005875e8[0] = 0;
}
}
