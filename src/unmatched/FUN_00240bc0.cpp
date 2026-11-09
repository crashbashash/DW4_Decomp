struct Meta { char p[28]; int f28; };
struct Ob { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual Meta *v20(); };
struct It { int bucket; int node; };
struct En { char p[12]; Meta *f12; int f16; };
extern int DAT_00498668[4];
extern int DAT_004ea5f0[4];
extern "C" {
int FUN_00240360(It *);
int FUN_00240370(It *, int);
int FUN_00240390(It *, int);
int FUN_00240420(int);
En *FUN_00240430(It *);
int FUN_00240440(It *, int);
int FUN_002404b0(Meta *, int);
int FUN_002407c0(int, void *, int);
int FUN_00240900(int, void *);
int FUN_00240fd0(int);
unsigned char FUN_0023dbc0(int, int, Ob *);
int FUN_00244a50(int, int);
int FUN_002467a0(int *, int);
int lua_type(int, int);
int lua_tag(int, int);
int lua_tostring(int, int);
void *lua_touserdata(int, int);
int igMetaObject_FindFieldByName(Meta *, int);
int strcmp(int, int);
/* matching construct: 5040 declaration orders */
int FUN_00240bc0(int L);
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
int FUN_00240bc0(int L) {
    int tag;
    int type;
    Ob *object;
    Meta *meta;
    void *bound;
    int field;
    int key;
    if (FUN_00244a50(L, 1) != 0) {
        return FUN_00240fd0(L);
    }
    tag = lua_tag(L, 1);
    type = lua_type(L, 2);
    object = (Ob *)lua_touserdata(L, 1);
    meta = object->v20();
    if (tag != DAT_00498668[0]) {
        bound = lua_touserdata(L, -1);
        if (type == 3) {
            key = lua_tostring(L, 2);
            field = findBoundField(meta, key);
            return field ? FUN_0023dbc0(L, field, object) : FUN_002407c0(L, bound, key);
        } else {
            return FUN_00240900(L, bound);
        }
    } else if (type == 3) {
        field = igMetaObject_FindFieldByName(meta, lua_tostring(L, 2));
        if (field) {
            return FUN_0023dbc0(L, field, object);
        }
        return 0;
    }
    FUN_002467a0(DAT_004ea5f0, meta->f28);
    return 0;
}
