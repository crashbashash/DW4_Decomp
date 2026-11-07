struct S { char pad[12]; int f12; char pad2[16]; int f32; int f36; };
extern "C" {
int FUN_00236f80(...);
extern int DAT_00587ce8[4];
extern int DAT_00589208[4];
void FUN_00390d70(S *arg0);
}
void FUN_00390d70(S *arg0) {
    if (arg0->f32 == 0) {
        arg0->f32 = FUN_00236f80(arg0->f12, DAT_00589208[0]);
    }
    if (arg0->f36 == 0) {
        arg0->f36 = FUN_00236f80(arg0->f12, DAT_00587ce8[0]);
    }
}
