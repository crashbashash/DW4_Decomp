/* Calls FUN_00126218 on the argument with the global state block D_004854a0 and returns the
 * argument. */
extern void *D_004854a0;    /* current C-library state block (also returned by FUN_00124d50) */
void FUN_00126218(void *arg, void *state);

void *FUN_001283f8(void *arg) {
    FUN_00126218(arg, D_004854a0);
    return arg;
}
