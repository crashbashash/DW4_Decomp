typedef struct Cfg { char pad[128]; int a; int b; int c; int d; } Cfg;
typedef struct TrackerConfig {
    char pad0[16]; int a; int pad20; int b; int c; int d;
    char pad36[12]; void *map; char pad52[44]; char mask0[132];
    int t0[32]; int t1[32]; int t2[16]; int t3[64];
    char pad804[8196]; char s0[255]; char pad9255; char pad9256[4]; char s1[255]; char s1end;
} TrackerConfig;
void FUN_0030cf20(void *, int);
void FUN_0030cf30(void *, int);
void FUN_0030cf40(void *);
int FUN_0030d300(void *, int);
void *memset(void *, int, unsigned int);
extern int DAT_004c1ee0[32];
extern int DAT_004c1f60[32];
extern int DAT_004c1fe0[16];
extern int DAT_004c2020[64];
extern Cfg *DAT_00586dc8[4];
void Gap__Core__igEventTracker__vfunc_13(TrackerConfig *self) {
    int i;
    self->s0[0] = 0;
    self->pad9255 = 0;
    self->s1[0] = 0;
    self->s1end = 0;
    if (DAT_00586dc8[0] != 0) {
        self->a = DAT_00586dc8[0]->a;
        self->b = DAT_00586dc8[0]->b;
        self->c = DAT_00586dc8[0]->c;
        self->d = DAT_00586dc8[0]->d;
    }
    FUN_0030cf20(self->map, 0x1000);
    FUN_0030cf30(self->map, 0x100);
    FUN_0030cf40(self->map);
    memset(self->mask0, 0xFF, 0x80);
    memset(self->t0, 0xFF, 0x80);
    memset(self->t1, 0xFF, 0x80);
    memset(self->t2, 0xFF, 0x40);
    memset(self->t3, 0xFF, 0x100);
    for (i = 0; i < 32; i++) {
        self->t0[i] = FUN_0030d300(self->map, DAT_004c1ee0[i]);
    }
    for (i = 0; i < 32; i++) {
        self->t1[i] = FUN_0030d300(self->map, DAT_004c1f60[i]);
    }
    for (i = 0; i < 16; i++) {
        self->t2[i] = FUN_0030d300(self->map, DAT_004c1fe0[i]);
    }
    for (i = 0; i < 64; i++) {
        self->t3[i] = FUN_0030d300(self->map, DAT_004c2020[i]);
    }
}
