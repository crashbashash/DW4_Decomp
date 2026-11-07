int igObject_IsKindOf();
int igObjectRefMetaField_Assign();
extern int DAT_00585b20[4];
struct M { char pad[8]; int f8; };
static inline void * cast0(void * o) { if (o != 0 && igObject_IsKindOf(o, DAT_00585b20[0]) != 0) { return o; } return 0; }
int FUN_0022db60(struct M *arg0, int arg1, int arg2, int arg3) {
    int var_v0;

    arg0 = cast0(arg0);
    arg2 = (int)cast0((void *)arg2);
    if ((arg0 != 0) && (arg2 != 0)) {
        igObjectRefMetaField_Assign(arg2, arg3, *(int *)(arg1 + arg0->f8));
        var_v0 = 1;
    }
    else { var_v0 = 0; }
    return var_v0;
}
