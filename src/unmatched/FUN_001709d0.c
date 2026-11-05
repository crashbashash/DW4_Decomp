typedef struct Ent { char p[144]; int f144; unsigned char f148; char q[11]; } Ent;
typedef struct Mgr { char p[16]; Ent *ents; } Mgr;
typedef struct Obj { char p[1336]; Mgr *f1336; } Obj;
int FUN_00171690(Obj *, Ent *, int, Mgr *);
int FUN_001f8830(int);
int FUN_001f88d0(int, int, int, Mgr *);
extern int DAT_00560850[4];
extern int DAT_00560858[4];
extern int DAT_005608cc[4];
int FUN_001709d0(Obj *arg0, int arg1, int arg2) {
    Mgr *m = arg0->f1336;
    Ent *e = m->ents + arg1;
    int i;
    int off;
    int flag;
    if (e == 0) {
        return 0;
    }
    flag = arg2 & 0xFF;
    if (e->f148 == flag) {
        DAT_005608cc[0] += 1;
    }
    if (e->f148 == flag) {
        return 1;
    }
    if (arg2 != 0) {
        for (i = 0; i < DAT_00560850[0]; i++) {
            off = i * 4;
            if (*(int *)(DAT_00560858[0] + off) < 0) {
                e->f144 = i;
                *(Ent **)(DAT_00560858[0] + off) = e;
                e->f148 = 1;
                FUN_00171690(arg0, e, off, m);
                FUN_001f8830(i);
                return 1;
            }
        }
        return 0;
    }
    FUN_001f88d0(e->f144, arg1, arg2, m);
    e->f148 = 0;
    *(int *)(DAT_00560858[0] + e->f144 * 4) = -1;
    return 1;
}
