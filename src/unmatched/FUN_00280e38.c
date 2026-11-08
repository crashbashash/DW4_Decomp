struct Ent00280e38 {
    short a;
    char pad2[18];
};

struct Ctx00280e38 {
    char pad0[128];
    char chan[32];                  /* +128 */
    char pad160[4];
    struct Ent00280e38 ent[128];    /* +164 */
    char b[5];                      /* +2724 */
    char pad2729[3];
    int i0;                         /* +2732 */
    int i1;                         /* +2736 */
    int i2;                         /* +2740 */
    char pad2744[2276];
    int j0;                         /* +5020 */
    int j1;                         /* +5024 */
};

/* Four 32-word tables reached at +12 of the context. */
struct Tab00280e38 {
    char pad0[2832];
    int t0[32];
    int t1[32];
    int t2[32];
    int t3[32];
};

extern struct Ctx00280e38 *DAT_004bb114;

void FUN_00280e38(void) {
    unsigned int i;

    DAT_004bb114->b[0] = 0;
    DAT_004bb114->b[1] = 0;
    DAT_004bb114->b[2] = 0;
    DAT_004bb114->b[3] = 0;
    DAT_004bb114->b[4] = 0;
    DAT_004bb114->i0 = 1;
    DAT_004bb114->i1 = 0;
    DAT_004bb114->j0 = 0;
    DAT_004bb114->j1 = 0;
    DAT_004bb114->i2 = 1;
    for (i = 0; i < 32; i++) {
        DAT_004bb114->chan[i] = 0;
        ((struct Tab00280e38 *)((char *)DAT_004bb114 + 12))->t0[i] = 0;
        ((struct Tab00280e38 *)((char *)DAT_004bb114 + 12))->t1[i] = 0;
        ((struct Tab00280e38 *)((char *)DAT_004bb114 + 12))->t2[i] = 0;
        ((struct Tab00280e38 *)((char *)DAT_004bb114 + 12))->t3[i] = 0xFF;
    }
    for (i = 0; i < 128; i++) {
        DAT_004bb114->ent[i].a = 0;
    }
}
