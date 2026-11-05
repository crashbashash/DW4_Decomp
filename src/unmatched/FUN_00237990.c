typedef struct E { int pad[2]; int f8; } E;
typedef struct L { int pad[2]; int f8; int pad2; E **f16; } L;
typedef struct A { int pad[2]; L *volatile f8; } A;
E *FUN_00237990(A *arg0, int arg1) {
    int i;
    int n;
    E *e;

    n = arg0->f8->f8;
    for (i = 0; i < n; i++) {
        e = arg0->f8->f16[i];
        if (arg1 == e->f8) {
            return e;
        }
    }
    return 0;
}
