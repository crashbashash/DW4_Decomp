extern int D_004f5368[];
extern int FUN_002b1970(void *h);
extern int memcmp(const void *a, const void *b, unsigned int n);
extern int FUN_002b1de0(void *h, int *a, int *b);
typedef struct { int state; char *info; unsigned int size; int ver; } H;
int FUN_002b19f0(H *h, int *out) {
    char *name;
    int v[2];
    *out = 0;
    name = h->info + 32;
    if (FUN_002b1970(h) == 1) return 0;
    if (h->size < 2048) {
        h->state = -1;
        return 0;
    }
    if (memcmp(name, D_004f5368, 24) != 0) {
        h->state = -1;
        return 0;
    }
    h->state = 2;
    if (FUN_002b1de0(h, &v[0], &v[1]) == 0) return 0;
    h->ver = v[0] * 100 + v[1];
    *out = 1;
    return 1;
}
