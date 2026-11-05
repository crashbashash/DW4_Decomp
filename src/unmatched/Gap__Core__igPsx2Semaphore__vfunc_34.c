int iPollSema(int);
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
struct T { char pad[12]; int t; };
void Gap__Core__igPsx2Semaphore__vfunc_34(int *arg0, struct T *arg1) {
    int *p;
    if (arg1->t == -1) { *arg0 = DAT_004fb418[0]; return; } p = (iPollSema(arg1->t) >= 0) ? &DAT_004fb410[0] : &DAT_004fb418[0]; *arg0 = *p;
}
