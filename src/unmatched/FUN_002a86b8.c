typedef struct { int state; char pad[228]; } Ent;
typedef struct { char pad[124]; int f124; char pad2[248]; int count; int pad3; Ent e[1]; } S;
extern void FUN_002a0e70(int *c);
extern void FUN_002a0e88(int *c);
extern int FUN_002a8b30(Ent *a, Ent *b);
Ent *FUN_002a86b8(char *h, int *out) {
    int c;
    Ent *best = 0;
    int n = 0;
    S *s;
    Ent *e;
    int i, cnt;
    FUN_002a0e70(&c);
    s = *(S **)(h + 8120);
    cnt = s->count;
    e = s->e;
    *out = 0;
    for (i = 0; i < cnt; i++, e++) {
        if (e->state == 2 || e->state == 4) {
            if (FUN_002a8b30(best, e) != 0) best = e;
            n++;
        }
    }
    if (n == 1 && s->f124 != 0) *out = n;
    FUN_002a0e88(&c);
    return best;
}
