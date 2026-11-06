/* Rounds size up to a multiple of the field's alignment: (size + a - 1) & ~(a - 1). Reusing the
 * mask local for its complement (m = ~m) orders the temporaries so the nor lands in v0 and the sum
 * in v1. */
extern "C" {
int igMetaField_AlignSize(void *, int);
}
struct A {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual int v25();
};
int igMetaField_AlignSize(void *p, int size)
{
    int m = ((A *)p)->v25() - 1;
    int s = size + m;
    m = ~m;
    return m & s;
}
