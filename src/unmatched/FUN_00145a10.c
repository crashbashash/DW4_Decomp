typedef struct S {
    char pad[8];
    unsigned char a0 : 1, a1 : 1, a2 : 1, a3 : 1, a4 : 1, a5 : 1, a6 : 1, a7 : 1;
    unsigned char b0 : 1, b1 : 1, b2 : 1, b3 : 1, b4 : 1, b5 : 1, b6 : 1, b7 : 1;
    unsigned char c;
} S;
typedef struct D {
    unsigned char d0 : 1, d1 : 1, d2 : 1, d3 : 1, d4 : 1, d5 : 1, d6 : 1, d7 : 1;
    unsigned char e : 5, g : 3;
    short pad;
} D;
typedef union U { D r; int i; } U;
int FUN_00145a10(void *arg0, S *a) {
    U u;
    u.r.d0 = a->a6;
    u.r.d1 = a->a1;
    u.r.d2 = a->b3;
    u.r.d3 = a->a4;
    u.r.d4 = a->b0;
    u.r.d5 = a->b1;
    u.r.d6 = a->b5;
    u.r.d7 = a->b2;
    u.r.e = a->c;
    return u.i;
}
