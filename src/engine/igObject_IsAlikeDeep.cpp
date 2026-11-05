struct Meta { int p0, p1, p2; int pad3; int fieldsHolder_dummy; };
struct FieldList { int p0, p1; int *items; int count; };
struct MetaObj { char pad[40]; FieldList *fields; };
class Obj;
extern "C" int igMetaField_IsAlikeDeep(...);
extern "C" int igMetaObject_GetFieldCount(...);
extern "C" int DAT_00587198[4];
class Obj {
public:
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4();
    virtual int v5(Obj *);
    virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19();
    virtual MetaObj *v20();
};
extern "C" int igObject_IsAlikeDeep(Obj *a, Obj *b) {
    int i;
    FieldList *fl;
    int n;
    if (b->v20() != a->v20()) return 0;
    fl = a->v20()->fields;
    n = fl->count;
    i = igMetaObject_GetFieldCount(DAT_00587198[0]);
    for (; i < n; i++) {
        if (igMetaField_IsAlikeDeep(fl->items[i], a, b) == 0) return 0;
    }
    return a->v5(b);
}
