typedef struct S { char p0[32]; int f32; char p36[6]; unsigned short lo : 12; unsigned short a : 1; unsigned short flag : 1; unsigned short b : 2; } S;
void FUN_002406a0(void);
int lua_pushusertag();
int lua_rawset();
int lua_pushcclosure();
int FUN_002406e0();

void FUN_0023eed0(int arg0, S *arg1) {
    lua_pushusertag(arg0, arg1, 0);
    if (arg1->flag == 0) {
        lua_pushcclosure(arg0, &FUN_002406e0, 1);
    } else if (!arg1->lo) {
        lua_pushcclosure(arg0, arg1->f32, 1);
    } else {
        lua_pushcclosure(arg0, (int *)FUN_002406a0, 1);
    }
    lua_rawset(arg0, -3);
}
