int igObject_IsKindOf();
extern int DAT_00586988[4];
struct M { char pad[8]; int f8; };
int FUN_0022e160(struct M *arg0, int arg1, struct M *arg2, int arg3) {
    int var_v0;

    if ((arg0 != 0) && (igObject_IsKindOf(arg0, DAT_00586988[0]) != 0)) {
        asm { nop }
    } else {
        arg0 = 0;
    }
    if ((arg2 != 0) && (igObject_IsKindOf(arg2, DAT_00586988[0]) != 0)) {
        asm { nop }
    } else {
        arg2 = 0;
    }
    var_v0 = 0;
    if ((arg0 != 0) && (arg2 != 0)) {
        var_v0 = 1;
        *(unsigned char *)(arg3 + arg2->f8) = *(unsigned char *)(arg1 + arg0->f8);
    }
    return var_v0;
}
