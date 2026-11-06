extern "C" {
int FUN_0032d850(...);
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
void Gap__igPsx2AudioContext__vfunc_48(int *arg0, void *arg1, int arg2, int arg3);
}
void Gap__igPsx2AudioContext__vfunc_48(int *arg0, void *arg1, int arg2, int arg3) {
    /* matching construct: variant search — decl order [1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots in declaration order, the reverse of the 2001 default */
    int sp2C;
    int sp28;

    FUN_0032d850(&sp28, *(int *)((char *)(arg1) + 12), arg2 | 0x80000, arg3, &sp2C, 1);
    if (sp2C == 2) {
        *arg0 = DAT_004fb410[0];
    } else {
        *arg0 = DAT_004fb418[0];
    }
}
