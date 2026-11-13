extern "C" {
int LuaStartupHook_Construct(int *, int (*)(), int);
extern int DAT_0058a180[4];
extern int DAT_0058a1a0[4];
int FUN_00371840();
int FUN_00371930();

void FUN_005216e0(void) {
    LuaStartupHook_Construct(&DAT_0058a180[0], &FUN_00371840, 0);
    LuaStartupHook_Construct(&DAT_0058a1a0[0], &FUN_00371930, 0);
}
}
