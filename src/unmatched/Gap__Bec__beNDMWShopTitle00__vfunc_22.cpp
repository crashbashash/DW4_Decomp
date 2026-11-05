/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int beNDMWWindow_PresentModelAtOrigin(int *, int *, int, int *, int *);
extern int DAT_0051cb28[4];
extern int DAT_0051cb38[4];
extern int DAT_0051cb40[4];
extern int DAT_0051cb50[4];
void Gap__Bec__beNDMWShopTitle00__vfunc_22(int *arg0) {
    beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051cb28[0], 0, &DAT_0051cb38[0], &DAT_0051cb40[0]);
    beNDMWWindow_PresentModelAtOrigin(arg0, &DAT_0051cb50[0], 0, &DAT_0051cb38[0], &DAT_0051cb40[0]);
}
} /* extern "C" */
