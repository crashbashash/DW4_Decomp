/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int igStrCmp(int, int *);
extern int DAT_00515e18[4];
int Gap__Bec__beNDMWMdlEnemy__vfunc_35(int dummy0, int arg1) {
    return igStrCmp(arg1, &DAT_00515e18[0]) == 0;
}
} /* extern "C" */
