extern "C" {
int LuaStartupHook_Construct(int *, int (*)(), int);
extern int DAT_0058a180[4];
extern int DAT_0058a1a0[4];
int beLuaWrapper_Create();
int BecLuaWrapper_Create();

void FUN_005216e0(void) {
    LuaStartupHook_Construct(&DAT_0058a180[0], &beLuaWrapper_Create, 0);
    LuaStartupHook_Construct(&DAT_0058a1a0[0], &BecLuaWrapper_Create, 0);
}
}
