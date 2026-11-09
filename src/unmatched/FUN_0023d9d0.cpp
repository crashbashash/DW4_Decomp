struct ScriptValue {
    signed char type;
    signed char indirection : 2;
    char pad2[14];
    union {
        signed char c;
        unsigned char uc;
        short s;
        unsigned short us;
        int i;
        unsigned int ui;
        long long ll;
        unsigned long long ull;
        bool b;
        float f;
        double d;
        char *str;
        void *object;
    } data;
};
extern "C" {
void lua_pushnumber(void *L, double n);
void lua_rawseti(void *L, int index, int n);
void FUN_0023cf10(ScriptValue *value, void *L, void *object, int mode);
void FUN_0023d070(ScriptValue *value, void *L, char *string);
void FUN_0023d9d0(ScriptValue *value, void *L, int table);
}
void FUN_0023d9d0(ScriptValue *value, void *L, int table) {
    if (value->indirection > 0) {
        FUN_0023cf10(value, L, value->data.object, 2);
    } else if (value->type == 10) {
        lua_pushnumber(L, value->data.i);
    } else if (value->type == 13) {
        FUN_0023d070(value, L, value->data.str);
    } else {
        switch (value->type) {
        case 1:
            lua_pushnumber(L, value->data.c);
            break;
        case 2:
            lua_pushnumber(L, value->data.uc);
            break;
        case 3:
            lua_pushnumber(L, value->data.s);
            break;
        case 4:
            lua_pushnumber(L, value->data.us);
            break;
        case 5:
            lua_pushnumber(L, value->data.i);
            break;
        case 6:
            lua_pushnumber(L, value->data.ui);
            break;
        case 7:
            lua_pushnumber(L, value->data.ll);
            break;
        case 8:
            lua_pushnumber(L, value->data.ull);
            break;
        case 9:
            lua_pushnumber(L, value->data.b);
            break;
        case 11:
            lua_pushnumber(L, value->data.f);
            break;
        case 12:
            lua_pushnumber(L, value->data.d);
            break;
        }
    }
    lua_rawseti(L, table, 1);
}
