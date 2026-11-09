struct Meta;
struct Instance {
    int vtable;
    unsigned int refCount : 23;
    unsigned int scriptHeld : 1;
    unsigned int refFlags : 8;
};
struct BoundType { char pad0[16]; Meta *meta; char pad20[20]; int userTag; };
struct It { int bucket; int node; };
struct En { char p[12]; Meta *f12; int f16; };
extern "C" {
extern int DAT_00498668[4];
extern int DAT_00498670[4];
int FUN_00240360(It *);
int FUN_00240370(It *, int);
int FUN_00240390(It *, int);
int FUN_00240420(int);
En *FUN_00240430(It *);
int FUN_00240440(It *, int);
int FUN_002404b0(Meta *, int);
int FUN_00241210(int, int, Instance *, int, int);
Instance *igMetaObject_CreateInstanceDefault(Meta *);
int igMetaObject_FindFieldByName(Meta *, int);
int lua_tag(int, int);
int lua_type(int, int);
int lua_tostring(int, int);
void *lua_touserdata(int, int);
void lua_pushnil(int);
int lua_next(int, int);
void lua_settop(int, int);
void lua_pushusertag(int, Instance *, int);
int strcmp(int, int);
/* matching construct: 720 declaration orders */
int FUN_00240160(int L);
}
static inline int findBoundField(Meta *meta, int key) {
    It it;
    En *e;
    FUN_00240440(&it, FUN_002404b0(meta, key));
    while (FUN_00240360(&it)) {
        e = FUN_00240430(&it);
        if (e->f12 == meta && strcmp(FUN_00240420(e->f16), key) == 0) {
            int field = e->f16;
            FUN_00240390(&it, -1);
            return field;
        }
        FUN_00240370(&it, 0);
    }
    FUN_00240390(&it, -1);
    return 0;
}

int FUN_00240160(int L) {
    Meta *meta;
    BoundType *bound;
    int userTag;
    Instance *object;
    int key;
    int field;
    if (DAT_00498670[0] == lua_tag(L, 1)) {
        meta = (Meta *)lua_touserdata(L, 1);
        userTag = DAT_00498668[0];
        bound = 0;
    } else {
        bound = (BoundType *)lua_touserdata(L, -1);
        meta = bound->meta;
        userTag = bound->userTag;
    }
    object = igMetaObject_CreateInstanceDefault(meta);
    if (lua_type(L, 2) == 4) {
        lua_pushnil(L);
        while (lua_next(L, 2)) {
            key = lua_tostring(L, -2);
            if (bound) {
                field = findBoundField(meta, key);
            } else {
                field = igMetaObject_FindFieldByName(meta, key);
            }
            FUN_00241210(L, field, object, key, -1);
            lua_settop(L, -2);
        }
    }
    object->scriptHeld = 1;
    lua_pushusertag(L, object, userTag);
    return 1;
}
