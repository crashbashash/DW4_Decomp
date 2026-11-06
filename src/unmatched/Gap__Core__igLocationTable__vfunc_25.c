/* The call result is tested where it is assigned; a separate local copy would put the argument
 * move before the branch. */
int strncpy();
int FUN_0030d1d0();
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
typedef struct E { int f0; int f4; int f8; int f12; int f16; } E;
typedef struct Tb { char p[8]; int n; char p2[4]; char *v; } Tb;
typedef struct S { char p[16]; Tb *f16; char p2[4]; int f24; int f28; } S;
void Gap__Core__igLocationTable__vfunc_25(int *arg0, S *arg1, int arg2, int *arg3, char *arg4, int arg5, int *arg6, char *arg7, int arg8, int *arg9) {
    int rc;
    Tb *t;
    E *e;
    int r;
    rc = DAT_004fb418[0];
    if (arg2 >= 0) {
        t = arg1->f16;
        if (arg2 * 5 < t->n) {
            e = (E *)(t->v + arg2 * 0x14);
            *arg3 = e->f0;
            if (arg4 != 0) {
                if ((r = FUN_0030d1d0(arg1->f24, e->f4)) != 0) {
                    strncpy(arg4, r, arg5);
                } else {
                    *arg4 = 0;
                }
            }
            *arg6 = e->f8;
            if (arg7 != 0) {
                if ((r = FUN_0030d1d0(arg1->f28, e->f12)) != 0) {
                    strncpy(arg7, r, arg8);
                } else {
                    *arg7 = 0;
                }
            }
            *arg9 = e->f16;
            rc = DAT_004fb410[0];
        }
    }
    *arg0 = rc;
}
