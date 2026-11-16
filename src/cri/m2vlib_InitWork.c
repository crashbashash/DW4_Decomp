void *memset();
extern int m2vlib_libwork[];
void m2vlib_InitWork(int n, char *buf, unsigned int size) {
    while (size < n * 0x700 + 0x40) {
        n--;
    }
    buf = (char *)(((int)buf + 63) & ~63);
    memset(buf, 0, n * 0x700);
    m2vlib_libwork[16] = n;
    m2vlib_libwork[17] = (int)buf;
}
