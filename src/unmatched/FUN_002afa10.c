typedef struct AvSyncSync {
    char pad[684];
    int rate;
    char pad688[12];
    int count;
    float pending;
    int last;
    float time;
} AvSyncSync;

typedef struct AvSyncObj {
    char pad[2336];
    int mode;
    char pad2340[408];
    int margin;
    char pad2752[616];
    AvSyncSync sync;
} AvSyncObj;

extern int DAT_004bea90;

void FUN_002afa10(AvSyncObj *obj, int *decision, float t, float ref)
{
    float margin = (float)obj->margin;
    AvSyncSync *sync = &obj->sync;
    int limit;

    if (ref + margin < t) {
        *decision = 0;
        return;
    }
    if (t <= ref - margin) {
        *decision = 1;
        if (sync->time == t || sync->pending == t)
            return;
        sync->pending = t;
        sync->count++;
        return;
    }
    limit = 0;
    if (DAT_004bea90 == 0xEA24 && obj->mode < 3)
        limit = sync->rate == 1000;
    if (limit >= sync->count)
        *decision = sync->last;
    else if (ref < t)
        *decision = 0;
    else
        *decision = 1;
    sync->count = 0;
    sync->time = t;
    sync->last = *decision;
}
