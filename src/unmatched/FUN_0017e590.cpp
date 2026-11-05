extern "C" {
void *FUN_0015f4a0(...);
int FUN_001eb5e0(...);
int igObject_IsKindOf(...);
extern int DAT_005610c8[4];
extern int DAT_00586808[4];
extern int DAT_00586818[4];
extern int DAT_00586830[4];
extern int DAT_00586840[4];
extern int DAT_00586898[4];
}
class VC { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); int pad[3]; int f16; };
struct Node { char p0[12]; VC *obj; char p1[16]; int f32; };
struct Self { char p[944]; int f944; };
extern "C" bool FUN_0017e590(Self *arg0, int arg1, int arg2, int *arg3, int *arg4) {
    Node *n2; VC *s; VC *r; VC *o2;
    bool var_s2 = false;
    Node *n = (Node *)FUN_0015f4a0(arg1, 9, 0);
    if (n != 0) {
        if (n->obj->vX() == DAT_00586808[0]) {
            *arg3 = n->obj->f16;
            FUN_001eb5e0(4, 0, 0, 0);
        } else if (n->obj->vX() == DAT_005610c8[0]) {
            *arg3 = n->obj->f16;
            FUN_001eb5e0(4, 0, 0, 0);
        } else {
            VC *o = n->obj;
            if (o->vX() == DAT_00586898[0]) {
                int a = n->f32;
                FUN_001eb5e0(4, 1, 7 - a, a);
                var_s2 = true;
                *arg3 = o->f16;
            } else if (o->vX() == DAT_00586818[0]) {
                int a = n->f32;
                FUN_001eb5e0(4, 0, 8 - a, a);
                *arg3 = o->f16;
            } else if (o->vX() == DAT_00586830[0]) {
                int a = n->f32;
                FUN_001eb5e0(4, 1, 0xF - a, a);
                *arg3 = o->f16;
            } else if (o->vX() == DAT_00586840[0]) {
                int a = n->f32;
                FUN_001eb5e0(4, 0, 0x10 - a, a);
                *arg3 = o->f16;
            }
        }
    } else {
        *arg3 = 0;
    }
    n2 = (Node *)FUN_0015f4a0(arg1, 4, 1);
    if (n2 != 0) {
        s = n2->obj;
        if (s != 0 && igObject_IsKindOf(s, DAT_005610c8[0]) != 0) {
            r = s;
        } else {
            r = 0;
        }
        if (r != 0) {
            *arg4 = r->f16;
        } else {
            o2 = n2->obj;
            if (o2->vX() == DAT_00586898[0]) {
                int a = n2->f32;
                FUN_001eb5e0(2, 1, 7 - a, a);
                *arg4 = o2->f16;
            } else if (o2->vX() == DAT_00586818[0]) {
                int a = n2->f32;
                FUN_001eb5e0(2, 0, 8 - a, a);
                *arg4 = o2->f16;
            } else if (o2->vX() == DAT_00586830[0]) {
                int a = n2->f32;
                FUN_001eb5e0(2, 1, 0xF - a, a);
                *arg4 = o2->f16;
            } else if (o2->vX() == DAT_00586840[0]) {
                int a = n2->f32;
                FUN_001eb5e0(2, 0, 0x10 - a, a);
                *arg4 = o2->f16;
            }
        }
    } else {
        *arg4 = 0;
    }
    if (arg0->f944 == 0) {
        if (*arg3 != 0) *arg3 = *arg3 + arg2 * 4;
        if (*arg4 != 0) *arg4 = *arg4 + arg2 * 8;
    }
    return var_s2;
}
