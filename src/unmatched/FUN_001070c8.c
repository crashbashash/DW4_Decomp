typedef struct {
    void (*f[11])(char *d);
} ExtTable;
extern ExtTable DAT_004d20b0;
unsigned int _ipuShowBits(char *d, int n);
void _ipuFlushBits(char *d, int n);
unsigned int FUN_00106c88(char *d, int n);
void FUN_00106df8(char *d);
void FUN_001070c8(char *d) {
    ExtTable tbl = DAT_004d20b0;
    unsigned int code;
    unsigned int id;

    FUN_00106df8(d);
    while ((code = _ipuShowBits(d, 32)) == 0x1B5 || code == 0x1B2) {
        if (code == 0x1B5) {
            _ipuFlushBits(d, 32);
            id = FUN_00106c88(d, 4);
            id = id > 10 ? 0 : id;
            tbl.f[id](d);
            FUN_00106df8(d);
        } else {
            _ipuFlushBits(d, 32);
            FUN_00106df8(d);
        }
    }
}
