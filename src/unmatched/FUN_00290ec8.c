typedef struct SfdLibWork {
    int params[16];
    char pad64[12];
    char *f76;
    char *f80;
    int f84;
    char *f88;
} SfdLibWork;

extern SfdLibWork DAT_00573f18;
extern int DAT_004f2a50[16];

extern void FUN_0028b350(void *dst, const void *src, int words);
extern void FUN_0028b530(void *dst, int value, int size);
extern void FUN_00291238(void *p, int size);

/* matching construct: 72-variant sweep — store order and declarations */
void FUN_00290ec8(int count, char *work)
{
    char *base;
    char *tables;
    char *pool;

    base = (char *)(((int)work + 63) & ~63);
    FUN_0028b530(base, 0, (count << 8) + 0x800);
    tables = base + (count << 10);
    pool = tables + 0x420;
    FUN_00291238(pool, 0x1BE0);
    FUN_0028b350(&DAT_00573f18, DAT_004f2a50, 16);
    DAT_00573f18.f76 = tables;
    DAT_00573f18.f80 = pool;
    DAT_00573f18.f84 = count;
    DAT_00573f18.f88 = base;
}
