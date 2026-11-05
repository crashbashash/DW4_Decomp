/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int beNDMWWindow_PresentModelAtOrigin(int *, int *, int, int *, int *);
extern int DAT_0051abf8[4];
extern int DAT_0051ac08[4];
extern int DAT_0051ac10[4];
extern int DAT_0051ac20[4];
void Gap__Bec__beNDMWStatusTitle00__vfunc_22(int *arg0) {
    beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051abf8[0], 0, &DAT_0051ac08[0], &DAT_0051ac10[0]);
    beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051ac20[0], 0, &DAT_0051ac08[0], &DAT_0051ac10[0]);
}
} /* extern "C" */
