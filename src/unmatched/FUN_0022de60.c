int igObject_IsKindOf();
extern int DAT_00586378[4];
static inline void * cast0(void * o) { if (o != 0 && igObject_IsKindOf(o, DAT_00586378[0]) != 0) { return o; } return 0; }
int FUN_0022de60(void *arg0, char *arg1, void *arg2, char *arg3) {
    int var_v0;
    arg0 = cast0(arg0);
    arg2 = cast0(arg2);
    if ((arg0 != 0) && (arg2 != 0)) {
        var_v0 = 1;
        *(float *)(arg3 + *(int *)((char *)(arg2) + 8)) = *(float *)(arg1 + *(int *)((char *)(arg0) + 8));
    }
    else { var_v0 = 0; }
    return var_v0;
}
