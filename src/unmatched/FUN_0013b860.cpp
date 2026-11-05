/* 0x0013b860 — calls the base initialiser, then copies the +8 field of the object returned by virtual slot 88 into the
 * 16-bit field at +8 of this. The int temporary keeps the word load (a direct short store would narrow it to lh). */
extern "C" {
void FUN_002ff130(void *);
void FUN_0013b860(void *);
}
struct R { int pad[2]; int f; };
struct A {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual R *v20();
};
void FUN_0013b860(void *p)
{
    FUN_002ff130(p);
    int t = ((A *)p)->v20()->f;
    ((short *)p)[4] = (short)t;
}
