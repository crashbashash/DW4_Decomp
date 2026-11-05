typedef struct E {
    int f0;
    int f4;
    unsigned char a0 : 2;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
    unsigned char a4 : 3;
    unsigned char b7 : 1;
    unsigned char c0 : 1;
    unsigned char c1 : 3;
    unsigned char c4 : 1;
    unsigned char c5 : 3;
    char pad[22];
} E;
typedef struct T { char pad[16]; E *tab; } T;
typedef struct C { char pad[12]; int h; } C;
extern T *D_0055f5d0[4];
extern int DAT_004fb410[4];
extern int DAT_004fb418[4];
int *FUN_00300db0(void *, int, int);
void FUN_00300f50(void *, int *);
void FUN_0032d6d0(int *, int, int, int *, int, int *, int, int);
void FUN_0032d850(int *, int, int, int, int, int);
void FUN_0010b7d8(int, int);

void FUN_00144030(int *arg0, C *arg1, int arg2, int arg3, int arg4, int arg5, unsigned char arg6, int arg7, unsigned char arg8) {
    unsigned char k;
    int v;
    int spAC;
    int *p;
    unsigned char s3;
    int *q;
    int spA8;
    E *e;
    int spA4;

    s3 = arg6;
    if (arg3 & 0xF) {
        *arg0 = DAT_004fb418[0];
        return;
    }
    e = (E *)((char *)D_0055f5d0[0]->tab + arg2 * 36);
    if (e->c0) {
        *arg0 = DAT_004fb418[0];
        return;
    }
    p = FUN_00300db0(arg1, 16, 16);
    q = FUN_00300db0(arg1, 16, 16);
    if (e->b2) {
        k = 4;
    } else if (e->b3) {
        k = 2;
    } else {
        k = 24;
    }
    if (e->b7) {
        k |= 0x10;
    }
    p[0] = (e->f4 << 8) | (k & 0xFF);
    p[1] = arg5;
    p[2] = arg4;
    p[3] = arg3 & 0xDFFFFFFF;
    FUN_0010b7d8(arg3, arg3 + arg5);
    if (s3) {
        FUN_0032d6d0(&spAC, arg1->h, arg2 | 0x70000, p, 16, 0, 0, 0);
        if (arg8 != 0) {
            *q = 2;
        } else {
            *q = 1;
        }
    } else {
        FUN_0032d6d0(&spA8, arg1->h, arg2 | 0x70000, p, 16, q, 16, 0);
    }
    FUN_00300f50(arg1, p);
    e->c4 = 1;
    v = *q;
    if (v != -1) {
        if (v == 2) {
            e->b2 = 1;
            if (e->f0 != 0) {
                FUN_0032d850(&spA4, arg1->h, arg2 | 0x240000, e->f0, 0, 0);
            }
        } else {
            e->b3 = 1;
        }
        FUN_00300f50(arg1, q);
        *arg0 = DAT_004fb410[0];
    } else {
        FUN_00300f50(arg1, q);
        *arg0 = DAT_004fb418[0];
    }
}
