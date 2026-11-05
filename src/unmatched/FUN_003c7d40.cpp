/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int igMetaEnum_Create(int *, int *, int *, int);
extern int DAT_004cc020[4];
extern int DAT_004cc030[4];
extern int DAT_00510d58[4];
extern int DAT_0058bee8[4];
int FUN_003c7d40(void) {
    if (DAT_0058bee8[0] == 0) {
        DAT_0058bee8[0] = igMetaEnum_Create(&DAT_00510d58[0], &DAT_004cc020[0], &DAT_004cc030[0], 4);
    }
    return DAT_0058bee8[0];
}
} /* extern "C" */
