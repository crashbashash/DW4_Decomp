int FUN_001eef70();
struct F { unsigned char c0:1; unsigned char c1:1; unsigned char c2:6; };
struct S { char p0[32]; int a; char p1[12]; int b; char p2[12]; struct F f; };
extern struct S *DAT_00568f04[4];
void FUN_00208120(void) {
    struct S *s = DAT_00568f04[0];
    if (s->a != s->b) goto call;
    if (s->f.c1 != 0) {
call:
        FUN_001eef70(1, s);
    }
}
