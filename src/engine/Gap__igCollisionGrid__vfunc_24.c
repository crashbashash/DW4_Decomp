typedef struct R { int pad; int f4; } R;
typedef struct L { char pad[8]; int f8; int pad2; R **f16; } L;
typedef struct A { char pad[44]; L *f44; L *f48; L *f52; } A;
int igObject_Destroy();

int Gap__igCollisionGrid__vfunc_24(A *arg0) {
    L *l;
    int n;
    int i;
    R *o;
    int n2;
    int j;

    l = arg0->f44;
    n = l->f8;
    for (i = 0; i < n; i++) {
        o = l->f16[i];
        if (o != 0) {
            o->f4 = o->f4 - 1;
            if (((unsigned long long) ((long long) o->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    n2 = l->f8;
    for (j = 0; j < n2; j++) {
        l->f16[j] = 0;
    }
    l->f8 = 0;

    l = arg0->f48;
    n = l->f8;
    for (i = 0; i < n; i++) {
        o = l->f16[i];
        if (o != 0) {
            o->f4 = o->f4 - 1;
            if (((unsigned long long) ((long long) o->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    n2 = l->f8;
    for (j = 0; j < n2; j++) {
        l->f16[j] = 0;
    }
    l->f8 = 0;

    l = arg0->f52;
    n = l->f8;
    for (i = 0; i < n; i++) {
        o = l->f16[i];
        if (o != 0) {
            o->f4 = o->f4 - 1;
            if (((unsigned long long) ((long long) o->f4 << 0x29) >> 0x29) == 0) {
                igObject_Destroy(o);
            }
        }
    }
    n2 = l->f8;
    for (j = 0; j < n2; j++) {
        l->f16[j] = 0;
    }
    l->f8 = 0;
    return 0;
}
