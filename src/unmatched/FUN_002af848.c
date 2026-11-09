typedef struct SyncCheckCfg {
    int f0;
    int f4;
    int rate;
} SyncCheckCfg;

typedef struct SyncCheckObj {
    char pad[2624];
    int mode;
} SyncCheckObj;

extern SyncCheckCfg DAT_004bea88;
void FUN_002ae968(SyncCheckObj *obj, int *time, int *unit);
void FUN_002af998(SyncCheckObj *obj, int time, int unit, int *decision);
void FUN_002afa10(SyncCheckObj *obj, int *decision, float t, float ref);

void FUN_002af848(SyncCheckObj *obj, int time, int unit, int *decision, int delay)
{
    SyncCheckCfg *cfg = &DAT_004bea88;
    int t, u;
    float vt;
    float at;

    FUN_002ae968(obj, &t, &u);
    if (u == 1) {
        if (t == -2) {
            *decision = 1;
            return;
        }
        FUN_002af998(obj, time, unit, decision);
        return;
    }
    t += u * delay / cfg->rate;
    vt = (float)time * 10000.0f / (float)unit;
    at = (float)t * 10000.0f / (float)u;
    if (obj->mode != 1) {
        FUN_002afa10(obj, decision, vt, at);
        return;
    }
    if (vt <= at)
        *decision = 1;
    else
        *decision = 0;
}
