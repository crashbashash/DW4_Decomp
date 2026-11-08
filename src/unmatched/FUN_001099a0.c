typedef struct { char p0[1448]; unsigned int a; unsigned int b; char p1[312]; unsigned int c; unsigned int d; char p2[312]; int e; } I;
void FUN_00105228(int);
void FUN_001099a0(I *p) {
    unsigned int spr = 0x70000000;
    FUN_00105228(1);
    p->a = spr;
    p->b = spr + 0x1800;
    p->c = spr + 0x1b00;
    p->d = spr + 0x3300;
    p->e = 0;
}
