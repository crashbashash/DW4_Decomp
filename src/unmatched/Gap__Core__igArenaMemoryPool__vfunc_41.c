/* 0x0031d1e0 — records the requested limit when none is set yet (or it does not exceed the current one) and hands back the
 * matching status word. Combat compiler at plain -O3; `arg2 <= lim` (not `lim >= arg2`) and the store repeated in both arms. */
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
void Gap__Core__igArenaMemoryPool__vfunc_41(int *arg0, char *arg1, unsigned long long arg2) {
    unsigned long long lim = *(unsigned long long *)(arg1 + 160);
    if (lim == 0 || arg2 <= lim) {
        *(unsigned long long *)(arg1 + 152) = arg2;
        *arg0 = DAT_004fb410[0];
    } else {
        *arg0 = DAT_004fb418[0];
    }
}
