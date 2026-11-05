class V88 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual int vX(); };
extern "C" {
struct M { char pad8[8]; int *arr; };
struct T { char pad8[8]; int *f8; int f12; };
struct K { char pad40[40]; T *f40; };
int igMetaField_IsAlikeExactly(int, void *, void *);
int igMetaObject_GetFieldCount(int);
extern int DAT_00587198[4];
int igObject_IsAlikeExactly(void *arg0, void *arg1) {
    int temp_s0;
    int i;
    T *temp_s1;
    int temp_s0_2;

    temp_s0 = ((V88 *)arg1)->vX();
    if (temp_s0 != ((V88 *)arg0)->vX()) {
        return 0;
    }
    temp_s1 = ((K *)((V88 *)arg0)->vX())->f40;
    temp_s0_2 = temp_s1->f12;
    for (i = igMetaObject_GetFieldCount(DAT_00587198[0]); i < temp_s0_2; i++) {
        if (igMetaField_IsAlikeExactly(temp_s1->f8[i], arg0, arg1) == 0) {
            return 0;
        }
    }
    return 1;
}
}
