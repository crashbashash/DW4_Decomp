struct M { char pad[8]; int *f8; int f12; };
struct W { char pad[40]; M *f40; };
struct W;
class V { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual int v32(V *); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual W *v88(); };
extern "C" {
int igMetaField_IsAlikeShallow(int, V *, V *);
int igMetaObject_GetFieldCount(int);
int igObject_IsAlikeShallow(V *arg0, V *arg1);
}
extern int DAT_00587198[4];
int igObject_IsAlikeShallow(V *arg0, V *arg1) {
    W *s0;
    int i;
    M *s1;
    int cnt;
    s0 = arg1->v88();
    if (s0 != arg0->v88()) {
        return 0;
    }
    s1 = arg0->v88()->f40;
    cnt = s1->f12;
    for (i = igMetaObject_GetFieldCount(DAT_00587198[0]); i < cnt; i++) {
        if (igMetaField_IsAlikeShallow(s1->f8[i], arg0, arg1) == 0) {
            return 0;
        }
    }
    return arg0->v32(arg1);
}
