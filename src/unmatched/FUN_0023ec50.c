struct E { char p0; unsigned char b7 : 1; unsigned char b6 : 1; unsigned char b5 : 1; unsigned char b4 : 1; unsigned char b3 : 1; unsigned char b2 : 1; unsigned char b1 : 1; unsigned char b0 : 1; char pad[22]; };
struct A { char pad[32]; int (*fn)(); char pad2[6]; unsigned short cnt : 12; unsigned short f12 : 1; unsigned short f13 : 1; unsigned short f14 : 1; unsigned short f15 : 1; };
struct F { unsigned char b7 : 1; unsigned char b6 : 1; unsigned char b5 : 1; unsigned char b4 : 1; unsigned char b3 : 1; unsigned char b2 : 1; unsigned char b1 : 1; unsigned char b0 : 1; };
int FUN_0023d5f0();
int FUN_0023d9d0();
int *FUN_00244a50();
int lua_remove();
int lua_insert();
int lua_tag();
int lua_pushusertag();

int FUN_0023ec50(struct A *arg0, int arg1) {
    int temp_s2;
    struct E sp80[64];
    struct E *base;
    int temp_s0;
    int var_s4;
    int *temp_v0;
    int temp_s5;
    int *src;
    int var_s5;
    temp_s2 = arg0->cnt;
    if (arg0->f15 != 0) {
        temp_v0 = FUN_00244a50(arg1, 1);
        if (temp_v0 != 0) {
            lua_pushusertag(arg1, temp_v0, lua_tag(arg1, 1));
            lua_insert(arg1, 1);
            lua_remove(arg1, 2);
        }
    }
    if (temp_s2 == 0) {
        return arg0->fn(arg1);
    }
    base = sp80;
    src = (int *)((char *)arg0 + 0x2C);
    var_s5 = 0;
    temp_s0 = arg0->f12 ? 2 : 1;
    while (var_s5 < temp_s2) {
        struct E *a0 = (struct E *)((char *)base + var_s5 * 0x18);
        if (a0 != 0) {
            FUN_0023d5f0(a0, src + var_s5 * 3, arg1, temp_s0 + var_s5);
        }
        var_s5 += 1;
    }
    lua_pushusertag(arg1, base, 0);
    lua_insert(arg1, -2);
    temp_s5 = arg0->fn(arg1);
    if (arg0->f14 != 0) {
        var_s4 = 0;
        while (var_s4 < temp_s2) {
            struct E *a0 = (struct E *)((char *)base + var_s4 * 0x18);
            if (a0->b0 != 0) {
                FUN_0023d9d0(a0, arg1, temp_s0 + var_s4);
            }
            var_s4 += 1;
        }
    }
    return temp_s5;
}
