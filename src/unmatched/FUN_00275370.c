/* Touches the volatile word 0x004ab5d8, calls FUN_00276d18(0) and FUN_00276da8(0), and returns the
 * address of the block at 0x004ab5e8. */
extern void FUN_00276d18(int arg);
extern void FUN_00276da8(int arg);
extern volatile int DAT_004ab5d8;
extern int DAT_004ab5e8[];

int *FUN_00275370(void) {
    DAT_004ab5d8;  /* volatile read, value unused */
    FUN_00276d18(0);
    FUN_00276da8(0);
    return DAT_004ab5e8;
}
