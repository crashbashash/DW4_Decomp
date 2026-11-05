extern int DAT_004fb410[4];
struct S { char p[12]; int f12; int p1; int f20; };
void Gap__Core__igPsx2Semaphore__vfunc_28(int *arg0, struct S *arg1, int arg2) {
    if (arg1->f12 == -1) {
        arg1->f20 = arg2;
        *arg0 = DAT_004fb410[0];
    } else {
        *arg0 = DAT_004fb410[2];
    }
}
