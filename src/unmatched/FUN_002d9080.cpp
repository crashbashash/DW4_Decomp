struct Item { int pad[6]; int f24; };
struct Obj { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();  virtual void vcall(int); int pad[7]; int key; int idx; };
struct Cont { int pad[2]; int count; };
extern "C" Item *FUN_002d8f10(Cont *, int);
extern "C" Item *FUN_002d7e90(Cont *, int);
extern "C" int FUN_002d9080(Cont *c, Obj *o) {
if (o->key != 0) { Item *it = FUN_002d8f10(c, o->key); if (it) { o->vcall(it->f24); return 1; } } else { int i = o->idx; int n = c->count; if (i >= 0 && i < n) { Item *it = FUN_002d7e90(c, i); o->vcall(it->f24); return 1; } } return 0;
}
