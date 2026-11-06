extern "C" {
int FUN_00236f80(int, int);
int igObject_IsKindOf(int, int);
int beLua__RunNamedChunk(int, int, int);
extern int DAT_00589208[4];
extern int DAT_0058a220[4];
void beNDMWWindow_RunMessageScript(int *arg0, int arg1, int arg2) {
    int var_s0;
    var_s0 = FUN_00236f80(arg0[2], DAT_00589208[0]);
    if (var_s0 != 0 && igObject_IsKindOf(var_s0, DAT_00589208[0]) != 0) { asm { nop } } else { var_s0 = 0; asm { nop } }
    DAT_0058a220[0] = arg2;
    beLua__RunNamedChunk(var_s0, arg1, 0);
}
}
