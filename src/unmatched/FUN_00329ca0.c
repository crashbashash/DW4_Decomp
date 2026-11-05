extern int *DAT_00587220[];
int sprintf();
int strcpy();
int FUN_00304430();
int FUN_00304680();
int FUN_0032ac70();
extern int DAT_004f95c8[4];
extern int DAT_004ff5c0[4];
void FUN_00329ca0(int unused, unsigned int addr, int len) {
    char buf[256];
    unsigned int lo0, hi0;
    unsigned int startPage = addr >> 26;
    unsigned int end = addr + len;
    unsigned int endPage = end >> 26;
    unsigned int page = startPage;
    unsigned int j = 0;
    unsigned int counter = 0;
    int pos = 0;
    lo0 = (addr & 0x3FFFFFF) >> 12;
    hi0 = (end & 0x3FFFFFF) >> 12;
    if (len == 0) return;
    while (page <= endPage) {
        int *table = DAT_00587220[page];
        if (table != 0) {
            unsigned int lo, hi;
            if (startPage < page) lo = 0; else lo = lo0;
            if (page < endPage) hi = 0x4000; else hi = hi0;
            for (j = lo; j < hi; ) {
                FUN_0032ac70(table, j);
                if ((counter & 0x3F) == 0) {
                    sprintf(buf, &DAT_004ff5c0[0], addr);
                    pos = 11;
                }
                buf[pos] = FUN_0032ac70(table, counter) + 0x30;
                pos++;
                if ((counter & 0x3F) == 0x3F) {
                    strcpy(buf + pos, &DAT_004f95c8[0]);
                    FUN_00304430(buf);
                    FUN_00304680();
                    pos = 0;
                }
                j++;
                counter++;
                addr += 0x1000;
            }
        }
        page++;
    }
    if (!(counter & 0x3F)) {
        strcpy(buf + pos, &DAT_004f95c8[0]);
        FUN_00304430(buf);
        FUN_00304680();
    }
}
