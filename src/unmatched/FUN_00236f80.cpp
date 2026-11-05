struct Obj { virtual int a0(); virtual int a1(); virtual int a2(); virtual int a3(); virtual int a4(); virtual int a5(); virtual int a6(); virtual int a7(); virtual int a8(); virtual int a9(); virtual int a10(); virtual int a11(); virtual int a12(); virtual int a13(); virtual int a14(); virtual int a15(); virtual int a16(); virtual int a17(); virtual int a18(); virtual int a19(); virtual int v20(); };
struct List { int pad[2]; unsigned int count; int pad2; Obj **arr; };
struct Mid { int pad[2]; List *list; };
struct Self { int pad[2]; Mid *mid; };
extern "C" { Obj *FUN_00236f80(Self *arg0, int arg1); }
Obj *FUN_00236f80(Self *arg0, int arg1) {
    unsigned int i;
    for (i = 0; i < arg0->mid->list->count; i++) {
        Obj *o = arg0->mid->list->arr[i];
        int r = o->v20(); if (r == arg1) return o;
    }
    return 0;
}
