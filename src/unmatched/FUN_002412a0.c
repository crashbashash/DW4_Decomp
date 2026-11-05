struct T { char pad[40]; int f40; int f44; };
struct S { char pad[28]; struct T *f28; void (*f32)(int); char pad2[6]; unsigned short a : 12; unsigned short b : 1; unsigned short c : 1; };
int FUN_0023ec50();
int FUN_002406e0();
int lua_settop();
int lua_remove();
int lua_insert();
int lua_tag();
struct S *lua_touserdata();
int lua_pushusertag();
void FUN_002412a0(int arg0) {
    int temp_v0;
    struct T *temp_a0;
    struct S *temp_s0;

    temp_s0 = lua_touserdata(arg0, -1);
    temp_v0 = lua_tag(arg0, 1);
    temp_a0 = temp_s0->f28;
    if ((temp_v0 == temp_a0->f40) || (temp_v0 == temp_a0->f44)) {
        lua_remove(arg0, 3);
    } else {
        lua_settop(arg0, -3);
        lua_insert(arg0, 1);
        lua_pushusertag(arg0, temp_s0, 0);
    }
    if (temp_s0->c == 0) {
        FUN_002406e0(arg0);
        return;
    }
    if (temp_s0->a != 0) {
        FUN_0023ec50(temp_s0, arg0);
        return;
    }
    temp_s0->f32(arg0);
}
