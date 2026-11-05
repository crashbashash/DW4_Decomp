int igObject_IsKindOf();
int igObjectRefMetaField_Assign();
extern int DAT_00585b20[4];
struct M { char pad[8]; int f8; };
int FUN_0022db60(struct M *arg0, int arg1, int arg2, int arg3) {
    int var_v0;

    if ((arg0 != 0) && (igObject_IsKindOf(arg0, DAT_00585b20[0]) != 0)) {
        asm { nop }
    } else {
        arg0 = 0;
    }
    if ((arg2 != 0) && (igObject_IsKindOf(arg2, DAT_00585b20[0]) != 0)) {
        asm { nop }
    } else {
        arg2 = 0;
    }
    var_v0 = 0;
    if ((arg0 != 0) && (arg2 != 0)) {
        igObjectRefMetaField_Assign(arg2, arg3, *(int *)(arg1 + arg0->f8));
        var_v0 = 1;
    }
    return var_v0;
}
