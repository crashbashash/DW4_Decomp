typedef struct O {
    int f0; int f4; int p8[3]; int f20; int f24; int f28; int f32; int f36; int f40; int f44; int f48; int f52; int f56; int f60; int f64;
    int p68; int f72; int f76; int f80; int f84; int f88; int f92; int f96; int f100; int f104; int f108; int f112;
} O;
int luaD_runprotected(O *, int (*)(), int *, int, int);
O *luaM_realloc(int, int, int);
int lua_close(O *);
int f_luaopen();
O *lua_open(int arg0, int arg1) {
    int sp3C = arg0;
    O *o = luaM_realloc(0, 0, 0x74);
    if (o == 0) {
        return 0;
    }
    o->f4 = 0;
    o->f56 = 0;
    o->f44 = 0;
    o->f60 = 0;
    o->f48 = 0;
    o->f52 = 0;
    o->f64 = 0;
    o->f24 = 0;
    o->f28 = 0;
    o->f32 = 0;
    o->f36 = 0;
    o->f40 = 0;
    o->f72 = 0;
    o->f76 = -1;
    o->f80 = 0;
    o->f84 = 0;
    o->f88 = -1;
    o->f96 = 0x74;
    o->f92 = 0x7FFFFFFD;
    o->f100 = 0;
    o->f104 = 0;
    o->f108 = 1;
    o->f20 = 0;
    o->f112 = arg1;
    if (luaD_runprotected(o, f_luaopen, &sp3C, 0x74, -1) != 0) {
        lua_close(o);
        return 0;
    }
    o->f92 = o->f96 * 2;
    return o;
}
