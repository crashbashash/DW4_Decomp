struct S { int v; };
extern "C" { extern int DAT_004fb418[4]; }
struct O { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22();
 virtual S v23(int, int, int, int, int, int, int); virtual int v24(int); };
extern "C" void Gap__Core__igSymbolTable__vfunc_27(int *out, O *o, int a, int b, int c, int d, int e, int f, int g, int *h) {
    S r;
    int i = o->v24(a);
    r.v = DAT_004fb418[0];
    *h = 0;
    if (i != -1) r = o->v23(i, b, c, d, e, f, g);
    *out = r.v;
}
