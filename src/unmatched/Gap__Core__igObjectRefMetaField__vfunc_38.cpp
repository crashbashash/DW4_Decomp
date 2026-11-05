class VC_84_1 { public: virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void *vX(int); };
struct R { char pad[4]; int f4; };
struct M { char pad[8]; int f8; char pad2[41]; unsigned char f53; };
extern "C" {
int FUN_00300770(...);
int igObjectRefMetaField_Assign(...);
int igObject_Destroy(...);
}
extern "C" void Gap__Core__igObjectRefMetaField__vfunc_38(M *arg0, int arg1, int arg2) {
    int temp_a0;
    VC_84_1 *temp_a1;
    R *temp_v0;
    int off;

    off = arg0->f8;
    temp_a0 = *(int *)(arg1 + off);
    temp_a1 = *(VC_84_1 **)(arg2 + off);
    if ((temp_a0 != 0) || (temp_a1 != 0)) {
        if ((temp_a0 != 0) && (temp_a1 != 0)) {
            FUN_00300770(temp_a0, temp_a1);
            return;
        }
        if (temp_a0 == 0) {
            temp_v0 = (R *)temp_a1->vX(0);
            igObjectRefMetaField_Assign(arg0, arg1, temp_v0);
            if ((arg0->f53 == 0) && (temp_v0 != 0)) {
                temp_v0->f4 = temp_v0->f4 - 1;
                if (((unsigned long long) ((long long) temp_v0->f4 << 0x29) >> 0x29) == 0) {
                    igObject_Destroy(temp_v0);
                }
            }
        } else if (temp_a1 == 0) {
            igObjectRefMetaField_Assign(arg0, arg1, 0);
        }
    }
}
