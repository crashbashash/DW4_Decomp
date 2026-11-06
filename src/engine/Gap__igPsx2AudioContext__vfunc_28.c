struct Ent { int f0; int f4; unsigned char used : 1; unsigned char rest : 7; char pad[3]; int f12; float f16; float f20; float f24; int pad2; int f32; };
struct Tbl { char pad[8]; int cnt; int pad2; struct Ent *items; };
int memset(void *, int, int);
extern struct Tbl *DAT_0055f5d0[4];
int Gap__igPsx2AudioContext__vfunc_28(void) {
    int cnt;
    struct Tbl *t;
    int i;
    struct Ent *e;
    t = DAT_0055f5d0[0];
    cnt = t->cnt;
    i = 0;
    for (; i < cnt; i++) {
        if (!t->items[i].used) {
            break;
        }
    }
    if (i == cnt) {
        return -1;
    }
    e = &t->items[i];
    memset(e, 0, 0x24);
    e->used = 1;
    e->f24 = 1.0f;
    e->f16 = 1.0f;
    e->f20 = 1.0f;
    e->f4 = 0x4000;
    e->f12 = 0x10000;
    e->f32 = -1;
    return i;
}
