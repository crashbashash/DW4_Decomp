/* The first field read is volatile so it is loaded from a0 before the copy to s1. */
int FUN_001751b0(int, int);
int FUN_00175140(int, float);
int FUN_00175220(int, void *);
int FUN_00175310(int, float);
int FUN_00175380(int, float);
void Gap__Core__igFogAttr__vfunc_24(char *arg0, int arg1) {
    FUN_001751b0(arg1, *(volatile int *)(arg0 + 12));
    FUN_00175140(arg1, *(float *)(arg0 + 24));
    FUN_00175220(arg1, arg0 + 0x1C);
    FUN_00175310(arg1, *(float *)(arg0 + 16));
    FUN_00175380(arg1, *(float *)(arg0 + 20));
}
