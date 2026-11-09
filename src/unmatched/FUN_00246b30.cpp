#include "dw4/igSmartPointer.h"
class ScriptFile : public igVirtualObject { public: virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual int open(int, int *); virtual int close(); virtual int read(int, int, int); virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3(); virtual void e4(); virtual void e5(); virtual void e6(); virtual void e7(); virtual void e8(); virtual void e9(); virtual int seek(int, int); virtual int size(); };
extern "C" {
int lua_dobuffer(int, int, int, int);
int luaM_realloc(int, int, int);
ScriptFile *FUN_002c4ca0(int);
extern int DAT_004eaab0[4];
}

extern "C" int FUN_00246b30(int state, int path) {
    igSmartPointer<ScriptFile> file(FUN_002c4ca0(0), AdoptReference());
    int size;
    int buffer;
    int result;
    if (file.p->open(path, &DAT_004eaab0[0]) == 0) {
        return 2;
    }
    file.p->seek(0, 2);
    size = file.p->size();
    buffer = luaM_realloc(state, 0, size);
    if (buffer == 0) {
        file.p->close();
        return 4;
    }
    file.p->seek(0, 0);
    file.p->read(buffer, size, 1);
    file.p->close();
    result = lua_dobuffer(state, buffer, size, path);
    luaM_realloc(state, buffer, 0);
    return result;
}
