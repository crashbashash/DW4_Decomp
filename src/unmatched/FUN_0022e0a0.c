/* FUN_0022e0a0 - dynamic-cast pair then a typed field copy. Parameters reused in place, one
 * padding nop in the then-arm, alternate compiler -O3. */
int igObject_IsKindOf();
extern int DAT_00586930[4];
int FUN_0022e0a0(void *arg0, int arg1, void *arg2, int arg3) {
    int var_v0;
    if ((arg0 != 0) && (igObject_IsKindOf(arg0, DAT_00586930[0]) != 0)) {
        asm { nop }
    } else {
        arg0 = (void *)(0);
        
    }
    if ((arg2 != 0) && (igObject_IsKindOf(arg2, DAT_00586930[0]) != 0)) {
        asm { nop }
    } else {
        arg2 = (void *)(0);
        
    }
    var_v0 = 0;
    if ((arg0 != 0) && (arg2 != 0)) {
        var_v0 = 1;
        *(char *)(arg3 + *(int *)((char *)(arg2) + 8)) = *(char *)(arg1 + *(int *)((char *)(arg0) + 8));
    }
    return var_v0;
}
