extern "C" {
void *igMetaObject_FindFieldByName(...);
int igObject_Destroy(...);
extern int DAT_004dd5c0[4];
extern int DAT_004dd5d0[4];
}
struct R { int w0; int refs; };
class M { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void *meta(); };
struct O { char pad[20]; M *m; R *b; R *a; };
extern "C" void Gap__Core__igPsx2UserUCodeExt__vfunc_29(O *arg0, M *arg1) {
    R *temp_v0;
    R *temp_a0;

    arg0->m = arg1;
    temp_v0 = (R *)igMetaObject_FindFieldByName(arg0->m->meta(), &DAT_004dd5c0[0]);
    if (temp_v0 != 0) {
        temp_v0->refs = temp_v0->refs + 1;
    }
    temp_a0 = arg0->a;
    if (temp_a0 != 0) {
        temp_a0->refs = temp_a0->refs - 1;
        if ((temp_a0->refs & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->a = temp_v0;
    temp_v0 = (R *)igMetaObject_FindFieldByName(arg0->m->meta(), &DAT_004dd5d0[0]);
    if (temp_v0 != 0) {
        temp_v0->refs = temp_v0->refs + 1;
    }
    temp_a0 = arg0->b;
    if (temp_a0 != 0) {
        temp_a0->refs = temp_a0->refs - 1;
        if ((temp_a0->refs & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    arg0->b = temp_v0;
}
