/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int igObject_InitHeader();
extern int DAT_00524950[4];
extern int DAT_0052cf80[4];
void *FUN_00458630(void *arg0) {
    igObject_InitHeader();
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_00524950[0]);
    *(int *)((char *)(arg0) + 8) = 0;
    *(int *)((char *)(arg0) + 0) = (int)(&DAT_0052cf80[0]);
    return arg0;
}
} /* extern "C" */
