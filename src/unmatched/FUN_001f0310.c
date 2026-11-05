int FUN_001efec0();
int FUN_001f00e0();
extern int DAT_00568f60[];
extern char DAT_005690b8[];
extern char GPR_00554bbc;
struct S { char pad[64]; unsigned char f64; };
void FUN_001f0310(int arg0) {
    struct S *temp_a1;
    temp_a1 = (struct S *)DAT_00568f60[arg0];
    if (DAT_005690b8[arg0] != 0 && (temp_a1->f64 & 1) && FUN_001efec0(arg0) != 0 && GPR_00554bbc == 0) {
        FUN_001f00e0(arg0);
    }
}
