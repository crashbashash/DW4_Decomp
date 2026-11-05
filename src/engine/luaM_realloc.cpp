extern "C" {
int lua_error(...);
int luaD_breakrun(...);
int Memory_AllocateDefaultBuffer(...);
int Memory_FreeBufferAlias_002ed4b0(...);
int thunk_FUN_002ed330(...);
extern int DAT_004eba10[4];
int luaM_realloc(int *arg0, int arg1, unsigned int arg2);
}
class VM { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int v216(unsigned); virtual void d53(); virtual void d54(); virtual void d55(); virtual int v232(); virtual void d57(); virtual void d58(); virtual void d59(); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual int v264(); };
int luaM_realloc(int *arg0, int arg1, unsigned int arg2) {
    int v;
    VM *t;
    if (arg2 >= 0xFFFFFFFDU) {
        lua_error(arg0, &DAT_004eba10[0]);
        return 0;
    }
    if (arg0 != 0) {
        t = (VM *)arg0[28];
        if (t != 0 && arg1 != (int)arg0) {
            if (arg2 == 0) {
                t->v264();
                return 0;
            }
            if (arg1 != 0) {
                arg1 = t->v232();
            } else {
                arg1 = t->v216(arg2);
            }
            if (arg1 == 0) {
                luaD_breakrun(arg0, 4);
            }
            return arg1;
        }
    }
    if (arg2 == 0) {
        Memory_FreeBufferAlias_002ed4b0(arg1);
        return 0;
    }
    if (arg1 != 0) {
        return thunk_FUN_002ed330(arg1, arg2);
    }
    return Memory_AllocateDefaultBuffer(arg2);
}
