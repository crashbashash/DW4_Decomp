typedef struct { char pad[352]; int f352; int f356; char pad2[284]; int f644; int f648; } S;
typedef struct { char pad[36]; int f36; int f40; } In;
typedef struct {
    char pad[12]; In in; int f56; int f60; char pad3[12]; int f76; int f80;
    char pad4[20]; int f104; char pad5[116]; int f224;
} O;
extern int D_004f5060[];
extern int FUN_002a96e0(void *h);
extern int FUN_002916f8(int a, int b, int c);
void FUN_002a70e8(char *h, O *o) {
    S *s = (S *)(h + 0xD28);
    In *in = &o->in;
    int t;
    o->f60 = in->f40;
    o->f56 = in->f36 - *(int *)(h + 3684) + s->f356;
    o->f76 = in->f36;
    o->f80 = in->f36 + s->f356;
    if (FUN_002a96e0(h) != 0) {
        t = FUN_002916f8(o->f60, (o->f224 - s->f352) * 1000, D_004f5060[o->f104]);
        o->f76 = t;
        o->f56 = o->f80 = t + s->f356;
    }
    if (s->f644 < o->f56) {
        s->f644 = o->f56;
        s->f648 = o->f60;
    }
}
