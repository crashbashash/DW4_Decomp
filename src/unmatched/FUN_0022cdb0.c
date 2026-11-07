int igObject_IsKindOf();
extern int DAT_00560f28[4];
static inline void * cast0(void * o) { if (o != 0 && igObject_IsKindOf(o, DAT_00560f28[0]) != 0) { return o; } return 0; }
int FUN_0022cdb0(void *arg0, int arg1, void *arg2, int arg3) {
    /* matching construct: variant search — decl order [2, 1, 0]; the unit compiler (combat build -O3 -Iinclude) assigns stack slots and registers in declaration order, the reverse of the 2001 default */
    void *temp_a1;
    void *temp_a0;
    int var_v0;
    arg0 = cast0(arg0);
    arg2 = cast0(arg2);
    if ((arg0 != 0) && (arg2 != 0)) {
        var_v0 = 1;
        temp_a0 = (void *)(arg1 + *(int *)((char *)(arg0) + 8));
        temp_a1 = (void *)(arg3 + *(int *)((char *)(arg2) + 8));
        *(unsigned char *)((char *)(temp_a1) + 0) = (unsigned char) *(unsigned char *)((char *)(temp_a0) + 0);
        *(unsigned char *)((char *)(temp_a1) + 1) = (unsigned char) *(unsigned char *)((char *)(temp_a0) + 1);
        *(unsigned char *)((char *)(temp_a1) + 2) = (unsigned char) *(unsigned char *)((char *)(temp_a0) + 2);
        *(unsigned char *)((char *)(temp_a1) + 3) = (unsigned char) *(unsigned char *)((char *)(temp_a0) + 3);
    }
    else { var_v0 = 0; }
    return var_v0;
}
