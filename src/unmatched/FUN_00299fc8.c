/* Calls FUN_0027ec10 and clears the four words at 0x57fa80..0x57fa8c. */
extern void FUN_0027ec10(void);
extern int DAT_0057fa80;
extern int DAT_0057fa84;
extern int DAT_0057fa88;
extern int DAT_0057fa8c;

void FUN_00299fc8(void) {
    FUN_0027ec10();
    DAT_0057fa80 = 0;
    DAT_0057fa84 = 0;
    DAT_0057fa88 = 0;
    DAT_0057fa8c = 0;
}
