extern "C" {
int FUN_0023f4f0(int, int, void *, void *, int, void *, int);
extern int DAT_004c8560[4];
extern int DAT_0050cfc0[4];
int LuaAPI_Dispatch();
void LuaAPI_Register(int arg0);
}

void LuaAPI_Register(int arg0) {
    FUN_0023f4f0(arg0, 0, (void *)&LuaAPI_Dispatch, &DAT_004c8560[0], 0x74, &DAT_0050cfc0[0], 0);
}
