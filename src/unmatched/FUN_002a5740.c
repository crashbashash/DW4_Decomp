typedef struct AudModeMode {
    int kind;
    int f4;
    int f8;
    int f12;
    int f16;
    int f20;
} AudModeMode;

typedef struct AudModeItem {
    short f0;
    unsigned short f2;
} AudModeItem;

typedef struct AudModeSub {
    char pad[28];
    AudModeMode cur;
    char pad52[6];
    unsigned short f58;
    char pad60[44];
    int active;
    AudModeMode saved;
    char pad132[1068];
    AudModeItem items[1];
} AudModeSub;

typedef struct AudModeObj {
    char pad[3368];
    AudModeSub sub;
} AudModeObj;

typedef struct AudModeEnt {
    char pad[16];
    int f16;
    int idx;
    int f24;
    int f28;
} AudModeEnt;

void FUN_002a5838(int id, int a, int b, int c, AudModeMode *mode);
void FUN_002a5a50(AudModeMode *saved, AudModeMode *cur);

void FUN_002a5740(AudModeObj *obj, AudModeEnt *ent, int id, int flag)
{
    AudModeSub *sub = &obj->sub;
    int b = ent->f28;
    int a = ent->f16;
    int idx = ent->idx;

    if (flag != 0 && id >= 0) {
        FUN_002a5838(id, a, b, idx, &obj->sub.cur);
        return;
    }
    if (sub->active == 0) {
        if (*(int *)((char *)obj + 13864) == 0) {
            sub->cur.kind = a;
            sub->cur.f4 = 0;
            sub->cur.f8 = 0;
            sub->cur.f12 = 0;
            sub->cur.f16 = 0;
            sub->cur.f20 = 0;
        }
    } else if (flag != 0) {
        FUN_002a5a50(&sub->saved, &sub->cur);
        sub->items[0].f2 = sub->f58;
        sub->items[idx].f2 = sub->f58;
    } else {
        sub->cur.kind = sub->saved.kind;
        sub->cur.f4 = sub->saved.f4;
        sub->cur.f8 = sub->saved.f8;
        sub->cur.f12 = sub->saved.f12;
        sub->cur.f16 = sub->saved.f16;
        sub->cur.f20 = sub->saved.f20;
    }
}
