/* Pushes five fields of arg0 (one int, three floats, one address) to a sink object arg1 through
 * five setters; the first field read is volatile so it is loaded from a0 before the copy to s1;
 * alternate compiler -O3. */
int FUN_001751b0(int, int);
int FUN_00175140(int, float);
int FUN_00175220(int, void *);
int FUN_00175310(int, float);
int FUN_00175380(int, float);
void FUN_0013cd20(char *arg0, int arg1) {
    FUN_001751b0(arg1, *(volatile int *)(arg0 + 12));
    FUN_00175140(arg1, *(float *)(arg0 + 24));
    FUN_00175220(arg1, arg0 + 0x1C);
    FUN_00175310(arg1, *(float *)(arg0 + 16));
    FUN_00175380(arg1, *(float *)(arg0 + 20));
}
