/* Calls FUN_0027ec10 and clears the four words at 0x57fa80..0x57fa8c. */
extern void FUN_0027ec10(void);
extern int mwsfsvr_vint_svr_id;
extern int mwsfsvr_vsync_svr_id;
extern int DAT_0057fa88;
extern int DAT_0057fa8c;

void FUN_00299fc8(void) {
    FUN_0027ec10();
    mwsfsvr_vint_svr_id = 0;
    mwsfsvr_vsync_svr_id = 0;
    DAT_0057fa88 = 0;
    DAT_0057fa8c = 0;
}
