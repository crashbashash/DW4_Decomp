typedef struct { char pad[4]; int f4; } R;
typedef struct { char pad[12]; R *fc; int f10; int f14; } A;
R *igMetaObject_FindFieldByName();
R *igObjectSystem_FindMetaByNameDefault();
int igObject_Destroy();
void FUN_001e6640(A *arg0) {
    R *volatile sp3C;
    R *t;
    R *m;
    R *f;
    sp3C = 0;
    m = igObjectSystem_FindMetaByNameDefault(arg0->f10);
    if (m != 0) {
        m->f4 = m->f4 + 1;
    }
    t = sp3C;
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
    sp3C = m;
    t = sp3C;
    if (t != 0) {
        f = igMetaObject_FindFieldByName(t, arg0->f14);
        if (f != 0) {
            f->f4 = f->f4 + 1;
        }
        t = arg0->fc;
        if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
        arg0->fc = f;
    }
    t = sp3C;
    if (t != 0) {
        t->f4 = t->f4 - 1;
        if (((unsigned long long)((long long)t->f4 << 0x29) >> 0x29) == 0) {
            igObject_Destroy(t);
        }
    }
}
