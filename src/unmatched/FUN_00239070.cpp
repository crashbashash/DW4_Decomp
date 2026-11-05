extern "C" {
int igMatrix44f_SetIdentity(...);
int Memory_FreeBuffer(...);
int igMetaField_AllocateArray(...);
int igObject_Destroy(...);
int igObject_GetAllocator(...);
extern int DAT_00562498[4];
extern int DAT_005624a0[4];
}
struct R { int w0; int refs; int w8; class M *m12; };
class M { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual int v96(); virtual int v100(); };
extern "C" void FUN_00239070(int *a, R *arg1) {
    int sp6C;
    int sp68;
    int temp_s1;
    int temp_s0;
    int var_s2;
    int var_s1;
    int var_s4;
    int var_s3;
    R *temp_a0;

    if (arg1 != 0) {
        arg1->refs = arg1->refs + 1;
    }
    temp_a0 = (R *)a[8];
    if (temp_a0 != 0) {
        temp_a0->refs = temp_a0->refs - 1;
        if ((temp_a0->refs & 0x7FFFFF) == 0) {
            igObject_Destroy(temp_a0);
        }
    }
    a[8] = (int)arg1;
    temp_s1 = ((R *)a[8])->m12->v96();
    temp_s0 = ((R *)a[8])->m12->v100();
    if (a[9] != 0) {
        Memory_FreeBuffer(a[9]);
        a[9] = 0;
    }
    if (a[10] != 0) {
        Memory_FreeBuffer(a[10]);
        a[10] = 0;
    }
    igMetaField_AllocateArray(&sp6C, DAT_00562498[0], a, temp_s1, igObject_GetAllocator(a));
    igMetaField_AllocateArray(&sp68, DAT_005624a0[0], a, temp_s0, igObject_GetAllocator(a));
    var_s3 = a[9];
    var_s4 = 0;
    while (var_s4 < temp_s1) {
        igMatrix44f_SetIdentity(var_s3);
        var_s3 += 0x40;
        var_s4 += 1;
    }
    var_s2 = a[10];
    var_s1 = 0;
    while (var_s1 < temp_s0) {
        igMatrix44f_SetIdentity(var_s2);
        var_s2 += 0x40;
        var_s1 += 1;
    }
}
