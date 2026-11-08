int igObject_IsKindOf();
extern int DAT_00585948[4];
static inline int *castToType(int *object) {
    if (object != 0 && igObject_IsKindOf(object, DAT_00585948[0]) != 0) {
        return object;
    }
    return 0;
}
int FUN_0022d9e0(int *arg0, int arg1, int *arg2, int arg3) {
    int *source = castToType(arg0);
    int *destination = castToType(arg2);
    if (source != 0 && destination != 0) {
        *(short *)(arg3 + destination[2]) = *(short *)(arg1 + source[2]);
        return 1;
    }
    return 0;
}
