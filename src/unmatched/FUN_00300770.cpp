struct Meta { int pad[2]; int *arr; int count; };
struct Holder { char pad[40]; Meta *meta; };
struct Obj { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void v4(int); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual Holder *v20();  };
extern "C" {
int igMetaField_ShallowCopy(int, Obj *, int);
int igMetaObject_GetFieldCount(int);
extern int DAT_00587198[];
void FUN_00300770(Obj *arg0, int arg1);
}
void FUN_00300770(Obj *arg0, int arg1) {
    Meta *m = arg0->v20()->meta;
    int n = m->count;
    int i;
    for (i = igMetaObject_GetFieldCount(DAT_00587198[0]); i < n; i++) {
        igMetaField_ShallowCopy(m->arr[i], arg0, arg1);
    }
    arg0->v4(arg1);
}
