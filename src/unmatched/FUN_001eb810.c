typedef struct S { int a, b, c, d, e, g; short f18; char f1a; unsigned char val:7; unsigned char fl:1; char pad[16]; } S;
extern S DAT_00490b40;
void FUN_001eb6a0(int, int *);
void FUN_001ee600(void);
void FUN_001eef70(int);
typedef struct T { unsigned short lo:1; unsigned short a:15; unsigned short b:15; unsigned short hi:1; unsigned short pad[14]; } T;
extern T DAT_00568db4;
extern int DAT_00568dc8[16];
extern int DAT_00568e50[16];
extern char *DAT_00568f04[16];
extern int DAT_00569228[16];

void FUN_001eb810(void) {
    int v[5];
    int *p = *(int **)(DAT_00568f04[0] + 48);
    FUN_001eb6a0(0, &v[0]);
    FUN_001eb6a0(1, &v[1]);
    FUN_001eb6a0(2, &v[2]);
    FUN_001eb6a0(3, &v[3]);
    FUN_001eb6a0(4, &v[4]);
    if (!(DAT_00569228[0] & 0x21)) v[1] = 0;
    if (!(DAT_00569228[0] & 0x24)) v[2] = 0;
    if (!(DAT_00569228[0] & 0x28)) v[3] = 0;
    if (!(DAT_00569228[0] & 0xE0)) v[4] = 0;
    p[0] = DAT_00490b40.a;
    p[1] = DAT_00490b40.b;
    p[2] = DAT_00490b40.c;
    p[3] = DAT_00490b40.d;
    DAT_00490b40.f18 = 30;
    DAT_00490b40.f1a = 1;
    DAT_00490b40.val = 0x6C;
    p[4] = DAT_00490b40.e;
    p[5] = DAT_00568dc8[0];
    p[6] = DAT_00568dc8[0];
    p[7] = *(int *)&DAT_00490b40.f18;
    ((float *)p)[8] = (float)v[0];
    if (DAT_00568db4.b + DAT_00568db4.a != 0)
        ((float *)p)[9] = (float)v[1];
    else
        ((float *)p)[9] = (float)v[4];
    ((float *)p)[10] = (float)v[2];
    ((float *)p)[11] = (float)v[3];
    *(int **)(DAT_00568f04[0] + 48) = p + 12;
    if (*(unsigned *)(DAT_00568f04[0] + 48) >= *(unsigned *)(DAT_00568f04[0] + 40)) {
        if (DAT_00568e50[0] != 0) {
            FUN_001ee600();
            return;
        }
        FUN_001eef70(1);
    }
}
