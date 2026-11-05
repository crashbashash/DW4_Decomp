#include "dw4/reflected.h"
int lua_type();
void *lua_touserdata();
int lua_pushstring();
int lua_rawget();
int igObject_Destroy();
extern int DAT_004ea530[4];
struct B { int w0; unsigned char b4, b5; unsigned char lo:7; unsigned char f:1; unsigned char b7; };
int FUN_00240530(int arg0) {
    igObject *temp_v0;
    struct B *temp_v0_2;

    if (lua_type(arg0, 1) == 4) {
        lua_pushstring(arg0, &DAT_004ea530[0]);
        lua_rawget(arg0, 1);
        temp_v0 = (igObject *)(lua_touserdata(arg0, -1));
        temp_v0->_refCount = temp_v0->_refCount - 1;
        if ((temp_v0->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_v0);
        }
        return 0;
    } else {
        temp_v0_2 = (struct B *)(lua_touserdata(arg0, 1));
        temp_v0_2->f = 0;
        ((igObject *)temp_v0_2)->_refCount = ((igObject *)temp_v0_2)->_refCount - 1;
        if ((((igObject *)temp_v0_2)->_refCount & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_v0_2);
        }
    }
    return 0;
}
