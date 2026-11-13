extern "C" {
int LuaStartupHook_Construct(int *, int (*)(), int);
extern int DAT_0058a180[4];
extern int DAT_0058a1a0[4];
int LuaAPIClass_Create();
int BecLuaClass_Create();

void FUN_005216e0(void) {
    LuaStartupHook_Construct(&DAT_0058a180[0], &LuaAPIClass_Create, 0);
    LuaStartupHook_Construct(&DAT_0058a1a0[0], &BecLuaClass_Create, 0);
}
}
