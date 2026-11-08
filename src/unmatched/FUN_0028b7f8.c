int FUN_0028b918();

typedef struct {
    int w[8];
} Unit28b;

typedef struct {
    char pad[40];
    Unit28b cur;
    Unit28b hist[3];
} Reader28b;

int FUN_0028b7f8(Reader28b *rd, int pos, int n, int *total, int *flags) {
    int out[2];
    int more;
    int fl;
    int i;
    Unit28b *c;

    while (n >= 4) {
        more = FUN_0028b918(rd, pos, n, &out[0], &out[1]);
        fl = *flags | out[1];
        pos += out[0];
        n -= out[0];
        *total += out[0];
        *flags = fl;
        if (more == 0) break;
    }
    if (*flags & 0x20000) {
        c = &rd->cur;
        i = 0;
        if (c->w[2] == 0) {
            i = (c->w[3] != 0) ? 1 : 2;
        }
        rd->hist[i] = *c;
    }
    return 0;
}
