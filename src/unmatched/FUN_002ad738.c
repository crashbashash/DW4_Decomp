typedef struct { char pad[3500]; int f3500; int f3504; int f3508; char pad2[28]; int f3540; } St;
typedef struct { char pad[36]; int f36; int f40; } Cf;
extern int FUN_0029ed48(void *h);
extern int FUN_002ad828(void *h);
extern void FUN_002ad870(void *h);
void FUN_002ad738(char *h) {
    Cf *cf = (Cf *)(h + 0xDBC);
    int *q = (int *)(h + 13868);
    St *s = *(St **)(h + 13864);
    int changed, base, t;
    if (FUN_0029ed48(h) == 0) {
    changed = 0;
    if (s->f3500 <= 0) {
        base = 0;
        if (q[1] != -3) base = s->f3540;
        if (base >= 0) {
            t = FUN_002ad828(h);
            if (t != -1) {
                changed = 1;
                s->f3500 = base + t;
            }
        }
    }
    if (s->f3504 <= 0 && cf->f36 > 0) {
        s->f3504 = cf->f36;
        changed = 1;
        s->f3508 = cf->f40;
    }
    if (changed) FUN_002ad870(h);
    }
}
