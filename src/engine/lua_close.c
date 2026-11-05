/* 0x00253170 - lua_close. Teardown releasing each owned block and its byte count; alternate compiler. Verified byte-identical by tools/verify.py. */
int luaC_collect();
int luaM_realloc();
int luaS_freeall();
struct A { char p[4]; int f4; int f8; char q[16]; int f28x; };
void lua_close(int *arg0) {
    int temp_v1_2;
    int var_v0;
    int temp_v1;

    luaC_collect(arg0, 1);
    luaS_freeall(arg0);
    temp_v1 = arg0[1];
    if (temp_v1 != 0) {
        temp_v1_2 = arg0[2] - temp_v1;
        var_v0 = temp_v1_2 / 16;
        arg0[24] = arg0[24] - ((var_v0 + 1) * 0x10);
    }
    luaM_realloc(arg0, arg0[1], 0);
    arg0[24] = arg0[24] - ((arg0[19] + 1) << 6);
    luaM_realloc(arg0, arg0[18], 0);
    arg0[24] = arg0[24] - (arg0[21] * 0x18);
    luaM_realloc(arg0, arg0[20], 0);
    arg0[24] = arg0[24] - arg0[7];
    luaM_realloc(arg0, arg0[6], 0);
    luaM_realloc(arg0, (int)arg0, 0);
}
