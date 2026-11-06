/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int igStrCmp(int, int *);
extern int DAT_0051db90[4];
int Gap__Bec__beNDMWMdlMapBase__vfunc_35(int dummy0, int arg1) {
    return igStrCmp(arg1, &DAT_0051db90[0]) == 0;
}
} /* extern "C" */
