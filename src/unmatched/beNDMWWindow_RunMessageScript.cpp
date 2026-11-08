extern "C" {
int FUN_00236f80(int, int);
int igObject_IsKindOf(int, int);
int beLua__RunNamedChunk(int, int, int);
extern int DAT_00589208[4];
extern int DAT_0058a220[4];
static inline int castToLuaManager(int object) {
    if (object != 0 && igObject_IsKindOf(object, DAT_00589208[0]) != 0) {
        return object;
    }
    return 0;
}
void beNDMWWindow_RunMessageScript(int *arg0, int arg1, int arg2) {
    int manager = castToLuaManager(FUN_00236f80(arg0[2], DAT_00589208[0]));
    DAT_0058a220[0] = arg2;
    beLua__RunNamedChunk(manager, arg1, 0);
}
}
