typedef struct { char pad[20]; int f20; int f24; } Info;
typedef struct { char pad[636]; int f636; int f640; } Sub;
extern int FUN_002a8500(void *h);
extern int FUN_002a86b8(void *h, void *buf);
extern void FUN_002a7e30(void *h, int v, Info **out);

int FUN_002a7d90(char *h, Info **out) {
    char buf[16];
    Sub *s = (Sub *)(h + 0xD28);
    int v;
    if (FUN_002a8500(h) == -1) {
        *out = 0;
        return 0;
    }
    v = FUN_002a86b8(h, buf);
    if (v == 0) {
        *out = 0;
        return v;
    }
    FUN_002a7e30(h, v, out);
    s->f636 = (*out)->f20;
    s->f640 = (*out)->f24;
    return 0;
}
