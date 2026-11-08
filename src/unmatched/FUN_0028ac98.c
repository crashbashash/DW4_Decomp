void *memset();
extern int DAT_00573eb8[];
void FUN_0028ac98(int n, char *buf, unsigned int size) {
    while (size < n * 0x700 + 0x40) {
        n--;
    }
    buf = (char *)(((int)buf + 63) & ~63);
    memset(buf, 0, n * 0x700);
    DAT_00573eb8[16] = n;
    DAT_00573eb8[17] = (int)buf;
}
