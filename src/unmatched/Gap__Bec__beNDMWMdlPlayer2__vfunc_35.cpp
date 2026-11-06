/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int igStrCmp(int, int *);
extern int DAT_005165b0[4];
int Gap__Bec__beNDMWMdlPlayer2__vfunc_35(int dummy0, int arg1) {
    return igStrCmp(arg1, &DAT_005165b0[0]) == 0;
}
} /* extern "C" */
