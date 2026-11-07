typedef struct S { char pad[312]; unsigned char f; } S;
int FUN_001e74b0();
int FUN_001e7500();
extern int DAT_005609fc[4];
void Gap__Gfx__igPsx2VisualContext__vfunc_145(S *arg0, int arg1) {
    if (arg0->f == (arg1 & 0xFF)) {
        DAT_005609fc[0] += 1;
    }
    arg0->f = arg1;
    if (arg1 != 0) {
        FUN_001e74b0(0xB);
    } else {
        FUN_001e7500(0xB);
    }
}
