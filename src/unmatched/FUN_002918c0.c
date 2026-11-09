typedef struct WorkSizeCfg {
    int mode;
    int size;
    int f8;
    int f12;
    int f16;
    int count;
} WorkSizeCfg;

/* matching construct: permuter, reduced by hand: the mode read in each test */
void FUN_002918c0(WorkSizeCfg *cfg, int *a, int *b, int *c, int *d, int *e, int *f)
{
    int count = cfg->count;
    int size;

    if (count <= 0)
        count = 1;
    size = cfg->size;
    if (cfg->mode == 2) {
        *a = size / 16384 * count * 2048;
        *b = 0;
        *c = 0;
        *d = 0;
        *e = 0;
        *f = 0;
    } else if (cfg->mode == 3) {
        *a = size / 16384 * count * 2048;
        *b = 0;
        *c = size / 16384 * 1024 + 2048;
        *d = 0;
        *e = 0;
        *f = 0;
    } else {
        *a = size / 16384 * count * 2048;
        *b = 0;
        *c = size / 16384 * 1024 + 2048;
        *d = 24012;
        *e = 24332;
        *f = 33216;
    }
}
