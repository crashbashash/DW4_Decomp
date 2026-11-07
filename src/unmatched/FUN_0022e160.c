int igObject_IsKindOf();
extern int DAT_00586988[4];
struct M { char pad[8]; int f8; };
static inline void * cast0(void * o) { if (o != 0 && igObject_IsKindOf(o, DAT_00586988[0]) != 0) { return o; } return 0; }
int FUN_0022e160(struct M *arg0, int arg1, struct M *arg2, int arg3) {
    int var_v0;

    arg0 = cast0(arg0);
    arg2 = cast0(arg2);
    if ((arg0 != 0) && (arg2 != 0)) {
        var_v0 = 1;
        *(unsigned char *)(arg3 + arg2->f8) = *(unsigned char *)(arg1 + arg0->f8);
    }
    else { var_v0 = 0; }
    return var_v0;
}
