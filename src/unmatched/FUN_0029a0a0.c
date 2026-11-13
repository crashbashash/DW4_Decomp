/* Calls FUN_0027e748(2, a, b, c) and records `a` in mwsfsvr_vsync_svr_id. */
extern void FUN_0027e748(int kind, int a, int b, int c);
extern int mwsfsvr_vsync_svr_id;

void FUN_0029a0a0(int a, int b, int c) {
    FUN_0027e748(2, a, b, c);
    mwsfsvr_vsync_svr_id = a;
}
