struct M; struct A;
extern "C" { A *Memory_GetAllocatorByName(...); A *Memory_GetDefaultAllocator(...); int igObject_ConstructPooled(...); }
class A { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual int vX(int); };

struct M { char p[26]; unsigned char f26; char q[5]; int f32; int f36; char r[20]; M *(*f60)(); char s[8]; int f72; char t[20]; char *f96; };
extern "C" int igMetaObject_CreateInstanceWithPool(M *arg0, A *arg1);
int igMetaObject_CreateInstanceWithPool(M *arg0, A *arg1) {
    int temp_s1;
    int temp_s1_2;
    char *temp_a0;
    A *var_s2;
    A *var_v0;
    M *(*temp_v0)();

    var_s2 = arg1;
    if (((arg0->f36 & 4) != 0) == 0) {
        return 0;
    }
    temp_v0 = arg0->f60;
    if (temp_v0 != 0) {
        return igMetaObject_CreateInstanceWithPool(temp_v0(), var_s2);
    }
    if (arg0->f26 == 1) {
        return 0;
    }
    if (var_s2 == 0) {
        temp_a0 = arg0->f96;
        if ((temp_a0 != 0) && (*temp_a0 != 0)) {
            var_s2 = Memory_GetAllocatorByName(temp_a0);
            if (var_s2 == 0) {
                var_v0 = Memory_GetDefaultAllocator();
                goto block_10;
            }
        } else {
            var_v0 = Memory_GetDefaultAllocator();
block_10:
            var_s2 = var_v0;
        }
    }
    temp_s1_2 = arg0->f32;
    temp_s1 = var_s2->vX(temp_s1_2 + arg0->f72);
    temp_s1 = temp_s1 + temp_s1_2;
    if (temp_s1 != 0) {
        igObject_ConstructPooled(temp_s1, arg0);
    }
    return temp_s1;
}

