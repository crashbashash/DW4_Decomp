typedef struct WorkCfgCfg {
    int f0;
    int f4;
    int f8;
    int f12;
    int f16;
    int f20;
    int f24;
    int count;
    int f32;
} WorkCfgCfg;

extern WorkCfgCfg DAT_005855b0;
extern int DAT_005855d8[2];
extern int DAT_005855e0[16];

void FUN_002a2fe0(WorkCfgCfg *cfg, int *work, int *bufs)
{
    int i;
    int count;

    DAT_005855b0 = *cfg;
    DAT_005855b0.f16 = 0;
    DAT_005855b0.f32 = 0;
    for (i = 0; i < 2; i++)
        DAT_005855d8[i] = (work[i] + 63) & ~63;
    count = cfg->count;
    for (i = 0; i < 16; i++) {
        if (i < count)
            DAT_005855e0[i] = (bufs[i] + 63) & ~63;
        else
            DAT_005855e0[i] = 0;
    }
}
