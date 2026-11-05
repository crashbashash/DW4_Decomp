int FUN_0023ec50();
int FUN_002406e0();
int lua_remove();
struct S { char pad[32]; int (*fn)(); char pad2[7]; unsigned char b0 : 5; unsigned char flag : 1; unsigned char b6 : 2; };
struct S *lua_touserdata();
void FUN_00240610(int arg0) {
    struct S *s;

    s = lua_touserdata(arg0, -1);
    lua_remove(arg0, 1);
    if (s->flag == 0) {
        FUN_002406e0(arg0);
        return;
    }
    if (*(unsigned short *)((char *)s + 42) & 0xFFF) {
        FUN_0023ec50(s, arg0);
        return;
    }
    s->fn(arg0);
}
