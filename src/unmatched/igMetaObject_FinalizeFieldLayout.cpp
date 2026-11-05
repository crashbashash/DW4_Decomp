extern "C" {
int FUN_002d3150(...);
struct M;
}
class VF { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual int vX(); char p0[4]; int off; char p1[6]; short idx; unsigned short sz; char p2[2]; void *owner; char p3[9]; unsigned char neg; };
struct M {
    char p0[32]; int w32; int w36; char p1[16]; M *parent; char p2[12]; int w72; char p3[12]; unsigned short w88;
};
extern "C" {
VF *igMetaObject_GetFieldAt(...);
int igMetaObject_GetFieldCount(...);
extern int DAT_00586dc8[4];
void igMetaObject_FinalizeFieldLayout(M *arg0);
}
void igMetaObject_FinalizeFieldLayout(M *arg0) {
    int off;
    int minAlign;
    unsigned short sz;
    int i;
    VF *f;
    int count;
    int nneg;
    int end;
    unsigned short maxAlign;
    int maxEnd;
    bool flag;
    count = igMetaObject_GetFieldCount();
    off = 0;
    maxEnd = 0;
    minAlign = 4;
    nneg = 0;
    maxAlign = 4;
    for (i = 0; i < count; i++) {
        f = igMetaObject_GetFieldAt(arg0, i);
        sz = f->vX();
        if (maxAlign < sz) maxAlign = sz;
        if (f->neg != 0) {
            nneg++;
            off = ~(sz - 1) & (off - f->sz);
            f->off = off;
        } else {
            flag = 0;
            if (arg0->parent == 0 || igMetaObject_GetFieldCount(arg0->parent) <= i) {
                flag = 1;
            } else if (igMetaObject_GetFieldAt(arg0->parent, i) != f) {
                flag = 1;
            }
            if (flag) {
                f->idx = i - nneg;
                f->owner = arg0;
            }
            minAlign = (sz < minAlign) ? minAlign : sz;
        }
        end = f->off; end += f->sz;
        if (maxEnd < end) maxEnd = end;
    }
    arg0->w88 = maxAlign;
    if (arg0->w72 != -1) arg0->w32 = -(off & ~(minAlign - 1));
    arg0->w36 |= 4;
    FUN_002d3150(DAT_00586dc8[0], arg0);
}
