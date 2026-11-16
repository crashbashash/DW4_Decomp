extern int m2vlib_libwork[];
void m2vlib_InitObjTbl(void) {
    int i;
    int n = m2vlib_libwork[16];
    int *p = (int *)m2vlib_libwork[17];
    for (i = 0; i < n; i++) {
        *p = 1;
        p += 0x680 / 4;
    }
}
