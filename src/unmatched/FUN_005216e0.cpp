/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int FUN_0023c8e0(int *, int (*)(), int);
extern int DAT_0058a180[4];
extern int DAT_0058a1a0[4];
int FUN_00371840();
int FUN_00371930();

void FUN_005216e0(void) {
    FUN_0023c8e0(&DAT_0058a180[0], &FUN_00371840, 0);
    FUN_0023c8e0(&DAT_0058a1a0[0], &FUN_00371930, 0);
}
} /* extern "C" */
