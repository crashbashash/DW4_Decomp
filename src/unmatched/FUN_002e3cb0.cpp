struct Ref { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); union { int w; struct { unsigned cnt:23; unsigned f:9; } b; } u; };
struct S { int pad[26]; Ref *ref; };
extern "C" { int igObject_Destroy(void *); void FUN_002e3cb0(S *self); }
void FUN_002e3cb0(S *self) {
    Ref *r;
    if (self->ref != 0) {
        self->ref->v22();
        r = self->ref;
        if (r != 0) {
            r->u.w = r->u.w - 1;
            if (r->u.b.cnt == 0) igObject_Destroy(r);
        }
        self->ref = 0;
    }
}
